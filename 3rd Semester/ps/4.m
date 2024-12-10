clear All
clc
%  Nickel powders are used in coatings used to shield electronic equipment.
%  A random sample is selected, and the sizes of nickel particles in each
%  coating are recorded (they are assumed to be approximately normally
%  distributed):
% X = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];

X = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];

n = length(X);
 
% H0: on average the nickel particles are equal to 3
% H1: on average the nickel particles are smaller than 3 - Left Tailed Test
% we must do a left-tailed test

% Alpha represents the significance level
alpha = 0.05;
% We have to test the mean of the population, and sigma is unknow, so we
% will use ttest for testing our hypothesis

% H0: on average the nickel particles are equal to 3
% H1: on average the nickel particles are smaller than 3 - Left Tailed Test
% we must do a left-tailed test, so tail = -1

% The testing value is equal to 3
fprintf("Point A)\n");

m0 = 3;
tail = -1;

[H, P, CI, STATS] = ttest(X, m0, alpha, tail);

if H == 0
    fprintf("The null hypothesis is not rejected!\n");
    fprintf("On average the nickel particles are equal to 3!\n");
else 
    fprintf("The null hypothesis is rejected!\n");
    fprintf("On average the nickel particles are smaller than 3!\n");
end

% Since it's a left tail test, our rejection region will be between -oo and
% tinv(alpha, n - 1)
t = tinv(alpha, n-1);

fprintf("The rejection region is (%.4f, %.4f)\n", -inf, t);
fprintf("The test statistics value is: %.4f\n", STATS.tstat);
fprintf("The P-value of the test is: %.4f\n", P);
fprintf("The value of H is: %d\n", H);


% a) Find a 99% confidence interval for the standard deviation of nickel
% particles.

alpha = 0.01;
q1 = chi2inv(1 - alpha / 2, n - 1);
q2 = chi2inv(alpha / 2, n - 1);

v = var(X);

left = ((n - 1) * v) / q1;
right = ((n - 1) * v) / q2;

% Since the standard deviation is the square root of the variance, left
% will become square root of left and right will become square root of
% right
left = sqrt(left);
right = sqrt(right);

fprintf("Point B)\n");
fprintf("The 99 confidence interval is (%.4f, %.4f)\n", left, right);



