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
    echo $((RANDOM % 10)) >> polynomials.txt # Generate a random coefficient
done

# Second polynomial
echo "$2" >> polynomials.txt # Write the degree
for i in $(seq 0 $2); do      # Loop through m+1 coefficients
    echo $((RANDOM % 10)) >> polynomials.txt # Generate a random coefficient
done

# Compile and run the C++ program
mpic++ -o mpi_reg_par mpi_reg_par.cpp
g++ -std=c++11 reg_par.cpp -o reg_par
mpirun -np 8 ./mpi_reg_par polynomials.txt
./reg_par polynomials.txt

diff mpi_reg_par_output.txt reg_par_output.txt