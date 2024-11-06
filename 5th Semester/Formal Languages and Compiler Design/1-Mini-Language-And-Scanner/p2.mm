// this program computes the sum of all the divisors for a number read from the keyboard, and displays the result
int a;
read(a);

int i;
i = 1;

int sum;
sum = 0;

while (i <= a) {
    if (a % i == 0) {
        sum = sum + i;
    }
    i = i + 1;
}

write(sum);