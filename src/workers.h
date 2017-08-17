#pragma once

#include <map>
#include <string.h>
#include <node.h>

namespace D3NE {

typedef void (*Worker)(Node node, InputData inputs, OutputData &outputs);

class Workers {
  std::map<std::string, Worker> map;

public:
  Workers() {}

  void put(std::string name, Worker worker) {
    this->map.insert(std::pair<std::string, Worker>(name, worker));
  }

  void call(std::string name, Node n, InputData i, OutputData &o) {
    if (this->map.count(name) == 0)
      throw std::invalid_argument("Worker does not exist");
    this->map[name](n, i, o);
  }
};
}