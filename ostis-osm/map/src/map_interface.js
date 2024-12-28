// Module that describes interfac interaction
const MapInterface = React.createClass({displayName: "MapInterface",
  propTypes: {
    store: React.PropTypes.object
  },

  componentDidMount: function() {
    this.cleanModel();
    this.initChosenListener();
    this.initObjectsListener();
    this.initLoadedListener();
  },

  cleanModel: function() {
    fluxify.doAction('clean');
  },

  initChosenListener: function() {
    this.props.store.on('change:chosen', (chosen) => {
      this.setState({chosen: chosen});
    });
  },

  initObjectsListener: function() {
    this.props.store.on('change:objects', (objects) => {
      this.setState({objects: Object.values(objects)});
    });
  },

  initLoadedListener: function() {
    this.props.store.on('change:loaded', (loaded) => {
      this.setState({loaded: loaded});
    });
  },

  getInitialState: function() {
    console.log("<===getInitialState===>")
    return {
      objects: Object.values(this.props.store.objects),
      chosen: this.props.store.chosen,
      loaded: this.props.store.loaded
    };
  },

  // function for handling marker interaction
  onClick: function(object) {
    console.log("===chosenObject===", object)
    fluxify.doAction('chooseObject', object);
  },

  onMapClick: function(coordinates) {
    console.log('==coordinates==>', coordinates)
    fluxify.doAction('importObject', coordinates);
  },

  render: function() {
    return (
      React.createElement(Loader, {loaded: this.state.loaded}, 
        React.createElement(Map, {objects: this.state.objects, chosen: this.state.chosen, onMarkerClick: this.onClick, onMapClick: this.onMapClick})
        )
      );
  }
});