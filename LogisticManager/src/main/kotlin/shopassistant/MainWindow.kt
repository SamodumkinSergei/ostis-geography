package shopassistant

import engine.ScRepository
import org.ostis.api.context.UncheckedScContext
import org.ostis.scmemory.model.element.ScElement
import org.ostis.scmemory.model.element.edge.ScEdge
import org.ostis.scmemory.model.element.node.ScNode
import org.ostis.scmemory.model.event.OnAddIngoingEdgeEvent
import org.ostis.scmemory.model.event.OnAddOutgoingEdgeEvent
import org.ostis.scmemory.websocketmemory.memory.SyncOstisScMemory
import java.awt.EventQueue
import java.awt.event.WindowAdapter
import java.awt.event.WindowEvent
import java.lang.RuntimeException
import java.net.URI
import javax.swing.JFrame
import javax.swing.JLabel
import javax.swing.JOptionPane


fun main(){
    EventQueue.invokeLater(::createAndShowGUI)

}

private fun createAndShowGUI() {
    val frame = MainWindow()
    frame.isVisible = true
}

private class MainWindow : JFrame(){
    private val information = JLabel("");
    private val scMemory = SyncOstisScMemory(URI("ws://localhost:8090/ws_json"));

    init {
        scMemory.open();
        val scContext = UncheckedScContext(scMemory);
        val execNode = scContext.findKeynode("executionStarted").get()?:throw RuntimeException("Init db first")
        scMemory.subscribeOnEvent(execNode,  OnOutgoingActionEdgeEvent())
        title = "Shop assistant";
        createUI()
    }

    private fun createUI() {
        information.text = "The propose of this program is to handle events from sales manager about trucks using sc-machine"
        add(information)
        defaultCloseOperation = EXIT_ON_CLOSE
        setSize(600, 100)
        setLocationRelativeTo(null)
        addWindowListener(object : WindowAdapter() {
            override fun windowClosing(e: WindowEvent) {
                scMemory.close();
                e.window.dispose()
            }
        })
    }

    private inner class OnOutgoingActionEdgeEvent: OnAddOutgoingEdgeEvent{
        override fun onEvent(mainElement: ScElement?, edge: ScEdge?, edgeTarget: ScElement?) {
            val newScMemory = SyncOstisScMemory(URI("ws://localhost:8090/ws_json"))
            newScMemory.open();
            val stops = ScRepository(newScMemory).getFreightOrderStops(edgeTarget as ScNode)
            JOptionPane.showMessageDialog(this@MainWindow, "New truck arrived: $stops");
        }
    }

}