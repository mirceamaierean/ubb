clear All
clc

X1 = [3.1 2.9 3.8 3.3 2.7 3.0 2.8 2.5 2.6 2.0 3.2 2.4 2.3 3.1 2.1 3.4];
X2 = [6.9 6.4 4.7 4.3 5.1 6.3 5.9 5.4 5.3 5.2 5.1 5.9 5.8 4.9];

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

% b.
%h0: miu1 = miu2
%h1: miu1 < miu2 - left-tailed test

tail = -1;


[h, p, ci, stats] = ttest2(X1, X2, alpha, tail, 'equal');
%vartype - equal (bcs in point a. we got same values for population
%variances. If they were equal, we would have used 'equal' parameter.

%p-P value; ci = confidence level

if h==0
  fprintf('H0 is not rejected. Other employees DO NOT dispose of more white papers than bank employees.\n')
else
  fprintf('H0 is rejected. Other employees DO dispose of more white papers than bank employees.\n')
end

fprintf('P-value of the test statistic is %e.\n', p)
fprintf('Observed value of the test statistic is %1.4f.\n', stats.tstat)

q1 = tinv(alpha, stats.df);

fprintf('Rejection region R is (%3.4f, +inf)\n', q1)
fprintf('\n\n\n\n');

