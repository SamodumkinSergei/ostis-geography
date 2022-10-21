echo ls
cd interface/sc-web-extensions/hotels_interface/
cp -R ./hotels_ui ../../../ostis-web-platform/sc-web/components/
paste -d"\n" ./Gruntfile.js ../../../ostis-web-platform/sc-web/Gruntfile.js > ../../../ostis-web-platform/sc-web/Gruntfile.js
cd ../../../ostis-web-platform/sc-web/client/templates
echo "COMPLETE"

cat <<EOT >> ./components.html
<script type="text/javascript" charset="utf-8" src="static/components/js/hotels_ui/hotels.js"></script>
EOT

cd ../../scripts
cd ..
grunt build
