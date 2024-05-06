function u = trans_solver_lf(Nt,Nx,lambda,a,u0)
% TRANS_SOLVER_LF solves transport equation $u_t + a u_x = 0$ 
% using the Lax-Friedrichs scheme.
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

% constructing the matirx for upwind scheme
ind = ones(1, Nx);
A2 = 0.5*(1+a*lambda).*diag(ind(2:Nx),-1);
A3 = 0.5*(1-a*lambda).*diag(ind(2:Nx),1);
A = A2 + A3;

% Fix left boundary point
A(1, 1) = 1; 
A(1, 2) = 0; 

u = (A^Nt) * u;

end

