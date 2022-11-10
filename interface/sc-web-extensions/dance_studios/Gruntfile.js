module.exports = function (grunt) {
    const dance_studiosDirPath = './dance_studios/';

    const scWebDirPath = '../../../ostis-web-platform/sc-web';
    const clientJsDirPath = scWebDirPath + '/client/static/components/js/';
    const clientCssDirPath = scWebDirPath + '/client/static/components/css/';
    const clientHtmlDirPath = scWebDirPath + '/client/static/components/html/';
    const clientImgDirPath = scWebDirPath + '/client/static/components/images/';
    const kbPath = '../../../kb/';

    grunt.initConfig({
        concat: {
            dance_studios: {
                src: [dance_studiosDirPath + 'src/*.js'],
                dest: dance_studiosDirPath + 'static/js/dance_studios.js'
            },
        },
        copy: {
            dance_studiosJs: {
                cwd: dance_studiosDirPath + 'static/js/',
                src: 'dance_studios.js',
                dest: clientJsDirPath + 'dance_studios/',
                expand: true,
                flatten: true
            },
            dance_studiosCss: {
                cwd: dance_studiosDirPath + 'static/css/',
                src: '*.css',
                dest: clientCssDirPath,
                expand: true,
                flatten: true
            },
            dance_studiosHtml: {
                cwd: dance_studiosDirPath + 'static/html/',
                src: ['*.html'],
                dest: clientHtmlDirPath,
                expand: true,
                flatten: true
            },
            dance_studiosImg: {
                cwd: dance_studiosDirPath + 'static/images/',
                src: '*.png',
                dest: clientImgDirPath + 'dance_studios/',
                expand: true,
                flatten: true
            }
        },
        watch: {
            dance_studiosJs: {
                files: dance_studiosDirPath + 'src/**',
                tasks: ['concat:dance_studios', 'copy:dance_studiosJs'],
            },
            dance_studiosCss: {
                files: dance_studiosDirPath + 'static/css/**',
                tasks: ['copy:dance_studiosCss'],
            },
            dance_studiosHtml: {
                files: [dance_studiosDirPath + 'static/html/**'],
                tasks: ['copy:dance_studiosHtml'],
            },
            dance_studiosImg: {
                files: [dance_studiosDirPath + 'static/images/**'],
                tasks: ['copy:dance_studiosImg'],
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
