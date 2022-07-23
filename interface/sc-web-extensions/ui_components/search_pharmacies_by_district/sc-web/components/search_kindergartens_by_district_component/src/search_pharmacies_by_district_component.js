SearchpharmaciesByDistrictComponent = {
    ext_lang: 'search_pharmacies_by_district_code',
    formats: ['format_search_pharmacies_by_district_json'],
    struct_support: true,

    factory: function (sandbox) {
        return new setSearchpharmaciesByDistrictViewerWindow(sandbox);
    }
};

var setSearchpharmaciesByDistrictViewerWindow = function (sandbox) {

    var self = this;
    this.sandbox = sandbox;
    this.sandbox.container = sandbox.container;

    var inputSeasons = '#series-tools-' + sandbox.container + " #series_district-input"

    var buttonFind = '#series-tools-' + sandbox.container + " #button-find-series-district";

    var keynodes = ['ui_search_pharmacies_by_district_in_memory'];

    $('#' + sandbox.container).prepend('<div class="inputBox" id="series-tools-' + sandbox.container + '"></div>');
    $('#series-tools-' + sandbox.container).load('static/components/html/search_pharmacies_by_district_component.html', function () {
        SCWeb.core.Server.resolveScAddr(keynodes, function (keynodes) {
            SCWeb.core.Server.resolveIdentifiers(keynodes, function (idf) {
                var buttonSearch = idf[keynodes['ui_search_pharmacies_by_district_in_memory']];

                $(buttonFind).html(buttonSearch);
                $(buttonFind).click(function () {
                    var districtString = $(inputSeasons).val();

                    console.log("pharmacies find district string" + districtString);

                    if (districtString) {
                        var searchParams = {
                            District: districtString.toString()
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
                var buttonLoad = idf[keynodes['ui_search_pharmacies_by_district_in_memory']];

                $(buttonFind).html(buttonLoad);
            });
        });
    };
    this.sandbox.eventApplyTranslation = $.proxy(this.applyTranslation, this);
};

SCWeb.core.ComponentManager.appendComponentInitialize(SearchpharmaciesBydistrictComponent);

function findFilms(searchParams) {
    console.log(searchParams);
    
    SCWeb.core.Server.resolveScAddr([searchParams.District], function (keynodes) {
        addr1 = keynodes[searchParams.District];
        console.log("addr1", addr1);
        console.log("arguments", SCWeb.core.Arguments._arguments);
        SCWeb.core.Server.resolveScAddr(["ui_menu_get_pharmacies_by_district"], function (data) {
            var cmd = data["ui_menu_get_pharmacies_by_district"];
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
