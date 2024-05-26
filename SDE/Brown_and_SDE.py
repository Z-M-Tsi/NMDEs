import numpy as np
import matplotlib.pyplot as plt
from plot_func import *

np.random.seed(42)

# Caculate the first and second variation of a Brownian motion
def variation(X, order):
    if order == 1:
        return np.cumsum(np.abs(np.diff(X)))
    elif order == 2:
        return np.cumsum((np.diff(X))**2)
    else:
        raise ValueError('Order must be 1 or 2')

# Caculate the mixed variation of X and S
def mixed_variation(X, S):
    return np.cumsum(np.diff(X)*np.diff(S))

# Simulate X and S
def simulate(params, X0, S0, dt, num_steps):
    
    # Unpack the parameters
    alpha = params['alpha']
    v = params['v']
    theta = params['theta']
    sigma = params['sigma']
    sigma1 = params['sigma1']
    sigma2 = params['sigma2']
    
    # Initialize the arrays
    X = np.zeros(num_steps)
    S = np.zeros(num_steps)
    X[0] = X0
    S[0] = S0

    # Simulate the process
    dBt = np.sqrt(dt) * np.random.normal(0, 1, num_steps)
    dWt = np.sqrt(dt) * np.random.normal(0, 1, num_steps)
    for i in range(1, num_steps):   
        X[i] = X[i-1] + alpha * (v - X[i-1]) * dt + sigma * dBt[i-1]
        S[i] = S[i-1] + theta * (X[i-1] - S[i-1]) * dt + sigma1 * dBt[i-1] + sigma2 * dWt[i-1]
        
    return X, S


# Parameters for different Brownian motions
num_trajectories = 5
num_steps = 1000
step_size = 0.1
t = np.arange(num_steps) * step_size

# Parameters for different time steps of the same Brownian motion
dt1 = [1e-1, 1e-2, 1e-3]
steps = [1e3, 1e4, 1e5]
t1 = [np.arange(steps[i]) * dt1[i] for i in range(len(dt1))]

# Parameters for the SDE
dt = 0.1
# num_steps = 1000
t = np.arange(num_steps) * dt

X0 = 2.5
S0 = 3.5

params_1 = {'alpha': 0.15, 'v': 3, 'theta': 0.15, 'sigma': 0.1, 'sigma1': 0.05, 'sigma2': 0.1,}
params_2 = {'alpha': 0.25, 'v': 3, 'theta': 0.25, 'sigma': 0.2, 'sigma1': 0.15, 'sigma2': 0.1,}
params_3 = {'alpha': 0.5, 'v': 3, 'theta': 0.5, 'sigma': 0.3, 'sigma1': 0.2, 'sigma2': 0.1,}
params = [params_1, params_2, params_3]

v = [3, 3, 3] # Long-term mean of X

if 'name'=='__main__':
    
    # Generate different Brownian motions
    brownian_motions = []
    for _ in range(num_trajectories):
        brownian_motion = np.cumsum(np.random.normal(0, np.sqrt(step_size), num_steps))
        brownian_motions.append(brownian_motion)
        
    plot_trajectories(t, brownian_motions, save=False)
    
    # Calculate the first and second variation of the first trajectory
    first_brs = []
    for i in range(len(dt1)):
        first_brs.append(np.cumsum(np.random.normal(0, np.sqrt(dt1[i]), int(steps[i]))))
        
    variations = []
    for i in range(len(dt1)):
        variations.append([])
        variations[i].append(variation(first_brs[i], order=1))
        variations[i].append(variation(first_brs[i], order=2))
        
    plot_variation(t1, variations, dt, save=False)
    
    # Simulate the processes
    Xs = []
    Ss = []
    for param in params:
        X, S = simulate(param, X0, S0, dt, num_steps)
        Xs.append(X)
        Ss.append(S)
    plot_XandS(t, Xs, Ss, v, save=False)
        
    # 2nd variation of X
    X_variations = []
    for X in Xs:
        X_variations.append(variation(X, order=2))

    plot_X(t, Xs, X_variations, v, save=False)
    
    # mixed variation of X and S
    mixed_variations = []
    for X, S in zip(Xs, Ss):
        mixed_variations.append(mixed_variation(X, S))
        plot_mixed_variation(t, mixed_variations, save=False)

