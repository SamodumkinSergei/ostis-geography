module.exports = function (grunt) {
    const street_translatorDirPath = './street_translator/';

    const scWebDirPath = '../../../ostis-web-platform/sc-web';
    const clientJsDirPath = scWebDirPath + '/client/static/components/js/';
    const clientCssDirPath = scWebDirPath + '/client/static/components/css/';
    const clientHtmlDirPath = scWebDirPath + '/client/static/components/html/';
    const clientImgDirPath = scWebDirPath + '/client/static/components/images/';

    grunt.initConfig({
        concat: {
            street_translator: {
                src: [street_translatorDirPath + 'src/*.js'],
                dest: street_translatorDirPath + 'static/js/street_translator.js'
            },
        },
        copy: {
            street_translatorJs: {
                cwd: street_translatorDirPath + 'static/js/',
                src: 'street_translator.js',
                dest: clientJsDirPath + 'street_translator/',
                expand: true,
                flatten: true
            },
            street_translatorCss: {
                cwd: street_translatorDirPath + 'static/css/',
                src: '*.css',
                dest: clientCssDirPath,
                expand: true,
                flatten: true
            },
            street_translatorHtml: {
                cwd: street_translatorDirPath + 'static/html/',
                src: ['*.html'],
                dest: clientHtmlDirPath,
                expand: true,
                flatten: true
            },
            street_translatorImg: {
                cwd: street_translatorDirPath + 'static/images/',
                src: '*.png',
                dest: clientImgDirPath + 'street_translator/',
                expand: true,
                flatten: true
            }
        },
        watch: {
            street_translatorJs: {
                files: street_translatorDirPath + 'src/**',
                tasks: ['concat:street_translator', 'copy:street_translatorJs'],
            },
            street_translatorCss: {
                files: street_translatorDirPath + 'static/css/**',
                tasks: ['copy:street_translatorCss'],
            },
            street_translatorHtml: {
                files: [street_translatorDirPath + 'static/html/**'],
                tasks: ['copy:street_translatorHtml'],
            },
            street_translatorImg: {
                files: [street_translatorDirPath + 'static/images/**'],
                tasks: ['copy:street_translatorImg'],
            },
        },
        exec: {
            updateCssAndJs: 'sh scripts/update_css_and_js.sh'
        }
    });

    grunt.loadNpmTasks('grunt-contrib-concat');
    grunt.loadNpmTasks('grunt-contrib-copy');
    grunt.loadNpmTasks('grunt-contrib-watch');
    grunt.loadNpmTasks('grunt-exec');

    grunt.registerTask('default', ['concat', 'copy', 'exec:updateCssAndJs', 'watch']);
    grunt.registerTask('build', ['concat', 'copy', 'exec:updateCssAndJs']);

};