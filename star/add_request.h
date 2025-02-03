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
  bool operator<(const AddDocument& document) const {
    if (this->vec.x.size() != document.vec.x.size()) {
      return this->vec.x.size() < document.vec.x.size();
    }
    for (size_t i = 0; i < this->vec.x.size(); ++i) {
      if (this->vec.x[i] != document.vec.x[i]) {
        return this->vec.x[i] < document.vec.x[i];
      }
    }
    return true;
  }

  Document vec;
  // 其他扩展参数
};

class AddRequest {
 public:
  std::vector<AddDocument> vecs;

};

}  // namespace star
