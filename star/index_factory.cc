// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/23 20:42
// Description:
//

#include "index_factory.h"
#include "impl/flat/flat_index.h"

namespace star {

const IndexFactory *IndexFactory::GetInstance() {
  static IndexFactory factory;
  return &factory;
}

std::unique_ptr<Index> IndexFactory::Create(const std::string &name) const {
  if (name == "flat") {
    return std::make_unique<FlatIndex>();
  }
  if (name == "knn") {
    return std::make_unique<KnnIndex>()
  }
  return nullptr;
}

} // namespace star
