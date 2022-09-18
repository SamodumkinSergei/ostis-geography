MapComponent = {
    ext_lang: 'openstreetmap_view',
    formats: ['format_openstreetmap_view'],
    struct_support: true,
    factory: function (sandbox) {
        var viewer = new MapViewer(sandbox);
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
    MapKeynodes.init().done(function () {
        self.initCallback();
        self.createReactComponent();
        self._callGenerateOSMQueryAgent();
    });
};

MapViewer.prototype._callGenerateOSMQueryAgent = function () {
    let self = this;
    var question = $('a.history-item.active').attr("sc_addr");
    window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_3F_A_A, [
        question,
        sc_type_arc_pos_const_perm,
        sc_type_node]).done(function (it) {
        var question_arg = it[0][2];
        SCWeb.core.Server.resolveScAddr(["ui_menu_generate_osm_query"],
            function (data) {
                var cmd = data["ui_menu_generate_osm_query"];
                SCWeb.core.Server.doCommand(cmd,
                    [question_arg], function (plain_text_result) {
                        console.log("GenerateOSMQueryAgent is done");
                        var result_question_node = plain_text_result.question;
                        setTimeout(function () {
                            SCWeb.core.Server.resolveScAddr(['nrel_answer'], function (keynodes) {
                                var nrel_answer_addr = keynodes['nrel_answer'];
                                window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_5F_A_A_A_F, [
                                    result_question_node,
                                    sc_type_arc_common | sc_type_const,
                                    sc_type_node,
                                    sc_type_arc_pos_const_perm,
                                    nrel_answer_addr])
                                    .done(function (iter) {
                                        var answer = iter[0][2];
                                        window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_3F_A_A, [
                                            answer,
                                            sc_type_arc_pos_const_perm,
                                            sc_type_link])
                                            .done(function (it3) {
                                                var answ_cont = it3[0][2];
                                                window.sctpClient.get_link_content(answ_cont, 'string')
                                                    .done(function (content) {
                                                        console.log("query: " + content);
                                                        self.sandbox.updateContent();
                                                    });
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
    var store = this.createStore();
    var mapInterface = React.createElement(MapInterface, {store: store});
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
