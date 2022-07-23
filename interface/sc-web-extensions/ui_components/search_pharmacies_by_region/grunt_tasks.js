module.exports = function() {

    var kb = 'kb/ui_components/search_pharmacies_by_region_component';
    var components = 'sc-web/components/search_pharmacies_by_region_component/';
    var clientJsDirPath = '../../../../ostis-web-platform/sc-web/client/static/components/js/';
    var clientCssDirPath = '../../../../ostis-web-platform/sc-web/client/static/components/css/';
    var clientHtmlDirPath = '../../../../ostis-web-platform/sc-web/client/static/components/html/';
    var clientImgDirPath = '../../../../ostis-web-platform/sc-web/client/static/components/images/';

    return  {
        concat: {
            search_pharmacies_by_region_component: {
                src: [
                    components + 'src/search_pharmacies_by_region_component.js'],
                dest: clientJsDirPath + 'search_pharmacies_by_region_component/search_pharmacies_by_region_component.js'
            }
        },
        copy: {
            search_pharmacies_by_region_component_IMG: {
                cwd: components + 'static/components/images/',
                src: ['*'],
                dest: clientImgDirPath + 'search_pharmacies_by_region_component/',
                expand: true,
                flatten: true
            },
            search_pharmacies_by_region_component_CSS: {
                cwd: components + 'static/components/css/',
                src: ['search_pharmacies_by_region_component.css'],
                dest: clientCssDirPath,
                expand: true,
                flatten: true
            },
            search_pharmacies_by_region_component_HTML: {
                cwd: components + 'static/components/html/',
                src: ['*.html'],
                dest: clientHtmlDirPath,
                expand: true,
                flatten: true
            },
            kb: {
                cwd: kb,
                src: ['*'],
                dest: '../../../../kb/ui_components/search_pharmacies_by_region_component/',
                expand: true,
                flatten: true
            }
        },
        watch: {
            search_pharmacies_by_region_component: {
                files: components + 'src/**',
                tasks: ['concat:search_pharmacies_by_region_component']
            },
            search_pharmacies_by_region_component_IMG: {
                files: [components + 'static/components/images/**'],
                tasks: ['copy:search_pharmacies_by_region_component_IMG']
            },
            search_pharmacies_by_region_component_CSS: {
                files: [components + 'static/components/css/**'],
                tasks: ['copy:search_pharmacies_by_region_component_CSS']
            },
            search_pharmacies_by_region_component_HTML: {
                files: [components + 'static/components/html/**',],
                tasks: ['copy:search_pharmacies_by_region_component_HTML']
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

