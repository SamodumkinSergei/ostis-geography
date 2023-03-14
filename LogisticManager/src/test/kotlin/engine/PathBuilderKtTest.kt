package engine

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.AfterEach
import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.BeforeEach
import org.ostis.scmemory.model.ScMemory
import org.ostis.scmemory.websocketmemory.memory.SyncOstisScMemory
import java.net.URI

internal class PathBuilderKtTest{

    lateinit var scMemory: ScMemory;

    @BeforeEach
    fun openScMemory(){
        scMemory = SyncOstisScMemory(URI("ws://localhost:8090/ws_json"))
        scMemory.open()
    }

    @AfterEach
    fun closeScMemory(){
        scMemory.close()
    }

    @Test
    fun testBasicPath(){
        val factory = "MilkFactory2"
        val shop = "Evroopt"
        val resultWarehouse = buildPath(factory, shop, scMemory);
        assertFalse(resultWarehouse.isEmpty())
        assertEquals("smallWarehouse", resultWarehouse[1]);
    }

    @Test
    fun testShortestPath(){
        val factory = "VegetablesFarm"
        val shop = "Sosedy"
        val resultWarehouse = buildPath(factory, shop, scMemory);
        assertFalse(resultWarehouse.isEmpty())
        assertEquals("smallWarehouse", resultWarehouse[1]);
    }

    @Test
    fun testBasicPath2(){
        val factory = "VegetablesFarm"
        val shop = "Korona"
        val resultWarehouse = buildPath(factory, shop, scMemory);
        assertFalse(resultWarehouse.isEmpty())
        assertEquals("bigWarehouse", resultWarehouse[1]);
    }


    @Test
    fun testNoPath(){
        val factory = "MilkFactory3"
        val shop = "Evroopt"
        val resultWarehouse = buildPath(factory, shop, scMemory);
        assertTrue(resultWarehouse.isEmpty())
    }
}
