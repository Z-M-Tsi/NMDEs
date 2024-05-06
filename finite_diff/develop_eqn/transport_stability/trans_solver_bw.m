function u = trans_solver_bw(Nt,Nx,lambda,a,u0)
% TRANS_SOLVER_BM solves transport equation $u_t + a u_x = 0$ 
% using the Beam-Warming scheme.
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
A1 = (1-a*lambda/2)*(1-a*lambda).*diag(ind);
A2 = (a*lambda)*(2-a*lambda).*diag(ind(2:Nx),-1);
A3 = -(a*lambda/2)*(1-a*lambda).*diag(ind(3:Nx),-2);
A = A1 + A2 + A3;

% Fix left boundary point
A(1, 1) = 1; 
A(2, 2) = 1; 
A(2, 1) = 0; 

u = (A^Nt) * u;



end

