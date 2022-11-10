ShopComponent = {
    ext_lang: 'shop_code',
    formats: ['format_shop'],
    struct_support: true,

    factory: function (sandbox) {
        return new ShopWindow(sandbox);
    }
};

ShopWindow = function (sandbox) {

    this.sandbox = sandbox;
    this.sandbox.container = sandbox.container;

    const keynodes = ['ui_shop_text_component', 'ui_shop_answer_button'];
    const textComponent = '#shop-' + sandbox.container + " #text-component";
    const answerButton = '#shop-' + sandbox.container + " #answer-button";
    const keyword = '#shop-' + sandbox.container + " #keyword";

    $('#' + sandbox.container).prepend('<div id="shop-' + sandbox.container + '"></div>');

    $('#shop-' + sandbox.container).load('static/components/html/shop.html', function () {
        getUIComponentsIdentifiers();

        $(answerButton).click(function (event) {
            event.preventDefault();
            let keywordText = $(keyword).val();

            if (keywordText) {
                findByIdentifier(keywordText);
            }
        });
    });

    this.applyTranslation = function () {
        getUIComponentsIdentifiers();
    };

    function getUIComponentsIdentifiers() {
        SCWeb.core.Server.resolveScAddr(keynodes, function (keynodes) {
            SCWeb.core.Server.resolveIdentifiers(keynodes, function (identifiers) {
                let textComponentScAddr = keynodes['ui_shop_text_component'];
                let textComponentText = identifiers[textComponentScAddr];
                $(textComponent).html(textComponentText);
                $(textComponent).attr('sc_addr', textComponentScAddr);
                let searchComponentScAddr = keynodes['ui_shop_search_component'];
                let answerButtonText = identifiers[keynodes['ui_shop_answer_button']];
                $(answerButton).html(answerButtonText);
            });
        });
    }

    function findByIdentifier(identifier) {
        const actionName = 'ui_menu_search_shops_in_the_city';
        SCWeb.core.Server.resolveScAddr([actionName, identifier], function (keynodes) {
            let keywordScAddr = keynodes[identifier];
            let actionScAddr = keynodes[actionName];
            if (!keywordScAddr && !actionScAddr){
                return;
            }
            // Simulate click on ui_menu_view_full_semantic_neighborhood button
            SCWeb.core.Main.doCommand(actionScAddr, [keywordScAddr], function (result) {
                // waiting for result
                if (result.question !== undefined) {
                    // append in history
                    SCWeb.ui.WindowManager.appendHistoryItem(result.question);
                }
            });
        });
    }

    this.sandbox.eventApplyTranslation = $.proxy(this.applyTranslation, this);
};

SCWeb.core.ComponentManager.appendComponentInitialize(ShopComponent);
