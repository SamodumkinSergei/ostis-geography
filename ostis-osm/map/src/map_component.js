// Component that describes usage of query agent
MapComponent = {
    ext_lang: 'openstreetmap_view',
    formats: ['format_openstreetmap_view'],
    struct_support: true,
    factory: function (sandbox) {
        const viewer = new MapViewer(sandbox);
        viewer.init();
        return viewer;
    }
};

MapViewer = function (sandbox) {
    this.sandbox = sandbox;
};

MapViewer.prototype.init = function () {
    this.generated = false
    var self = this;
    MapKeynodes.init(function () {
        self.initCallback();
        self.createReactComponent();
        self._callGenerateOSMQueryAgent();
    });
};

MapViewer.prototype._callGenerateOSMQueryAgent = function () {
    console.log("<===generateOSMQueryAgent===>")
    let self = this;

    const question = $('a.history-item.active').attr("sc_addr");
    let template = new sc.ScTemplate();
    template.triple(
        new sc.ScAddr(parseInt(question)),
        sc.ScType.EdgeAccessVarPosPerm,
        sc.ScType.NodeVar
    );
    window.scClient.searchByTemplate(template)
    .then(result => {
        const question_arg = result[0].get(2);
        SCWeb.core.Server.resolveScAddr(["ui_menu_generate_osm_query", 'nrel_answer'])
            .then(keynodes => {
                // const cmd = keynodes["ui_menu_generate_osm_query"];
                console.log("===keynodes===", keynodes)
                console.log("keynodes['ui_menu_generate_osm_query']===", keynodes["ui_menu_generate_osm_query"])
                const cmd = window.scClient.searchKeynodes["ui_menu_generate_osm_query"];
                console.log("<===enter_callGenerateOSMQueryAgent===>")
                SCWeb.core.Server.doCommand(cmd,
                    [question_arg.value], function (plain_text_result) {
                        console.log("GenerateOSMQueryAgent is done");
                        const result_question_node = plain_text_result.question;
                        setTimeout(() => {
                            const nrel_result = keynodes['nrel_result'];
                            let template = new sc.ScTemplate();
                            template.quintuple(
                                new sc.ScAddr(result_question_node),
                                sc.ScType.EdgeDCommonVar,
                                sc.ScType.NodeVar,
                                sc.ScType.EdgeAccessVarPosPerm,
                                new sc.ScAddr(nrel_result)
                            );
                            window.scClient.searchByTemplate(template)
                            .then((result) => {
                                const answer = result[0].get(2);
                                let template = new sc.ScTemplate();
                                template.triple(
                                    answer,
                                    sc.ScType.EdgeAccessVarPosPerm,
                                    sc.ScType.LinkVar
                                );
                                window.scClient.searchByTemplate(template)
                                .then((result) => {
                                    const answ_cont = result[0].get(2);
                                    window.scClient.getLinkContents([answ_cont])
                                    .then((content) => {
                                        console.log("query: " + content[0].data);
                                        self.sandbox.updateContent();
                                    });
                                });
                            });
                        }, 1000);
                    });
            });
    });
}

MapViewer.prototype.initCallback = function () {
    this.sandbox.eventStructUpdate = $.proxy(this.eventStructUpdate, this);
}

MapViewer.prototype.createReactComponent = function () {
    console.log("<===createStore===>")
    const store = this.createStore();
    console.log("<===createMapInterface===>")
    const mapInterface = React.createElement(MapInterface, {store: store});
    ReactDOM.render(mapInterface, document.getElementById(this.sandbox.container));
}

MapViewer.prototype.createStore = function () {
    return MapStore.get();
};

MapViewer.prototype.eventStructUpdate = function (added, contour, arc) {
    fluxify.doAction('changeContour', contour);
    if (this.generated === false) {
        MapUtils.extractor(arc).extract();
        this.generated = true;
    }
};

SCWeb.core.ComponentManager.appendComponentInitialize(MapComponent);