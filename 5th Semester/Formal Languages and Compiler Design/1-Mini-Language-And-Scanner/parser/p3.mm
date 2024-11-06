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
