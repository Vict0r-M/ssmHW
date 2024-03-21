import matplotlib.pyplot as plt

# Read the results from the file
with open('week1_WarmUp/ex2_SeveralDice/output/results.txt', 'r') as file:
    results = [int(line.strip()) for line in file.readlines()]

# Plotting the histogram
plt.hist(results, bins='auto', edgecolor='black', density=True)
plt.title('Distribution of Dice Roll Sums')
plt.xlabel('Sum')
plt.ylabel('Probability Density')
plt.show()