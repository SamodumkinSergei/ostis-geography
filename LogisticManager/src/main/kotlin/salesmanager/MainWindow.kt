package salesmanager


import engine.ScRepository
import engine.buildPath
import org.ostis.api.context.UncheckedScContext
import org.ostis.scmemory.websocketmemory.memory.SyncOstisScMemory
import java.awt.EventQueue
import java.awt.event.*
import java.net.URI
import javax.swing.*
import javax.swing.GroupLayout.Alignment.BASELINE

class MainWindow(title: String) : JFrame() {

    private val chooseWarehouse = JLabel("No path");
    private val shopsCombobox = JComboBox<String>();
    private val factoriesCombobox = JComboBox<String>();
    private val startExecutionButton = JButton("Start execution");
    private val scMemory = SyncOstisScMemory(URI("ws://localhost:8090/ws_json"));
    private val scContext = UncheckedScContext(scMemory);
    private var scRepository: ScRepository;
    private var foundWarehouseName: String? = null;

    init {
        scMemory.open();
        scRepository = ScRepository(scMemory);
        createUI(title)
    }

    private fun createUI(title: String) {

        factoriesCombobox.font = factoriesCombobox.font.deriveFont(14f)
        factoriesCombobox.addItemListener(MainItemListener())
        factoriesCombobox.addMouseListener(FactoryListener())


        shopsCombobox.font = shopsCombobox.font.deriveFont(14f)
        shopsCombobox.addItemListener(MainItemListener())
        shopsCombobox.addMouseListener(ShopListener())

        startExecutionButton.addActionListener {
            val x = foundWarehouseName;
            if (foundWarehouseName != null) {
                scRepository.createFreightOrder(
                    factoriesCombobox.selectedItem.toString(),
                    foundWarehouseName!!,
                    shopsCombobox.selectedItem.toString()
                )
            }
        }

        createLayout(factoriesCombobox, shopsCombobox, chooseWarehouse, startExecutionButton);

        setTitle(title)

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


    private fun createLayout(vararg arg: JComponent) {

        val pane = contentPane
        val gl = GroupLayout(pane)
        pane.layout = gl

        gl.autoCreateContainerGaps = true
        gl.autoCreateGaps = true

        gl.setHorizontalGroup(
            gl.createSequentialGroup()
                .addComponent(arg[0])
                .addComponent(arg[1])
                .addComponent(arg[2])
                .addComponent(arg[3])
        )
        gl.setVerticalGroup(
            gl.createParallelGroup(BASELINE)
                .addComponent(arg[0])
                .addComponent(arg[1])
                .addComponent(arg[2])
                .addComponent(arg[3])
        )
        pack()
    }

    inner class MainItemListener() : ItemListener {
        override fun itemStateChanged(e: ItemEvent?) {
            if (e != null) {
                if (e.stateChange == ItemEvent.SELECTED) {
                    if (shopsCombobox.selectedItem != null && factoriesCombobox.selectedItem != null) {
                        val path = buildPath(
                            factoriesCombobox.selectedItem.toString(),
                            shopsCombobox.selectedItem.toString(),
                            scMemory
                        );
                        if (path.isNotEmpty()) {
                            chooseWarehouse.text = path[1];
                            foundWarehouseName = path[1]
                        } else {
                            chooseWarehouse.text = "No path";
                            foundWarehouseName = null;
                        }
                    }
                    //display.text = e.item.toString()
                    // find warehouse
                }
            }
        }

    }

    inner class ShopListener() : MouseListener {
        override fun mouseClicked(e: MouseEvent?) {
            val foundShopNames = scRepository.getAllShopNames();
            shopsCombobox.removeAllItems();
            foundShopNames.forEach {
                shopsCombobox.addItem(it)
            }
            // update list
        }

        override fun mousePressed(e: MouseEvent?) {
        }

        override fun mouseReleased(e: MouseEvent?) {
        }

        override fun mouseEntered(e: MouseEvent?) {
        }

        override fun mouseExited(e: MouseEvent?) {
        }

    }

    inner class FactoryListener() : MouseListener {
        override fun mouseClicked(e: MouseEvent?) {
            val foundFactoryName = scRepository.getAllFactoryNames();
            factoriesCombobox.removeAllItems();
            foundFactoryName.forEach {
                factoriesCombobox.addItem(it)
            }
        }

        override fun mousePressed(e: MouseEvent?) {
        }

        override fun mouseReleased(e: MouseEvent?) {
        }

        override fun mouseEntered(e: MouseEvent?) {
        }

        override fun mouseExited(e: MouseEvent?) {
        }

    }
}

private fun createAndShowGUI() {
    val frame = MainWindow("Sales manager")
    frame.isVisible = true
}

fun main() {
    EventQueue.invokeLater(::createAndShowGUI)
}