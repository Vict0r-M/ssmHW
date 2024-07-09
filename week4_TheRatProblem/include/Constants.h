#pragma once

// Type definition for real numbers
typedef double real;

// Simulation parameters
const real PROB_SPONTANEOUS = 0.01; // Probability of spontaneous aggression
const int T_MAX = 100;             // Maximum number of simulation cycles
const real L = 1.0;                // Side length of the area for continuous model
const real R_MIN = 0.0001;         // Minimum perception radius
const real R_MAX = 0.035;          // Maximum perception radius
const real R_STEP = 0.001;         // Step size for varying the perception radius

// Discrete model specific constants
const int SIZE = 250;              // Size of the grid for the discrete model
const int NRAT = 100000;           // Number of rats
const int CALM = 0;                // State representing a calm rat
const int AGGRESSIVE = 1;          // State representing an aggressive rat
const int EMPTY = -1;              // State representing an empty cell