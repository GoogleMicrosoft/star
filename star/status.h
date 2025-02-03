// -*- coding: utf-8-unix; -*-
// Copyright (c) 2025
//
// Author: 2450866102@qq.com
// Date: 2025/2/2 20:25
// Description:
//

#pragma once

#include <string>

namespace star {

class Status {
 public:
  Status(int code, std::string message) : status_code_(code), message_(std::move(message)) {}

  int Code() const {
    return status_code_;
  }

  std::string Message() const {
    return message_;
  }

  bool Ok() const {
    return status_code_ == 0;
  }

 private:
  int status_code_ = 0;
  std::string message_;
  // 其他扩展参数
};

inline Status OkStatus() {
  return {0, ""};
}

}  // namespace star
