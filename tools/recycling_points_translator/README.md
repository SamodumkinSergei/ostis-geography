# Recycling Points Translator

Parsing from [OpenStreetMap](https://www.openstreetmap.org) into .scs files using phpQuery

## Parameters 
Change in config file:

| Parameter | Description                                                               | 
| :-------- |:------------------------------------------------------------------------- |
| `keywords`| Search keywords (e.g. "Recycling Points", "макулатура", "Белвторресурсы") |
| `kbPath`  | Absolute path to folder where the concepts will be placed                 |


## Run

Install php:

```bash
  sudo apt install php7.2-cli
  sudo apt install php7.2-xml
```

Run script:

```bash
  php ./translator.php
```