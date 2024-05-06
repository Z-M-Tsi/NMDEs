function u = trans_solver(T,L,tau,h,a,u0,mode)
% TRANS_SOLVER solves transport equation $u_t + a u_x = 0$ .
%   Parameters:
%       - T: total time
%       - L: length of spatial domain
%       - tau: time step size
%       - h: spatial step size
%       - a: advection speed
%       - u0: initial condition
%       - mode: numerical method ('upwind', 'B-W', 'L-F', 'L-W')
%
%   Returns:
%       - u: numerical solution of the transport equation
%
%   Latest Version by ZM on May-06-2024
%   Tested successfully!

Nt = T/tau + 1;
Nx = L/h + 1;
lambda = tau/h;

switch mode
    case 'upwind'
        u = trans_solver_upwind(Nt,Nx,lambda,a,u0);
    case 'B-W'
        u = trans_solver_bw(Nt,Nx,lambda,a,u0);
    case 'L-F'
        u = trans_solver_lf(Nt,Nx,lambda,a,u0);
    case 'L-W'
        u = trans_solver_lw(Nt,Nx,lambda,a,u0);
end

end

