% This program is used to compare shooting method program
% shooting.m with bvp4c in MATLAB
% The test function is given by
% y" = - \frac{2}{x} y' + \frac{2}{x^2} y + \frac{\sin\ln x}{x^2}, x \in [1,2]
% with boundary conditions y(1) = 1, y(2) = 2
% The exact solution is
% y(x) = c_1 x + \frac{c_2}{x^2} - \frac{3}{10}\sin\ln x -\frac{1}{10}\cos\ln x, 
% where c_2 = \frac{1}{70}[8-12\sin(\ln 2) - 4\cos(\ln 2)]
% and c_1 = \frac{11}{10}-c_2.
% set step length h = 0.05
% Latest Version by ZM on Mar-08-2024
% Tested successfully!


clear; clc;

% Initialization
h = 0.05; x = 1:h:2;
coef_a = [1, 0]; 
coef_b = [1, 0];
u_exact = exact_sol(x);

% shooting
bound = [coef_a, 1, coef_b, 2];
u_shoot = shooting(@ds_fun, bound, x, 0);

% bvp4c
guess_sol = [2 2];
solinit = bvpinit(x, guess_sol);
sol = bvp4c(@bvpfun, @bc, solinit);
u = deval(sol, x);

% Numerical Results
plot(x,u(1,:),'+k', x,u_shoot,'ok', x,u_exact,'-r','MarkerSize',8)
legend('shooting.m', 'bvp4c',  'Exact Solution', 'Location','southeast')
xlabel x, ylabel u
title("Computational Solution vs Analytical Solution")
hold on



function dy = bvpfun(x, u) % equation to solve in bvp4c
dy = [u(2); -2.*u(2)./x + 2.*u(1)./x.^2 + sin(log(x))./x.^2];
end

function dys = ds_fun(x, u) % equation to solve in shooting.m
dys = [u(2); -2.*u(2)./x + 2.*u(1)./x.^2 + sin(log(x))./x.^2; u(4); -2.*u(4)./x + 2.*u(3)./x.^2];
end

function res=bc(ua, ub) % boundary conditions for bvp4c
res=[ua(1)-1; ub(1)-2];
end

function u = exact_sol(x) % exact solution
c2 = (8-12.*sin(log(2))-4.*cos(log(2)))/70;
c1 = 1.1-c2;
u = c1.*x + c2./x.^2 -0.3.*sin(log(x)) - 0.1.*cos(log(x));
end
