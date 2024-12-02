#!/bin/bash
# Generate a script that creates one file representing 2 polynomials
# Each polynomial has its degree and coefficients.
# The file includes n, the degree of the first polynomial, followed by n+1 coefficients,
# and m, the degree of the second polynomial, followed by m+1 coefficients.

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
g++ -std=c++11 karatsuba_sequential.cpp -o karatsuba_sequential
g++ -std=c++11 regular_sequential.cpp -o regular_sequential
g++ -std=c++11 regular_parallelized.cpp -o regular_parallel
g++ -std=c++11 karatsuba_parallelized.cpp -o karatsuba_parallel
./karatsuba_sequential polynomials.txt
./karatsuba_parallel polynomials.txt
./regular_sequential polynomials.txt
./regular_parallel polynomials.txt

# now, compare the results
diff karatsuba_parallelized_output.txt karatsuba_sequential_output.txt
diff karatsuba_parallelized_output.txt regular_sequential_output.txt
diff karatsuba_parallelized_output.txt regular_parallelized_output.txt


