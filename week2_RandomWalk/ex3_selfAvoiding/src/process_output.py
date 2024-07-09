import matplotlib.pyplot as plt
import numpy as np
import re
from cycler import cycler

def parse_line(line):
    points = re.findall(r'\((\-?\d+), (\-?\d+)\)', line)
    return [(int(x), int(y)) for x, y in points]

def plot_format(ax):
    params = {'axes.labelsize': 13, 'font.size': 16, 'legend.fontsize': 11,
              'xtick.labelsize': 13, 'ytick.labelsize': 13, 'figure.figsize': [8, 8 / 1.618]}
    plt.rcParams.update(params)
    colors = cycler('color', ['#B22222', '#3388BB', '#9988DD',
                              '#EECC55', '#88BB44', '#FFBBBB'])
    plt.rc('axes', facecolor='#E6E6E6', edgecolor='none', axisbelow=True,
           grid=True, prop_cycle=colors)
    plt.rc('grid', color='w', linestyle='solid')
    plt.rc('xtick', direction='out', color='black')
    plt.rc('ytick', direction='out', color='black')
    plt.rc('patch', edgecolor='#E6E6E6')
    plt.rc('lines', linewidth=2)

    fig = plt.gcf()
    rect = plt.Rectangle((-0.02, -0.02), 1.04, 1.04, fill=False, edgecolor='black', linewidth=4, transform=fig.transFigure, figure=fig)
    fig.patches.extend([rect])
    plt.tight_layout(pad=0)

def plot_results(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    all_steps = []
    for line in lines:
        steps = parse_line(line.strip())
        all_steps.append(steps)

    max_steps = max(len(steps) for steps in all_steps)
    mean_d_squared = np.zeros(max_steps)

    for steps in all_steps:
        d_squared = [(x**2 + y**2) for x, y in steps]
        for i, d in enumerate(d_squared):
            mean_d_squared[i] += d

    mean_d_squared /= len(all_steps)

    # Plot 〈d^2(N)〉
    plt.figure()
    plt.plot(range(1, max_steps + 1), mean_d_squared)
    plt.xlabel('Steps')
    plt.ylabel('Mean Squared Distance')
    plt.title('Mean Squared Distance Dependence on N')
    plt.ticklabel_format(axis='both', style='sci', scilimits=(-2, 3), useMathText=True)
    plot_format(plt.gca())
    plt.savefig('week2_RandomWalk/ex3_SelfAvoiding/output/mean_squared_distance_1D.png', dpi=500, bbox_inches='tight', pad_inches=0, facecolor='#C0C0C0')
    plt.show()

    # Plot probability distribution of the number of steps before getting blocked
    steps_before_block = [len(steps) for steps in all_steps]
    plt.figure()
    plt.hist(steps_before_block, bins=14, alpha=1, ec='w', label='Steps to block')
    plt.xlabel('Number of Steps')
    plt.ylabel('Frequency')
    plt.title('Distribution of Steps Before Getting Blocked')
    plt.legend()
    plt.ticklabel_format(axis='both', style='sci', scilimits=(-2, 3), useMathText=True)
    plot_format(plt.gca())
    plt.savefig('week2_RandomWalk/ex3_SelfAvoiding/output/steps_distribution_1D.png', dpi=500, bbox_inches='tight', pad_inches=0, facecolor='#C0C0C0')
    plt.show()

    # Probability of getting blocked
    blocked_probability = sum(1 for steps in all_steps if len(steps) < max_steps) / len(all_steps)
    print(f"Probability of getting blocked: {blocked_probability:.2f}")

if __name__ == "__main__":
    filename = "week2_RandomWalk/ex3_SelfAvoiding/output/all_simulations_1D.txt"
    plot_results(filename)
    plot_results(filename)