SearchpharmaciesByRegionComponent = {
    ext_lang: 'search_pharmacies_by_region_code',
    formats: ['format_search_pharmacies_by_region_json'],
    struct_support: true,

    factory: function (sandbox) {
        return new setSearchpharmaciesByRegionViewerWindow(sandbox);
    }
};

var setSearchpharmaciesByRegionViewerWindow = function (sandbox) {

    var self = this;
    this.sandbox = sandbox;
    this.sandbox.container = sandbox.container;

    var inputSeasons = '#series-tools-' + sandbox.container + " #series_region-input"

    var buttonFind = '#series-tools-' + sandbox.container + " #button-find-series-region";

    var keynodes = ['ui_search_pharmacies_by_region_in_memory'];

    $('#' + sandbox.container).prepend('<div class="inputBox" id="series-tools-' + sandbox.container + '"></div>');
    $('#series-tools-' + sandbox.container).load('static/components/html/search_pharmacies_by_region_component.html', function () {
        SCWeb.core.Server.resolveScAddr(keynodes, function (keynodes) {
            SCWeb.core.Server.resolveIdentifiers(keynodes, function (idf) {
                var buttonSearch = idf[keynodes['ui_search_pharmacies_by_region_in_memory']];

                $(buttonFind).html(buttonSearch);
                $(buttonFind).click(function () {
                    var RegionString = $(inputSeasons).val();

                    console.log("pharmacies find Region string" + RegionString);

                    if (RegionString) {
                        var searchParams = {
                            Region: RegionString.toString()
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
                var buttonLoad = idf[keynodes['ui_search_pharmacies_by_region_in_memory']];

                $(buttonFind).html(buttonLoad);
            });
        });
    };
    this.sandbox.eventApplyTranslation = $.proxy(this.applyTranslation, this);
};

SCWeb.core.ComponentManager.appendComponentInitialize(SearchpharmaciesByRegionComponent);

function findFilms(searchParams) {
    console.log(searchParams);
    
    SCWeb.core.Server.resolveScAddr([searchParams.Region], function (keynodes) {
        addr1 = keynodes[searchParams.Region];
        console.log("addr1", addr1);
        console.log("arguments", SCWeb.core.Arguments._arguments);
        SCWeb.core.Server.resolveScAddr(["ui_menu_get_pharmacies_by_region"], function (data) {
            var cmd = data["ui_menu_get_pharmacies_by_region"];
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
