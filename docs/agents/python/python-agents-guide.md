# A guide to making sc-agents in Python

## Used libraries

- [py-sc-client](https://github.com/ostis-ai/py-sc-client) - The python implementation of the client for communication with the OSTIS Technology web-oriented platform. This module is compatible with 0.7.0 version of sc-machine.
- [py-sc-kpm](https://github.com/ostis-ai/py-sc-kpm) - The library contains the python implementation of useful classes and functions to work with the sc-memory.

## Making a Python agent

Making agents requires:

- Agent module
- The agents themselves

### Making the agents module

1. Create a subdirectory *{name}_module* in the [modules](https://github.com/ostis-apps/ostis-geography/tree/main/problem-solver/py/modules) directory.

2. Create the file *{Name}Module.py* in the created folder.

3. Type in it the following code:

```py
from sc_kpm import ScModule
from .Name1Agent import Name1Agent
from .Name2Agent import Name2Agent


class NameModule(ScModule):
    def __init__(self):
        super().__init__(
          # your agents
          Name1Agent(), 
          Name2Agent(),
        )
```

### Agents creation

1. Create the agent files: *{Name1}Agent.py*, *{Name2}Agent.py*.

2. Type the following code into them:

```py
from sc_client import client
from sc_client.models import scAddr
from sc_kpm import ScAgentClassic, ScResult, ScKeynodes


class NameAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("name") # your agent name
        self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        If not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK

        # Write your agent logic code here

        return status
```

3. Let's start writing the agent logic.

## Connecting the agents

In order to connect the agents, you have to put them into [server.py](https://github.com/ostis-apps/ostis-geography/blob/main/problem-solver/py/server.py):

1. Let's import the agents:

```py
From modules.name_module.NameModule import Name1Agent, Name2Agent
```

2. Insert the agents into the main function:

```py
def main(args: dict):
    server = ScServer(f "ws://{args[SC_SERVER_HOST]}:{args[SC_SERVER_PORT]}")

    With server.connect():
        modules = [
            ...
            # your agents
            Name1Agent(),
            Name2Agent(),
        ]
        server.add_modules(*modules)

        With server.register_modules():
            server.wait_for_sigint()
            server.remove_modules(*modules)
```

## Testing agents

1. Run sc-server and sc-web (see [readme](https://github.com/ostis-apps/ostis-geography/blob/main/README.md)).

2. Go to the folder [problem-solver/py](https://github.com/ostis-apps/ostis-geography/blob/main/problem-solver/py/).

3. Run [server.py](https://github.com/ostis-apps/ostis-geography/blob/main/problem-solver/py/server.py) with the following command:

```sh
python3 ./server.py
```

4. Check if the agents are working properly.
