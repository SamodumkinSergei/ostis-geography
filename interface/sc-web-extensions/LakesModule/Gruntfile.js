module.exports = function (grunt) {
    const lakesDirPath = './lakes/';

    const scWebDirPath = '../../../ostis-web-platform/sc-web';
    const clientJsDirPath = scWebDirPath + '/client/static/components/js/';
    const clientCssDirPath = scWebDirPath + '/client/static/components/css/';
    const clientHtmlDirPath = scWebDirPath + '/client/static/components/html/';
    const clientImgDirPath = scWebDirPath + '/client/static/components/images/';
    const kbPath = '../../../kb/';

    grunt.initConfig({
        concat: {
            lakes: {
                src: [lakesDirPath + 'src/*.js'],
                dest: lakesDirPath + 'static/js/lakes.js'
            },
        },
        copy: {
            lakesJs: {
                cwd: lakesDirPath + 'static/js/',
                src: 'lakes.js',
                dest: clientJsDirPath + 'lakes/',
                expand: true,
                flatten: true
            },
            lakesCss: {
                cwd: lakesDirPath + 'static/css/',
                src: '*.css',
                dest: clientCssDirPath,
                expand: true,
                flatten: true
            },
            lakesHtml: {
                cwd: lakesDirPath + 'static/html/',
                src: ['*.html'],
                dest: clientHtmlDirPath,
                expand: true,
                flatten: true
            },
            lakesImg: {
                cwd: lakesDirPath + 'static/images/',
                src: '*.png',
                dest: clientImgDirPath + 'lakes/',
                expand: true,
                flatten: true
            },
            lakesKb: {
                cwd: lakesDirPath + 'kb/',
                src: '*.scs',
                dest: kbPath + 'lakes/',
                expand: true,
                flatten: true
            },
        },
        watch: {
            lakesJs: {
                files: lakesDirPath + 'src/**',
                tasks: ['concat:lakes', 'copy:lakesJs'],
            },
            lakesCss: {
                files: lakesDirPath + 'static/css/**',
                tasks: ['copy:lakesCss'],
            },
            lakesHtml: {
                files: [lakesDirPath + 'static/html/**'],
                tasks: ['copy:lakesHtml'],
            },
            lakesImg: {
                files: [lakesDirPath + 'static/images/**'],
                tasks: ['copy:lakesImg'],
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
