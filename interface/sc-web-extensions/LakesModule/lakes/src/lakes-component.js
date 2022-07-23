LakesComponent = {
    ext_lang: 'lakes_code',
    formats: ['format_lakes'],
    struct_support: true,
    concept_square: 0,
    concept_lake: 0,
    nrel_area: 0,
    factory: function (sandbox) {
        return new LakesWindow(sandbox);
    }
};

LakesWindow = function (sandbox) {

    this.sandbox = sandbox;
    this.sandbox.container = sandbox.container;

    const keynodes = ['ui_lakes_text_component', 'ui_lakes_search_component', 'ui_lakes_answer_button',
    'ui_lakes_info_block', 'concept_square', 'concept_lake', 'nrel_area'];
    const minArea = '#lakes-' + sandbox.container + " #min-area";
    const maxArea = '#lakes-' + sandbox.container + " #max-area";
    const answerButton = '#lakes-' + sandbox.container + " #answer-button1";
    const infoBlock = '#lakes-' + sandbox.container + " #info"

    $('#' + sandbox.container).prepend('<div id="lakes-' + sandbox.container + '"></div>');

    $('#lakes-' + sandbox.container).load('static/components/html/lakes.html', function () {
        getUIComponentsIdentifiers();

        $(answerButton).click(function (event) {
            event.preventDefault();
            let minAreaValue = $(minArea).val();
            let maxAreaValue = $(maxArea).val();
            if (minAreaValue && maxAreaValue) {
                findLakesByArea(parseInt(minAreaValue), parseInt(maxAreaValue));
            }
        });
    });

    this.applyTranslation = function () {
        getUIComponentsIdentifiers();
    };

    function getUIComponentsIdentifiers() {
        SCWeb.core.Server.resolveScAddr(keynodes, function (keynodes) {
            SCWeb.core.Server.resolveIdentifiers(keynodes, function (identifiers) {
                let searchComponentScAddr = keynodes['ui_lakes_search_component'];
                let searchComponentText = identifiers[searchComponentScAddr];
                $(answerButton).html(searchComponentText);
                $(answerButton).attr('sc_addr', searchComponentScAddr);
                LakesComponent.concept_square = keynodes['concept_square'];
                LakesComponent.concept_lake = keynodes['concept_lake'];
                LakesComponent.nrel_area = keynodes['nrel_area'];
            });
        });
    }

    function findLakesByArea(minArea, maxArea) {
        window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_3F_A_A, [
            LakesComponent.concept_lake,
            sc_type_arc_pos_const_perm,
            sc_type_node]).
            done(function(identifiers) {
                for (let i = 0; i < identifiers.length; ++i) {
                    let lake = identifiers[i][2];
                    window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_5F_A_A_A_F, [
                        identifiers[i][2],
                        sc_type_arc_common | sc_type_const,
                        sc_type_link,
                        sc_type_arc_pos_const_perm,
                        LakesComponent.nrel_area
                    ]).done(function (identifiers) {
                        SCWeb.core.Server.resolveIdentifiers([identifiers[0][2], lake], function (keynodes) {
                            window.sctpClient.get_link_content(identifiers[0][2], 'string').done(function (content) {
                                let area = parseInt(content);
                                if (area >= minArea && area <= maxArea) {
                                    $('#info').html($('#info').html() + keynodes[lake] + "<br/>");
                                }}); 
                            
                        });
                    });
                }
            });
    }
};

SCWeb.core.ComponentManager.appendComponentInitialize(LakesComponent);
