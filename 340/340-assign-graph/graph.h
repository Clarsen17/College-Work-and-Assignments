#ifndef NIU_CSCI340_GRAPH_H
#define NIU_CSCI340_GRAPH_H

#include "graph.decl.h"
#include "config.h"
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <iostream>

size_t Graph::nvertices() const {
    return vertices.size();
}

size_t Graph::nedges() const {
    return edges.size();
}

std::string Graph::v_label(size_t vertex) const {
    return vertex < vertices.size() ? vertices[vertex] : "";
}

ssize_t Graph::v_index(const std::string &label) const {
    auto it = v_lut.find(label);
    return it != v_lut.end() ? it->second : -1;
}

void Graph::assign(const std::vector<std::string> &new_vertices, const std::vector<GraphEdge> &new_edges) {
    vertices = new_vertices;
    edges = new_edges;
    v_lut.clear();

    // Populate vertex lookup table
    for (size_t i = 0; i < vertices.size(); ++i) {
        v_lut[vertices[i]] = i;
    }

    // Initialize adjacency matrix
    student.adj_matrix.assign(vertices.size(), std::vector<double>(vertices.size(), INFINITY));
    for (const auto &edge : edges) {
        student.adj_matrix[edge.origin][edge.destination] = edge.weight;
    }
}

bool Graph::edge_exists(size_t origin, size_t destination) const {
    return student.adj_matrix[origin][destination] != INFINITY;
}

double Graph::edge_weight(size_t origin, size_t destination) const {
    return student.adj_matrix[origin][destination];
}

std::vector<AdjListEdge> Graph::undirected_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> list;

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (student.adj_matrix[vertex][i] != INFINITY) {
            list.push_back({i, student.adj_matrix[vertex][i]});
        }
        if (student.adj_matrix[i][vertex] != INFINITY && i != vertex) { // Avoid duplicate self-loops
            list.push_back({i, student.adj_matrix[i][vertex]});
        }
    }

    // Sort by vertex label first, then by weight
    std::sort(list.begin(), list.end(), [this](const AdjListEdge &a, const AdjListEdge &b) {
        const std::string &label_a = vertices[a.vertex];
        const std::string &label_b = vertices[b.vertex];
        return label_a < label_b || (label_a == label_b && a.weight < b.weight);
    });

    return list;
}

std::vector<AdjListEdge> Graph::in_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> list;

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (student.adj_matrix[i][vertex] != INFINITY) {
            list.push_back({i, student.adj_matrix[i][vertex]});
        }
    }

    // Sort by vertex label first, then by weight
    std::sort(list.begin(), list.end(), [this](const AdjListEdge &a, const AdjListEdge &b) {
        const std::string &label_a = vertices[a.vertex];
        const std::string &label_b = vertices[b.vertex];
        return label_a < label_b || (label_a == label_b && a.weight < b.weight);
    });

    return list;
}

std::vector<AdjListEdge> Graph::out_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> list;

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (student.adj_matrix[vertex][i] != INFINITY) {
            list.push_back({i, student.adj_matrix[vertex][i]});
        }
    }

    // Sort by vertex label first, then by weight
    std::sort(list.begin(), list.end(), [this](const AdjListEdge &a, const AdjListEdge &b) {
        const std::string &label_a = vertices[a.vertex];
        const std::string &label_b = vertices[b.vertex];
        return label_a < label_b || (label_a == label_b && a.weight < b.weight);
    });

    return list;
}

std::vector<double> Graph::weighted_adjacency_matrix() const {
    std::vector<double> matrix;
    for (const auto &row : student.adj_matrix) {
        matrix.insert(matrix.end(), row.begin(), row.end());
    }
    return matrix;
}

std::vector<bool> Graph::unweighted_adjacency_matrix() const {
    std::vector<bool> matrix;
    for (const auto &row : student.adj_matrix) {
        for (double weight : row) {
            matrix.push_back(weight != INFINITY);
        }
    }
    return matrix;
}

template <typename FN>
void Graph::depth_first(size_t start, FN visitfn, bool connected_only) {
    std::vector<bool> visited(vertices.size(), false);
    std::stack<size_t> s;
    s.push(start);

    while (!s.empty()) {
        size_t current = s.top();
        s.pop();

        if (visited[current]) continue;
        visitfn(current);
        visited[current] = true;

        auto neighbors = out_adjacency_list(current);
        std::sort(neighbors.rbegin(), neighbors.rend(), [](const AdjListEdge &a, const AdjListEdge &b) {
            return a.vertex < b.vertex;
        });

        for (const auto &adj : neighbors) {
            if (!visited[adj.vertex]) s.push(adj.vertex);
        }
    }

    if (!connected_only) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (!visited[i]) depth_first(i, visitfn, true);
        }
    }
}

template <typename FN>
void Graph::breadth_first(size_t start, FN visitfn, bool connected_only) {
    std::vector<bool> visited(vertices.size(), false);
    std::queue<size_t> q;
    q.push(start);

    while (!q.empty()) {
        size_t current = q.front();
        q.pop();

        if (visited[current]) continue;
        visitfn(current);
        visited[current] = true;

        auto neighbors = out_adjacency_list(current);
        std::sort(neighbors.begin(), neighbors.end(), [](const AdjListEdge &a, const AdjListEdge &b) {
            return a.vertex < b.vertex;
        });

        for (const auto &adj : neighbors) {
            if (!visited[adj.vertex]) q.push(adj.vertex);
        }
    }

    if (!connected_only) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (!visited[i]) breadth_first(i, visitfn, true);
        }
    }
}

std::vector<size_t> Graph::toposort() const {
    std::vector<size_t> result, in_degree(vertices.size(), 0);

    for (const auto &edge : edges) {
        in_degree[edge.destination]++;
    }

    std::queue<size_t> q;
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (in_degree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        size_t current = q.front();
        q.pop();
        result.push_back(current);

        for (const auto &adj : out_adjacency_list(current)) {
            if (--in_degree[adj.vertex] == 0) q.push(adj.vertex);
        }
    }

    return result.size() == vertices.size() ? result : std::vector<size_t>();
}

std::vector<dijkstra_row> Graph::dijkstra(size_t start) const {
    if (std::any_of(edges.begin(), edges.end(), [](const GraphEdge &e) { return e.weight < 0; })) {
        std::cout << "Error: Dijkstra's algorithm does not support graphs with negative edge weights.\n";
        return {};
    }

    std::vector<dijkstra_row> table(vertices.size(), {0, false, INFINITY, -1});
    table[start] = {start, false, 0, -1};
    auto compare = [&table](size_t lhs, size_t rhs) { return table[lhs].shortest_known > table[rhs].shortest_known; };
    std::priority_queue<size_t, std::vector<size_t>, decltype(compare)> pq(compare);
    pq.push(start);

    while (!pq.empty()) {
        size_t current = pq.top();
        pq.pop();

        if (table[current].visited) continue;
        table[current].visited = true;

        for (const auto &adj : out_adjacency_list(current)) {
            double new_distance = table[current].shortest_known + adj.weight;
            if (new_distance < table[adj.vertex].shortest_known) {
                table[adj.vertex] = {adj.vertex, false, new_distance, static_cast<ssize_t>(current)};
                pq.push(adj.vertex);
            }
        }
    }

    return table;
}

#endif // NIU_CSCI340_GRAPH_H

