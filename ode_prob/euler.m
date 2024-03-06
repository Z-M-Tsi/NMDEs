function [X,U] = euler(du, x, u0, mode)
% Forward and Backward Euler method to solve ODE
% use prediction-coccrection in backward euler
% Latest Version by ZM on Mar-06-2024
% Tested with euler_test.m

if isequal(size(x),[1,2])
    X = linspace(x(1), x(2), 50);
else
    X = x;
end

U = zeros(length(X), 1); U(1) = u0;

switch mode
    case 'foreward'
        for n = 1:length(X)-1
            h = X(n+1)-X(n);
            U(n+1) = U(n) + h*du(X(n), U(n));
        end
    case 'backward'
        for n = 1:length(X)-1
            h = X(n+1)-X(n);
            K1 = du(X(n), U(n));
            U_pred = U(n) + h*du(X(n), U(n));
            K2 = du(X(n+1), U_pred);
            U(n+1) = U(n) + h*(K1+K2)/2;
        end
end

end

