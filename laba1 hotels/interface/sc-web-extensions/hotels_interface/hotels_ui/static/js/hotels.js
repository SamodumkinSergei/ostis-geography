var hotelsSection = {};

function extend(child, parent) {
    var F = function() {};
    F.prototype = parent.prototype;
    child.prototype = new F();
    child.prototype.constructor = child;
    child.superclass = parent.prototype;
}

hotelsSection.DrawComponent = {
    ext_lang: 'hotels_section',
    formats: ['hotels_json'],
    struct_support: true,
    factory: function(sandbox) {
        return new hotelsSection.DrawWindow(sandbox);
    }
};

hotelsSection.DrawWindow = function(sandbox) {
    this.sandbox = sandbox;
    this.paintPanel = new hotelsSection.PaintPanel(this.sandbox.container);
    this.paintPanel.init();
    this.recieveData = function(data) {
        console.log("in recieve data" + data);
    };

    var scElements = {};

    function drawAllElements() {
        var dfd = new jQuery.Deferred();
        // for (var addr in scElements) {
        jQuery.each(scElements, function(j, val) {
            var obj = scElements[j];
            if (!obj || obj.translated) return;
            // check if object is an arc
            if (obj.data.type & sc_type_arc_pos_const_perm) {
                var begin = obj.data.begin;
                var end = obj.data.end;
                // logic for component update should go here
            }

        });
        SCWeb.ui.Locker.hide();
        dfd.resolve();
        return dfd.promise();
    }

    // resolve keynodes
    var self = this;
    this.needUpdate = false;
    this.requestUpdate = function() {
        var updateVisual = function() {
            // check if object is an arc
            var dfd1 = drawAllElements();
            dfd1.done(function(r) {
                return;
            });


            /// @todo: Don't update if there are no new elements
            window.clearTimeout(self.structTimeout);
            delete self.structTimeout;
            if (self.needUpdate)
                self.requestUpdate();
            return dfd1.promise();
        };
        self.needUpdate = true;
        if (!self.structTimeout) {
            self.needUpdate = false;
            SCWeb.ui.Locker.show();
            self.structTimeout = window.setTimeout(updateVisual, 1000);
        }
    }

    this.eventStructUpdate = function(added, element, arc) {
        window.sctpClient.get_arc(arc).done(function(r) {
            var addr = r[1];
            window.sctpClient.get_element_type(addr).done(function(t) {
                var type = t;
                var obj = new Object();
                obj.data = new Object();
                obj.data.type = type;
                obj.data.addr = addr;
                if (type & sc_type_arc_mask) {
                    window.sctpClient.get_arc(addr).done(function(a) {
                        obj.data.begin = a[0];
                        obj.data.end = a[1];
                        scElements[addr] = obj;
                        self.requestUpdate();
                    });
                }
            });
        });
    };
    // delegate event handlers
    this.sandbox.eventDataAppend = $.proxy(this.receiveData, this);
    this.sandbox.eventStructUpdate = $.proxy(this.eventStructUpdate, this);
    this.sandbox.updateContent();
};
SCWeb.core.ComponentManager.appendComponentInitialize(hotelsSection.DrawComponent);

hotelsSection.PaintPanel = function(containerId) {
    this.containerId = containerId;
};

hotelsSection.PaintPanel.prototype = {

    init: function() {
        this._initMarkup(this.containerId);
    },

    _initMarkup: function(containerId) {
        var container = $('#' + containerId);

        var self = this;
        container.append('<label for="introduction" id="interface"><u><h2>Добро пожаловать в систему, посвященную отелям РБ</h2></u></label>');
        container.append('<label for="hotels" id="hotels"><b><a href="https://ru.wikipedia.org/wiki/Отель" target="_blank">Отель</a><b></label>');

        container.append('<button id="about-hotels" type="button">Что такое отель?</button>');
        $('#about-hotels').click(function() {
            self._hotels();
        });


        container.append('<button id="find_hotels_by_star_rating" type="button">Найти отели по количеству звезд</button>');
        $('#find_hotels_by_star_rating').click(function() {
            self._findHotelsByStarRating();
        });

        container.append('<button id="find_hotels_by_min_price_per_night" type="button">Найти отели по минимальной цене за сутки</button>');
        $('#find_hotels_by_min_price_per_night').click(function() {
            self._findHotelsByMinPricePerNight();
        });
		
		container.append('<button id="find_hotels_by_city_centre_distance" type="button">Найти отели по расстоянию от центра города</button>');
        $('#find_hotels_by_city_centre_distance').click(function() {
            self._findHotelsByCityCentreDistance();
        });

    },

    _findHotelsByStarRating: function() {
        var argOneAddr;
        SCWeb.core.Server.resolveScAddr([SCWeb.core.Arguments._arguments[0]], function(keynodes) {
            console.log("key", keynodes);
            console.log("arguments", SCWeb.core.Arguments._arguments[0]);
            argOneAddr = SCWeb.core.Arguments._arguments[0];
            SCWeb.core.Server.resolveScAddr(["ui_menu_get_hotel_by_star_rating"],
                function(data) {
                    var cmd = data["ui_menu_get_hotel_by_star_rating"];
                    SCWeb.core.Main.doCommand(cmd, [argOneAddr], function(result) {
                        if (result.question != undefined) {
                            SCWeb.ui.WindowManager.appendHistoryItem(result.question);
                        }
                    });
                });
        });
    },

    _findHotelsByMinPricePerNight: function() {
        var argOneAddr;
        SCWeb.core.Server.resolveScAddr([SCWeb.core.Arguments._arguments[0]], function(keynodes) {
            console.log("key", keynodes);
            console.log("arguments", SCWeb.core.Arguments._arguments[0]);
            argOneAddr = SCWeb.core.Arguments._arguments[0];
            SCWeb.core.Server.resolveScAddr(["ui_menu_get_hotel_by_min_price_per_night"],
                function(data) {
                    var cmd = data["ui_menu_get_hotel_by_min_price_per_night"];
                    SCWeb.core.Main.doCommand(cmd, [argOneAddr], function(result) {
                        if (result.question != undefined) {
                            SCWeb.ui.WindowManager.appendHistoryItem(result.question);
                        }
                    });
                });
        });
    },
	
	_findHotelsByCityCentreDistance: function() {
        var argOneAddr;
        SCWeb.core.Server.resolveScAddr([SCWeb.core.Arguments._arguments[0]], function(keynodes) {
            console.log("key", keynodes);
            console.log("arguments", SCWeb.core.Arguments._arguments[0]);
            argOneAddr = SCWeb.core.Arguments._arguments[0];
            SCWeb.core.Server.resolveScAddr(["ui_menu_get_hotel_by_city_centre_distance"],
                function(data) {
                    var cmd = data["ui_menu_get_hotel_by_city_centre_distance"];
                    SCWeb.core.Main.doCommand(cmd, [argOneAddr], function(result) {
                        if (result.question != undefined) {
                            SCWeb.ui.WindowManager.appendHistoryItem(result.question);
                        }
                    });
                });
        });
    },

    _hotels: function() {
        var addr;
        SCWeb.core.Server.resolveScAddr(['concept_hotel'], function(keynodes) {
            addr = keynodes['concept_hotel'];
            SCWeb.core.Server.resolveScAddr(["ui_menu_view_full_semantic_neighborhood"],
                function(data) {
                    var cmd = data["ui_menu_view_full_semantic_neighborhood"];
                    SCWeb.core.Main.doCommand(cmd, [addr], function(result) {
                        if (result.question != undefined) {
                            SCWeb.ui.WindowManager.appendHistoryItem(result.question);
                        }
                    });
                });
        });
    },

    /**/
    _findSubject: function(object) {
        var addr;
        SCWeb.core.Server.resolveScAddr([object], function(keynodes) {
            addr = keynodes[object];
            SCWeb.core.Server.resolveScAddr(["ui_menu_view_full_semantic_neighborhood"],
                function(data) {
                    var cmd = data["ui_menu_view_full_semantic_neighborhood"];
                    SCWeb.core.Main.doCommand(cmd, [addr], function(result) {
                        if (result.question != undefined) {
                            SCWeb.ui.WindowManager.appendHistoryItem(result.question);
                        }
                    });
                });
        });
    },

    _findMainIdentifier: function() {
        console.log("inFind");
        var main_menu_addr, nrel_main_idtf_addr;
        SCWeb.core.Server.resolveScAddr(['ui_main_menu', 'nrel_main_idtf'], function(keynodes) {
            main_menu_addr = keynodes['ui_main_menu'];
            nrel_main_idtf_addr = keynodes['nrel_main_idtf'];
            console.log(main_menu_addr);
            console.log(nrel_main_idtf_addr);
            window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_5F_A_A_A_F, [
                main_menu_addr,
                sc_type_arc_common | sc_type_const,
                sc_type_link,
                sc_type_arc_pos_const_perm,
                nrel_main_idtf_addr
            ]).
            done(function(identifiers) {
                window.sctpClient.get_link_content(identifiers[0][2], 'string').done(function(content) {
                    alert('Главный идентификатор: ' + content);
                });
            });
        });
    },

    _generateNodes: function() {
        var main_menu_addr, nrel_main_idtf_addr, lang_en_addr;
        SCWeb.core.Server.resolveScAddr(['ui_main_menu', 'lang_en', 'nrel_main_idtf'], function(keynodes) {
            main_menu_addr = keynodes['ui_main_menu'];
            nrel_main_idtf_addr = keynodes['nrel_main_idtf'];
            lang_en_addr = keynodes['lang_en'];

            window.sctpClient.create_link().done(function(generatedLink) {
                window.sctpClient.set_link_content(generatedLink, 'Main menu');
                window.sctpClient.create_arc(sc_type_arc_common | sc_type_const, main_menu_addr, generatedLink).done(function(generatedCommonArc) {
                    window.sctpClient.create_arc(sc_type_arc_pos_const_perm, nrel_main_idtf_addr, generatedCommonArc);
                });
                window.sctpClient.create_arc(sc_type_arc_pos_const_perm, lang_en_addr, generatedLink);
            });
            $('#generateNodes').attr("sc_addr", main_menu_addr);
            SCWeb.core.Server.resolveScAddr(["ui_menu_view_full_semantic_neighborhood"],
                function(data) {
                    var cmd = data["ui_menu_view_full_semantic_neighborhood"];
                    SCWeb.core.Main.doCommand(cmd, [main_menu_addr], function(result) {
                        if (result.question != undefined) {
                            SCWeb.ui.WindowManager.appendHistoryItem(result.question);
                        }
                    });
                });
        });
    }
};
