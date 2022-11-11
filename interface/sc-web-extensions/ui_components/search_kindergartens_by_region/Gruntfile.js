module.exports = function(grunt) {

    var tasks = require('./grunt_tasks.js')();

    grunt.initConfig(tasks);

    require('load-grunt-tasks')(grunt);
    grunt.loadNpmTasks('grunt-exec');
    grunt.registerTask('build', ['concat', 'copy', 'exec:updateCssAndJs']);
    grunt.registerTask('default', ['concat', 'copy', 'exec:updateCssAndJs', 'watch']);
};
