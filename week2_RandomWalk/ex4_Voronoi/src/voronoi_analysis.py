import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import Voronoi, voronoi_plot_2d
from scipy.optimize import curve_fit
from shapely.geometry import Polygon
from cycler import cycler

def plot_format(ax):
    params = {'axes.labelsize':13, 'font.size':16, 'legend.fontsize':11,
              'xtick.labelsize':13, 'ytick.labelsize':13, 'figure.figsize':[8, 8/1.618]}
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

def compute_voronoi_sizes(points, dimension):
    if dimension == 1:
        # For 1D, use sorted points and compute intervals
        sorted_points = np.sort(points)
        sizes = np.diff(sorted_points)
    elif dimension == 2:
        # For 2D, use Voronoi diagram
        vor = Voronoi(points)
        sizes = []
        for region in vor.regions:
            if not -1 in region and len(region) > 0:
                polygon = [vor.vertices[i] for i in region]
                sizes.append(Polygon(polygon).area)
    return sizes

def plot_histogram(sizes, dimension):
    plt.figure()
    hist, bins, _ = plt.hist(sizes, bins=30, density=True, ec='w', alpha=0.5)
    bin_centers = (bins[:-1] + bins[1:]) / 2

    if dimension == 1:
        def func(x, a):
            return a * x * np.exp(-x)
        popt, _ = curve_fit(func, bin_centers, hist)
        plt.plot(bin_centers, func(bin_centers, *popt), 'k-', lw=2, label='x * exp(-x)')
        plot_title = '1D Voronoi Cell Size Distribution'
        plot_filename = 'week2_RandomWalk/ex4_Voronoi/output/voronoi_1d_hist.png'
    elif dimension == 2:
        def func(x, a):
            return a * x**2.5 * np.exp(-x)
        popt, _ = curve_fit(func, bin_centers, hist)
        plt.plot(bin_centers, func(bin_centers, *popt), 'k-', lw=2, label='x^(5/2) * exp(-x)')
        plot_title = '2D Voronoi Cell Size Distribution'
        plot_filename = 'week2_RandomWalk/ex4_Voronoi/output/voronoi_2d_hist.png'
    
    plt.xlabel('Cell Size')
    plt.ylabel('Density')
    plt.legend()
    plt.title(plot_title)
    plot_format(plt.gca())
    plt.savefig(plot_filename, dpi=500, bbox_inches='tight', pad_inches=0, facecolor='#C0C0C0')
    plt.show()

def draw_voronoi(points):
    vor = Voronoi(points)
    fig, ax = plt.subplots()
    voronoi_plot_2d(vor, ax=ax, show_vertices=False, line_colors='orange',
                    line_width=2, line_alpha=0.6, point_size=2)

    for region in vor.regions:
        if not -1 in region and len(region) > 0:
            polygon = [vor.vertices[i] for i in region]
            plt.fill(*zip(*polygon), alpha=0.4)
    
    plt.plot(points[:, 0], points[:, 1], 'ko', markersize=3)
    plot_format(ax)
    plt.title('Voronoi Diagram')
    plot_filename = 'week2_RandomWalk/ex4_Voronoi/output/voronoi_diagram.png'
    plt.savefig(plot_filename, dpi=500, bbox_inches='tight', pad_inches=0, facecolor='#C0C0C0')
    plt.show()

def main():
    dimension = int(input("Enter the dimension (1 or 2): "))
    
    if dimension == 1:
        points = np.sort(np.random.rand(100))
        sizes = compute_voronoi_sizes(points, dimension)
        plot_histogram(sizes, dimension)
    elif dimension == 2:
        points = np.random.rand(100, 2)
        sizes = compute_voronoi_sizes(points, dimension)
        plot_histogram(sizes, dimension)
        draw_voronoi(points)

if __name__ == "__main__":
    main()