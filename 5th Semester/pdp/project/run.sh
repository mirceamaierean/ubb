#!/bin/bash

# Ensure the script receives two arguments for the degrees
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <degree_of_first_polynomial> <degree_of_second_polynomial>"
    exit 1
fi

# Remove the file if it exists and create a new one
rm -f polynomials.txt
touch polynomials.txt

# First polynomial
echo "$1" >> polynomials.txt # Write the degree
for i in $(seq 0 $1); do      # Loop through n+1 coefficients
    echo $((RANDOM % 9 + 1)) >> polynomials.txt # Generate a random coefficient
done

# Second polynomial
echo "$2" >> polynomials.txt # Write the degree
for i in $(seq 0 $2); do      # Loop through m+1 coefficients
    echo $((RANDOM % 10)) >> polynomials.txt # Generate a random coefficient
done

# Compile and run the C++ program
# g++ -std=c++11 karatsuba_sequential.cpp -o karatsuba_sequential
g++ -std=c++20 fft_parallelized.cpp -o fft_parallelized
g++ -std=c++20 fft_iterative_seq.cpp -o fft_it_seq
mpic++ -std=c++20 -o fft_mpi fft_mpi.cpp 2> /dev/null
g++ -std=c++20 fft_sequential.cpp -o fft_sequential
g++ -std=c++20 regular_parallelized.cpp -o regular_parallel

./fft_parallelized polynomials.txt 5
mpirun -np 8 ./fft_mpi polynomials.txt
./fft_sequential polynomials.txt
./fft_it_seq polynomials.txt
./regular_parallel polynomials.txt
# ./regular_parallel polynomials.txt
# ./regular_sequential polynomials.txt

# now, compare the results
diff fft_sequential_output.txt fft_parallelized_output.txt
diff fft_sequential_output.txt fft_mpi_output.txt
diff fft_sequential_output.txt fft_it_output.txt

# diff karatsuba_parallelized_output.txt karatsuba_sequential_output.txt
# diff karatsuba_parallelized_output.txt regular_sequential_output.txt
# diff karatsuba_parallelized_output.txt regular_parallelized_output.txt


