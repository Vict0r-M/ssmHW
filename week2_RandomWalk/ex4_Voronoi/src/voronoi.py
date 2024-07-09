import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import Voronoi, voronoi_plot_2d

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

    @staticmethod
    def compute_polygon_area(vertices):
        return 0.5 * np.abs(np.dot(vertices[:, 0], np.roll(vertices[:, 1], 1)) -
                            np.dot(vertices[:, 1], np.roll(vertices[:, 0], 1)))

    def eliminate_outliers(self):
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

    def plot_histograms(self):
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))

        bin_centers_1D = (self.bin_edges_1D[:-1] + self.bin_edges_1D[1:]) / 2
        bin_centers_2D = (self.bin_edges_2D[:-1] + self.bin_edges_2D[1:]) / 2
        
        ax1.bar(bin_centers_1D, self.hist_1D, width=np.diff(self.bin_edges_1D), align='center')
        ax1.set_title('1D Voronoi Cell Size Distribution')
        ax1.set_xlabel('Cell Size')
        ax1.set_ylabel('Normalized Frequency')

        ax2.bar(bin_centers_2D, self.hist_2D, width=np.diff(self.bin_edges_2D), align='center')
        ax2.set_title('2D Voronoi Cell Size Distribution')
        ax2.set_xlabel('Cell Size')
        ax2.set_ylabel('Normalized Frequency')

        # Fit and plot the expected distributions
        x = np.linspace(0, self.max_cell_size_1D, 100)
        y_1D = x * np.exp(-x)
        ax1.plot(x, y_1D / y_1D.sum(), 'k-', lw=2, label='x * exp(-x)')
        ax1.legend()

        x = np.linspace(0, self.max_cell_size_2D, 100)
        y_2D = x**2.5 * np.exp(-x)
        ax2.plot(x, y_2D / y_2D.sum(), 'k-', lw=2, label='x^(5/2) * exp(-x)')
        ax2.legend()

        plt.tight_layout()
        plt.show()

    def plot_voronoi_diagram(self):
        points = self.points_2D[0]
        vor = Voronoi(points)
        fig, ax = plt.subplots(figsize=(6, 6))
        voronoi_plot_2d(vor, ax=ax, show_vertices=False, line_colors='orange', line_width=2)

        # Color the regions
        regions = [vor.regions[i] for i in vor.point_region if -1 not in vor.regions[i]]
        for region in regions:
            polygon = [vor.vertices[i] for i in region]
            ax.fill(*zip(*polygon), alpha=0.4)

        ax.set_title('2D Voronoi Diagram')
        plt.show()


num_points = 100
canvas_size = 10
num_bins = 50
num_simulations = 100
max_cell_size_1D = 5
max_cell_size_2D = 1

simulation = VoronoiSimulation(num_points, canvas_size, num_bins, num_simulations, max_cell_size_1D, max_cell_size_2D)

simulation.generate_points()
simulation.compute_1D_voronoi()
simulation.compute_2D_voronoi()
simulation.eliminate_outliers()
simulation.aggregate_distributions()
simulation.normalize_distributions()

# Plot histograms
simulation.plot_histograms()

# Plot Voronoi diagram for a single 2D simulation
simulation.plot_voronoi_diagram()