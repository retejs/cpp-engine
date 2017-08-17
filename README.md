D3 Node Engine
====
#### Cross-platform implementation of the Engine for [D3 Node Editor](https://github.com/Ni55aN/D3-Node-Editor)

### Usage

Library is header-only, so it's enought to include "D3NE.h"
```cpp
#include "D3NE.h"

using namespace D3NE;
```
Define workers
```cpp
Workers workers;

workers.put("number", [](Node node, InputData inputs, OutputData &outputs) {
    auto num = node.data.get<picojson::object>()["num"].get<double>();
    outputs[0].reset(new int(num));
});

workers.put("add", [](D3NE::Node node, InputData inputs, OutputData &outputs) {
    auto inp1 = inputs[0][0].get<int>();
    auto inp2 = inputs[1][0].get<int>();

    outputs[0].reset(new int(inp1 + inp2));
    printf("Add result: %s\n", to_string(inp1 + inp2).c_str());
});
```

Declare Engine and pass [JSON string](https://github.com/Ni55aN/D3-Node-Engine/tree/master/src) for processing
```cpp
Engine *engine = new Engine("demo@0.1.0", workers);

string json = ...;

JSON data;
data.from(json);

engine->process(data);
```

License
----
MIT