// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/23 22:41
// Description:
//

#pragma once

#include <memory>
#include <vector>

namespace star {

struct KDNode {
  //  int id;                        // 向量ID
  std::vector<float> vector;      // 向量数据
  int axis;                       // 当前节点的划分轴
  std::unique_ptr<KDNode> left;   // 左子节点
  std::unique_ptr<KDNode> right;  // 右子节点

  KDNode(const std::vector<float>& vector, int axis)
      : vector(vector), axis(axis), left(nullptr), right(nullptr) {}
};

}  // namespace star
