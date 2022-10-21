### Interface for hotels

The following method was chosen as the implementation:
<a href = "https://github.com/MikhailSadovsky/ostis-UI-component-sample/wiki/Component-integration" target= "_blank">instructions</a>

## Start Working

In order to start the interface, you must do the following:

* Run the following commands or run bash-file <b>"hotels_install.sh"</b>:
    ``` sh
    echo ls
    cd interface/sc-web-extensions/hotels_interface/
    cp -R ./hotels_ui ../../../ostis-web-platform/sc-web/components/
    paste -d"\n" ./Gruntfile.js ../../../ostis-web-platform/sc-web/Gruntfile.js > ../../../ostis-web-platform/sc-web/Gruntfile.js
    cd ../../../ostis-web-platform/sc-web/client/templates
    echo "COMPLETE"

    cat <<EOT >> ./components.html
    <script type="text/javascript" charset="utf-8" src="static/components/js/hotels_ui/hotels.js"></script>
    EOT

    cd ../../scripts
    cd ..
    grunt build
    ``` 
* Build knowledge base
    ```sh
    cd {project-name}/ostis-web-platform/scripts
    ./build_kb.sh
    ```
* Run sctp-server & sc-web
Please note that JSON Websocket protocol will be available as well after start.
    Run on Linux:
    ```sh
    #Terminal 1
    cd {project-name}/ostis-web-platform/scripts
    ./run_sctp.sh

    #Terminal 2
    cd {project-name}/ostis-web-platform/scripts
    ./run_scweb.sh
    ```
* Open interface via expert mode
* Choose the <b>$param_1</b> needed
* Select the agent you want to run
* Get an answer to a question