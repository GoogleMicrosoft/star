// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/2 21:10
// Description:
//

#include "star/impl/flat/flat_index.h"
#include "star/index_factory.h"
#include "gtest/gtest.h"

#include <random>

namespace star {

std::vector<float> GenerateRandomVector(size_t dimension) {
  std::random_device rd;  // 用于生成种子
  std::mt19937 gen(rd()); // 使用Mersenne Twister引擎
  // 定义浮点数分布范围
  std::uniform_real_distribution<float> dis(
      -10.0, 10.0); // 生成范围在-10.0到10.0之间的浮点数

  std::vector<float> result;
  for (int i = 0; i < dimension; ++i) {
    float random_value = dis(gen);
    result.emplace_back(random_value);
  }
  return result;
}

class SimpleIndexTest : public ::testing::Test {
protected:
  void SetUp() override {
    for (const auto &kItem : index_impl_names) {
      auto index = IndexFactory::GetInstance()->Create(kItem);
      EXPECT_NE(index, nullptr);
      indexes.emplace_back(std::move(index));
    }
  }

  std::vector<std::string> index_impl_names = {"flat", "knn"};
  std::vector<std::unique_ptr<Index>> indexes{};
  size_t vector_dimension = 10;
};

TEST_F(SimpleIndexTest, SearchTest) {
  for (const auto &index : indexes) {
    SearchRequest request;
    request.x = GenerateRandomVector(vector_dimension);
    request.k = 5;
    SearchResponse response = index->Search(request);
    std::cout << "response:" << response.vecs.size() << std::endl;
    EXPECT_LE(response.vecs.size(), request.k);
  }
}

TEST_F(SimpleIndexTest, AddTest) {
  for (const auto &index : indexes) {
    AddRequest request;
    for (size_t i = 0; i < 100; ++i) {
      AddDocument add_document;
      add_document.vec.x = GenerateRandomVector(vector_dimension);
      request.vecs.emplace_back(add_document);
    }
    Status status = index->Add(request);
    EXPECT_TRUE(status.Ok());
  }
}

TEST_F(SimpleIndexTest, DeleteTest) {
  for (const auto &index : indexes) {
    DeleteRequest request;
    // 待删除的是空向量
    Status status = index->Delete(request);
    EXPECT_FALSE(status.Ok());
  }
}

} // namespace star
