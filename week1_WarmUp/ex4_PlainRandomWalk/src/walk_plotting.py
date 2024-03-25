import numpy as np
import matplotlib.pyplot as plt

# Plot 1: Histogram for the 1D case
def plot_1d_histogram(filepath):
    data = np.loadtxt(filepath)
    plt.figure(figsize=(10, 6))
    plt.hist(data, bins=101, alpha=0.75, color='red')
    plt.title('Histogram of Final Positions (1D Random Walk)')
    plt.xlabel('Final Position')
    plt.ylabel('Frequency')
    plt.grid(True)
    plt.savefig('week1_WarmUp/ex4_PlainRandomWalk/output/1d_distribution.png')
    plt.show()
    plt.close()

# Plot 2, 3, 4, and 5: 2D cases
def plot_2d_steps_vs_distance(filepaths, titles):
    plt.figure(figsize=(14, 10))
    for i, (filepath, title) in enumerate(zip(filepaths, titles), start=1):
        data = np.loadtxt(filepath, delimiter=',')
        steps = data[:, 0]
        distances = data[:, 1]

        plt.subplot(2, 2, i)
        plt.plot(steps, distances, marker='.', ms=7, linestyle='-', color='red')
        plt.title(title)
        plt.xlabel('Number of Steps')
        plt.ylabel('Average Squared Distance')
        plt.grid(True)

    plt.tight_layout(pad=3.0)  # Adjust padding between and around subplots
    plt.subplots_adjust(hspace=0.3)  # Adjust the height spacing between subplots
    plt.savefig('week1_WarmUp/ex4_PlainRandomWalk/output/2d_directions_comparison.png')
    plt.show()
    plt.close()


# File paths and titles for the 2D plots
filepaths_2d = [
    'week1_WarmUp/ex4_PlainRandomWalk/output/2d_4_main_halt.txt',
    'week1_WarmUp/ex4_PlainRandomWalk/output/2d_4_diag.txt',
    'week1_WarmUp/ex4_PlainRandomWalk/output/2d_8_directions.txt',
    'week1_WarmUp/ex4_PlainRandomWalk/output/2d_8_directions_halt.txt'
]
titles_2d = [
    '2D Random Walk: 4 Main Directions + Halt',
    '2D Random Walk: 4 Diagonals',
    '2D Random Walk: 8 Directions',
    '2D Random Walk: 8 Directions + Halt'
]

# Execute plotting functions
plot_1d_histogram('week1_WarmUp/ex4_PlainRandomWalk/output/1d_final_positions.txt')
plot_2d_steps_vs_distance(filepaths_2d, titles_2d)
