// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/2 20:18
// Description:
//

#pragma once

#include <vector>
#include "document.h"

namespace star {

struct AddDocument {
  Document vec;
  // 其他扩展参数
};

class AddRequest {
 public:
  std::vector<AddDocument> vecs;

};

}  // namespace star
