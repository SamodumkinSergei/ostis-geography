for path in `find ../components/ -name "*.jsx"`
do
  echo "prepare $path"
  jsx $path "$path/../" -x jsx
done
