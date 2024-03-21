import numpy as np
import matplotlib.pyplot as plt
import argparse

def simulate_throws(throwsNr, diceNrLow, incrementsNr):
    # Calculate the number of dice for each increment:
    dice_counts = np.arange(diceNrLow, diceNrLow + incrementsNr * 1, 1)

    # Create a 3D array: increments x throwsNr x dice_count:
    all_throws = np.random.randint(1, 7, (incrementsNr, throwsNr, dice_counts[-1]))

    if incrementsNr > 0:
        # Use the first layer corresponding to the first increment (1 dice):
        outcomes = all_throws[0, :, 0]
        
        # Count occurrences of each side:
        counts = np.bincount(outcomes, minlength=7)[1:]  # Skip index 0 to align with dice sides 1-6
        probabilities = counts / throwsNr
        print("Probabilities for each side of 1 dice: ", probabilities)
    
    # Calculate variances for each increment by dynamically selecting the relevant dice:
    variances = [np.var(np.mean(all_throws[i, :, :dice], axis=1)) for i, dice in enumerate(dice_counts)]
    
    return dice_counts, variances

def plot_variance(dice_counts, variances):
    """Plot variance as a function of the number of dice, with an additional log-scaled plot."""
    plt.figure(figsize=(20, 6))
    
    # Original plot:
    plt.subplot(1, 2, 1)
    plt.plot(dice_counts, variances, marker='.', ms=8, linestyle='-', color='b')
    plt.title('Variance Decay with Increasing Number of Dice')
    plt.xlabel('Number of Dice')
    plt.ylabel('Variance of the Average Values')
    plt.grid(True)
    
    # Log-scaled plot:
    plt.subplot(1, 2, 2)
    plt.plot(dice_counts, variances, marker='.', ms=8, linestyle='-', color='r')
    plt.xscale('log')
    plt.yscale('log')
    plt.title('Log-Scaled Variance Decay (log scale)')
    plt.xlabel('Number of Dice (log scale)')
    plt.ylabel('Variance of the Average Values')
    plt.grid(True)
    
    plt.savefig('week1_WarmUp/ex1_SingleDieThrowing/output/dice_plots.png')
    plt.show()

def main():
    parser = argparse.ArgumentParser(description="Dice Simulation")
    parser.add_argument("--throwsNr", type=int, required=True, help="Number of simulations")
    parser.add_argument("--incrementsNr", type=int, required=True, help="Number of increments")
    args = parser.parse_args()

    dice_counts, variances = simulate_throws(args.throwsNr, 1, args.incrementsNr)
    plot_variance(dice_counts, variances)

if __name__ == "__main__":
    main()