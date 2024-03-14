function U = five_point_dirichlet(F, bd_value, x_interp, y_interp, n)
% Solver for Poisson's equations with Dirichlet condition
% Uses five-point differential format with fast DST
% Latest Version by ZM on Mar-15-2024
% Tested with poisson_test.m

% Inputs:
% F: (n-1)x(n-1) matrix of f in -\Delta u = f
% bd_value: [left, right, bottom, top], Dirichlet conditions of rectangle
% x_interp: [x_1, x_2], interval of rectangle area in horizonal direction 
% y_interp: [y_1, y_2], interval of rectangle area in vertical direction
% n: numbers of divisions

% Expansion factor
x_scale = x_interp(2) - x_interp(1);
y_scale = y_interp(2) - y_interp(1);

% Dirichlet boundary condition
left = bd_value(1,:); 
right = bd_value(2,:);
bottom = bd_value(3,:); 
top = bd_value(4,:); 

% Homogenization
F(:,end) = F(:,end) + n^2 .* right(2:end-1)' ./ x_scale^2;
F(:,1) = F(:,1) + n^2 .* left(2:end-1)' ./ x_scale^2;
F(1,:) = F(1,:) + n^2 .* bottom(2:end-1) ./ y_scale^2;
F(end,:) = F(end,:) + n^2 .* top(2:end-1) ./ y_scale^2;

% Generate eigenvector
ind = 1:n-1;
eigen_vec = (4*n^2)*(sin((0.5*pi/n)*ind)).^2;
E = bsxfun(@plus, eigen_vec./x_scale^2, eigen_vec'./y_scale^2);

% Compute V = PFQ by fast DST
V = dst(dst(F)')';

% Compute W with eigenvectors
W = (4/n^2)*V./E;

% Compute U = PWQ by fast DST
U = dst(dst(W)')';

end

