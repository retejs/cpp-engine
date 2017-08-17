#pragma once

#include <vector>

namespace D3NE {

class Input;
typedef std::vector<Input> Inputs;

struct InputConnection {
  long node;
  int output;
};

class Input {
public:
  std::vector<InputConnection> connections;
};
}