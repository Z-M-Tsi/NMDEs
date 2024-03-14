% This program is used to test five_point_dirichlet.m and test_func.m
% which solves Poisson's equation -\Delta u = f by five points format
% in a rectangle area [x_1,x_2]x[y_1,y_2]
% The test function is given by u(x, y) = exp(1+\sin x + \sin y)
% with Nonhomogeneous Dirichlet boundary conditions (see test_func.m)
% Latest Version by ZM on Mar-15-2024
% Tested successfully!

% Setting rectangle area
x = [1 3];
y = [4 7];

% Numbers of divisions
ns = 10.*2.^(1:9);

error = zeros(length(ns), 1);
% fileID = fopen('dst_error.txt', 'w');
for k = 1:length(ns)
    error(k) = test_func(x, y, ns(k));
    % fprintf(fileID, 'Error norm when n = %d: %e\n', ns(k), error(k));
    disp(['Error norm when n = ', num2str(ns(k)), ': ', num2str(error(k))]);
end
% fclose(fileID);

% Numerical results
figure;
loglog(ns,error,'+k','MarkerSize',8);
hold on
loglog(ns,1./ns.^2,'--');
grid on
xlabel n, ylabel error
legend('Error','Second-order Convergence Reference Line')
title('Convergence of Fast DST Method for Five Points Differential Format')


