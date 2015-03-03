clc;
clear;

c1 = -3 : 3;
c2 = -3 : 3;
c1 = ones(c1)' * c1;
c1 = c1(:)';

c2 = -3 : 3;
c2 = c2' * ones(c2);
c2 = c2(:)';

x = 0:0.01:1;

e1 = exp(-x)';
e2 = exp(-2 * x)';

y = e1 * c1 + e2 * c2;

plot(x, y);
//prod();//permute all elements
