echo ls
cd interface/sc-web-extensions/bank_way_interface/
cp -R ./bank_way ../../../ostis-web-platform/sc-web/components/
#mv ./Gruntfile.js ../../../ostis-web-platform/sc-web/Gruntfile.js
#paste -d"\n" ./Gruntfile.js ../../../ostis-web-platform/sc-web/Gruntfile.js > ../../../ostis-web-platform/sc-web/Gruntfile.js
cd ../../../ostis-web-platform/sc-web/client/templates
echo "COMPLETE"

#cat <<EOT >> ./components.html
#<script type="text/javascript" charset="utf-8" src="/static/components/js/bank_way/bank_way.js"></script>
#EOT

cd ../../scripts
cd ..
grunt build
