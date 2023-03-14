package engine

data class Warehouse(
    val name: String,
    val connectedShops: MutableMap<Shop, Int>,
    val connectedFactories: MutableMap<Factory, Int>,
    val connectedWarehouse: MutableMap<Warehouse, Int>
){
    override fun toString(): String {
        return "Warehouse(name='$name.', connectedShops=$connectedShops, connectedFactories=$connectedFactories, connectedWarehouse=${connectedWarehouse.size})"
    }
}