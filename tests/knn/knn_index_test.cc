// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/2 21:10
// Description:
//

#include "gtest/gtest.h"
#include "star/index.h"
#include "star/impl/brute_force/brute_force_index.h"

#include <random>

namespace star {

std::vector<float> GenerateRandomVector(size_t dimension) {
  std::random_device rd;  // 用于生成种子
  std::mt19937 gen(rd()); // 使用Mersenne Twister引擎
  // 定义浮点数分布范围
  std::uniform_real_distribution<float> dis(-10.0, 10.0); // 生成范围在-10.0到10.0之间的浮点数

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
    // 在每个测试之前设置
    index = new BruteForceIndex();
  }

  void TearDown() override {
    // 在每个测试之后清理
    delete index;
  }

  Index* index = nullptr;
};

TEST_F(SimpleIndexTest, SearchTest) {
  SearchRequest request;
  request.x = GenerateRandomVector(10);
  request.k = 5;
  SearchResponse response = index->Search(request);
  EXPECT_LE(response.vecs.size(), request.k);
}

TEST_F(SimpleIndexTest, AddTest) {
  AddRequest request;
  Status status = index->Add(request);
  EXPECT_TRUE(status.Ok());
}

TEST_F(SimpleIndexTest, DeleteTest) {
  DeleteRequest request;
  Status status = index->Delete(request);
  EXPECT_TRUE(status.Ok());
}

}  // namespace star
