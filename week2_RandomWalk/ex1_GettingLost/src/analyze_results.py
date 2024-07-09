import numpy as np
import matplotlib.pyplot as plt
from cycler import cycler

def load_data(filename):
    data = []
    with open(filename, 'r') as file:
        for line in file:
            values = list(map(int, line.strip().split()))
            step_count = values[0]
            steps = values[1:]
            data.append((step_count, steps))
    return data

def analyze_data(data):
    results = []
    for step_count, steps in data:
        steps_array = np.array(steps)
        num_returned = np.sum(steps_array == step_count)
        probability = num_returned / len(steps)
        results.append((step_count, probability))
    return results

def save_analysis(filename, results):
    with open(filename, 'w') as file:
        for step_count, probability in results:
            file.write(f"{step_count} {probability}\n")

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
    rect = plt.Rectangle((-0.02, -0.02), 1.04, 1.04, fill=False, edgecolor='black',
                          linewidth=4, transform=fig.transFigure, figure=fig)
    fig.patches.extend([rect])
    plt.tight_layout(pad=0)

def aggregate_data(results, bin_size):
    aggregated_results = []
    for i in range(0, len(results), bin_size):
        bin_step_counts = [result[0] for result in results[i:i + bin_size]]
        bin_probabilities = [result[1] for result in results[i:i + bin_size]]
        avg_step_count = np.mean(bin_step_counts)
        avg_probability = np.mean(bin_probabilities)
        aggregated_results.append((avg_step_count, avg_probability))
    return aggregated_results

def plot_data(results, dimension, bin_size=10, log_log=False):
    aggregated_results = aggregate_data(results, bin_size)
    
    step_counts = [result[0] for result in aggregated_results]
    probabilities = [result[1] for result in aggregated_results]

    plt.figure()
    
    if log_log:

        bins = np.linspace(min(step_counts), max(step_counts), len(step_counts) + 1)
        bin_centers = (bins[:-1] + bins[1:]) / 2

        plt.bar(bin_centers, probabilities, width=np.diff(bins), align='center', ec='w')

        #bins = np.logspace(np.log10(min(step_counts)), np.log10(max(step_counts)), len(step_counts) + 1)
        #bin_centers = 10 ** ((np.log10(bins[:-1]) + np.log10(bins[1:])) / 2)
        #plt.bar(bin_centers, probabilities, width=np.diff(bins), align='center', ec='w')
        ax = plt.gca()
        #ax.set_xscale('log')
        ax.set_yscale('log')

        # Fit a straight line to the log-log plot
        log_step_counts = np.log(step_counts)
        log_probabilities = np.log(probabilities)
        slope, intercept = np.polyfit(log_step_counts, log_probabilities, 1)
        fit_line = np.exp(intercept) * np.array(step_counts)**slope
        plt.plot(step_counts, fit_line, color='black', linestyle='--')
    else:
        plt.plot(step_counts, probabilities, marker='o', linestyle='-')
        plt.ticklabel_format(axis='both', style='sci', scilimits=(-2, 3), useMathText=True)
    
    plt.xlabel('Steps')
    plt.ylabel('Probability')
    plt.title(f'Return Probability Distribution in {dimension}')
    
    ax = plt.gca()
    plot_format(ax)
    
    filepath = f'week2_RandomWalk/ex1_GettingLost/output/return_probability_{dimension}.png'
    plt.savefig(filepath, dpi=500, bbox_inches='tight', pad_inches=0, facecolor='#C0C0C0')
    plt.show()

def main():
    dimensions = ['1D', '1D', '2D', '3D']
    for dim in dimensions:
        print(f"Analyzing {dim} data...")
        data = load_data(f'week2_RandomWalk/ex1_GettingLost/output/return_steps_{dim}.txt')
        results = analyze_data(data)
        save_analysis(f'week2_RandomWalk/ex1_GettingLost/output/return_probability_{dim}.txt', results)
        plot_data(results, dim, bin_size=25, log_log=True)  # Set log_log to True to enable log-log plotting
        print(f"Analysis for {dim} data completed.")

if __name__ == "__main__":
    main()