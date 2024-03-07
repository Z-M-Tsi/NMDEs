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
% Latest Version by ZM on Mar-07-2024


clear; clc;

% Initialization
h = 0.05; x = 1:h:2;
coef_a = [1, 0]; 
coef_b = [1, 0];
u_exact = exact_sol(x);

% shooting
bound = [coef_a, 1, coef_b, 2];
shoot_u = shooting(@ds_fun, bound, x, 0);

% bvp4c
guess_sol = [2 2];
solinit = bvpinit(x, guess_sol);
sol = bvp4c(@bvpfun, @bc, solinit);
u = deval(sol, x);


plot(x,u(1,:),'+k',x,u_exact,'-r','MarkerSize',8)
xlabel x, ylabel u

function dy = bvpfun(x, u) % equation to solve
dy(1) = u(2);
dy(2) = -2.*u(2)./x + 2.*u(1)./x.^2 + sin(log(x))./x.^2;
end

function dys = ds_fun(x, u)
dys = zeros(4, 1);
dys(1) = u(2);
dys(2) = -2.*u(2)./x + 2.*u(1)./x.^2 + sin(log(x))./x.^2;
dys(3) = u(4);
dys(4) = -2.*u(4)./x + 2.*u(3)./x.^2;
end


function res=bc(ua, ub) % boundary conditions
res=[ua(1)-1; ub(1)-2];
end

function u = exact_sol(x) % analytic solution
c2 = (8-12.*sin(log(2))-4.*cos(log(2)))/70;
c1 = 1.1-c2;
u = c1.*x + c2./x.^2 -0.3.*sin(log(x)) - 0.1.*cos(log(x));
end
