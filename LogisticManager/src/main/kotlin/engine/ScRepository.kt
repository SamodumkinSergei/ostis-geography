package engine

import org.ostis.api.context.UncheckedScContext
import org.ostis.scmemory.model.ScMemory
import org.ostis.scmemory.model.element.edge.EdgeType
import org.ostis.scmemory.model.element.link.LinkType
import org.ostis.scmemory.model.element.link.ScLinkString
import org.ostis.scmemory.model.element.node.NodeType
import org.ostis.scmemory.model.element.node.ScNode
import org.ostis.scmemory.model.pattern.factory.ScPattern3FactoryWithNames
import org.ostis.scmemory.model.pattern.factory.ScPattern5FactoryWithNames
import java.util.Optional
import java.util.stream.Stream
import kotlin.jvm.optionals.getOrNull

class ScRepository(val scMemory: ScMemory) {
    private val shopClassNode: ScNode
    private val shopRelName: ScNode
    private val factoryClassNode: ScNode
    private val factoryRelName: ScNode
    private val freightOrderClass: ScNode
    private val executionNodeClass: ScNode
    private val stopRel: ScNode
    private val warehouseRelName: ScNode
    var scContext: UncheckedScContext = UncheckedScContext(scMemory)

    init {
        shopClassNode =
            scContext.findKeynode("shop").getOrNull() ?: throw RuntimeException("Please, init base first");
        shopRelName =
            scContext.findKeynode("shopName*").getOrNull() ?: throw RuntimeException("Please, init base first");
        factoryClassNode =
            scContext.findKeynode("factory").getOrNull() ?: throw RuntimeException("Please, init base first");
        factoryRelName =
            scContext.findKeynode("factoryName*").getOrNull() ?: throw RuntimeException("Please, init base first");
        freightOrderClass =
            scContext.findKeynode("freightOrder").getOrNull() ?: throw RuntimeException("Please, init base first")
        executionNodeClass =
            scContext.findKeynode("executionStarted").getOrNull() ?: throw RuntimeException("Please, init base first")
        stopRel =
            scContext.findKeynode("stop'").getOrNull() ?: throw RuntimeException("Please, init base first")
        warehouseRelName =
            scContext.findKeynode("warehouseName*").getOrNull() ?: throw RuntimeException("Please, init base first");
    }

    fun getAllShopNames(): Stream<String> {
        val foundShopNodes = getAllShopNodes();
        return foundShopNodes.flatMap { shopNode ->
            scContext.find(
                ScPattern5FactoryWithNames.getFNodeAEdgeALinkAEdgeFNodePattern(
                    shopNode,
                    EdgeType.D_COMMON,
                    LinkType.LINK,
                    EdgeType.ACCESS,
                    shopRelName
                )
            ).map { it.get3() }
                .map { it as ScLinkString }
                .map { it.content }
        }.distinct()
            .filter { it != null }
    }

    fun getAllShopNodes(): Stream<ScNode> {
        return scContext.find(
            ScPattern3FactoryWithNames.getFNodeAEdgeANodePattern(
                shopClassNode,
                EdgeType.ACCESS,
                NodeType.NODE
            )
        ).map { it.get3() };
    }

    fun getAllFactoryNodes(): Stream<ScNode> {
        return scContext.find(
            ScPattern3FactoryWithNames.getFNodeAEdgeANodePattern(
                factoryClassNode,
                EdgeType.ACCESS,
                NodeType.NODE
            )
        ).map { it.get3() };
    }

    private fun getAllWarehouseNodes(): Stream<ScNode> {
        return scContext.find(
            ScPattern3FactoryWithNames.getFNodeAEdgeANodePattern(
                scContext.findKeynode("warehouse").get(),
                EdgeType.ACCESS,
                NodeType.NODE
            )
        ).map { it.get3() };
    }

    fun getAllFactoryNames(): Stream<String> {
        val scContext = UncheckedScContext(scMemory);
        val foundFactoryNodes = getAllFactoryNodes();
        return foundFactoryNodes.flatMap { factoryNode ->
            scContext.find(
                ScPattern5FactoryWithNames.getFNodeAEdgeALinkAEdgeFNodePattern(
                    factoryNode,
                    EdgeType.D_COMMON,
                    LinkType.LINK,
                    EdgeType.ACCESS,
                    factoryRelName
                )
            ).map { it.get3() }
                .map { it as ScLinkString }
                .map { it.content }
        }.distinct()
    }

    fun createFreightOrder(factoryName: String, warehouseName: String, shopName: String): ScNode {
        val factoryNode = getNodeByNameAndRelation(
            this,
            factoryName,
            "factoryName*",
            getAllFactoryNodes()
        ).getOrNull() ?: throw java.lang.RuntimeException("Factory name suddenly disappears...")
        val warehouseNode = getNodeByNameAndRelation(
            this,
            warehouseName,
            "warehouseName*",
            getAllWarehouseNodes()
        ).getOrNull() ?: throw java.lang.RuntimeException("Warehouse name suddenly disappears...")
        val shopNode = getNodeByNameAndRelation(
            this,
            shopName,
            "shopName*",
            getAllShopNodes()
        ).getOrNull() ?: throw java.lang.RuntimeException("Shop name suddenly disappears...")
        val freightOrder = scContext.createNode(NodeType.NODE);
        scContext.createEdge(EdgeType.ACCESS, freightOrderClass, freightOrder)
        listOf(factoryNode, warehouseNode, shopNode).forEach {
            val relEdge = scContext.createEdge(EdgeType.D_COMMON, freightOrder, it)
            scContext.createEdge(EdgeType.ACCESS, stopRel, relEdge)
        }
        scContext.createEdge(EdgeType.ACCESS, executionNodeClass, freightOrder);
        return freightOrder;
    }

    fun getFreightOrderStops(freightOrderNode: ScNode): List<String> {
        val allStops = scContext.find(
            ScPattern5FactoryWithNames.getFNodeAEdgeANodeAEdgeFNodePattern(
                freightOrderNode,
                EdgeType.D_COMMON,
                NodeType.NODE,
                EdgeType.ACCESS,
                stopRel
            )
        ).map { it.get3() }.toList()
        val shopName = getNodeNameByRel(allStops, shopRelName).getOrNull()?:throw RuntimeException("Bad things happens...");
        val warehouseName = getNodeNameByRel(allStops, warehouseRelName).getOrNull()?:throw RuntimeException("Bad things happens...");
        val factoryName = getNodeNameByRel(allStops, factoryRelName).getOrNull()?:throw RuntimeException("Bad things happens...");
        return listOf(factoryName, warehouseName, shopName);
    }

    private fun getNodeNameByRel(allNodes: List<ScNode>, relNode: ScNode): Optional<String> {
        return allNodes.stream().flatMap { shopNode ->
            scContext.find(
                ScPattern5FactoryWithNames.getFNodeAEdgeALinkAEdgeFNodePattern(
                    shopNode,
                    EdgeType.D_COMMON,
                    LinkType.LINK,
                    EdgeType.ACCESS,
                    relNode
                )
            )
                .map { it.get3() }
                .map { it as ScLinkString }
                .map { it.content }
        }.distinct()
            .filter { it != null }
            .findFirst()
    }

}