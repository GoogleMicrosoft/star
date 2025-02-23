// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/23 22:40
// Description:
//

#pragma once

#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <queue>
#include <vector>

#include "star/distance/euclidean_distance.h"
#include "star/impl/ann/kd_node.h"
#include "star/index.h"

namespace star {

class KDTreeIndex final : public Index {
 public:
  KDTreeIndex() = default;

  /// 检索接口
  [[nodiscard]] SearchResponse Search(const SearchRequest& request) const override;

  /// 添加向量接口
  Status Add(const AddRequest& request) override {
    for (const auto& vector : request.vecs) {
      // 如果树为空，创建根节点
      if (!root_) {
        root_ = std::make_unique<KDNode>(vector, 0);  // 从第0个维度开始划分
        continue;
      }
      // 否则，将新节点插入到树中
      InsertKDTree(root_.get(), vector);
    }
    return OkStatus();
  }

  /// 删除向量接口
  Status Delete(const DeleteRequest& request) override {
    int id = request.id();

    // 从根节点开始搜索要删除的节点
    DeleteKDTree(root_.get(), id);
    return Status::OK();
  }

 private:
  // 计算两个向量之间的欧几里得距离
  float CalculateDistance(const std::vector<float>& v1, const std::vector<float>& v2) const {
    float distance = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
      distance += (v1[i] - v2[i]) * (v1[i] - v2[i]);
    }
    return std::sqrt(distance);
  }

  // 将新节点插入到KD树中
  void InsertKDTree(KDNode* node, const std::vector<float>& vector) {
    int axis = node->axis;

    // 如果新节点的值小于当前节点，向左子树插入
    if (vector[axis] < node->vector[axis]) {
      if (node->left) {
        InsertKDTree(node->left.get(), vector);
      } else {
        // 如果左子树为空，创建新节点
        node->left = std::make_unique<KDNode>(vector, (axis + 1) % vector.size());
      }
    } else {
      // 否则，向右子树插入
      if (node->right) {
        InsertKDTree(node->right.get(), vector);
      } else {
        // 如果右子树为空，创建新节点
        node->right = std::make_unique<KDNode>(vector, (axis + 1) % vector.size());
      }
    }
  }

  // 在KD树中搜索最近的k个节点
  void SearchKDTree(
      const KDNode* node,
      const std::vector<float>& query_vector,
      size_t k,
      std::priority_queue<const KDNode*,
                          std::vector<const KDNode*>,
                          decltype(std::declval<KDTreeIndex>().CompareDistance)>* pq) const {
    if (!node) {
      return;
    }

    // 将当前节点添加到优先队列中
    pq->push(node);
    if (pq->size() > k) {
      pq->pop();  // 如果队列大小超过k，移除最远的节点
    }

    float threshold = pq->size() == k ? CalculateDistance(query_vector, pq->top()->vector)
                                      : std::numeric_limits<float>::max();
    int axis = node->axis;

    // 决定搜索哪个子树
    bool search_left = query_vector[axis] < node->vector[axis];
    const KDNode* next_node = search_left ? node->left.get() : node->right.get();

    // 递归搜索子树
    SearchKDTree(next_node, query_vector, k, pq);

    // 检查是否需要搜索另一个子树
    float distance_to_split_plane = std::fabs(query_vector[axis] - node->vector[axis]);
    if (distance_to_split_plane < threshold) {
      const KDNode* other_node = search_left ? node->right.get() : node->left.get();
      SearchKDTree(other_node, query_vector, k, pq);
    }
  }

  // 从KD树中删除节点
  void DeleteKDTree(KDNode* node, int id) {
    if (!node) {
      return;
    }

    if (node->id == id) {
      // 找到要删除的节点
      if (node->left && node->right) {
        // 如果节点有两个子节点，用后继节点替换当前节点
        KDNode* successor = FindMinNode(node->right.get(), node->axis);
        node->id = successor->id;
        node->vector = successor->vector;
        DeleteKDTree(node->right.get(),
                     successor->id);  // 从右子树中删除后继节点
      } else if (node->left) {
        // 如果节点只有一个左子节点，用左子节点替换当前节点
        node->id = node->left->id;
        node->vector = node->left->vector;
        node->right = std::move(node->left->right);
        node->left = std::move(node->left->left);
      } else if (node->right) {
        // 如果节点只有一个右子节点，用右子节点替换当前节点
        node->id = node->right->id;
        node->vector = node->right->vector;
        node->left = std::move(node->right->left);
        node->right = std::move(node->right->right);
      } else {
        // 如果节点没有子节点，直接删除
        node = nullptr;
      }
    } else {
      // 递归搜索左右子树
      int axis = node->axis;
      if (id < node->vector[axis]) {
        DeleteKDTree(node->left.get(), id);
      } else {
        DeleteKDTree(node->right.get(), id);
      }
    }
  }

  // 找到指定轴上的最小值节点
  KDNode* FindMinNode(KDNode* node, int axis) {
    if (!node) {
      return nullptr;
    }

    KDNode* min_node = node;
    KDNode* left_min = FindMinNode(node->left.get(), axis);
    KDNode* right_min = FindMinNode(node->right.get(), axis);

    if (left_min && left_min->vector[axis] < min_node->vector[axis]) {
      min_node = left_min;
    }
    if (right_min && right_min->vector[axis] < min_node->vector[axis]) {
      min_node = right_min;
    }

    return min_node;
  }

  std::unique_ptr<KDNode> root_;  // KD树的根节点
};

}  // namespace star
