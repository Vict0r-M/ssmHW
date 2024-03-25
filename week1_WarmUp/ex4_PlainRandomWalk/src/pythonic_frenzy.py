import numpy as np
import os
import argparse

def initialize_seed():
    np.random.seed()

def simulate_1d_walks(steps, num_simulations, output_path):
    steps_array = np.random.choice([-1, 1], size=(num_simulations, steps))
    final_positions = steps_array.cumsum(axis=1)[:, -1]
    np.savetxt(output_path, final_positions, fmt='%d')

def simulate_2d_walks(max_steps, num_simulations, directions, output_path):
    all_steps = np.random.choice(len(directions), size=(num_simulations, max_steps))
    walks = directions[all_steps]  # Shape: num_simulations x max_steps x 2

    # Cumulative sum to get positions at each step
    cumulative_walks = walks.cumsum(axis=1)
    squared_distances = (cumulative_walks ** 2).sum(axis=2)  # Squared distances from (0,0)

    avg_squared_distances = [np.mean(squared_distances[:, step]) for step in range(max_steps)]
    
    with open(output_path, "w") as file:
        for step, avg_dist in enumerate(avg_squared_distances, start=1):
            file.write(f"{step}, {avg_dist}\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Run random walk simulations.')
    parser.add_argument('--steps', type=int, help='Number of steps for the 1D simulations', required=True)
    parser.add_argument('--num_1Dsimulations', type=int, help='Number of 1D simulations', required=True)
    parser.add_argument('--max_steps', type=int, help='Max number of steps for the 2D simulations', required=True)
    parser.add_argument('--num_2Dsimulations', type=int, help='Number of 2D simulations', required=True)
    
    args = parser.parse_args()
    
    os.makedirs("output", exist_ok=True)
    initialize_seed()

    simulate_1d_walks(args.steps, args.num_1Dsimulations, "week1_WarmUp/ex4_PlainRandomWalk/output/1d_final_positions_python.txt")
    print("1D simulations completed.")

    directions_4_main_halt = np.array([[0, 1], [1, 0], [0, -1], [-1, 0], [0, 0]])
    directions_4_diag = np.array([[1, 1], [1, -1], [-1, -1], [-1, 1]])
    directions_8 = np.array([[0, 1], [1, 0], [0, -1], [-1, 0], [1, 1], [1, -1], [-1, -1], [-1, 1]])
    directions_8_halt = np.array([[0, 1], [1, 0], [0, -1], [-1, 0], [1, 1], [1, -1], [-1, -1], [-1, 1], [0, 0]])

    directions_sets = [directions_4_main_halt, directions_4_diag, directions_8, directions_8_halt]
    filenames = ["2d_4_main_halt_python.txt", "2d_4_diag_python.txt", "2d_8_directions_python.txt", "2d_8_directions_halt_python.txt"]

    for directions, filename in zip(directions_sets, filenames):
        simulate_2d_walks(args.max_steps, args.num_2Dsimulations, directions, f"week1_WarmUp/ex4_PlainRandomWalk/output/{filename}")
        print(f"2D simulations for {filename} completed.")