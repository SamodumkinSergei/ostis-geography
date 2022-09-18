cp -R ./map ../sc-web/components
cp -R ./common ../sc-web/client/static
cd ../sc-web/scripts
./prepare_jsx.sh
python build_components.py -i -a
cd ..
grunt build