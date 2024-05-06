function u = trans_solver_upwind(Nt,Nx,lambda,a,u0)
% TRANS_SOLVER_UPWIND solves transport equation $u_t + a u_x = 0$ 
% using the upwind scheme.
%   Parameters:
%       - Nt: number of time steps
%       - Nx: number of spatial grid points
%       - lambda: Courant number (time step / spatial step)
%       - a: advection speed
%       - u0: initial condition
%
%   Returns:
%       - u: numerical solution of the transport equation
%
%   Latest Version by ZM on May-06-2024
%   Tested successfully!

u = u0;

% constructing the matrix for the upwind scheme
ind = ones(1, Nx);
A = (1 - a * lambda) * diag(ind) + a * lambda * diag(ind(2:Nx), -1); 
A(1, 1) = 1;  % Fix left boundary point

u = (A^Nt) * u;
end

