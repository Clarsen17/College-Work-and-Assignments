#ifndef NIU_CSCI340_CONFIG_H
#define NIU_CSCI340_CONFIG_H

#include <vector>
#include <limits>

// Additional data structure for efficient graph storage.
struct StudentExtra {
    std::vector<std::vector<double>> adj_matrix; // Weighted adjacency matrix
};

#endif // NIU_CSCI340_CONFIG_H

