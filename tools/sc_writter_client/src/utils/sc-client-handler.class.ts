import { ScClient, ScAddr, ScConstruction, ScLinkContent, ScLinkContentType, ScType } from 'ts-sc-client';

import { ScClientHandlerInterface } from './interfaces/sc-client-handler.interface';

export class ScClientHandler implements ScClientHandlerInterface {
    public readonly scClient: ScClient;

    public isConnected: boolean;

    public readonly scAddresses: Map<number, ScAddr>;

    public readonly scLinkContentsByAddresses: Map<number, ScLinkContent>;

    public readonly scConstructions: Map<string, ScConstruction>;

    constructor(webSocketUrl: string = '') {
        this.isConnected = false;

        this.scClient = new ScClient(webSocketUrl);

        this.scClient.addEventListener("open", () => { this.isConnected = true });
        
        this.scClient.addEventListener("error", this.onError);
        
        this.scClient.addEventListener("close", this.onDisconnect);

        this.scAddresses = new Map<number, ScAddr>();

        this.scLinkContentsByAddresses = new Map<number, ScLinkContent>();

        this.scConstructions = new Map<string, ScConstruction>();
    }

    private onConnect(): void {
        this.isConnected = true;
    }

    private onError(): void {
        this.isConnected = false;
    }

    private onDisconnect(): void {
        this.isConnected = false;
    }

    public getIsConnected(): boolean {
        return this.isConnected;
    }
    
    public createAddress(address: number): ScAddr | null {
        const newAddress = new ScAddr(+address);

        if (newAddress.isValid()) {
            this.scAddresses.set(address, newAddress);

            return newAddress;
        }

        return null;
    }

    public getAvailableAddresses(): Map<number, ScAddr> {
        return this.scAddresses;
    }

    public getAddressByNumber(address: number): ScAddr | undefined {
        return this.scAddresses.get(address);
    }

    public getScLinkContentByScAddress(address: number): ScLinkContent | undefined {
        return this.scLinkContentsByAddresses.get(address);
    }

    public setScLinkContentByScAddress(address: number, content: ScLinkContent): void {
        this.scLinkContentsByAddresses.set(address, content);
    }

    public getScLinkContentsWithScAddresses(): Map<number, ScLinkContent> {
        return this.scLinkContentsByAddresses;
    }

    public createLinkContent(content: string, address?: ScAddr): ScLinkContent {
        if (address) {
            const newScContent = new ScLinkContent(content, ScLinkContentType.String, address);

            this.scLinkContentsByAddresses.set(address.value, newScContent);

            return newScContent;
        }

        return new ScLinkContent(content, ScLinkContentType.String);
    }

    public createScConstruction(constructionName?: string): ScConstruction {
        const construction = new ScConstruction();

        if (constructionName) {
            this.scConstructions.set(constructionName, construction);
        }

        return construction;
    }

    public getScConstructionByName(constructionName: string): ScConstruction | undefined {
        return this.scConstructions.get(constructionName);
    }

    public setScConstructionByName(constructionName: string, construction: ScConstruction): void {
        this.scConstructions.set(constructionName, construction);
    }

    public getScConstructionsWithNames(): Map<string, ScConstruction> {
        return this.scConstructions;
    }

    public createNodeInScConstruction(construction: ScConstruction | string, nodeName?: string): void {
        if (typeof construction === 'string') {
            const findedScConstruction = this.scConstructions.get(construction);

            findedScConstruction?.createNode(ScType.NodeConst, nodeName);

            return;
        }

        construction.createNode(ScType.NodeConst, nodeName);
    }

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

    public createEdgeInInConstruction(
        construction: ScConstruction | string,
        source: ScAddr | string,
        target: ScAddr | string,
        edgeName?: string,
    ): void {
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

    public async uploadScElementsToKB(
        construction: ScConstruction | string,
    ): Promise<void> {
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

    public async uploadScElementsBySCs(
        content: string[],
    ): Promise<void> {
        try {
            console.log(content);
            await this.scClient.createElementsBySCs(content);
        } catch (error) {
            console.log(error);
            throw new Error('Error on upload SC-constructions');
        }
    }
}

export default ScClientHandler;