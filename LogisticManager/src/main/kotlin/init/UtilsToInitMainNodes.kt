package init

import engine.Factory
import engine.Shop
import engine.StopLocation
import engine.Warehouse
import org.ostis.api.context.UncheckedScContext
import org.ostis.scmemory.model.element.edge.EdgeType
import org.ostis.scmemory.model.element.link.LinkType
import org.ostis.scmemory.model.element.node.NodeType
import org.ostis.scmemory.model.element.node.ScNode
import org.ostis.scmemory.websocketmemory.memory.SyncOstisScMemory
import java.lang.RuntimeException
import java.net.URI
import java.nio.file.Files
import java.nio.file.Paths

import kotlin.collections.ArrayList
import kotlin.collections.HashMap
import kotlin.io.path.name


private val scMemory = SyncOstisScMemory(URI("ws://localhost:8090/ws_json"));
private val scContext = UncheckedScContext(scMemory);
private val warehouses = ArrayList<Warehouse>();

fun initAll() {
    scMemory.open();
    val draftWarehousesLink = HashMap<Warehouse, Map<String, Int>>();
    val nameToWarehouseMap = HashMap<String, Warehouse>();
    val projectDirAbsolutePath = Paths.get("").toAbsolutePath().toString()
    val resourcesPath = Paths.get(projectDirAbsolutePath, "/src/main/resources/warehouses")
    Files.walk(resourcesPath).filter { item -> Files.isRegularFile(item) }.forEach { warehouseFile ->
        val shops = HashMap<Shop, Int>()
        val factories = HashMap<Factory, Int>()
        val connectedWarehouses = HashMap<Warehouse, Int>()
        val linksForCurrentWarehouse = HashMap<String, Int>();
        Files.readAllLines(warehouseFile).stream().forEach {
            val arr = it.split(" ")
            if (arr[0] == "F") factories[Factory(arr[1])] = arr[2].toInt()
            else if (arr[0] == "S") shops[Shop(arr[1])] = arr[2].toInt()
            else if (arr[0] == "W") linksForCurrentWarehouse[arr[1]] = arr[2].toInt()
            else throw RuntimeException("Can't parse letter '${arr[0]}'")
        }
        val newWarehouse = Warehouse(warehouseFile.fileName.name, shops, factories, connectedWarehouses)
        nameToWarehouseMap[newWarehouse.name] = newWarehouse;
        draftWarehousesLink[newWarehouse] = linksForCurrentWarehouse;
        warehouses.add(newWarehouse)
    }
    initWarehouses();
    draftWarehousesLink.forEach{(warehouse, linkedWarehouses)->
        run {
            linkedWarehouses.forEach { (otherWarehouse, distance) ->
                run {
                    val x = nameToWarehouseMap[otherWarehouse];
                    if (x!=null)
                        warehouse.connectedWarehouse[x] = distance;
                }
            }
        }
    }

    scMemory.close();
}

fun initWarehouses() {
    val warehouseClass = scContext.resolveKeynode("warehouse", NodeType.CLASS);
    val factoryClass = scContext.resolveKeynode("factory", NodeType.CLASS);
    val shopClass = scContext.resolveKeynode("shop", NodeType.CLASS);
    val warehouseNameRel = scContext.resolveKeynode("warehouseName*", NodeType.CONST_NO_ROLE);
    val factoryNameRel = scContext.resolveKeynode("factoryName*", NodeType.CONST_NO_ROLE);
    val shopNameRel = scContext.resolveKeynode("shopName*", NodeType.CONST_NO_ROLE);

    val nameToFactoryMap = HashMap<String, ScNode>();
    val nameToShopMap = HashMap<String, ScNode>();
    warehouses.stream().forEach {
        val warehouseNode = scContext.createNode(NodeType.NODE);
        scContext.createEdge(
            EdgeType.ACCESS, warehouseClass, warehouseNode
        ); //mean that warehouseNode has class warehouse.

        val warehouseNameLink = scContext.createStringLink(LinkType.LINK, it.name);
        val warehouseToNameEdge = scContext.createEdge(EdgeType.D_COMMON, warehouseNode, warehouseNameLink);
        scContext.createEdge(EdgeType.ACCESS, warehouseNameRel, warehouseToNameEdge);
        initDependedNodes(it.connectedShops, warehouseNode, shopClass, shopNameRel, nameToShopMap);
        initDependedNodes(it.connectedFactories, warehouseNode, factoryClass, factoryNameRel, nameToFactoryMap);
    }
    scContext.resolveKeynode("freightOrder", NodeType.CLASS);
    scContext.resolveKeynode("executionStarted", NodeType.CLASS);
    scContext.resolveKeynode("stop'", NodeType.ROLE);
}

fun initDependedNodes(
    connectedShops: MutableMap<out StopLocation, Int>, warehouseNode: ScNode, nodeClass: ScNode, nodeRelToName: ScNode, cacheNameRel: HashMap<String, ScNode>
) {
    connectedShops.forEach { (location, distance) ->
        val currentNode: ScNode?
        if (cacheNameRel.containsKey(location.name)) {
            currentNode = cacheNameRel[location.name]
        } else {
            currentNode = scContext.createNode(NodeType.NODE)
            scContext.createEdge(EdgeType.ACCESS, nodeClass, currentNode)
            val nodeNameLink = scContext.createStringLink(LinkType.LINK, location.name)
            val nodeToNameEdge = scContext.createEdge(EdgeType.D_COMMON, currentNode, nodeNameLink);
            scContext.createEdge(EdgeType.ACCESS, nodeRelToName, nodeToNameEdge);
            cacheNameRel[location.name] = currentNode
        }

        val toWarehouseDistance = scContext.createIntegerLink(LinkType.LINK, distance);
        val warehouseShopRoad = scContext.createEdge(EdgeType.U_COMMON, warehouseNode, currentNode);
        scContext.createEdge(EdgeType.ACCESS, toWarehouseDistance, warehouseShopRoad);
    }
}

fun main() {
    initAll()
}
