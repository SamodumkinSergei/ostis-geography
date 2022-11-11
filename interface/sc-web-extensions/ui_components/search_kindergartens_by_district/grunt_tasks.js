module.exports = function() {


    var kb = 'kb/ui_components/search_kindergartens_by_district_component';
    var components = 'sc-web/components/search_kindergartens_by_district_component/';
    var clientJsDirPath = '../../../../ostis-web-platform/sc-web/client/static/components/js/';
    var clientCssDirPath = '../../../../ostis-web-platform/sc-web/client/static/components/css/';
    var clientHtmlDirPath = '../../../../ostis-web-platform/sc-web/client/static/components/html/';
    var clientImgDirPath = '../../../../ostis-web-platform/sc-web/client/static/components/images/';


    return  {
        concat: {
            search_kindergartens_by_district_component: {
                src: [
                    components + 'src/search_kindergartens_by_district_component.js'],
                dest: clientJsDirPath + 'search_kindergartens_by_district_component/search_kindergartens_by_district_component.js'
            }
        },
        copy: {
            search_kindergartens_by_district_component_IMG: {
                cwd: components + 'static/components/images/',
                src: ['*'],
                dest: clientImgDirPath + 'search_kindergartens_by_district_component/',
                expand: true,
                flatten: true
            },
            search_kindergartens_by_district_component_CSS: {
                cwd: components + 'static/components/css/',
                src: ['search_kindergartens_by_district_component.css'],
                dest: clientCssDirPath,
                expand: true,
                flatten: true
            },
            search_kindergartens_by_district_component_HTML: {
                cwd: components + 'static/components/html/',
                src: ['*.html'],
                dest: clientHtmlDirPath,
                expand: true,
                flatten: true
            },
            kb: {
                cwd: kb,
                src: ['*'],
                dest: '../../../../kb/ui_components/search_kindergartens_by_district_component/',
                expand: true,
                flatten: true
            }
        },
        watch: {
            search_kindergartens_by_district_component: {
                files: components + 'src/**',
                tasks: ['concat:search_kindergartens_by_district_component']
            },
            search_kindergartens_by_district_component_IMG: {
                files: [components + 'static/components/images/**'],
                tasks: ['copy:search_kindergartens_by_district_component_IMG']
            },
            search_kindergartens_by_district_component_CSS: {
                files: [components + 'static/components/css/**'],
                tasks: ['copy:search_kindergartens_by_district_component_CSS']
            },
            search_kindergartens_by_district_component_HTML: {
                files: [components + 'static/components/html/**',],
                tasks: ['copy:search_kindergartens_by_district_component_HTML']
            },
            copyKB: {
                files: [kb + '**',],
                tasks: ['copy:kb']
            }
        },
        exec: {
          updateCssAndJs: 'sh add-css-and-js.sh'
        }
    }
};

