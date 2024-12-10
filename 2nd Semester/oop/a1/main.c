//
// Created by Mircea Măierean on 02.03.2023.
//
#include <stdio.h>
#include <string.h>

void generatePrimeNumbersSmallerThanNaturalNumber(int naturalNumber, char isPrimeNumber[])
{
    // naturalNumber: integer number
    // isPrimeNumber: array of characters, where the value is 1 if the number is prime, and 0 if the number is not prime
    // This function generates the prime numbers smaller than the natural number using the Eratosthenes Sieve

    // 0 and 1 are not prime numbers
    isPrimeNumber[0] = 0;
    isPrimeNumber[1] = 0;

    // Mark all the numbers that are even as not prime
    for (int number = 4; number < naturalNumber; number += 2)
        isPrimeNumber[number] = 0;

    // Find the numbers using Eratosthenes Sieve
    // Loop until we reach the integer part of the square root of our number
    for (int number = 3; number * number <= naturalNumber; number += 2)
        if (isPrimeNumber[number] == 1)
            // If our number is prime, we mark all the multiples of this number as not a prime number
            // To optimize the code, we start from the square of the nr, because the multiples smaller than the squares are already marked
            for (int multiple = number * number; multiple < naturalNumber; multiple += number)
                isPrimeNumber[multiple] = 0;
}

void makeListOfPrimeNumbers(int naturalNumber, char isPrimeNumber[], int primeNumbers[], int *lengthOfArray)
{
    // naturalNumber: integer number
    // isPrimeNumber: array of characters, where the value is 1 if the number is prime, and 0 if the number is not prime
    // primeNumbers: array of integers, where we will store the prime numbers
    // lengthOfArray: pointer to an integer, where we will store the length of the array of prime numbers
    // This function makes a list of the prime numbers smaller than the natural number transmitted as a parameter

    int length = 0;
    for (int number = 2; number < naturalNumber; ++number)
        if (isPrimeNumber[number] == 1)
            primeNumbers[length++] = number;
    *lengthOfArray = length;
}

void printPrimeNumbers(int lengthOfArray, int primeNumbers[])
{
    // lengthOfArray: integer number, the length of the array of prime numbers
    // primeNumbers: array of integers, where we will store the prime numbers
    // This function prints the prime numbers

    for (int i = 0; i < lengthOfArray; ++i)
        printf("%d ", primeNumbers[i]);
}

void performTheOperationsOnConsoleBasedApplication() {
    // In this functions, the magic happens. We perform the operations on a console based application.
    int naturalNumber, primeNumbers[1000001], vectorOfNumbers[1001], lengthOfArrayOfPrimeNumbers = 0, lengthOfVector = 0, option,
        lengthOfLongestIncreasingSubsequence = 0, lengthOfCurrentIncreasingSubsequence = 0, startOfLongestIncreasingSubsequence = 0, startOfCurrentIncreasingSubsequence = 0;
    char isPrimeNumber[1000001];

    while (1)
    {
        printf("Welcome to the first homework for Object Oriented Programming course!\n"
               "In order to perform the operations, please choose one of the following options, by writing the corresponding digit to each operations:\n"
               "1. Read a vector of natural numbers from the console. \n"
               "2. Print the elements of the vector. \n"
               "3. Find the prime numbers smaller than a given natural number, that you are going to read from the keyboard.\n"
               "4. Find the longest increasing contiguous subsequence, such that the sum of that any 2 consecutive elements is a prime number.\n"
               "5. Exit the program.\n"
                "Your option is: ");
        scanf("%d", &option);
        if (option == 5)
            return;
        switch (option)
        {
            case 1:
                printf("Please enter the length of the vector: ");
                scanf("%d", &lengthOfVector);
                printf("Please enter the elements of the vector: ");
                for (int i = 0; i < lengthOfVector; ++i)
                    scanf("%d", &vectorOfNumbers[i]);
                break;
            case 2:
                printf("The elements of the vector are: ");
                for (int i = 0; i < lengthOfVector; ++i)
                    printf("%d ", vectorOfNumbers[i]);
                printf("\n");
                break;
            case 3:
                // We start our program by assuming that all the numbers are prime. For each position in our array, the value is set to 1.
                memset(isPrimeNumber, 1, sizeof(isPrimeNumber));
                printf("Please enter the natural number: ");
                scanf("%d", &naturalNumber);
                // We generate the prime numbers smaller than the natural number
                generatePrimeNumbersSmallerThanNaturalNumber(naturalNumber, isPrimeNumber);
                // We make a list of the prime numbers
                makeListOfPrimeNumbers(naturalNumber, isPrimeNumber, primeNumbers, &lengthOfArrayOfPrimeNumbers);
                printf("The prime numbers smaller than %d are: ", naturalNumber);
                printPrimeNumbers(lengthOfArrayOfPrimeNumbers, primeNumbers);
                printf("\n");
                break;
            case 4:
                memset(isPrimeNumber, 1, sizeof(isPrimeNumber));
                // We generate the prime numbers smaller than 1000001. We assume that the sum of any 2 consecutive elements of the vector is smaller than 1000001
                generatePrimeNumbersSmallerThanNaturalNumber(1000001, isPrimeNumber);
                lengthOfCurrentIncreasingSubsequence = 1;
                // We start from the second element of the vector, because we need to check the sum of the current element with the previous one
                for (int i = 1; i < lengthOfVector; ++i)
                {
                    // If the current element is bigger than the previous one and the sum of the current element with
                    // the previous one is a prime number, we increase the length of the current increasing subsequence
                    if (vectorOfNumbers[i] > vectorOfNumbers[i - 1] && vectorOfNumbers[i] + vectorOfNumbers[i - 1] > 1 && isPrimeNumber[vectorOfNumbers[i] + vectorOfNumbers[i - 1]] == 1)
                    {
                        lengthOfCurrentIncreasingSubsequence++;
                        if (lengthOfCurrentIncreasingSubsequence > lengthOfLongestIncreasingSubsequence)
                        {
                            lengthOfLongestIncreasingSubsequence = lengthOfCurrentIncreasingSubsequence;
                            startOfLongestIncreasingSubsequence = startOfCurrentIncreasingSubsequence;
                        }
                    }
                    // Else, our current increasing subsequence ends here, so we start a new one, not before we update the length of the longest increasing subsequence if
                    // the length of the current increasing subsequence is bigger than the length of the longest increasing subsequence we had known until now
                    else
                    {
                        startOfCurrentIncreasingSubsequence = i;
                        lengthOfCurrentIncreasingSubsequence = 1;
                    }
                }
                printf("The length of the longest increasing contiguous subsequence, such that the sum of that any 2 consecutive elements is a prime number is %d\n", lengthOfLongestIncreasingSubsequence);
                printf("The longest increasing contiguous subsequence, that respects this condition is: ");
                for (int i = startOfLongestIncreasingSubsequence; i < startOfLongestIncreasingSubsequence + lengthOfLongestIncreasingSubsequence; ++i)
                    printf("%d ", vectorOfNumbers[i]);
                printf("\n");
                break;
            default:
                printf("Please enter a valid option!\n");
                break;
        }

    }
}

int main(int argc, char * argv[])
{
    performTheOperationsOnConsoleBasedApplication();
    return 0;
}