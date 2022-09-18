SearchpharmaciesBycityComponent = {
    ext_lang: 'search_pharmacies_by_city_code',
    formats: ['format_search_pharmacies_by_city_json'],
    struct_support: true,

    factory: function (sandbox) {
        return new setSearchpharmaciesBycityViewerWindow(sandbox);
    }
};

var setSearchpharmaciesBycityViewerWindow = function (sandbox) {

    var self = this;
    this.sandbox = sandbox;
    this.sandbox.container = sandbox.container;

    var inputSeasons = '#series-tools-' + sandbox.container + " #series_city-input"

    var buttonFind = '#series-tools-' + sandbox.container + " #button-find-series-city";

    var keynodes = ['ui_search_pharmacies_by_city_in_memory'];

    $('#' + sandbox.container).prepend('<div class="inputBox" id="series-tools-' + sandbox.container + '"></div>');
    $('#series-tools-' + sandbox.container).load('static/components/html/search_pharmacies_by_city_component.html', function () {
        SCWeb.core.Server.resolveScAddr(keynodes, function (keynodes) {
            SCWeb.core.Server.resolveIdentifiers(keynodes, function (idf) {
                var buttonSearch = idf[keynodes['ui_search_pharmacies_by_city_in_memory']];

                $(buttonFind).html(buttonSearch);
                $(buttonFind).click(function () {
                    var cityString = $(inputSeasons).val();

                    console.log("pharmacies find city string" + cityString);

                    if (cityString) {
                        var searchParams = {
                            city: cityString.toString()
                        };

                        findpharmacies(searchParams);
                    }
                });
            });
        });
    });

    this.applyTranslation = function (namesMap) {
        SCWeb.core.Server.resolveScAddr(keynodes, function (keynodes) {
            SCWeb.core.Server.resolveIdentifiers(keynodes, function (idf) {
                var buttonLoad = idf[keynodes['ui_search_pharmacies_by_city_in_memory']];

                $(buttonFind).html(buttonLoad);
            });
        });
    };
    this.sandbox.eventApplyTranslation = $.proxy(this.applyTranslation, this);
};

SCWeb.core.ComponentManager.appendComponentInitialize(SearchpharmaciesBycityComponent);

function findFilms(searchParams) {
    console.log(searchParams);
    
    SCWeb.core.Server.resolveScAddr([searchParams.city], function (keynodes) {
        addr1 = keynodes[searchParams.city];
        console.log("addr1", addr1);
        console.log("arguments", SCWeb.core.Arguments._arguments);
        SCWeb.core.Server.resolveScAddr(["ui_menu_get_pharmacies_by_city"], function (data) {
            var cmd = data["ui_menu_get_pharmacies_by_city"];
            console.log("cmd", cmd);
            SCWeb.core.Main.doCommand(cmd, [addr1], function (result) {
                if (result.question != undefined) {
                    consonle.log(result.question);
                    SCWeb.ui.WindowManager.appendHistoryItem(result.question);
                }
            });
        });
    });
}
