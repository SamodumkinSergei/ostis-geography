StreetTranslatorComponent = {
    ext_lang: 'street_translator_code',
    formats: ['format_street_translator'],
    struct_support: true,

    factory: function (sandbox) {
        return new StreetTranslatorWindow(sandbox);
    }
};

StreetTranslatorWindow = function (sandbox) {

    this.sandbox = sandbox;
    this.sandbox.container = sandbox.container;

    const keynodes = ['ui_street_translator_enName_input', 'ui_street_translator_ruName_input', 'ui_street_translator_count_input',
        'ui_street_translator_button'];
    const answerButton = '#streetTranslator-' + sandbox.container + " #translate-button";
    const nameInEnglish = '#streetTranslator-' + sandbox.container + " #nameInEnglish";
    const nameInRussian = '#streetTranslator-' + sandbox.container + " #nameInRussian";
    const count = '#streetTranslator-' + sandbox.container + " #count";

    $('#' + sandbox.container).prepend('<div id="streetTranslator-' + sandbox.container + '"></div>');

    $('#streetTranslator-' + sandbox.container).load('static/components/html/street_translator.html', function () {
        getUIComponentsIdentifiers();
        $(answerButton).click(function (event) {
            event.preventDefault();
            let englishName = $(nameInEnglish).attr('sc_addr');
            let russanName = $(nameInRussian).attr('sc_addr');
            let countNum = $(count).attr('sc_addr');
            startTranslation(englishName, russanName, countNum);
        });
    });

    this.applyTranslation = function () {
        getUIComponentsIdentifiers();
    };

    function getUIComponentsIdentifiers() {
        SCWeb.core.Server.resolveScAddr(keynodes, function (keynodes) {
            SCWeb.core.Server.resolveIdentifiers(keynodes, function (identifiers) {
                let enNameComponentScAddr = keynodes['ui_street_translator_enName_input'];
                let enNameComponentText = identifiers[enNameComponentScAddr];
                //$(nameInEnglish).html(enNameComponentText);
                $(nameInEnglish).attr('sc_addr', enNameComponentScAddr);
                let ruNameComponentScAddr = keynodes['ui_street_translator_ruName_input'];
                let ruNameComponentText = identifiers[ruNameComponentScAddr];
                //$(nameInRussian).html(ruNameComponentText);
                $(nameInRussian).attr('sc_addr', ruNameComponentScAddr);
                let countScAddr = keynodes['ui_street_translator_count_input'];
                let countText = identifiers[countScAddr];
                //$(count).html(countText);
                $(count).attr('sc_addr', countScAddr);
                let translateButtonText = identifiers[keynodes['ui_street_translator_button']];
                $(answerButton).html(translateButtonText);
            });
        });
    }

    function startTranslation(enNameAddr, ruNameAddr, countAddr) {
        const actionName = "ui_menu_street_translator";
        SCWeb.core.Server.resolveScAddr([actionName], function (keynodes) {
            let actionScAddr = keynodes[actionName];
            SCWeb.core.Main.doCommand(actionScAddr, [enNameAddr, ruNameAddr, countAddr], function (res) {
                //SCWeb.ui.WindowManager.appendHistoryItem(res.question);
            })
        })
    }

    this.sandbox.eventApplyTranslation = $.proxy(this.applyTranslation, this);
};

SCWeb.core.ComponentManager.appendComponentInitialize(StreetTranslatorComponent);