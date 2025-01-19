#include <iostream>
#include <vector>
#include <cmath>
#include <cuda_runtime.h>
#include <cuComplex.h>
#include <chrono>

// Define M_PI if not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define CHECK_CUDA for error handling
#define CHECK_CUDA(stat)                                               \
    if ((stat) != cudaSuccess)                                         \
    {                                                                  \
        fprintf(stderr, "CUDA error: %s\n", cudaGetErrorString(stat)); \
        exit(EXIT_FAILURE);                                            \
    }

// Define reverse_bits_gpu for bit-reversal
__device__ uint32_t reverse_bits_gpu(uint32_t x)
{
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
    return (x >> 16) | (x << 16);
}

using namespace std;
using namespace std::chrono;

const double PI = acos(-1);

// FFT Kernel with inverse flag
__global__ void fft_kernel(const cuFloatComplex *x, cuFloatComplex *Y, uint32_t N, int logN, bool inverse)
{
    uint32_t i = threadIdx.x + blockIdx.x * blockDim.x;

    if (i >= N)
        return;

    // Bit-reversal permutation
    uint32_t rev = reverse_bits_gpu(i);
    rev = rev >> (32 - logN);
    Y[i] = x[rev];

    __syncthreads();

    // Cooley-Tukey FFT
    for (int s = 1; s <= logN; s++)
    {
        int mh = 1 << (s - 1); // Half-size
        int m = 1 << s;        // Size
        int k = (i / mh) * m;  // Block start
        int j = i % mh;        // Position within block

        if (j < mh)
        {
            // Compute the twiddle factor
            float angle = (inverse ? +1.0f : -1.0f) * (float)M_PI * j / mh;
            float tr, ti;
            sincosf(angle, &ti, &tr);
            cuFloatComplex twiddle = make_cuFloatComplex(tr, ti);

            // Butterfly operations
            cuFloatComplex a = Y[k + j];
            cuFloatComplex b = cuCmulf(twiddle, Y[k + j + mh]);

            Y[k + j] = cuCaddf(a, b);
            Y[k + j + mh] = cuCsubf(a, b);
        }

        __syncthreads();
    }
}

// FFT GPU Function
int fft_gpu(const cuFloatComplex *x, cuFloatComplex *Y, uint32_t N, bool inverse)
{
    if (N & (N - 1))
    {
        fprintf(stderr, "N=%u must be a power of 2.\n", N);
        return -1;
    }

    int logN = (int)log2f((float)N);
    cudaError_t st;

    cuFloatComplex *x_dev;
    cuFloatComplex *Y_dev;

    // Allocate device memory
    st = cudaMalloc((void **)&Y_dev, sizeof(*Y) * N);
    CHECK_CUDA(st);

    st = cudaMalloc((void **)&x_dev, sizeof(*x) * N);
    CHECK_CUDA(st);

    // Copy input data to device
    st = cudaMemcpy(x_dev, x, sizeof(*x) * N, cudaMemcpyHostToDevice);
    CHECK_CUDA(st);

    // Define CUDA grid and block dimensions
    int block_size = 256;
    dim3 block(block_size, 1);
    dim3 grid((N + block_size - 1) / block_size, 1);

    // Launch FFT kernel
    fft_kernel<<<grid, block>>>(x_dev, Y_dev, N, logN, inverse);
    st = cudaGetLastError();
    CHECK_CUDA(st);

    // Copy result back to host
    st = cudaMemcpy(Y, Y_dev, sizeof(*x) * N, cudaMemcpyDeviceToHost);
    CHECK_CUDA(st);

    // Free device memory
    st = cudaFree(x_dev);
    CHECK_CUDA(st);
    st = cudaFree(Y_dev);
    CHECK_CUDA(st);

    // Normalize if inverse FFT
    if (inverse)
    {
        for (uint32_t i = 0; i < N; i++)
        {
            Y[i].x /= N;
            Y[i].y /= N;
        }
    }

    return 0;
}

// Bit-Reversal Function for Host
uint32_t reverse_bits(uint32_t x)
{
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
    return (x >> 16) | (x << 16);
}

// Function to Clean Coefficients by Removing Small Artifacts
vector<long long> clean_coefficients(const vector<cuFloatComplex> &data, int n, double threshold = 1e-3)
{
    vector<long long> result(n, 0);
    for (int i = 0; i < n; i++)
    {
        float real_part = cuCrealf(data[i]);
        if (fabs(real_part) > threshold)
        {
            result[i] = round(real_part);
        }
    }
    return result;
}

// Debugging Function to Print Complex Vectors
void debug_output(const vector<cuFloatComplex> &data, const string &label)
{
    cout << label << ":\n";
    for (size_t i = 0; i < data.size(); ++i)
    {
        cout << "Index: " << i << ", Value: (" << cuCrealf(data[i]) << ", " << cuCimagf(data[i]) << ")\n";
    }
    cout << endl;
}

// Debugging Function to Print Zero-Padded Arrays
void debug_zero_padding(const vector<cuFloatComplex> &data, const string &label)
{
    cout << label << " (size = " << data.size() << "):\n";
    for (size_t i = 0; i < data.size(); i++)
    {
        cout << "Index: " << i << ", Value: (" << cuCrealf(data[i]) << ", " << cuCimagf(data[i]) << ")\n";
    }
    cout << endl;
}

// Debugging Function to Print Final Cleaned Result
void debug_final_result(const vector<long long> &result)
{
    cout << "Final cleaned result: ";
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
}

// Polynomial Multiplication Function
vector<long long> multiply(const vector<long long> &a, const vector<long long> &b)
{
    // Determine the size for FFT (next power of 2)
    int n = 1;
    while (n < a.size() + b.size())
    {
        n <<= 1;
    }

    // Initialize complex vectors with zero-padding
    vector<cuFloatComplex> fa(n, make_cuFloatComplex(0.0, 0.0));
    vector<cuFloatComplex> fb(n, make_cuFloatComplex(0.0, 0.0));

    // Populate fa with coefficients of polynomial a
    for (size_t i = 0; i < a.size(); ++i)
    {
        fa[i] = make_cuFloatComplex(a[i], 0.0);
    }

    // Populate fb with coefficients of polynomial b
    for (size_t i = 0; i < b.size(); ++i)
    {
        fb[i] = make_cuFloatComplex(b[i], 0.0);
    }

    // Perform forward FFT on both polynomials
    vector<cuFloatComplex> fa_transformed(n);
    vector<cuFloatComplex> fb_transformed(n);

    fft_gpu(fa.data(), fa_transformed.data(), n, false);
    fft_gpu(fb.data(), fb_transformed.data(), n, false);

    // Element-wise multiplication in frequency domain
    vector<cuFloatComplex> result_transformed(n);
    for (int i = 0; i < n; i++)
    {
        result_transformed[i] = cuCmulf(fa_transformed[i], fb_transformed[i]);
    }

    // Perform inverse FFT on the multiplied result
    vector<cuFloatComplex> fa_inverse(n);
    fft_gpu(result_transformed.data(), fa_inverse.data(), n, true);

    // Clean coefficients by removing small numerical artifacts
    vector<long long> result = clean_coefficients(fa_inverse, n);

    // Trim trailing zeros to get the final polynomial coefficients
    while (!result.empty() && result.back() == 0)
    {
        result.pop_back();
    }

    // Debug final cleaned result
    debug_final_result(result);

    return result;
}

// Main Function
int main()
{
    // Define two polynomials a(x) and b(x)
    // Example:
    // a(x) = 9 + x + 3x^2 + 7x^3 + 5x^4 + 4x^5
    // b(x) = 7 + 8x + 8x^2 + 3x^3 + 6x^4 + 2x^5
    ifstream fin("File1.txt");
    ofstream fout("ok.txt");
    vector<long long> a, b;
    fin >> n;
    for (int i = 0; i <= n; i++)
    {
        int x;
        fin >> x;
        a.push_back(x);
    }
    fin >> m;
    for (int i = 0; i <= m; i++)
    {
        int x;
        fin >> x;
        b.push_back(x);
    }

    auto start = high_resolution_clock::now();

    // Perform polynomial multiplication
    vector<long long> c = multiply(a, b);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "FFT Cuda Execution Time: " << duration.count() << " microseconds" << endl;

    for (int i = 0; i < c.size(); i++)
    {
        fout << c[i] << " ";
    }
    fout << endl;
    return 0;
}
