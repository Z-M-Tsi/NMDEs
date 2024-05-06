
% Given parameters
h = 0.1;
tau = 0.08;
T = 4;
Nt = T / tau + 1;
t = linspace(0, T, Nt);

a_values = [1, 2, 4];
L_values = [8, 16, 32];

for i = 1:length(a_values)
    a = a_values(i);
    L = L_values(i);

    Nx = L / h + 1;
    x = linspace(-L / 4, 3 * L / 4, Nx);
    u0 = arrayfun(@(x) f(x, 0, a), x)';

    methods = {'upwind', 'B-W', 'L-F', 'L-W'};
    u = cell(1, length(methods));
    
    for j = 1:length(methods)
        u{j} = trans_solver(T, L, tau, h, a, u0, methods{j});
    end

    stability_plot(x, u, a);

    % compare with analytical solution when a=1
    if a==1
        u_exact = arrayfun(@(x) f(x, T, 1), x)';
        for i = 1:length(u)
            subplot(2, 2, i);
            plot(x, u_exact, 'LineWidth', 1.2); hold on
        end
    end
    
end


% Analytical solution
function u = f(x, t, a)
    u = (x - a * t <= 0);
end


% plot to show stability
function stability_plot(x, u, a)
    figure;
    methods = {'Upwind', 'Beam-Warming', 'Lax-Friedrichs', 'Lax-Wendroff'};
    for i = 1:length(u)
        subplot(2, 2, i);
        plot(x, u{i}, 'LineWidth', 1.2); hold on
        if a == 1
            ylim([-0.5, 1.5]);
        end
        title(methods{i});
        xlabel('x');
        ylabel('u');
        grid on;  
    end
end
