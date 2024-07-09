import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import Voronoi, voronoi_plot_2d
from scipy.optimize import curve_fit
import matplotlib.patches as patches
from cycler import cycler

class VoronoiSimulation:
    def __init__(self, num_points, canvas_size, num_bins, num_simulations, max_cell_size_1D, max_cell_size_2D):
        self.num_points = num_points
        self.canvas_size = canvas_size
        self.num_bins = num_bins
        self.num_simulations = num_simulations
        self.max_cell_size_1D = max_cell_size_1D
        self.max_cell_size_2D = max_cell_size_2D
        self.points_1D = np.zeros((num_simulations, num_points))
        self.points_2D = np.zeros((num_simulations, num_points, 2))
        self.cell_sizes_1D = []
        self.cell_sizes_2D = []
        self.bin_edges_1D = np.linspace(0, max_cell_size_1D, num_bins + 1)
        self.bin_edges_2D = np.linspace(0, max_cell_size_2D, num_bins + 1)

    def generate_points(self):
        for i in range(self.num_simulations):
            np.random.seed(i)
            self.points_1D[i] = np.random.uniform(0, self.canvas_size, self.num_points)
            self.points_2D[i] = np.random.uniform(0, self.canvas_size, (self.num_points, 2))

    def compute_1D_voronoi(self):
        for i in range(self.num_simulations):
            points_1D = np.sort(self.points_1D[i])
            intervals = np.diff(points_1D)
            self.cell_sizes_1D.append(intervals)

    def compute_2D_voronoi(self):
        for i in range(self.num_simulations):
            vor = Voronoi(self.points_2D[i])
            regions = [vor.regions[j] for j in vor.point_region if -1 not in vor.regions[j]]
            sizes = [self.compute_polygon_area(vor.vertices[region]) for region in regions]
            self.cell_sizes_2D.append(sizes)

    # Define plot formatter:
    @staticmethod
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

    @staticmethod
    def compute_polygon_area(vertices):
        return 0.5 * np.abs(np.dot(vertices[:, 0], np.roll(vertices[:, 1], 1)) -
                            np.dot(vertices[:, 1], np.roll(vertices[:, 0], 1)))

    def eliminate_outliers(self):
        self.max_actual_cell_size_1D = np.mean([np.max(sizes) for sizes in self.cell_sizes_1D])
        self.max_actual_cell_size_2D = np.mean([np.max(sizes) for sizes in self.cell_sizes_2D])
        
        self.cell_sizes_1D = [sizes[sizes <= self.max_cell_size_1D] for sizes in map(np.array, self.cell_sizes_1D)]
        self.cell_sizes_2D = [sizes[sizes <= self.max_cell_size_2D] for sizes in map(np.array, self.cell_sizes_2D)]

    def aggregate_distributions(self):
        self.hist_1D = np.zeros(self.num_bins)
        self.hist_2D = np.zeros(self.num_bins)
        for sizes in self.cell_sizes_1D:
            hist, _ = np.histogram(sizes, bins=self.bin_edges_1D)
            self.hist_1D += hist
        for sizes in self.cell_sizes_2D:
            hist, _ = np.histogram(sizes, bins=self.bin_edges_2D)
            self.hist_2D += hist
        self.hist_1D /= self.num_simulations
        self.hist_2D /= self.num_simulations

    def normalize_distributions(self):
        self.hist_1D = self.hist_1D / np.sum(self.hist_1D)
        self.hist_2D = self.hist_2D / np.sum(self.hist_2D)

    def fit_distributions(self):
        def func_1D(x, a, b):
            return a * x * np.exp(-b * x)
        
        def func_2D(x, a, b):
            return a * x**2.5 * np.exp(-b * x)

        bin_centers_1D = (self.bin_edges_1D[:-1] + self.bin_edges_1D[1:]) / 2
        bin_centers_2D = (self.bin_edges_2D[:-1] + self.bin_edges_2D[1:]) / 2

        popt_1D, _ = curve_fit(func_1D, bin_centers_1D, self.hist_1D, p0=[1, 1])
        popt_2D, _ = curve_fit(func_2D, bin_centers_2D, self.hist_2D, p0=[1, 1])

        self.scale_1D, self.width_scale_1D = popt_1D
        self.scale_2D, self.width_scale_2D = popt_2D

    def plot_histograms(self):
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))

        bin_centers_1D = (self.bin_edges_1D[:-1] + self.bin_edges_1D[1:]) / 2
        bin_centers_2D = (self.bin_edges_2D[:-1] + self.bin_edges_2D[1:]) / 2
        
        ax1.bar(bin_centers_1D, self.hist_1D, width=np.diff(self.bin_edges_1D), align='center', ec='w')
        ax1.set_title('1D Voronoi Cell Size Distribution')
        ax1.set_xlabel('Cell Size')
        ax1.set_ylabel('Normalized Frequency')

        ax2.bar(bin_centers_2D, self.hist_2D, width=np.diff(self.bin_edges_2D), align='center', ec='w')
        ax2.set_title('2D Voronoi Cell Size Distribution')
        ax2.set_xlabel('Cell Size')
        ax2.set_ylabel('Normalized Frequency')

        # Fit and plot the expected distributions using actual max cell sizes
        x_1D = np.linspace(0, self.max_cell_size_1D, 100)
        y_1D = self.scale_1D * x_1D * np.exp(-self.width_scale_1D * x_1D)
        ax1.plot(x_1D, y_1D / np.max(y_1D) * np.max(self.hist_1D), 'k-', lw=2, label='x * exp(-x)')
        ax1.legend()

        x_2D = np.linspace(0, self.max_cell_size_2D, 100)
        y_2D = self.scale_2D * x_2D**2.5 * np.exp(-self.width_scale_2D * x_2D)
        ax2.plot(x_2D, y_2D / np.max(y_2D) * np.max(self.hist_2D), 'k-', lw=2, label='x^(5/2) * exp(-x)')
        ax2.legend()

        plt.tight_layout()
        plt.ticklabel_format(axis='both', style='sci', scilimits=(-2,3), useMathText=True)
        self.plot_format(plt.gca())
        plt.savefig('week2_RandomWalk/ex4_Voronoi/output/whut_hist.png', dpi=500, bbox_inches='tight', pad_inches=0, facecolor='#C0C0C0')
        plt.show()

    def plot_voronoi_diagram(self):
        points = self.points_2D[1]
        vor = Voronoi(points)
        fig, ax = plt.subplots(figsize=(6, 6))
        voronoi_plot_2d(vor, ax=ax, show_vertices=False, line_colors='orange', line_width=2)

        # Color the regions with distinct colors
        regions, vertices = vor.regions, vor.vertices
        cmap = plt.cm.get_cmap('tab20')
        for region_index, region in enumerate(regions):
            if not -1 in region:
                polygon = vertices[region]
                ax.fill(*zip(*polygon), color=cmap(region_index % 20), alpha=0.4)

        ax.set_title('2D Voronoi Diagram')
        plt.ticklabel_format(axis='both', style='sci', scilimits=(-2,3), useMathText=True)
        plt.savefig('week2_RandomWalk/ex4_Voronoi/output/whut_2d_diagram.png', dpi=500, bbox_inches='tight', pad_inches=0, facecolor='#C0C0C0')
        plt.show()

if __name__ == "__main__":
    num_points = 100
    canvas_size = 100
    num_bins = 50
    num_simulations = 100
    max_cell_size_1D = 7
    max_cell_size_2D = 400

    simulation = VoronoiSimulation(num_points, canvas_size, num_bins, num_simulations, max_cell_size_1D, max_cell_size_2D)

    simulation.generate_points()
    simulation.compute_1D_voronoi()
    simulation.compute_2D_voronoi()
    simulation.eliminate_outliers()
    simulation.aggregate_distributions()
    simulation.normalize_distributions()

    # Fit the distributions
    simulation.fit_distributions()

    # Plot histograms with fitted lines
    simulation.plot_histograms()
    simulation.plot_histograms()

    # Plot Voronoi diagram for a single 2D simulation
    simulation.plot_voronoi_diagram()