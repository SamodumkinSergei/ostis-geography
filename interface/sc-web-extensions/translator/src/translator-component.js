ExampleComponent = {
    ext_lang: 'example_code',
    formats: ['format_example'],
    struct_support: true,

    factory: function (sandbox) {
        return new ExampleWindow(sandbox);
    }
};

ExampleWindow = function (sandbox) {

    this.sandbox = sandbox;
    this.sandbox.container = sandbox.container;

    const keynodes = ['ui_example_text_component', 'ui_example_search_component', 'ui_example_answer_button',
    'ui_example_info_block'];
    const textComponent = '#example-' + sandbox.container + " #text-component";
    const searchComponent = '#example-' + sandbox.container + " #search-component";
    const answerButton = '#example-' + sandbox.container + " #answer-button";
    const keyword = '#example-' + sandbox.container + " #keyword";
    const infoBlock = '#example-' + sandbox.container + " #info"

    $('#' + sandbox.container).prepend('<div id="example-' + sandbox.container + '"></div>');

    $('#example-' + sandbox.container).load('static/components/html/example.html', function () {
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
                let textComponentScAddr = keynodes['ui_example_text_component'];
                let textComponentText = identifiers[textComponentScAddr];
                $(textComponent).html(textComponentText);
                $(textComponent).attr('sc_addr', textComponentScAddr);
                let searchComponentScAddr = keynodes['ui_example_search_component'];
                let searchComponentText = identifiers[searchComponentScAddr];
                $(searchComponent).html(searchComponentText);
                $(searchComponent).attr('sc_addr', searchComponentScAddr);
                let answerButtonText = identifiers[keynodes['ui_example_answer_button']];
                $(answerButton).html(answerButtonText);
                let infoBlockText = identifiers[keynodes['ui_example_info_block']];
                $(infoBlock).html(infoBlockText);
            });
        });
    }

    function findByIdentifier(identifier) {
        var exec = require('child_process').exec;


        exec(
            "pip install -r ../../../../tools/translator/requirements.txt",
            function (error, stdout, stderr) {
                console.log('stdout: ' + stdout);
                console.log('stderr: ' + stderr);
                if (error !== null) {
                    console.log('exec error: ' + error);
                }
            }
        )
        command = "python3 ../../../../tools/translator/" + identifier
        exec(command,
            function (error, stdout, stderr) {
                console.log('stdout: ' + stdout);
                console.log('stderr: ' + stderr);
                if (error !== null) {
                    console.log('exec error: ' + error);
                }
            });

    }

    this.sandbox.eventApplyTranslation = $.proxy(this.applyTranslation, this);
};

SCWeb.core.ComponentManager.appendComponentInitialize(ExampleComponent);