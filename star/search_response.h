// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/2 20:14
// Description:
//

#pragma once

#include <vector>
#include "document.h"

namespace star {

struct ResponseDocument {
  Document document;
  float similarity = 0.0;      // 和目标向量的相似度
};

class SearchResponse {
 public:
  std::vector<ResponseDocument> vecs;  // 返回的多个相似向量
};

}  // namespace star
