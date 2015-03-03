h = 0.1;
t = 0:h:6;
u = sin(t);
A = [0 0; -1/h 0];
B = [1; 1/h];
C = [0 1];
v = zeros(B);
x = zeros(u);

for k = 2:length(t)
    v = A * v - B * u(k);
    x(k) = C * v;
end
