% PS-practic-ex3
% Nickel powders are used in coatings used to shield electronic equipment. A random sample is selected,
% and the sizes of nickel particles in each coating are recorded (they are assumed to be approximately normally
% distributed):
% X = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];
% a. Find a 95% confidence interval for the average size of nickel particles.
% b. At the 1% significance level, on average, do these nickel particles seem to be smaller than 3?
clear 
clc

X = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];

n = length(X);
m = mean(X);
s = std(X);

% a) Find a 95% confidence interval for the average size of nickel
% particles.

alpha = 0.05;
t = tinv(1-alpha/2, n-1);
left = m - s*t/sqrt(n);
right = m + s*t/sqrt(n);

fprintf("a)\n");
fprintf("The 95 confidence interval is (%.4f, %.4f)\n", left, right);

fprintf("b)\n");

alpha = 0.05;
m0 = 3

% H0: on average the nickel particles are equal to 3
% H1: on average the nickel particles are smaller than 3 - Left Tailed Test
% we must do a left-tailed test

[H, P, CI, STATS] = ttest(X, m0, alpha, -1);

if H == 0
    fprintf("\nThe null hypothesis is not rejected!\n");
    fprintf("On average the nickel particles are equal to 3!\n");
else 
    fprintf("\nThe null hypothesis is rejected!\n");
    fprintf("On average the nickel particles are smaller than 3!\n");
end

t = tinv(alpha, n-1);

fprintf("The rejection region is (%.4f, %.4f)\n", -inf, t);
fprintf("The test statistics value is: %.4f\n", STATS.tstat);
fprintf("The P-value of the test is: %.4f\n", P);
fprintf("The value of H is: %.4f\n", H);