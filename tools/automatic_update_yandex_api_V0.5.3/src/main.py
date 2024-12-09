import json
import os
import requests
from jinja2 import Environment, FileSystemLoader
from googletrans import Translator

translator = Translator()

api_key = "API_KEY"
url = "https://search-maps.yandex.ru/v1/"
places_ru = {"школа", "пруд", "сквер", "кафе", "ресторан", "отель", "парк", "банк", "общежитие",
             "университет", "офис", "пиццерия", "кофейня", "озеро", "пляж", "река", "набережная",
             "остановка общественного транспорта", "метро", "торговый центр", "театр", "кинотеатр", "казино",
             "секонд-хенд", "ремонт обуви", "ремонт ключей", "магазин игрушек", "ресторан быстрого питания",
             "парикмахерская", "автомастерская", "поликлиника", "больница", "аквапарк", "железная дорога", "вокзал",
             "автовокзал", "дом культуры", "библиотека", "автозаправочная станция", "строительный магазин",
             "дом правительства", "площадь", "памятник", "фонтан", "магазин", "супермаркет", "церковь", "завод",
             "галерея",
             "администрация", "бассейн", "музей", "депо", "полиция", "госпиталь", "детский сад", "пожарное депо",
             "кладбище", "стадион", "столовая", "склад", "СТО", "мотель", "рынок", "гостиница", "выставка", "бар",
             "дискотека", "собор", "часовня", "лицей", "колледж", "аптека", "парковка", "паркинг", "сервисный центр"}

places_en = {"school", "pond", "square", "cafe", "restaurant", "hotel", "park", "bank", "hostel",
             "university", "office", "pizzeria", "coffee house", "lake", "beach", "river", "quay",
             "public transport stop", "metro", "shopping center", "theater", "cinema", "casino",
             "second hand", "shoe repair", "key repair", "toy store", "fast food restaurant",
             "hairdressing salon", "car repair shop", "polyclinic", "hospital", "water park", "railroad", "station",
             "bus station", "house of culture", "library", "gas station", "hardware store",
             "government house", "square", "monument", "fountain", "shop", "supermarket", "church", "factory",
             "gallery",
             "administration", "pool", "museum", "depot", "police", "hospital", "kindergarten", "fire station",
             "cemetery", "stadium", "canteen", "warehouse", "service station", "motel", "market", "hotel", "exhibition",
             "bar",
             "disco", "cathedral", "chapel", "lyceum", "college", "pharmacy", "parking", "parking", "service center"}

cities_ru = ["Минск", "Брест", "Гомель", "Гродно", "Могилев", "Витебск"]

cities_en = ["Minsk", "Brest", "Gomel", "Grodno", "Mogilev", "Vitebsk"]


def get_places_yandex(URL, KEY, PLACES_EN, CITIES_EN, LANG):
    for CITY in CITIES_EN:
        for PLACE in PLACES_EN:
            PARAMS = {'apikey': KEY, 'text': str(CITY) + ',' + str(PLACE), 'lang': LANG, 'results': 500}
            r = requests.get(url=URL, params=PARAMS)
            data = r.json()
            print(CITY)
            print(PLACE)
            NAME = str(CITY + '_' + PLACE)
            print(NAME)
            print(data)
            with open("json_row/"+ NAME + '.json', 'w') as outfile:
                json.dump(data, outfile)
        print("Done")


def generate_scs_instances(json_r, CITY):
    item_counter = 0
    for item in json.load(json_r)["features"]:
        point = {'name': 'n/a', 'name_en': 'n/a', 'name_en_clear': 'n/a', 'description': 'n/a', 'id': 'n/a',
                 'address': 'n/a', 'url': 'n/a', 'phones': 'n/a',
                 'category': 'n/a', 'hours': 'n/a', 'coordinates_E': 'n/a', 'coordinates_N': 'n/a'}

        if "name" in item["properties"].keys():
            point['name'] = item["properties"]["name"]
        if "description" in item["properties"].keys():
            point['description'] = item["properties"]["description"]
        if "CompanyMetaData" in item["properties"].keys():
            if "id" in item["properties"]["CompanyMetaData"].keys():
                point['id'] = item["properties"]["CompanyMetaData"]["id"]
            if "address" in item["properties"]["CompanyMetaData"].keys():
                point['address'] = item["properties"]["CompanyMetaData"]["address"].replace('\\', '')
            if "url" in item["properties"]["CompanyMetaData"].keys():
                point['url'] = item["properties"]["CompanyMetaData"]["url"]
            if "Phones" in item["properties"]["CompanyMetaData"].keys():
                point['phones'] = item["properties"]["CompanyMetaData"]["Phones"][0]["formatted"]
            if "class" in item["properties"]["CompanyMetaData"]["Categories"][0].keys():
                point['category'] = item["properties"]["CompanyMetaData"]["Categories"][0]["class"].replace(' ', '_')
            if "Hours" in item["properties"]["CompanyMetaData"].keys():
                point['hours'] = item["properties"]["CompanyMetaData"]["Hours"]["text"]
        if "coordinates" in item["geometry"].keys():
            point['coordinates_E'] = item["geometry"]["coordinates"][0]
        if "coordinates" in item["geometry"].keys():
            point['coordinates_N'] = item["geometry"]["coordinates"][1]
        if point['category'] == 'n/a' or point['id'] == 'n/a':
            print("ERROR: invalid params")
            continue
        # point['name_en'] = translator.translate(str(point['name']))
        # point['name_en_clear'] = point['name_en'].replace(' ', '_').replace('"', "_").replace('*', '').replace(',','')
        path = "kb/domains/" + str(CITY) + '/' + str(point['category'])
        if not os.path.exists(path):
            os.makedirs(path)
            print("Created dir :"+path)
        environment = Environment(loader=FileSystemLoader("tools/automatic_update_yandex_api_V0.5.3/src/templates/"))
        template = environment.get_template("scs_sample.txt")
        filename = str(point['category']) + '_' + point['id']
        if not os.path.exists(path+"/"+filename + ".scs"):
            content = template.render(
                # name_en_clear=point['name_en_clear'],
                categories=point['category'],
                id=point['id'],
                name_ru=point['name'],
                name_en=point['name'],
                address=point['address'],
                phones=point['phones'],
                hours=point['hours'],
                coordinates_E=point['coordinates_E'],
                coordinates_N=point['coordinates_N'],
                url=point['url'],
                city=CITY
            )
            with open(path + '/' + filename + ".scs", mode="w", encoding="utf-8") as scs:
                scs.write(content)
            print("Created file : ", path + '/' + filename + ".scs")
            item_counter += 1
        else:
            print("WARNING: file "+path+"/"+filename + ".scs"+" already exist")

    return item_counter


# get_places_yandex(url, api_key, places_en, cities_en, "en_US")
os.chdir('../../../')
counter = 0
for city in cities_en:
    for place in places_en:
        name = str(city + '.' + place)
        with open("tools/automatic_update_yandex_api_V0.5.3/src/json_row/" + name + ".json", 'r') as json_row:
            counter += generate_scs_instances(json_row, city)
print("Total added :", counter)
