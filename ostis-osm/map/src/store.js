MapStore = {
  get: function() {
    this.store = this.store || this.create();
    return this.store;
  },

  create: function() {
    return fluxify.createStore({
      id: "MapStore",
      initialState: {
        objects: {},
        chosen: null,
        contour: null,
        loaded: true
      },
      actionCallbacks: {
        importObject: function(updater, coordinates) {
          var objects = Object.assign({}, this.objects);
          MapUtils.importer(coordinates).import();
        },
        changeObject: function(updater, object) {
          var objects = Object.assign({}, this.objects);
          objects[object.id] = Object.assign({}, objects[object.id], object);
          updater.set({objects: objects});
        },
        clean: function(updater) {
          updater.set({objects: {}, chosen: null});
        },
        chooseObject: function(updater, object) {
          updater.set({chosen: object})
        },
        resetChosen: function(updater) {
          updater.set({chosen: null})
        },
        changeContour: function(updater, contour) {
          updater.set({contour: contour})
        },
        setLoadState: function(updater, loaded) {
          updater.set({loaded: loaded})
        }
      }
    });
  }
}