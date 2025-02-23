// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/23 20:42
// Description:
//

#pragma once

#include "index.h"

#include <functional>
#include <map>
#include <memory>

namespace star {

class IndexFactory {
public:
  static const IndexFactory *GetInstance();

  std::unique_ptr<Index> Create(const std::string &name) const;
};

} // namespace star
