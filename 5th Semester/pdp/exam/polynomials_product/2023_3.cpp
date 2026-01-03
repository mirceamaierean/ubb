/*
    By doing [chunkSize = (p.size() + q.size() - 1) / nrProc] we set a size for the chunk on the lower bound, which in the case when [p.size() + q.size() - 1] is not divizible with [nrProc] will miss coefficients. For example, if [p.size() = 4] and [q.size() = 3] and [nrProc = 4], then [chunkSize = 1], meaning that [process 0 will compute the coefficient 0], [process 1 will compute  the coefficient 1], [process 2 will compute the coefficient 2], [process 3 will compute the coefficient 3], leaving the rest of the coefficients (4, 5, 6) equal to 0 and untouched by any process. To fix the issue, we can choose a [chunkSize] on the upper bound, which might overflow the original [p.size() + q.size() - 1] size. But this won't be a problem as long as we are careful to set the according size to [r] as well in the parent process 0 and to trim it afterwards to remove the added zeros. We can do so by doing [chunkSize = (p.size() + q.size() - 1 + nrProc - 1) / nrProc]. For example, if [p.size() = 3] and [q.size() = 4], and we have 4 processes, then [r.size() = 6], but each process will get a chunk of size [chunkSize = 2], meaning that: [process 0 will compute the coefficients (0, 1)], [process 1 will compute the coefficients (2, 3)], [process 2 will compute the coefficients (4, 5)], [process 3 will compute the coefficients (6, 7)], resulting in 8 integers gathered by the parent process 0. => (E)
    
    A: False - we allocate more memory than it is actually gathered.
    B: False - since we use MPI_Bcast, every child process will receive and send something back to the parent process 0.
    C: False - similar to B.
    D: False - even worse, a coefficient is computed at most once, meaning it is computed once or maybe never.
    F: False - if by computed incorrectly we mean they are not computed, thus being left equal to 0, then it's True, otherwise, the coefficients that are actually computed, are computed in a correct manner.
*/

void product(int nrProc, std::vector<int> const &p, std::vector<int> const &q, std::vector<int> &r)
{
    int sizes[2];
    sizes[0] = p.size();
    sizes[1] = q.size();
    MPI_Bcast(sizes, 2, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(const_cast<int *>(p.data()), p.size(), MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(const_cast<int *>(q.data()), q.size(), MPI_INT, 0, MPI_COMM_WORLD);
    std::vector<int> partRes;
    partProd(0, nrProc, p, q, partRes);
    r.resize((p.size() + q.size() - 1 + nrProc - 1) / nrProc * nrProc); // r.resize(p.size() + q.size() - 1);
    MPI_Gather(partRes.data(), partRes.size(), MPI_INT, r.data(), partRes.size(), MPI_INT, 0, MPI_COMM_WORLD);
    while (r.back() == 0 && r.size() > 1)
        r.pop_back(); // this was fully added, not corrected
}

void worker(int myId, int nrProc)
{
    int sizes[2];
    MPI_Bcast(sizes, 2, MPI_INT, 0, MPI_COMM_WORLD);
    std::vector<int> p(sizes[0]);
    std::vector<int> q(sizes[1]);
    MPI_Bcast(p.data(), p.size(), MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(q.data(), q.size(), MPI_INT, 0, MPI_COMM_WORLD);
    std::vector<int> r;
    partProd(myId, nrProc, p, q, r);
    // int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
    MPI_Gather(r.data(), r.size(), MPI_INT, nullptr, 0, MPI_INT, 0, MPI_COMM_WORLD);
}

void partProd(int myId, int nrProc, std::vector<int> const &p, std::vector<int> const &q, std::vector<int> &r)
{
    int chunkSize = (p.size() + q.size() - 1 + nrProc - 1) / nrProc; // int chunkSize = (p.size() + q.size() - 1) / nrProc;
    r.resize(chunkSize, 0);
    size_t baseIdx = chunkSize * myId;
    for (int i = 0; i < chunkSize; ++i)
    {
        for (int j = 0; j <= i + baseIdx; ++j)
        {
            if (j < p.size() && i + baseIdx - j < q.size())
            {
                r[i] += p[j] * q[i + baseIdx - j];
            }
        }
    }
}