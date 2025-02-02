// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@gmail.com
// Date: 2025/1/31 00:12
// Description:
//

#pragma once

#include "search_request.h"
#include "search_response.h"
#include "status.h"
#include "add_request.h"
#include "delete_request.h"

namespace star {

/// 索引基类定义
class Index {
 public:
  /// 检索接口
  virtual SearchResponse Search(const SearchRequest& request) const = 0;

  /// 添加向量接口
  virtual Status Add(const AddRequest& request) = 0;

  /// 删除向量接口
  virtual Status Delete(const DeleteRequest& request) = 0;
};
}  // namespace star
