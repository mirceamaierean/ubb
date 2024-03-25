% PS-practic-ex3
% 2. A manufacturer of gunpowder has developed a new powder which was tested in 12 shells. The resulting
% muzzle velocities in m/s are (they are assumed to be approximately normally distributed):
% [1001.7 975.0 978.3 988.3 978.7 988.8 1000.3 979.2 968.9 983.5 999.2 985.6];
% a. At the 5% significance level, does the data suggest that, on average, the muzzles are faster than 995 m/s?
% b. Find a 99% confidence interval for the standard deviation of the velocity of shells of this type.
clear 
clc

X = [1001.7 975.0 978.3 988.3 978.7 988.8 1000.3 979.2 968.9 983.5 999.2 985.6];

n = length(X);
alpha = 0.05;
% a) at a 5% significance level, does the data suggest that on avereage,
% the muzzles are faster than 995 m/s
% H0: on average the muzzles are of speed 995
% H1: the muzzles are faster than 995 (>) => we have a right tail test

m0 = 995;
tail = 1;

[H, P, CI, STATS] = ttest(X, m0, alpha, tail);

if H == 0
    fprintf("\nThe null hypothesis is not rejected!\n");
    fprintf("On average the muzzles are not faster than 995!\n");
else 
    fprintf("\nThe null hypothesis is rejected!\n");
    fprintf("On average the muzzles are faster than 995!\n");
end

t = tinv(1 - alpha, n-1);

fprintf("The rejection region is (%.4f, %.4f)\n", -inf, t);
fprintf("The test statistics value is: %.4f\n", STATS.tstat);
fprintf("The P-value of the test is: %.4f\n", P);
fprintf("The value of H is: %d\n", H);

% b) find a 99% confidence interval for the standard deviation of the
% velocity of shells of this type

alpha = 0.01;
q = tinv(1 - alpha / 2, n - 1);
m = mean(X);
s = std(X);

left = m - s / sqrt(n) * q;
right = m + s / sqrt(n) * q;

fprintf("b)\n");
fprintf("The 99 confidence interval is (%.4f, %.4f)\n", left, right);
