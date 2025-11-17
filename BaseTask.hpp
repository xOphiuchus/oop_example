#pragma once
#include <nlohmann/json.hpp>

class BaseTask {
public:
  virtual ~BaseTask() = default;
  virtual void display() const = 0;
  virtual nlohmann::json toJson() const = 0;
  virtual void markDone() = 0;
  virtual bool isDone() const = 0;
  virtual int getId() const = 0;
};
