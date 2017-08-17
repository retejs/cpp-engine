#pragma once

#include <algorithm>
#include <string.h>
#include "json.h"
#include "workers.h"

namespace D3NE {

class Engine {
public:
  std::string id;
  Workers workers;
  Nodes nodes;
  std::map<long, OutputData> nodesOutput;

  Engine(std::string id, Workers workers) {
    this->id = id;
    this->workers = workers;
  }

  OutputData backProcess(Node node) {

    if (nodesOutput.count(node.id) == 1)
      return nodesOutput[node.id];

    InputData inputData;

    for (auto const &input : node.inputs) {
      OutputData outData;
      for (auto const &c : input.connections) {
        OutputData out = this->backProcess(this->nodes[c.node]);
        IOData val = out[c.output];
        outData.push_back(val);
      }
      inputData.push_back(outData);
    }

    std::string key = node.title;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    nodesOutput[node.id] = OutputData(node.outputs.size());
    std::transform(node.outputs.begin(), node.outputs.end(),
                   nodesOutput[node.id].begin(),
                   [](const Output &val) { return IOData(); });

    this->workers.call(key, node, inputData, nodesOutput[node.id]);
    return nodesOutput[node.id];
  }

  void forwardProcess(Node node) {

    for (auto const &output : node.outputs)
      for (auto const &c : output.connections) {
        this->backProcess(this->nodes[c.node]);
        this->forwardProcess(this->nodes[c.node]);
      }
  }

  void process(JSON data) {

    this->nodes.clear();
    this->nodes = data.nodes;

    // if (startNode == NULL)
    Node startNode = this->nodes.begin()->second;

    this->backProcess(startNode);
    this->forwardProcess(startNode);
  }
};
}
