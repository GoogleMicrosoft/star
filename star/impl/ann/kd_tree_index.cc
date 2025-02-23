// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/23 22:40
// Description:
//

#include "kd_tree_index.h"

namespace star {

[[nodiscard]] SearchResponse
KDTreeIndex::Search(const SearchRequest &request) const {
  SearchResponse response;
  const std::vector<float> &query_vector = request.x;
  size_t k = request.k;

  // 使用优先队列来存储最近的k个节点
  auto cmp = [&query_vector](const KDNode *a, const KDNode *b) {
    return EuclideanDistance(query_vector, a->vector) >
           EuclideanDistance(query_vector, b->vector);
  };
  std::priority_queue<const KDNode *, std::vector<const KDNode *>,
                      decltype(cmp)>
      pq(cmp);

  // 从根节点开始搜索
  SearchKDTree(root_.get(), query_vector, k, &pq);

  // 将优先队列中的节点添加到响应中
  while (!pq.empty()) {
    const KDNode *node = pq.top();
    pq.pop();
    ResponseDocument document;
    document.document.x = node->vector;
    document.similarity = EuclideanDistance(query_vector, node->vector);
    response.vecs.emplace_back(document);
  }

  return response;
}

} // namespace star
