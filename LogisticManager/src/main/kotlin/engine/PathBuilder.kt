package engine

import org.ostis.api.context.UncheckedScContext
import org.ostis.scmemory.model.ScMemory
import org.ostis.scmemory.model.element.edge.EdgeType
import org.ostis.scmemory.model.element.link.LinkType
import org.ostis.scmemory.model.element.link.ScLinkInteger
import org.ostis.scmemory.model.element.link.ScLinkString
import org.ostis.scmemory.model.element.node.NodeType
import org.ostis.scmemory.model.element.node.ScNode
import org.ostis.scmemory.model.pattern.ScPatternTriplet
import org.ostis.scmemory.model.pattern.factory.ScPattern5FactoryWithNames
import org.ostis.scmemory.websocketmemory.memory.pattern.DefaultWebsocketScPattern
import org.ostis.scmemory.websocketmemory.memory.pattern.SearchingPatternTriple
import org.ostis.scmemory.websocketmemory.memory.pattern.element.AliasPatternElement
import org.ostis.scmemory.websocketmemory.memory.pattern.element.FixedPatternElement
import org.ostis.scmemory.websocketmemory.memory.pattern.element.TypePatternElement
import java.util.*
import java.util.stream.Stream
import kotlin.collections.HashMap
import kotlin.jvm.optionals.getOrNull

private val warehouseNodeToNameLink = HashMap<ScNode, String>();
fun buildPath(factory: String, shop: String, scMemory: ScMemory): List<String> {
    val scContext = UncheckedScContext(scMemory);
    val scRepository = ScRepository(scMemory);
    val shopNode = getNodeByNameAndRelation(scRepository, shop, "shopName*", scRepository.getAllShopNodes())
        .getOrNull() ?: throw RuntimeException("Can't find shop with this name ")
    val factoryNode = getNodeByNameAndRelation(scRepository, factory, "factoryName*", scRepository.getAllFactoryNodes())
        .getOrNull() ?: throw RuntimeException("Can't find factory with this name ")

    val shopWarehouses = getConnectedWarehousesWithDistance(scRepository, shopNode);
    val factoryWarehouses = getConnectedWarehousesWithDistance(scRepository, factoryNode);
    val adjacentWarehouses = HashSet(shopWarehouses.keys)
    adjacentWarehouses.retainAll(factoryWarehouses.keys);

    if (adjacentWarehouses.isEmpty())
        return listOf() //or try to find path through warehouses
    else if (adjacentWarehouses.size == 1)
        return listOf(
            factory,
            getWarehouseNameByNode(adjacentWarehouses.first()).get(),
            shop
        )
    else {
        val warehouseWithShortestPath = findShortestPath(adjacentWarehouses, shopWarehouses, factoryWarehouses)
        return listOf(
            factory,
            getWarehouseNameByNode( warehouseWithShortestPath).get(),
            shop
        )
    }
}

fun getNodeByNameAndRelation(
    scRepository: ScRepository,
    name: String,
    relation: String,
    allNodes: Stream<ScNode>
): Optional<ScNode> {
    return allNodes.flatMap {
        scRepository.scContext.find(
            ScPattern5FactoryWithNames.getFNodeAEdgeALinkAEdgeFNodePattern(
                it,
                EdgeType.D_COMMON,
                LinkType.LINK,
                EdgeType.ACCESS,
                scRepository.scContext.findKeynode(relation).getOrNull()
                    ?: throw RuntimeException("Please, init base first")
            )
        )
    }.filter { (it.get3() as ScLinkString).content == name }
        .map { it.get1() }
        .findFirst()
}

private fun getWarehouseNameByNode(node: ScNode): Optional<String> {
    return Optional.of(warehouseNodeToNameLink[node]?:throw java.lang.RuntimeException("I don't know name of this warehouse"))
}

private fun getConnectedWarehousesWithDistance(scRepository: ScRepository, currentNode: ScNode): Map<ScNode, Int> {
    val allCloseNodes: ScPatternTriplet = SearchingPatternTriple(
        TypePatternElement(NodeType.NODE, AliasPatternElement("maybeWarehouse")),
        TypePatternElement(EdgeType.U_COMMON, AliasPatternElement("roadToAnotherLocation")),
        FixedPatternElement(currentNode)
    )
    val filterOnlyWarehouseNodes: ScPatternTriplet = SearchingPatternTriple(
        FixedPatternElement(scRepository.scContext.findKeynode("warehouse").get()),
        TypePatternElement(EdgeType.ACCESS, AliasPatternElement("justFromClass")),
        AliasPatternElement("maybeWarehouse")
    )
    val getDistance: ScPatternTriplet = SearchingPatternTriple(
        TypePatternElement(LinkType.LINK, AliasPatternElement("linkWithDistance")),
        TypePatternElement(EdgeType.ACCESS, AliasPatternElement("qwe")),
        AliasPatternElement("roadToAnotherLocation")
    )
    val getName: ScPatternTriplet = SearchingPatternTriple(
        AliasPatternElement("maybeWarehouse"),
        TypePatternElement(EdgeType.D_COMMON, AliasPatternElement("abc")),
        TypePatternElement(LinkType.LINK, AliasPatternElement("linkWithName")),
    )

    val pattern = DefaultWebsocketScPattern()
    pattern.addElement(allCloseNodes);
    pattern.addElement(filterOnlyWarehouseNodes);
    pattern.addElement(getDistance);
    pattern.addElement(getName);
    val foundConstruction = scRepository.scContext.find(pattern)
        .map { it.toList() }
        .toList()
    foundConstruction.forEach{
        warehouseNodeToNameLink[it[0]as ScNode] = (it[11] as ScLinkString).content
    }
    return foundConstruction.associateBy({ it.toList()[0] as ScNode }, { (it[6] as ScLinkInteger).content })
}

private fun findShortestPath(
    warehouses: Set<ScNode>,
    distanceFromShopToWarehouse: Map<ScNode, Int>,
    distanceFromFactoryToWarehouse: Map<ScNode, Int>
): ScNode = Collections.min(warehouses.associateBy(
    { it }, { distanceFromShopToWarehouse[it]!! + distanceFromFactoryToWarehouse[it]!! }
).entries, Comparator.comparingInt { it.value }).key;
