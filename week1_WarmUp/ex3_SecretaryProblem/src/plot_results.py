import matplotlib.pyplot as plt
import numpy as np

def read_results(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        k_values = [int(line.split()[0]) for line in lines]
        values = [float(line.split()[1]) for line in lines]
    return k_values, np.array(values)/2000000

def plot_graphs(success_file, total_rank_file):
    k_success, success = read_results(success_file)
    k_total_rank, total_rank = read_results(total_rank_file)

    plt.figure(figsize=(14, 6))

    plt.subplot(1, 2, 1)
    plt.plot(k_success, success, marker='.', ms=8)
    plt.title('Success Rate by k')
    plt.xlabel('k')
    plt.ylabel('Success Rate')

    plt.subplot(1, 2, 2)
    plt.plot(k_total_rank, total_rank, marker='.', ms=8, color='red')
    plt.title('Total Rank by k')
    plt.xlabel('k')
    plt.ylabel('Total Rank')

    plt.tight_layout()
    plt.savefig('week1_WarmUp/ex3_SecretaryProblem/output/results.png')
    plt.show()

if __name__ == '__main__':
    plot_graphs("week1_WarmUp/ex3_SecretaryProblem/output/success.txt", "week1_WarmUp/ex3_SecretaryProblem/output/total_rank.txt")