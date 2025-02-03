// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/3 21:19
// Description:
//

#pragma once

#include "star/index.h"
#include <set>

namespace star {

class BruteForceIndex final : public Index {
 public:
  /// 检索接口
  SearchResponse Search(const SearchRequest& request) const override;

  /// 添加向量接口
  /// @returns 如果剩余存储容量小于request中需要添加的向量个数，则返回添加失败
  Status Add(const AddRequest& request) override;

  /// 删除向量接口
  Status Delete(const DeleteRequest& request) override;

 private:
  // 暴力检索向量索引实现，将所有向量存储中同一个set中，只用做小规模向量正确性验证
  std::set<AddDocument> vectors_;
  // 存储的向量个数限制
  size_t vector_count_limit_ = 10000;
};

}  // namespace star
