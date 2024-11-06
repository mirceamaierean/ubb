// this program reads a number n from the keyboard
// after that, it reads n values, and computes the sum of all of them
// and displays the result on the screen
int n;
read(n);

int sum;
sum = 0;

int i;
i = 0;

int val;

while (i < n) {
    read(val);
    sum = sum + val;
    i = i + 1;
}

write("Sum is ", sum);
