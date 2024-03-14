function error = test_func(x, y, n)
% Generate test function for poisson_test.m
% test function: u(x, y) = exp(1+\sin x + \sin y)
% f(x, y) = -(\cos^2 x + \cos^2 y - \sin x - \sin y)exp(1+\sin x + \sin y)
% Latest Version by ZM on Mar-15-2024
% Tested with poisson_test.m

% Inputs:
% x: [x_1, x_2], interval of rectangle area in horizonal direction 
% y: [y_1, y_2], interval of rectangle area in vertical direction
% n: numbers of divisions

% Generating grid
xp = linspace(x(1), x(2), n+1);
yp = linspace(y(1), y(2), n+1);
[X, Y] = meshgrid(xp(2:end-1), yp(2:end-1));

% Exact solution
f = -(cos(X).^2 + cos(Y).^2 - sin(X) - sin(Y)).*exp(1 + sin(X) + sin(Y));
exact_u = @(X,Y)exp(1 + sin(X) + sin(Y));

% Nonhomogeneous Dirichlet conditions
left_bc = exact_u(x(1), yp); right_bc = exact_u(x(2), yp);     
bottom_bc = exact_u(xp, y(1)); top_bc = exact_u(xp, y(2)); 
bd = [left_bc; right_bc; bottom_bc; top_bc];

% Computing with five_point_dirichlet.m and return the error
exact_solution = exact_u(X, Y);
U = five_point_dirichlet(f, bd, x, y, n);
error = norm(U - exact_solution, 'fro')/n;
end

