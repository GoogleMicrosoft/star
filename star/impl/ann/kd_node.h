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

struct Node {
  std::vector<double> coordinates;
  int id;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;

  Node(const std::vector<double>& coords, int id)
      : coordinates(coords), id(id), left(nullptr), right(nullptr) {}
};

}  // namespace star
