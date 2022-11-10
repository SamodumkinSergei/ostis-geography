DanceStudiosComponent = {
    ext_lang: 'dance_studios_code',
    formats: ['format_dance_studios'],
    struct_support: true,
    concept_year_of_foundation: 0,
    concept_dance_studio: 0,
    nrel_year_of_foundation: 0,
    factory: function (sandbox) {
        return new DanceStudiosWindow(sandbox);
    }
};

DanceStudiosWindow = function (sandbox) {

    this.sandbox = sandbox;
    this.sandbox.container = sandbox.container;

    const keynodes = ['ui_dance_studios_text_component', 'ui_dance_studios_search_component', 'ui_dance_studios_answer_button',
    'ui_dance_studios_info_block', 'concept_year_of_foundation', 'concept_dance_studio', 'nrel_year_of_foundation'];
    const foundYear = '#dance_studios-' + sandbox.container + " #found-year";
    const answerButton = '#dance_studios-' + sandbox.container + " #answer-button1";
    const infoBlock = '#dance_studios-' + sandbox.container + " #info"

    $('#' + sandbox.container).prepend('<div id="dance_studios-' + sandbox.container + '"></div>');

    $('#dance_studios-' + sandbox.container).load('static/components/html/dance_studios.html', function () {
        getUIComponentsIdentifiers();

        $(answerButton).click(function (event) {
            event.preventDefault();
            let foundYearValue = $(foundYear).val();
          
            
            if (foundYearValue) {
                findDanceStudiosByFoundingYear(parseInt(foundYearValue));
            }
        });
    });

    this.applyTranslation = function () {
        getUIComponentsIdentifiers();
    };

    function getUIComponentsIdentifiers() {
        SCWeb.core.Server.resolveScAddr(keynodes, function (keynodes) {
            SCWeb.core.Server.resolveIdentifiers(keynodes, function (identifiers) {
                let searchComponentScAddr = keynodes['ui_dance_studios_search_component'];
                let searchComponentText = identifiers[searchComponentScAddr];
                $(answerButton).html(searchComponentText);
                $(answerButton).attr('sc_addr', searchComponentScAddr);
                DanceStudiosComponent.concept_year_of_foundation = keynodes['concept_year_of_foundation'];
                DanceStudiosComponent.concept_dance_studio = keynodes['concept_dance_studio'];
                DanceStudiosComponent.nrel_year_of_foundation = keynodes['nrel_year_of_foundation'];
            });
        });
    }

    function findDanceStudiosByFoundingYear(foundYear) {
        window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_3F_A_A, [
            DanceStudiosComponent.concept_dance_studio,
            sc_type_arc_pos_const_perm,
            sc_type_node]).
            done(function(identifiers) {
                for (let i = 0; i < identifiers.length; ++i) {
                    let dance_studio = identifiers[i][2];
                    window.sctpClient.iterate_elements(SctpIteratorType.SCTP_ITERATOR_5F_A_A_A_F, [
                        identifiers[i][2],
                        sc_type_arc_common | sc_type_const,
                        sc_type_node,
                        sc_type_arc_pos_const_perm,
                        DanceStudiosComponent.nrel_year_of_foundation
                    ]).done(function (identifiers) {
                        SCWeb.core.Server.resolveIdentifiers([identifiers[0][2], dance_studio], function (keynodes) {
                            let year_of_foundation = parseInt(keynodes[identifiers[0][2]]);

                            if (year_of_foundation == foundYear) {
                                document.getElementById("info").innerHTML += keynodes[dance_studio] + "<br/>";
                            }
                        });
                    });
                }
            });
    }
};

SCWeb.core.ComponentManager.appendComponentInitialize(DanceStudiosComponent);
