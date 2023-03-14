for path in `find ../sc-web/components/ -name "*.jsx"`
do
  echo "prepare $path"
  jsx $path "$path/../" -x jsx
done
