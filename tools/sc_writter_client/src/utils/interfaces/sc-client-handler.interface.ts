import { ScAddr, ScClient, ScConstruction, ScLinkContent } from "ts-sc-client/build/lib";

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