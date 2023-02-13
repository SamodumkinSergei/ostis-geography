# Инструкция по написанию sc агентов на Python

## Используемые библиотеки

- [py-sc-client](https://github.com/ostis-ai/py-sc-client) - Реализация на Python клиента для связи с веб-ориентированной платформой технологий OSTIS. Модуль совместим с версией 0.7.0 sc-machine.
- [py-sc-kpm](https://github.com/ostis-ai/py-sc-kpm) - Библиотека содержит Python реализацию полезных классов и функций для работы с sc-памятью.

## Написание агента на Python

Для написания агентов требуется:

- Модуль агентов
- Сами агенты

### Создание модуля агентов

1. Создаем подпапку *{name}_module* в папке [modules](https://github.com/ostis-apps/ostis-geography/tree/main/problem-solver/py/modules).

2. Создаем файл *{Name}Module.py* в созданной папке.

3. Вписываем в него следующий код:

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

### Создание агентов

1. Создаем файлы агентов: *{Name1}Agent.py*, *{Name2}Agent.py*.

2. Вписываем в них следующий код:

```py
from sc_client import client
from sc_client.models import ScAddr
from sc_kpm import ScAgentClassic, ScResult, ScKeynodes


class NameAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("name") # your agent name
        self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK

        # Write your agent logic code here

        return status
```

3. Приступаем к написанию логики агентов.

## Подключение агентов

Для подключения агентов требуется вписать их в [server.py](https://github.com/ostis-apps/ostis-geography/blob/main/problem-solver/py/server.py):

1. Импортируем агентов:

```py
from modules.name_module.NameModule import Name1Agent, Name2Agent
```

2. Вписываем агентов в функцию main:

```py
def main(args: dict):
    server = ScServer(f"ws://{args[SC_SERVER_HOST]}:{args[SC_SERVER_PORT]}")

    with server.connect():
        modules = [
            ...
            # your agents
            Name1Agent(),
            Name2Agent(),
        ]
        server.add_modules(*modules)

        with server.register_modules():
            server.wait_for_sigint()
            server.remove_modules(*modules)
```

## Тестирование агентов

1. Запускаем sc-server и sc-web (смотреть [readme](https://github.com/ostis-apps/ostis-geography/blob/main/README.md)).

2. Переходим в папку [problem-solver/py](https://github.com/ostis-apps/ostis-geography/blob/main/problem-solver/py/).

3. Запускаем [server.py](https://github.com/ostis-apps/ostis-geography/blob/main/problem-solver/py/server.py) следующей командой:

```sh
python3 ./server.py
```

4. Проверяем работоспособность агентов.
