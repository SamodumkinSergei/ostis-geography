cp -R ./map ../sc-web/components
cp -R ./common ../sc-web/client/static
cd ../sc-web/scripts
./prepare_jsx.sh
python3 build_components.py -i -a
cd ..
grunt build