function y = shooting(ds_func, bc, x, guess)
% shooting method to solve boundary value problem
% y" = f(x, y, y') x \in [a,b],
% a_0y(a) - a_1y'(a) = \alpha,
% b_0y(b) + b_1y'(b) = \beta.
% choose Newton's method to optimize the guess

% ds_func: function to solve
% bc: [coef_a, alpha, coef_b, beta], boundary conditions
% where coef_a = [a_0, a_1], coef_b = [b_0, b_1]
% x: interval of time variable
% guess: initial guess of s for c_0y(a) - c_1y'(a) = s
% Latest Version by ZM on Mar-08-2024
% Tested with shooting_test.m

% unpack boundary conditions
coef_a = bc(1:2); alpha = bc(3);
coef_b = bc(4:5); beta = bc(6);

% choose proper c_0 and c_1 to make c_0a_1 - c_1a_0 = 1 
if coef_a(1)==0 && coef_a(2)~=0
    coef_c(2) = 0;
    coef_c(1) = 1/coef_a(2);
elseif coef_a(1)~=0 && coef_a(2)==0
    coef_c(2) = -1/coef_a(1);
    coef_c(1) = 0;
else
    coef_c(2) = 1/coef_a(1);
    coef_c(1) = 2/coef_a(2);
end

% shooting
tol = 1e-6;

init = [coef_a(2)*guess-coef_c(2)*alpha; coef_a(1)*guess-coef_c(1)*alpha; coef_a(2); coef_a(1)];
[~, y_shoot] = ode45(ds_func, x, init);
y_shoot = y_shoot.';
error = coef_b * y_shoot(1:2,end) - beta;
while abs(error) >= tol
    init = [coef_a(2)*guess-coef_c(2)*alpha; coef_a(1)*guess-coef_c(1)*alpha; coef_a(2); coef_a(1)];
    [~, y_shoot] = ode45(ds_func, x, init);
    y_shoot = y_shoot.';
    error = coef_b * y_shoot(1:2,end) - beta;
    D_error = coef_b * y_shoot(3:4,end);
    guess = guess - error/D_error;
end

y = y_shoot(1,:);

end

