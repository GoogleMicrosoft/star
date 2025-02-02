// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/2 20:20
// Description:
//

#pragma once

#include <vector>

namespace star {

struct Document {
  std::vector<float> x;  // 返回的相似向量
  float similarity;      // 和目标向量的相似度
  // 其他扩展参数
};

}  // namespace star
