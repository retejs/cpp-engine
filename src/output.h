#pragma once

#include <vector>

namespace D3NE {

class Output;
typedef std::vector<Output> Outputs;

struct OutputConnection {
  long node;
  int input;
};

class Output {
public:
  std::vector<OutputConnection> connections;
};
}