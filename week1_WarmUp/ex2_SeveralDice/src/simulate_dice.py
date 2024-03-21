import argparse
import numpy as np
import matplotlib.pyplot as plt
import os

def simulate_dice_throws(n_experiments, dice_count):
    """Simulate dice throws and return sums of results."""
    # Simulate throws: results shape is (n_experiments, dice_count)
    results = np.random.randint(1, 7, size=(n_experiments, dice_count))
    sums = results.sum(axis=1)  # Sum across dice for each experiment
    return sums

def plot_and_save_histogram(sums, n_experiments, dice_count):
    """Plot histogram of dice sums and save to file."""
    plt.hist(sums, bins='auto', edgecolor='black', density=True)
    plt.title(f'Distribution of Dice Roll Sums\n{n_experiments} Experiments, {dice_count} Dice')
    plt.xlabel('Sum')
    plt.ylabel('Probability Density')
    plt.grid(True)

    # Ensure output directory exists
    output_dir = 'week1_WarmUp/ex2_SeveralDice/output'
    os.makedirs(output_dir, exist_ok=True)
    plot_filename = os.path.join(output_dir, f'dice_distribution_{n_experiments}_{dice_count}.png')
    plt.savefig(plot_filename)
    print(f'Plot saved to {plot_filename}')
    plt.close()

def main():
    parser = argparse.ArgumentParser(description='Simulate dice throws and plot distribution of sums.')
    parser.add_argument('--n_experiments', type=int, default=1000, help='Number of experiments to simulate.')
    parser.add_argument('--dice_count', type=int, default=2, help='Number of dice to throw in each experiment.')
    
    args = parser.parse_args()

    sums = simulate_dice_throws(args.n_experiments, args.dice_count)
    plot_and_save_histogram(sums, args.n_experiments, args.dice_count)

if __name__ == '__main__':
    main()