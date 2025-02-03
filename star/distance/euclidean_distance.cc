// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/3 21:39
// Description:
//

#include "star/distance/euclidean_distance.h"

#include <cmath>

namespace star {

float EuclideanDistance(const std::vector<float>& a, const std::vector<float>& b) {
  if (a.size() != b.size()) {
    return 0.0;
  }
  float sum = 0.0;
  for (size_t i = 0; i < a.size(); ++i) {
    float diff = a[i] - b[i];
    sum += diff * diff;
  }
  return std::sqrt(sum);
}

}  // namespace star
