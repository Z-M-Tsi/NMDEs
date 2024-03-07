% This program is used to compare the performance of two ODE solvers:
% euler.m and ode45 in MATLAB
% The test function is given by
% y' = \frac{1}{x^2} - \frac{y}{x}, x \in [1,2]
% with initial value y(1) = 1
% Set step length h = 0.05
% The exact solution is y = \frac{\ln x + 1}{x}
% Latest Version by ZM on Mar-07-2024
% Tested successfully!

clear; clc;

% Initialization
h = 0.05; x = 1:h:2;
u0 = 1;
u_exact = ((log(x)+1)./x).';

% Forward Euler
[x, u_fore] = euler(@odefun, x, u0, 'foreward');
% Backward Euler (prediction and correction)
[x, u_back] = euler(@odefun, x, u0, 'backward');
% ode45
[x, u_ode45] = ode45(@odefun, x, u0);

% Numerical Results
figure;
plot(x,u_fore,'xk', x,u_back,'ok', x,u_ode45,'+k', x,u_exact,'-r', 'MarkerSize',8)
legend('Forward Euler', 'Backward Euler', 'ode45', 'Exact Solution', 'Location','northeast')
xlabel x, ylabel u
title("Computational Solution vs Analytical Solution")
hold on

error_fore = abs(u_exact - u_fore);
error_back = abs(u_exact - u_back);
error_ode45 = abs(u_exact - u_ode45);

% figure;
% semilogy(x,error_fore,'xk', x,error_back,'ok', x,error_ode45,'+k', 'MarkerSize',8)
% legend('Forward Euler', 'Backward Euler', 'ode45', 'Location','east')
% title("Error")
% hold on

function du = odefun(x, u)
du = 1/x^2 - u/x;
end