function [x,U] = euler(du, x, u0, mode)
% Forward and Backward Euler method to solve ODE in 1D
% use prediction-coccrection in backward euler
% du: function to solve
% x: interval of time variable
% u0: initial value
% mode: forward or backward Euler method
% Latest Version by ZM on Mar-07-2024
% Tested with euler_test.m

U = zeros(length(x), 1); U(1) = u0;

switch mode
    case 'foreward'
        for n = 1:length(x)-1
            h = x(n+1)-x(n);
            U(n+1) = U(n) + h*du(x(n), U(n));
        end
    case 'backward'
        for n = 1:length(x)-1
            h = x(n+1)-x(n);
            K1 = du(x(n), U(n));
            U_pred = U(n) + h*du(x(n), U(n));
            K2 = du(x(n+1), U_pred);
            U(n+1) = U(n) + h*(K1+K2)/2;
        end
end

end

