function y = shooting(ds_func, bc, x, guess)
%SHOOTING Summary of this function goes here
%   Detailed explanation goes here

% unpack boundary conditions
coef_a = bc(1:2); alpha = bc(3);
coef_b = bc(4:5); beta = bc(6);

% choose proper c0 and c1   
if coef_a(1)==0 && coef_a(2)~=0
    coef_c(2) = 0;
    coef_c(1) = -1/coef_a(2);
elseif coef_a(1)~=0 && coef_a(2)==0
    coef_c(2) = 1/coef_a(1);
    coef_c(1) = 0;
else
    coef_c(2) = 2/coef_a(1);
    coef_c(1) = 1/coef_a(2);
end

% shooting
max_iter = 1000;
tol = 1e-6;

for iter = 1:max_iter
    init = [coef_a(1)*guess-coef_c(1)*alpha, coef_c(2)*alpha-coef_a(2)*guess, coef_a(2), coef_a(1)];
    [~, y_shoot] = ode45(ds_func, x, init);
    y_shoot = y_shoot.';
    error = coef_b * y_shoot(1:2,end) - beta;
    D_error = coef_b * y_shoot(3:4,end);
    
    if abs(error) < tol
        break;
    else
        guess = guess - error/D_error;
    end
end

y = y_shoot(1,:);

end

