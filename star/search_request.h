// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/2 20:13
// Description:
//

#include <vector>

namespace star {

class SearchRequest {
 public:
  std::vector<float> x;  // 输入的目标向量
  int k;                 // 期望返回k个相似向量
};

} // namespace star
