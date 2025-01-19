import matplotlib.pyplot as plt

def generate_graph(input1, input2, input3, input4):
    """
    Generates a graph with 4 lines, each representing the execution time
    for an individual iteration from the given inputs.

    Args:
        input1, input2, input3, input4: Arrays representing execution times.
    """
    iterations = list(range(1, len(input1) + 1))

    plt.figure(figsize=(10, 6))

    plt.plot(iterations, input1, label="Iterative Sequential FFT", color="blue")
    plt.plot(iterations, input2, label="Recursive Sequntial FFT", color="red")
    plt.plot(iterations, input3, label="Recursive Parallelized FFT", color="green")
    plt.plot(iterations, input4, label="Recursive Parallelized FFT using MPI", color="purple")

    plt.xlabel("Iteration")
    plt.ylabel("Execution Time (ms)")
    plt.title("Execution Time per Iteration")
    plt.legend()
    plt.grid(True)

    plt.show()

def read_file(filename):

    with open(filename, "r") as file:
        while True:
            line = file.readline()
            if not line:
                break
            # split line by space
            line = line.split()
            # convert string to float
            line = [float(i) for i in line]
            print(len(line))
            return line

# Example usage
# read array from file
# input1 = read_file("input1.txt")

input1 = read_file("fft_it_seq_output.txt");
input2 = read_file("fft_sequential_output.txt");
input3 = read_file("fft_parallelized_output.txt");
input4 = read_file("fft_mpi_output.txt");

generate_graph(input1, input2, input3, input4)
