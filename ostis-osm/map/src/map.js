// Module that describes complete component that will be displayed and used
const Map = React.createClass({displayName: "Map",
  propTypes: {
    objects: React.PropTypes.array,
    chosen: React.PropTypes.object,
    onMarkerClick: React.PropTypes.func,  // That was onClick in map_interface
    onMapClick: React.PropTypes.func      // That was onMapClick in map_interface
  },

  // Changing the style of cursor with alt down
  // Can be moved to event listener directly, but is separated for better readability
  initCursorListener: function() {
    const handleKeyDown = (event) => {
      console.log("===isAltEvent===", event.keyCode === 18)
      if (event.altKey)
        console.log('===altDown===')
        this.refs.map.style.cursor = "crosshair";
    }

    const handleKeyUp = () => {
      console.log('===keyUp===')
      this.refs.map.style.cursor = "";
    }    

    document.body.addEventListener('keydown', handleKeyDown)
    document.body.addEventListener('keyup', handleKeyUp);
  },

  // Creating of map that will use map tiles from OSM project
  // Requires internet connection
  createMap: function() {
    this.map = new L.Map('map', {zoomControl: false});                // L is leaflet
    const osmUrl='http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png'; // Getting tile from OSM
    const osm = new L.TileLayer(osmUrl, {minZoom: 1, maxZoom: 17});   // Setting gotten tile on our map
    this.map.addLayer(osm);
  },

  // This event will get OSM coordinates with specified click (alt click)
  bindMapClickAction: function() {
    const handleAltClick = (event) => {
      console.log("===originalEventOfClick===", event.originalEvent)
      console.log("===isOriginalAltEvent===", event.originalEvent.altKey)
      console.log("===isAltEvent===", event.altKey)
      if (event.originalEvent.altKey) {
        console.log("===event.latlng===", event.latlng)
        this.props.onMapClick(event.latlng)
      }
    }

    console.log('===boundMapActionClick===')
    this.map.on('click', handleAltClick);
  },

  // Setting zoom buttons
  fixZoomControls: function() {
    new L.control.zoom({position: 'bottomright'}).addTo(this.map);
  },

  // Clearing setted markers on map
  clearMap: function() {
    if (this.markers)
      this.map.removeLayer(this.markers);
  },


  addMarkersToMap: function() {
    let markers = [];
    const onMarkerClick = this.props.onMarkerClick;                                         // Which is onClick in map_interface
    this.props.objects.map(function(object) {
      if (!MapUtils.empty(object.geojson)) {                                                // If there is no such marker
        const marker = L.geoJSON(object.geojson).on('click', () => onMarkerClick(object));  // Creating new marker and binding click behaviour
        console.log("===marker===", marker)
        markers.push(marker);                                                               // Pushing marker to existing ones
      }
    });
    if (markers.length > 0) {                                                               // If there are markers
      this.markers = L.featureGroup(markers);                                               // Getting markers from leaflet
      this.markers.addTo(this.map);                                                         // Adding marker to map
      this.map.fitBounds(this.markers.getBounds());                                         // Setting markers bounds for better display
    }
  },

  setInitialView: function() {
    this.map.setView([53, 27], 1);
  },

  setCenter: function() {
    if (this.props.chosen && !MapUtils.empty(this.props.chosen.geojson))
      this.map.fitBounds(L.geoJSON(this.props.chosen.geojson).getBounds());
  },

  componentDidMount: function() {
    console.log("===eventBinding===")
    this.createMap();
    console.log("===mapCreated===")
    this.bindMapClickAction();
    console.log("===mapClickBinded===")
    this.setInitialView();
    console.log("===initialViewSeted===")
    this.fixZoomControls();
    console.log("===zoomControlsFixed===")
    this.initCursorListener();
    console.log("===cursorListenerInited===")
  },

  componentDidUpdate: function() {
    this.clearMap();
    this.addMarkersToMap();
    this.setCenter();
  },

  render: function() {
    return (
      React.createElement("div", {id: "map", ref: "map", style: {position: "absolute", top: "0px", left: "0px", width: "100%", height: "100%"}})
    );
  }
});