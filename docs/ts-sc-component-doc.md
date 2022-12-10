# Пример реализации компонента интерфейса при помощи sc-web

### Выполнили: Клинцов Антон, Евгений Нестеров, Кирилушкин Александр
### Группа: 921702

## Подготовка пакета

Документация предполагает, что на вашей локальной машине установлена программная платформа <strong>NodeJS</strong> и пакетный менеджер <strong>npm</strong> (или <strong>yarn</strong>).

Прежде чем приступить к разработке компонента пользовательского интерфейса, для работы с <strong>SC-WEB</strong>,
необходимо склонировать пакет <strong>'ts-sc-client'</strong> к себе на компьютер ([GitHub-репозиторий и документация к пакету](https://github.com/ostis-ai/ts-sc-client)):

    git clone https://github.com/ostis-ai/ts-sc-client.git

После того, как покет был склонирован, требуется перейти в только что созданную директорию:

    cd ts-sc-client

Далее, установка необходимых пакетных зависимостей:

    yarn install

или 

    npm install

Оратите внимание, что вся необходимая конфигурация <strong>Webpack</strong> уже готова, поэтому теперь остаётся лишь собрать пакет с помощью:

    yarn build

или

    npm run build

На данном этапе подготовка пакета к подключению в будущий компонент готова.


## Импорт пакета в проектируемый компонент 

Стоит отметить, что данный пример использует <strong>JavaScript-фреймворк React</strong>, однако вы можете использовать любой другой предпочтительный способ реализации системы пользовательского интерфейса.

Принимая во внимания, что на данном этапе ваше приложение уже проинициализировано, необходимо выполнить установку ранее описанного пакета следующим образом:

    npm install ../path-to-the-cloned-package

<strong>../path-to-the-cloned-package</strong> - путь к пакету, который вы ранее склонировали (линковка с помощью <strong>npm link</strong> не тестировалась). Работает? Отлично, вот наш пакет и установлен.


## Реализация интерфейса

<em>В целом, я рекомендую не делать проектируемую систему напрямую зависимой от импортированного пакета, но вы можете делать свою архитектуры по-своему, поэтому некоторые последующие советы можете подстраивать под свои нужды.</em>

Повторюсь, если вам такой подход к построению архитектуры не нравится, вы можете использовать функционал напрямую, документация к нему находится в репозитории библиотеки.

Создадим новую папку 'utils' внутри директории 'src', в которой, в свою очередь, создаём еще одну директорию 'interfaces' с файлом 'sc-client-handler.interface.ts', или же любым другим способом, который будет давать вам понять, что это интерфейс. Вставляем в этот файл следующее содержимое:

```ts
    export interface ScClientHandlerInterface {
        readonly scClient: ScClient;
        readonly scAddresses: Map<number, ScAddr>;
        readonly scLinkContentsByAddresses: Map<number, ScLinkContent>;
        readonly scConstructions: Map<string, ScConstruction>

        createAddress(address: number): ScAddr | null;
        getAvailableAddresses(): Map<number, ScAddr>;
        getAddressByNumber(address: number): ScAddr | undefined;
        getScLinkContentByScAddress(address: number): ScLinkContent | undefined;
        setScLinkContentByScAddress(address: number, content: ScLinkContent): void;
        getScLinkContentsWithScAddresses(): Map<number, ScLinkContent>;
        createLinkContent(content: string, address?: ScAddr): ScLinkContent;
        createScConstruction(constructionName?: string): ScConstruction;
        getScConstructionByName(constructionName: string): ScConstruction | undefined;
        setScConstructionByName(constructionName: string, construction: ScConstruction): void;
        getScConstructionsWithNames(): Map<string, ScConstruction>;
        createNodeInScConstruction(construction: ScConstruction | string, nodeName?: string): void;
        createLinkInScConstruction(
            construction: ScConstruction | string,
            link: ScLinkContent | number,
            linkName?: string
        ): void;
        createEdgeInInConstruction(
            construction: ScConstruction | string,
            source: ScAddr | string,
            target: ScAddr | string,
            edgeName?: string,
        ): void;
        uploadScElementsToKB(
            construction: ScConstruction | string,
        ): Promise<void>;
        uploadScElementsBySCs(
            content: string[],
        ): Promise<void>;
    }
```

С помощью данного интерфейса наше приложение и будет взаимодействовать с библиотекой 'ts-sc-client'. 

В директории 'utils' создаём файл с именем 'sc-client-handler.class.ts', который будет экспортировать класс, наследуемый от ранее созданного интерфейса. Сперва внесём следующее содержимое и остановимся ненадолго на нем:

```ts
    // sc-client-handler.class.ts
    import { ScClient } from 'ts-sc-client';

    import { ScClientHandlerInterface } from './interfaces/sc-client-handler.interface';

    export class ScClientHandler implements ScClientHandlerInterface {
        private readonly scClient: ScClient;

        constructor(webSocketUrl: string) {
            this.scClient = new ScClient(webSocketUrl);

            this.scClient.addEventListener("open", this.onConnect)
            
            this.scClient.addEventListener("error", this.onError)
            
            this.scClient.addEventListener("close", this.onDisconnect)
        }

        private onConnect(): void {
            // Коллбэк при установке соединения с БЗ
        }

        private onError(): void {
            // Коллбэк при ошибке соединения с БЗ
        }

        private onDisconnect(): void {
            // Коллбэк при закрытии соединения с БЗ
        }
    }
```

По-умолчанию ScClient ориентирован на браузерную работу, что в нашем случае и подходит, однако, если вы реализуете API на NodeJs, вам следует вместо предложенного варианта, воспользоваться любой импортированной реализацией технологии Websocket:

```ts
    import { WebSocket } from "ws";

    const client = new ScClient(new WebSocket('ws://localhost:8090'));
```

Обычно, URL для работы по websocket с базой знаний 'ws://localhost:8090', однако в вашем случае он может быть иным. Также убедитесь, что на момент запуска приложения SC-сервер запущен.

### Создание SC-Адреса

Сперва реализуем создание абстракции над адресом в SC-памяти (далее просто адрес). Обновим импорт (в дальнейшем этот пункт будет пропускаться, очевидно, что об упущенном импорте IDE вас предупредит)::

```ts (ds)
    //sc-client-handler.class.ts
    import { ScClient, ScAddr } from 'ts-sc-client';
```

Создадим в нашем классе поле с модификатором доступа private:

```ts
    //sc-client-handler.class.ts
    private readonly scAddresses: Map<number, ScAddr>;
```

Обновим конструктор:

```ts
    //sc-client-handler.class.ts
    import { ScClient, ScAddr } from 'ts-sc-client';
```

И внесём следующую реализацию:

```ts
    public createAddress(address: number): ScAddr | null {
        const newAddress = new ScAddr(+address);

        if (newAddress.isValid()) {
            this.scAddresses.set(address, newAddress);

            return newAddress;
        }

        return null;
    }
```

Теперь подробнее: в классе мы объявили словарь, который будет хранить в себе все объявленные ранее адреса, таким образом мы сможем избежать злокачественного дублирования, однако стоит понимать, что при попытке создать адрес с уже существующим значением, старый будет перезаписан. К тому же, таким образом, мы можем получить доступ по значению адреса к адресам в любой удобный для нас момент времени. Можно заметить, что, при успешном добавлении адресса будет возвращен созданный адрес (т.к. возвращаемая переменная имеет ссылочный тип, её смело можно использовать в вашей бизнес-логике для оперирования), в противном случае - null.

### Создание контента SC-Ссылки

Реализуем метод создания контента SC-ссылки:

```ts
    export class ScClientHandler implements ScClientHandlerInterface {
        // ...
        public createLinkContent(content: string, address?: ScAddr) {
            if (address) {
                const newScContent = new ScLinkContent(content, ScLinkContentType.String, address);

                this.scLinkContentsByAddresses.set(address.value, newScContent);

                return newScContent;
            }

            return new ScLinkContent(content, ScLinkContentType.String);
        }
        // ...
    }
```

Функция возвращает созданный контент, который далее может использоваться в вашей бизнес логике. Также, как можно заметить, что контент сразу же можно прявязать к переданному SC-Адресу. Как можно заметить, при прямой привязке к контенту ссылки, данная связка будет занесена в словарь. Поэтому объявим его и добавим в конструктор, реализуя необходимые методы получения и обновления:

```ts
    export class ScClientHandler implements ScClientHandlerInterface {
        // ...
        private readonly scLinkContentsByAddresses: Map<number, ScLinkContent>;
        //...
        constructor(webSocketUrl: string = '') {
            //...
            this.scLinkContentsByAddresses = new Map<number, ScLinkContent>();
            //...
        }
        // ...
        public getScLinkContentByScAddress(address: number): ScLinkContent | undefined {
            return this.scLinkContentsByAddresses.get(address);
        }
        public setScLinkContentByScAddress(address: number, content: ScLinkContent): void {
            this.scLinkContentsByAddresses.set(address, content);
        }
        //...
        public getScLinkContentsWithScAddresses(): Map<number, ScLinkContent> {
            return this.scLinkContentsByAddresses;
        }
        // ...
    }
```

### Создание SC-Конструкций

#### Создание

Далее я предлагаю реализацию создания SC-конструкций в двух вариантах: первый - без хранения конструкций в оперативной памяти (если необходимо создавать конструкции, без дальнейшего использования в будущем) и второй - с хранением конструкций в оперативной памяти (если есть необходимость оперирования над SC-Компонентами в разных компонентах вашего приложения):

```ts
    export class ScClientHandler implements ScClientHandlerInterface {
        public createScConstruction(name?: string): ScConstruction {
            const construction = new ScConstruction();

            if (name) {
                this.scConstructions.set(name, construction);
            }

            return construction;
        }
    }
```

Как можно заметить, если, в качестве параметра, будет передано название конструкции, она будет сохранена в словаре и в дальнейшем, при необходимости, может быть получена по названию. При отсутствии же параметра, конструкция будет возвращена без предварительного сохранения. И, соответственно, соответствующий функционал для работы со словарём:

```ts
    export class ScClientHandler implements ScClientHandlerInterface {
        // ...
        private readonly scConstructions: Map<string, ScConstruction>;
        //...
        constructor(webSocketUrl: string = '') {
            //...
            this.scConstructions = new Map<string, ScConstruction>();
            //...
        }
        // ...
        public getScConstructionByName(name: string): ScConstruction | undefined {
            return this.scConstructions.get(name);
        }
        // ...
        public setScConstructionByName(name: string, construction: ScConstruction): void {
            this.scConstructions.set(name, construction);
        }
        // ...
        public getScConstructionsWithNames(): Map<string, ScConstruction> {
            return this.scConstructions;
        }
        // ...
    }
```

### Работа с SC-Конструкцией

<strong>Создание SC-Узла</strong>:

```ts
    export class ScClientHandler implements ScClientHandlerInterface {
        // ...
        public createNodeInScConstruction(construction: ScConstruction | string, nodeName?: string): void {
            if (typeof construction === 'string') {
                const findedScConstruction = this.scConstructions.get(construction);

                findedScConstruction?.createNode(ScType.NodeConst, nodeName);

                return;
            }

            construction.createNode(ScType.NodeConst, nodeName);
        }
        // ...
    }
```

Обратите внимание, при передаче названия конструкции, в качестве аргумента "construction", будет произведена попытка поиска конструкции из имеющегося списка конструкций, при неудаче, узел не будет добавлен, поэтому стоит это учитывать. При получения доступа к той или иной конструкции (через метод получения по названию из списка нашего класса ("<strong>getScConstructionByName()</strong>") или напрямую, если вы его объявили явно или без сохранения) вы сможете получить тот или иной элемент конструкции (см. документацию библиотеки) (ну, или можете сами реализовать шлюз-версию поиска в нашем классе, если я этого еще не сделал). Необязательным параметром в данном методе вы можете передать название SC-узла.

<strong>Создание SC-Ссылки</strong>:

```ts
    export class ScClientHandler implements ScClientHandlerInterface {
        // ...
        public createLinkInScConstruction(
            construction: ScConstruction | string,
            link: ScLinkContent | number,
            linkName?: string
        ): void {
            const linkContent =
                typeof link === 'number' ?
                    this.scLinkContentsByAddresses.get(link) :
                    link;

            if(!linkContent) {
                return;
            }

            if (typeof construction === 'string') {
                const findedScConstruction = this.scConstructions.get(construction);

                findedScConstruction?.createLink(ScType.LinkConst, linkContent, linkName);

                return;
            }

            construction.createLink(ScType.NodeConst, linkContent, linkName);
        }
        // ...
    }
```

Аналогичный вариант метода создания, только теперь для SC-Ссылки, в качестве аргумента "construction", передаётся уже существующая конструкция, или название уже ранее сохранённой конструкции. Ранее мы обявляли хранилище для ScLinkContent'ов, поэтому в качестве второго аргумента вы можете передать его адресс. Третий необязательный аргумент - название ссылки.

<strong>Создание SC-Ребра</strong>:

```ts
    export class ScClientHandler implements ScClientHandlerInterface {
        // ...
        public createEdgeInInConstruction(
            construction: ScConstruction | string,
            source: ScAddr | string,
            target: ScAddr | string,
            edgeName?: string,
        ) {
            if (typeof construction === 'string') {
                const findedScConstruction = this.scConstructions.get(construction);

                findedScConstruction?.createEdge(
                    ScType.EdgeAccessConstPosPerm,
                    source,
                    target,
                    edgeName,
                );

                return;
            }

            construction.createEdge(
                ScType.EdgeAccessConstPosPerm,
                source,
                target,
                edgeName,
            ); 
        }
        // ...
    }
```

В качестве аргумента "construction", передаётся уже существующая конструкция, или название уже ранее сохранённой конструкции. Вторым аргументом передаётся адрес или название первого элемента дуги ("откуда"),  третим - передаётся адрес или название второго элемента дуги ("куда"). Третий необязательный параметр выступает в качестве названия ребра.

#### Выгрузка в БЗ: 

```ts
    export class ScClientHandler implements ScClientHandlerInterface {
        // ...
        public async uploadScElementsToKB(
            construction: ScConstruction | string,
        ) {
            try {
                if (typeof construction === 'string') {
                    const findedScConstruction = this.scConstructions.get(construction);
        
                    if (!findedScConstruction) {
                        return;
                    }
        
                    await this.scClient.createElements(findedScConstruction);
        
                    return;
                }
        
                await this.scClient.createElements(construction);
            } catch {
                throw new Error('Error on upload SC-construction');
            }
        }
        // ...
    }
```

Ранее мы давали понять SC-Клиенту по какому URL он может общаться с БЗ, поэтому чтобы гарантировать удовлетворительный результат работы данного метода, стоит проверить браузерную консоль на наличие ошибок (после запуска сервера, разумеется). В данном варианте реализации выгрузки, происходит выгрузка SC-Конструкций, которые, как предполагается, мы ранее инициализировали, налогично с предыдущими методами, имеетася возможность выгрузки по названию сохранённой конструкции или по явной передаче её. 


Однако, также предоставляется возможность выгрузки SC-Конструкций в виде уже готвого текста, который соответствует синтаксису SCs:

```ts
    export class ScClientHandler implements ScClientHandlerInterface {
        // ...
        public async uploadScElementsBySCs(
            content: string[],
        ) {
            try {
                await this.scClient.createElementsBySCs(content);
            } catch {
                throw new Error('Error on upload SC-constructions');
            }
        }
        // ...
    }
```

### Репозиторий с примером и возможно обновлённой документацией: [@Dartosh](https://github.com/Dartosh/ts-sc-component)
