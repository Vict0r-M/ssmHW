import argparse
import numpy as np
import matplotlib.pyplot as plt
import os

def simulate_dice(throwsNr, diceNr):
    # Simulate throws:
    results = np.random.randint(1, 7, size=(throwsNr, diceNr))
    sums = results.sum(axis=1)  # Sum across dice for each experiment
    return sums

def plot_histogram(sums, throwsNr, diceNr):
    # Plot histogram of dice sums:
    plt.hist(sums, bins='auto', edgecolor='black', density=True)
    plt.title(f'Distribution of Dice Roll Sums\n{throwsNr} Experiments, {diceNr} Dice')
    plt.xlabel('Sum')
    plt.ylabel('Probability Density')
    plt.grid(True)

    # Ensure output directory exists
    output_dir = 'week1_WarmUp/ex2_SeveralDice/output'
    os.makedirs(output_dir, exist_ok=True)
    plot_filename = 'dice_distribution.png'
    plt.savefig('week1_WarmUp/ex2_SeveralDice/output/dice_distribution.png')
    print(f'Plot saved to dice_distribution.png')
    plt.close()

def main():
    parser = argparse.ArgumentParser(description='Simulate dice throws and plot distribution of sums.')
    parser.add_argument('--throwsNr', type=int, default=1000, help='Number of experiments to simulate.')
    parser.add_argument('--diceNr', type=int, default=2, help='Number of dice to throw in each experiment.')
    
    args = parser.parse_args()

    sums = simulate_dice(args.throwsNr, args.diceNr)
    plot_histogram(sums, args.throwsNr, args.diceNr)

if __name__ == '__main__':
    main()