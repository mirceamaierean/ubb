int n;
n = 7;
n = 7.5;
n = 7.00000;
n = 0.00007;
n = 0.700000;
n = 0.0000700;
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

write("sum", sum);
write("su\"m", sum);
write("su\'m", sum);
write('a', sum);