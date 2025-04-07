// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/23 22:40
// Description:
//

#include "kd_tree_index.h"

namespace star {

KDTreeIndex::KDTreeIndex(int dimension) : dimension_(dimension), root_(nullptr) {}

double KDTreeIndex::Distance(const std::vector<double>& a, const std::vector<double>& b) const {
    double dist = 0.0;
    for (size_t i = 0; i < dimension_; ++i) {
        dist += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return dist;
}

std::unique_ptr<KDTreeIndex::Node> KDTreeIndex::InsertHelper(KDTreeIndex::Node* node, const std::vector<double>& point, int depth) {
    if (!node) {
        return std::make_unique<Node>(point, point.size());
    }

    int axis = depth % dimension_;
    if (point[axis] < node->coordinates[axis]) {
        node->left = InsertHelper(node->left.get(), point, depth + 1);
    } else {
        node->right = InsertHelper(node->right.get(), point, depth + 1);
    }

    return std::unique_ptr<Node>(node);
}

std::optional<KDTreeIndex::Node*> KDTreeIndex::FindHelper(KDTreeIndex::Node* node, int id) const {
    if (!node) {
        return std::nullopt;
    }

    if (node->id == id) {
        return node;
    }

    auto left_result = FindHelper(node->left.get(), id);
    if (left_result) {
        return left_result;
    }

    return FindHelper(node->right.get(), id);
}

KDTreeIndex::Node* KDTreeIndex::NearestNeighborHelper(KDTreeIndex::Node* node, const std::vector<double>& query, KDTreeIndex::Node* best_node, double& best_dist, int depth) const {
    if (!node) {
        return best_node;
    }

    int axis = depth % dimension_;
    double dist = (query, node->coordinates);

    if (dist < best_dist) {
        best_dist = dist;
        best_node = node;
    }

    KDTreeIndex::Node* next_branch = nullptr;
    if (query[axis] < node->coordinates[axis]) {
        next_branch = NearestNeighborHelper(node->left.get(), query, best_node, best_dist, depth + 1);
    } else {
        next_branch = NearestNeighborHelper(node->right.get(), query, best_node, best_dist, depth + 1);
    }

    if (std::abs(query[axis] - node->coordinates[axis]) < best_dist) {
        if (query[axis] < node->coordinates[axis]) {
            NearestNeighborHelper(node->right.get(), query, best_node, best_dist, depth + 1);
        } else {
            NearestNeighborHelper(node->left.get(), query, best_node, best_dist, depth + 1);
        }
    }

    return best_node;
}

SearchResponse KDTreeIndex::Search(const SearchRequest& request) const {
    SearchResponse response;
    if (!root_) {
        return response;
    }

    double best_dist = std::numeric_limits<double>::max();
    Node* best_node = NearestNeighborHelper(root_.get(), request.query_vector, nullptr, best_dist, 0);
    if (best_node) {
        response.id = best_node->id;
        response.distance = best_dist;
    }
    return response;
}

Status KDTreeIndex::Add(const AddRequest& request) {
    root_ = InsertHelper(root_.get(), request.vector, 0);
    return OkStatus();
}

Status KDTreeIndex::Delete(const DeleteRequest& request) {
    auto node_to_delete = FindHelper(root_.get(), request.id);
    if (!node_to_delete) {
        return {-1, "Vector with ID not found"};
    }

    // Simple deletion logic: set the node to nullptr (not efficient for large trees)
    if (node_to_delete->left) {
        node_to_delete->left.reset();
    }
    if (node_to_delete->right) {
        node_to_delete->right.reset();
    }
    return OkStatus();
}

}  // namespace star
