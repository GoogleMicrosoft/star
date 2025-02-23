// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/3 21:19
// Description:
//

#include "star/impl/flat/flat_index.h"
#include "star/distance/euclidean_distance.h"

namespace star {

/// 检索接口
SearchResponse FlatIndex::Search(const SearchRequest& request) const {
  SearchResponse response;
  std::vector<std::pair<const AddDocument*, float>> candidate_vectors;
  for (const auto& kVector: vectors_) {
    float distance = EuclideanDistance(kVector.vec.x, request.x);
    candidate_vectors.emplace_back(&kVector, distance);
  }
  if (request.k < candidate_vectors.size()) {
    std::sort(candidate_vectors.begin(),
              candidate_vectors.end(),
              [](const std::pair<const AddDocument*, float>& a,
                 const std::pair<const AddDocument*, float>& b) { return a.second > b.second; });
    candidate_vectors.resize(request.k);
  }
  for (const auto& item: candidate_vectors) {
    ResponseDocument document;
    document.document = item.first->vec;
    document.similarity = item.second;
    response.vecs.emplace_back(std::move(document));
  }
  return response;
}

/// 添加向量接口
Status FlatIndex::Add(const AddRequest& request) {
  auto remaining_capacity = vectors_.size() - vector_count_limit_;
  if (vectors_.size() - vector_count_limit_ < request.vecs.size()) {
    return {-1, "remaining capacity " + std::to_string(remaining_capacity) + ", can not add"};
  }
  for (const auto& kVec: request.vecs) {
    vectors_.emplace(kVec);
  }
  return OkStatus();
}

/// 删除向量接口
Status FlatIndex::Delete(const DeleteRequest& request) {
  return OkStatus();
}

}  // namespace star
