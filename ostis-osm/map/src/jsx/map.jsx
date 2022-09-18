var Map = React.createClass({
  propTypes: {
    objects: React.PropTypes.array,
    chosen: React.PropTypes.object,
    onMarkerClick: React.PropTypes.func,
    onMapClick: React.PropTypes.func
  },

  initCursorListener: function() {
    document.body.addEventListener('keydown', (event) => {
      if (event.ctrlKey)
        this.refs.map.style.cursor = "crosshair";
    });
    document.body.addEventListener('keyup', () => {
      this.refs.map.style.cursor = "";
    });
  },

  createMap: function() {
    this.map = new L.Map('map', {zoomControl: false});
    var osmUrl='http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png';
    var osm = new L.TileLayer(osmUrl, {minZoom: 1, maxZoom: 17});
    this.map.addLayer(osm);
  },

  bindMapClickAction: function() {
    this.map.on('click', (event) => {
      if (event.originalEvent.ctrlKey)
        this.props.onMapClick(event.latlng)
    });
  },

  fixZoomControls: function() {
    new L.control.zoom({position: 'bottomright'}).addTo(this.map);
  },

  clearMap: function() {
    if (this.markers)
      this.map.removeLayer(this.markers);
  },

  addMarkersToMap: function() {
    var markers = [];
    var onMarkerClick = this.props.onMarkerClick;
    this.props.objects.map(function(object) {
      if (!MapUtils.empty(object.geojson)) {
        var marker = L.geoJSON(object.geojson).on('click', () => onMarkerClick(object));
        markers.push(marker);
      }
    });
    if (markers.length > 0) {
      this.markers = L.featureGroup(markers); 
      this.markers.addTo(this.map);
      this.map.fitBounds(this.markers.getBounds());
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
    this.createMap();
    this.bindMapClickAction();
    this.setInitialView();
    this.fixZoomControls();
    this.initCursorListener();
  },

  componentDidUpdate: function() {
    this.clearMap();
    this.addMarkersToMap();
    this.setCenter();
  },

  render: function() {
    return (
      <div id="map" ref="map" style={{position: "absolute", top: "0px", left: "0px", width: "100%", height: "100%"}}></div>
    );
  }
});
