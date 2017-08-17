#pragma once

#include <string.h>
#include <iostream>
#include "node.h"
#include "group.h"
#include "picojson.h"

using namespace std;
namespace pj = picojson;
using pja = pj::array;
using pjo = pj::object;
using pjv = pj::value;
using pjoi = pjo::iterator;
using pjai = pja::iterator;
namespace D3NE {

class JSON {
public:
  string id;
  Nodes nodes;
  Groups groups;

  JSON() {}

  void from(string json) {
    pjv v;
    string err = pj::parse(v, json);
    if (!err.empty()) {
      cerr << err << endl;
      return;
    }

    id = v.get<pjo>()["id"].get<string>();

    nodes.clear();
    auto nodesObj = v.get<pjo>()["nodes"].get<pjo>();
    for (pjoi i = nodesObj.begin(); i != nodesObj.end(); ++i) {
      long id = atol(i->first.c_str());
      pjo obj = i->second.get<pjo>();
      nodes.insert(pair<long, Node>(id, parseNode(id, obj)));
    }

    groups.clear();
    pjo groupsObj = v.get<pjo>()["groups"].get<pjo>();
    for (pjoi i = groupsObj.begin(); i != groupsObj.end(); ++i) {
      long id = atol(i->first.c_str());
      pjo obj = i->second.get<pjo>();
      groups.insert(pair<long, Group>(id, parseGroup(id, obj)));
    }
  }

  Group parseGroup(long id, pjo obj) {
    Group group;
    group.id = id;
    group.title = obj["title"].get<string>();
    auto nodes = obj["nodes"].get<pja>();

    for (pjai i = nodes.begin(); i != nodes.end(); ++i)
      group.nodes.push_back((int)i->get<double>());

    group.minWidth = obj["minWidth"].get<double>();
    group.minHeight = obj["minHeight"].get<double>();

    group.width = obj["width"].get<double>();
    group.height = obj["height"].get<double>();

    pja position = obj["position"].get<pja>();
    group.position[0] = position[0].get<double>();
    group.position[1] = position[1].get<double>();

    return group;
  }

  Node parseNode(long id, pjo obj) {
    Node node;
    node.id = id;
    node.title = obj["title"].get<string>();
    node.data = obj["data"];

    if (obj["group"].is<picojson::null>())
      node.group = 0;
    else
      node.group = atol(obj["group"].get<string>().c_str());

    pja position = obj["position"].get<pja>();
    node.position[0] = position[0].get<double>();
    node.position[1] = position[1].get<double>();

    pja inp = obj["inputs"].get<pja>();
    for (pjai i = inp.begin(); i != inp.end(); ++i)
      node.inputs.push_back(parseInput(i->get<pjo>()));

    pja out = obj["outputs"].get<pja>();
    for (pjai i = out.begin(); i != out.end(); ++i)
      node.outputs.push_back(parseOutput(i->get<pjo>()));
    return node;
  }

  Input parseInput(pjo obj) {
    Input input;
    auto cons = obj["connections"].get<pja>();

    for (pjai i = cons.begin(); i != cons.end(); ++i) {
      auto c = i->get<pjo>();

      InputConnection con = {atol(c["node"].to_str().c_str()),
                             atoi(c["output"].to_str().c_str())};
      input.connections.push_back(con);
    }

    return input;
  }

  Output parseOutput(pjo obj) {
    Output output;
    auto cons = obj["connections"].get<pja>();

    for (pjai i = cons.begin(); i != cons.end(); ++i) {
      auto c = i->get<pjo>();

      OutputConnection con = {atol(c["node"].to_str().c_str()),
                              atoi(c["input"].to_str().c_str())};
      output.connections.push_back(con);
    }

    return output;
  }
};
}