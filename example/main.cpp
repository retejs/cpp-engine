#include <stdio.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <string>
#include "D3NE.h"

using namespace std;
using namespace D3NE;

int main() {

  Workers workers;

  workers.put("number", [](Node node, InputData inputs, OutputData &outputs) {
    auto num = node.data.get<picojson::object>()["num"].get<double>();
    outputs[0].reset(new int(num));
  });

  workers.put("add", [](Node node, InputData inputs, OutputData &outputs) {
    auto inp1 = inputs[0][0].get<int>();
    auto inp2 = inputs[1][0].get<int>();

    outputs[0].reset(new int(inp1 + inp2));
    printf("Add result %s\n", to_string(inp1 + inp2).c_str());
  });

  Engine *engine = new Engine("demo@0.1.0", workers);

  std::ifstream t("../demo.json");
  std::string json((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());

  JSON data;
  data.from(json);

  engine->process(data);
  return 0;
}