const MapUtils = {
    SQUARE_SIDE: 0.0001,
    doOSMQuery: function (query, callback) {
        $.ajax({
            method: 'POST',
            url: "http://overpass-api.de/api/interpreter",
            data: {
                data: query
            },
            success: callback
        })
    },
    getOSMQueryForCoordinates: function (coordinates) {
        let square = [
            coordinates.lat - MapUtils.SQUARE_SIDE,
            coordinates.lng - MapUtils.SQUARE_SIDE,
            coordinates.lat + MapUtils.SQUARE_SIDE,
            coordinates.lng + MapUtils.SQUARE_SIDE
        ].join(",");
        return MapUtils.getOSMQuery(
            "node(" + square + ");" +
            "way(" + square + ");" +
            "relation(" + square + ");"
        );
    },
    getOSMQuery: function (query) {
        query = query.trim();
        if (/\[out:json\];/.test(query) || /out skel qt/.test(query)) return query;
        if (/^\([^)]+\);/.test(query)) return '[out:json];' + query + 'out body; >; out skel qt;';
        return '[out:json];(' + query + '); out body; >; out skel qt;';
    },
    empty: function (geojson) {
        return !geojson || !geojson.features || !geojson.features.length;
    },
    importer: function (coordinates) {
        const contour = MapStore.get().contour;
        return {
            import: function () {
                MapUtils.doOSMQuery(MapUtils.getOSMQueryForCoordinates(coordinates), (data) => {
                    data.elements.map((element) => {
                        if (element["tags"] && element["tags"]["name"])
                            this.createNode(element);
                    });
                });
            },
            createNode: function (element) {
                let constr = new sc.ScConstruction();
                constr.createNode(sc.ScType.NodeConst);
                window.scClient.createElements(constr)
                .then(elems => {
                    element["ostisId"] = elems[0];
                    $.when(this.importIdentifier(element), this.importQuery(element))
                    .done(() => {
                        console.log("Created");
                        this.addToContour(element);
                    })
                    .fail(() => {
                        console.log("Failed to import");
                    })
                });
            },
            showModal: function (element) {
                $.toast(element["tags"]["name"] + " добавлен на карту");
            },
            importIdentifier: function (element) {
                return new Promise(resolve => {
                    let constr = new sc.ScConstruction();
                    constr.createLink(
                        sc.ScType.LinkConst,
                        new sc.ScLinkContent(element, element["tags"]["name"]),
                        "_link"
                    );
                    constr.createEdge(
                        sc.ScType.EdgeDCommonConst,
                        new sc.ScAddr(element["ostisId"]),
                        "_link",
                        "_arc"
                    );
                    constr.createEdge(
                        sc.ScType.EdgeAccessConstPosPerm,
                        new sc.ScAddr(MapKeynodes.get("nrel_main_idtf")),
                        "_arc"
                    );
                    constr.createEdge(
                        sc.ScType.EdgeAccessConstPosPerm,
                        new sc.ScAddr(MapKeynodes.get("lang_ru")),
                        "_link"
                    );
                    window.scClient.createElements(constr).then(resolve);
                });
            },
            importQuery: function (element) {
                return new Promise(resolve => {
                    let constr = new sc.ScConstruction();
                    constr.createLink(
                        sc.ScType.LinkConst,
                        new sc.ScLinkContent(element, element["type"] + "(" + element["id"] + ");"),
                        "_link"
                    );
                    constr.createEdge(
                        sc.ScType.EdgeDCommonConst,
                        new sc.ScAddr(element["ostisId"]),
                        "_link",
                        "_arc"
                    );
                    constr.createEdge(
                        sc.ScType.EdgeAccessConstPosPerm,
                        new sc.ScAddr(MapKeynodes.get("nrel_osm_query")),
                        "_arc"
                    );
                    window.scClient.createElements(constr).then(resolve);
                });
            },
            addToContour: function (element) {
                console.log(contour);
                console.log(element["ostisId"]);
                let constr = new sc.ScConstruction();
                constr.createEdge(
                    sc.ScType.EdgeAccessConstPosPerm,
                    new sc.ScAddr(contour),
                    new sc.ScAddr(element["ostisId"]),
                );
                window.scClient.createElements(constr)
                .then(_ => {
                    this.showModal(element);
                });
            }
        }
    },
    extractor: function (arc) {
        const contour = MapStore.get().contour;
        return {
            extract: function () {
                let self = this;
                const question = $('a.history-item.active').attr("sc_addr");
                let template = new sc.ScTemplate();
                template.triple(
                    new sc.ScAddr(parseInt(question)),
                    sc.ScType.EdgeAccessVarPosPerm,
                    sc.ScType.NodeVar
                );
                window.scClient.templateSearch(template)
                .then(result => {
                    const question_arg = result[0].get(2);
                    self.checkTerrainObject(question_arg.value)
                    .then(() => {
                        self.extractIdentifier(question_arg.value);
                        self.extractCoordinates(question_arg.value);
                    })
                })
            },
            checkTerrainObject: async function (object) {
                let template = new sc.ScTemplate();
                template.triple(
                    new sc.ScAddr(object),
                    sc.ScType.EdgeDCommonVar,
                    sc.ScType.LinkVar,
                    sc.ScType.EdgeAccessVarPosPerm,
                    new sc.ScAddr(MapKeynodes.get("nrel_osm_query"))
                );
                return await window.scClient.templateSearch(template);
            },
            extractIdentifier: function (object) {
                let template = new sc.ScTemplate();
                template.tripleWithRelation(
                    new sc.ScAddr(object),
                    sc.ScType.EdgeDCommonVar,
                    [sc.ScType.LinkVar, "_link"],
                    sc.ScType.EdgeAccessVarPosPerm,
                    new sc.ScAddr(MapKeynodes.get("nrel_main_idtf"))
                );
                template.triple(
                    new sc.ScAddr(MapKeynodes.get("lang_ru")),
                    sc.ScType.EdgeAccessVarPosPerm,
                    "_link"
                );
                window.scClient.templateSearch(template)
                .then(result => {
                    window.scClient.getLinkContents([result[0].get("_link")])
                    .then(result => {
                        fluxify.doAction('changeObject', {id: object, title: result[0].data});
                    });
                });
            },
            extractImage: function (object) {
                let template = new sc.ScTemplate();
                template.tripleWithRelation(
                    [sc.ScType.NodeVar, "_node"],
                    sc.ScType.EdgeDCommonVar,
                    new sc.ScAddr(object),
                    sc.ScType.EdgeAccessVarPosPerm,
                    new sc.ScAddr(MapKeynodes.get("rrel_key_sc_element"))
                );
                template.triple(
                    new sc.ScAddr(MapKeynodes.get("sc_illustration")),
                    sc.ScType.EdgeAccessVarPosPerm,
                    "_node"
                );
                template.tripleWithRelation(
                    [sc.ScType.NodeVar, "_translation_node"],
                    sc.ScType.EdgeDCommonVar,
                    "_node",
                    sc.ScType.EdgeAccessVarPosPerm,
                    new sc.ScAddr(MapKeynodes.get("nrel_sc_text_translation"))
                );
                template.tripleWithRelation(
                    "_translation_node",
                    sc.ScType.EdgeDCommonVar,
                    [sc.ScType.LinkVar, "_image_link"],
                    sc.ScType.EdgeAccessVarPosPerm,
                    new sc.ScAddr(MapKeynodes.get("rrel_example"))
                );
                window.scClient.templateSearch(template)
                .then(result => {
                    window.scClient.getLinkContents([result[0].get("_image_link")])
                    .then(linkResult => {
                        fluxify.doAction('changeObject', {id: object, image: linkResult[0].data});
                    });
                });
            },
            extractDescription: function (object) {
                let template = new sc.ScTemplate();
                template.tripleWithRelation(
                    [sc.ScType.NodeVar, "_node"],
                    sc.ScType.EdgeDCommonVar,
                    new sc.ScAddr(object),
                    sc.ScType.EdgeAccessVarPosPerm,
                    new sc.ScAddr(MapKeynodes.get("rrel_key_sc_element"))
                );
                template.triple(
                    new sc.ScAddr(MapKeynodes.get("sc_definition")),
                    sc.ScType.EdgeAccessVarPosPerm,
                    "_node"
                );
                template.tripleWithRelation(
                    [sc.ScType.NodeVar, "_translation_node"],
                    sc.ScType.EdgeDCommonVar,
                    "_node",
                    sc.ScType.EdgeAccessVarPosPerm,
                    new sc.ScAddr(MapKeynodes.get("nrel_sc_text_translation"))
                );
                template.tripleWithRelation(
                    "_translation_node",
                    sc.ScType.EdgeDCommonVar,
                    [sc.ScType.LinkVar, "_description_link"],
                    sc.ScType.EdgeAccessVarPosPerm,
                    new sc.ScAddr(MapKeynodes.get("rrel_example"))
                );
                template.triple(
                    new sc.ScAddr(MapKeynodes.get("lang_ru")),
                    sc.ScType.EdgeAccessVarPosPerm,
                    "_description_link"
                );
                window.scClient.templateSearch(template)
                .then(result => {
                    window.scClient.getLinkContents([result[0].get("_description_link")])
                    .then(descriptions => {
                        fluxify.doAction('changeObject', {id: object, description: descriptions[0].data});
                    });
                });
            },
            extractCoordinates: function (object) {
                let template = new sc.ScTemplate();
                template.tripleWithRelation(
                    new sc.ScAddr(object),
                    sc.ScType.EdgeDCommonVar,
                    [sc.ScType.LinkVar, "_query_link"],
                    sc.ScType.EdgeAccessVarPosPerm,
                    new sc.ScAddr(MapKeynodes.get("nrel_osm_query"))
                );
                window.scClient.templateSearch(template)
                .then(result => {
                    window.scClient.getLinkContents([result[0].get("_description_link")])
                    .then(quieries => {
                        self.extractGeoJSON(object, quieries[0].data);
                    });
                });
            },
            extractGeoJSON: function (id, query) {
                MapUtils.doOSMQuery(MapUtils.getOSMQuery(query), function (data) {
                    fluxify.doAction('changeObject', {id: id, geojson: osmtogeojson(data)});
                })
            },
        }
    }
}