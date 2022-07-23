module.exports = function (grunt) {
    const translatorDirPath = './translator/';

    const scWebDirPath = '../../ostis-web-platform/sc-web';
    const clientJsDirPath = scWebDirPath + '/client/static/components/js/';
    const clientCssDirPath = scWebDirPath + '/client/static/components/css/';
    const clientHtmlDirPath = scWebDirPath + '/client/static/components/html/';
    const clientImgDirPath = scWebDirPath + '/client/static/components/images/';

    grunt.initConfig({
        concat: {
            translator: {
                src: [translatorDirPath + 'src/*.js'],
                dest: translatorDirPath + 'static/js/translator.js'
            },
        },
        copy: {
            translatorJs: {
                cwd: translatorDirPath + 'static/js/',
                src: 'translator.js',
                dest: clientJsDirPath + 'translator/',
                expand: true,
                flatten: true
            },
            translatorCss: {
                cwd: translatorDirPath + 'static/css/',
                src: '*.css',
                dest: clientCssDirPath,
                expand: true,
                flatten: true
            },
            translatorHtml: {
                cwd: translatorDirPath + 'static/html/',
                src: ['*.html'],
                dest: clientHtmlDirPath,
                expand: true,
                flatten: true
            },
            translatorImg: {
                cwd: translatorDirPath + 'static/images/',
                src: '*.png',
                dest: clientImgDirPath + 'translator/',
                expand: true,
                flatten: true
            }
        },
        watch: {
            translatorJs: {
                files: translatorDirPath + 'src/**',
                tasks: ['concat:translator', 'copy:translatorJs'],
            },
            translatorCss: {
                files: translatorDirPath + 'static/css/**',
                tasks: ['copy:translatorCss'],
            },
            translatorHtml: {
                files: [translatorDirPath + 'static/html/**'],
                tasks: ['copy:translatorHtml'],
            },
            translatorImg: {
                files: [translatorDirPath + 'static/images/**'],
                tasks: ['copy:translatorImg'],
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
