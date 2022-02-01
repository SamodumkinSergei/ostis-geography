sudo chmod +x ./prepare_jsx.sh
cp ./openstreetmap_view.scs ../../kb/openstreetmap_view.scs
cp ./prepare_jsx.sh ../sc-web/scripts/prepare_jsx.sh
cp -R ./map ../sc-web/components
cp -R ./common ../sc-web/client/static
cd ../sc-web/client/templates

cat <<EOT >> ./common.html
<script type="text/javascript" charset="utf-8" src="/static/common/react/react.js"></script>
<script type="text/javascript" charset="utf-8" src="/static/common/react/react-dom.js"></script>
<script type="text/javascript" charset="utf-8" src="/static/common/bootstrap-slider/js/bootstrap-slider.js"></script>
<script type="text/javascript" charset="utf-8" src="/static/common/leaflet/js/leaflet.js"></script>
<script type="text/javascript" charset="utf-8" src="/static/common/react-autocomplete/react-autocomplete.js"></script>
<script type="text/javascript" charset="utf-8" src="/static/common/osmtogeojson/osmtogeojson.js"></script>
<script type="text/javascript" charset="utf-8" src="/static/common/fluxify/fluxify.js"></script>
<script type="text/javascript" charset="utf-8" src="/static/common/toast/jquery.toast.min.js"></script>
<script type="text/javascript" charset="utf-8" src="/static/common/react-loader/react-loader.js"></script>

<link rel="stylesheet" type="text/css" href="/static/common/leaflet/css/leaflet.css" />
<link rel="stylesheet" type="text/css" href="/static/common/bootstrap-slider/css/bootstrap-slider.css" />
<link rel="stylesheet" type="text/css" href="/static/common/toast/jquery.toast.min.css" />
EOT

cat <<EOT >> ./components.html
<script type="text/javascript" charset="utf-8" src="/static/components/js/map/map.js"></script>
<link rel="stylesheet" type="text/css" href="/static/components/css/map.css" />
EOT

cd ../../scripts
./prepare_jsx.sh
python3 build_components.py -i -a
cd ..
grunt build