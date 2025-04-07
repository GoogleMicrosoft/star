// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/23 22:40
// Description:
//

#pragma once

#include <vector>
#include <memory>
#include <cmath>
#include <limits>
#include <optional>

#include "star/index.h"
#include "kd_node.h"

namespace star {

class KDTreeIndex : public Index {
 public:
    explicit KDTreeIndex(int dimension);

    SearchResponse Search(const SearchRequest& request) const override;

    Status Add(const AddRequest& request) override;

    Status Delete(const DeleteRequest& request) override;

 private:
    std::unique_ptr<Node> root_ = nullptr;
    int dimension_ = -1;

    std::unique_ptr<Node> InsertHelper(Node* node, const std::vector<float>& point, int depth);
    std::optional<Node*> FindHelper(Node* node, int id) const;
    Node* NearestNeighborHelper(Node* node, const std::vector<float>& query, Node* best_node, float& best_dist, int depth) const;
    float Distance(const std::vector<float>& a, const std::vector<float>& b) const;
};

}  // namespace star
