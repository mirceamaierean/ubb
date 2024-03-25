clc
clear All

% To reach the maximum efficiency in performing an assembling operation in a manufacturing plant, new
% employees are required to take a 1-month training course. A new method was suggested, and the manager wants
% to compare the new method with the standard one, by looking at the lengths of time required for employees
% to assemble a certain device. They are given below (and assumed approximately normally distributed):
% Assembling times
% Standard 46 37 39 48 47 44 35 31 44 37
% New 35 33 31 35 34 30 27 32 31 31

% a. At the 5% significance level, do the population variances seem to differ?
% b. Find a 95% confidence interval for the difference of the average assembling times.

X1 = [46 37 39 48 47 44 35 31 44 37];
X2 = [35 33 31 35 34 30 27 32 31 31];

% if you see in the statement confidence interval, INSTANTLY WRITE THESE 
n1 = length(X1);
n2 = length(X2);
v1 = var(X1);
v2 = var(X2);
m1 = mean(X1);
m2 = mean(X2);

% 5% significance level
alpha = 0.05;

% H0: sigma1 = sigma2
% H1 sigma1 != sigma2 - two-tailed test - tail = 0
tail = 0;

% we have to test the variances of the 2 populations, and we know both
% sigma, so we will use vartest2

[h, p, ci, stats] = vartest2(X1, X2, alpha, tail);

fprintf('point a!\n');

if h == 0
    fprintf('H0 is not rejected, i.e, sigmas are equal\n');
else 
    fprintf('H0 is rejected, population variances differ \n');
end

q1 = finv(alpha / 2, stats.df1, stats.df2);
q2 = finv(1 - alpha / 2, stats.df1, stats.df2);

fprintf('Observed value is %1.4f\n', stats.fstat);
fprintf('P-value is %1.4f\n', p);
fprintf('Rejection region R is (-inf, %3.4f) U (%3.4f, inf)\n', q1, q2);

fprintf('\npoint b !\n');

if h == 0
    n = n1 + n2 - 2;
    q = tinv(1 - alpha / 2, n);
    sp = sqrt(((n1 - 1) * v1 + (n2 - 1) * v2) / n);
    left = m1 - m2 - q * sp * sqrt(1/n1+1/n2);
    right = m1 - m2 + q * sp * sqrt(1/n1+1/n2);
else 
    c = (v1/n1)/(v1/n1 + v2/n2);
    n = c ^ 2 / (n1-1) + (1-c) ^ 2/ (n2 - 1);
    n = 1/n;
    t = tinv(1 - alpha/2, n);
    left = m1 - m2 - t * sqrt(v1/n1 + v2/n2);
    right = m1 - m2 + t * sqrt(v1/n1 + v2/n2);
end

fprintf("\nb)\n");
fprintf("The 95 confidence interval is: (%f, %f)\n", left, right);


