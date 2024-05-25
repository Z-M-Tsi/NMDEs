import numpy as np
import matplotlib.pyplot as plt



def plot_trajectories(t, brownian_motions, save=False, filename='brownian_motion.eps'):
    '''
    Plot multiple Brownian motion trajectories.
    
    Parameters:
        t (array-like): The time values for the trajectories.
        brownian_motions (list of array-like): A list of arrays representing the Brownian motion trajectories.
        save (bool, optional): Whether to save the plot as a file. Defaults to False.
        filename (str, optional): The filename to save the plot. Defaults to 'brownian_motion.eps'.

    Returns:
        None
    '''

    num_trajectories = len(brownian_motions)

    plt.figure(figsize=(8, 5))
    for i in range(num_trajectories):
        plt.plot(t, brownian_motions[i], label=f'Trajectory {i+1}', linewidth=0.8)
        
    plt.xlabel('Time')
    plt.ylabel('Value')
    plt.title('Brownian Motion Trajectories')
    plt.legend()
    plt.grid(True)
    
    if save:
        plt.savefig(filename)

    plt.show()



def plot_variation(t, variations, save=False, filename='variation.eps'):
    '''
    Plot the variation of two variables over time.

    Parameters:
        t (array-like): The time values.
        variations (list of array-like): A list of two arrays representing 1st- and 2nd-order variations.
        save (bool, optional): Whether to save the plot as a file. Default is False.
        filename (str, optional): The filename to save the plot. Default is 'variation.eps'.

    Returns:
        None
    '''

    plt.figure(figsize=(6, 3))
    for i in range(2):
        plt.subplot(1, 2, i+1)
        plt.plot(t[1:], variations[i])
        plt.title(label='{:} Variation'.format('First' if i==0 else 'Second'))
        plt.xlabel('Time')
        plt.grid(True)
        
    plt.tight_layout()

    if save:
        plt.savefig(filename)
    
    plt.show()



def plot_X(t, X, X_variation, v, save=True, filename='X.eps'):
    """
    Plot the trajectory of X and its second-order variation.

    Parameters:
        t (array-like): The time values.
        X (list of array-like): A list of arrays representing the trajectories of X.
        X_variation (list of array-like): A list of arrays representing the second-order variations of X.
        v (list of array-like): A list of values representing the long-term mean of X.
        save (bool, optional): Whether to save the plot. Defaults to True.
        filename (str, optional): The filename to save the plot. Defaults to 'X.eps'.

    Returns:
        None
    """

    nums = len(X)
    title_str = ['Trajectory of $X$', '2nd variation of $X$']
    
    plt.figure(figsize=(9, 2.5*nums))  
    gs = plt.GridSpec(nums, 3, width_ratios=[2, 1, 1])

    for i in range(nums):
        # plot trajectories
        ax1 = plt.subplot(gs[i, 0])
        ax1.plot(t, X[i], linewidth=0.9)
        ax1.plot(t, np.ones_like(t)*v[i], color='red', linestyle='--')
        ax1.set_xlabel('Time')
        ax1.set_ylabel('value')
        ax1.set_title('{0}$_{1}$'.format(title_str[0], i+1))
        ax1.grid(True)

        # plot 2nd-order variations
        ax2 = plt.subplot(gs[i, 1])
        ax2.plot(t[1:], X_variation[i])
        ax2.set_xlabel('Time')
        ax2.set_title('{0}$_{1}$'.format(title_str[1], i+1))
        ax2.grid(True)

    plt.tight_layout()

    if save:
        plt.savefig(filename)
    
    plt.show()



def plot_XandS(t, Xs, Ss, v, save=False, filename='XandS.eps'):
    '''
    Plot the values of X and S over time.

    Parameters:
        t (array-like): The time values.
        Xs (list of array-like): A list of arrays representing the trajectories of X.
        Ss (list of array-like): A list of arrays representing the trajectories of S.
        v (list of array-like): A list of values representing the long-term mean of X.
        save (bool, optional): Whether to save the plot as a file. Defaults to False.
    filename (str, optional): The filename to save the plot. Defaults to 'XandS.eps'.

    Returns:
        None
    '''

    plt.figure(figsize=(8, 3.5*len(Xs)))
    for i in range(len(Xs)):
        plt.subplot(len(Xs), 1, i+1)
        plt.plot(t, Xs[i], label='$X_{}$'.format(i+1), linewidth=0.9)
        plt.plot(t, Ss[i], label='$S_{}$'.format(i+1), linewidth=0.9)
        plt.axhline(y=v[i], color='r', linestyle='--')
        plt.xlabel('Time')
        plt.ylabel('Value')
        plt.legend(loc='upper right')
        plt.grid(True)
        
    if save:
        plt.savefig(filename)
        
    plt.show()



def plot_mixed_variation(t, mixed_variations, save=False, filename='mixed_variation.eps'):
    
    '''
    Plots the mixed variation of variables over time.

    Parameters:
        t (array-like): The time values.
        mixed_variations (list of array-like): A list of arrays representing the mixed variations.
        save (bool, optional): Whether to save the plot as a file. Defaults to False.
        filename (str, optional): The filename to save the plot. Defaults to 'mixed_variation.eps'.

    Returns:
        None
    '''

    nums = len(mixed_variations)

    plt.figure(figsize=(3*nums, 2.5))
    for i in range(nums):
        plt.subplot(1, nums, i+1)
        plt.plot(t[1:], mixed_variations[i])
        plt.xlabel('Time')
        plt.title('Mixed Variation of $X_{0}$ and $S_{0}$'.format(i+1))
        plt.grid(True)

    if save:
        plt.savefig(filename)

    plt.show()