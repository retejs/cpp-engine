#pragma once

namespace D3NE {

class Group;
typedef std::map<long, Group> Groups;

class Group {
public:
  long id;
  std::vector<long> nodes;
  double minWidth, minHeight;
  double position[2];
  std::string title;
  double width, height;
};
}