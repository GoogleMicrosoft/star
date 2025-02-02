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

class SearchResponse {
 public:
  std::vector<Document> vecs;  // 返回的多个相似向量
};

}  // namespace star
