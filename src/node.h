#pragma once

#include <map>
#include <memory>
#include <typeinfo>
#include "input.h"
#include "output.h"
#include "picojson.h"

namespace D3NE {

class Node;
typedef std::map<long, Node> Nodes;
class IOData : public std::shared_ptr<void> {
  const std::type_info *ti;

public:
  template <typename T> void reset(T *ptr) {
    std::shared_ptr<void>::reset(ptr);
    ti = &typeid(T);
  }

  template <typename T> bool isType() { return typeid(T) == *ti; }
  template <typename T> T get() {
    if (std::shared_ptr<void>::get() == NULL)
      throw std::invalid_argument("Pointer is NULL");

    return *(T *)std::shared_ptr<void>::get();
  }
};
typedef std::vector<IOData> OutputData;
typedef std::vector<std::vector<IOData>> InputData;

class Node {

public:
  picojson::value data;
  long id;
  long group;
  double position[2];
  std::string title;
  Inputs inputs;
  Outputs outputs;

  Node() {}
};
}