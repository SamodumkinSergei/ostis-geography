## Улицы
Пример формализации улицы, достаточный для отображения на карте, находится в этом [файле](template_street.scs)

## Районы, города, поселки, сельсоветы и т.д.

#### Города:
``` 
brest <- concept_city;   //принадлежность классу город
=>nrel_main_idtf:   //идентификаторы на русском и на английском
    [Brest]
    (* <- lang_en;; <- name_en;;*);
    [Брест]
    (* <- lang_ru;; <- name_ru;; <- name;;*);
=>nrel_admin_level:   //информация об административном уровне
    [6]
    (*<-concept_admin_level;;*);
=>nrel_country:
    belarus;
=>nrel_region:
    brest_region;   //системный идентификатор брестского региона
=>nrel_district:
    brest_district;;   //системный идентификатор брестского района
```
#### Районы города:
```
leninsky_city_district_brest  <- concept_city_district;   //принадлежность классу городского района
=>nrel_main_idtf:   //идентификаторы на русском и на английском
    [Leninsky District]
    (* <- lang_en;; <- name_en;;*);
    [Ленинский район]
    (* <- lang_ru;; <- name_ru;; <- name;;*);
=>nrel_admin_level:   //информация об административном уровне
    [9]
    (*<-concept_admin_level;;*);
=>nrel_country:
    belarus;
=>nrel_region:   //системный идентификатор брестского региона
    brest_region;
=>nrel_district:   //системный идентификатор брестского района
    brest_district;
=>nrel_city:
    brest;;
```
### Все сельсоветы реализованы!

#### Деревни/поселки/хуторы:
```
baranauka <- concept_village;   //принадлежность классу деревень
=>nrel_main_idtf:   //идентификаторы на русском и на английском
    [Baranauka]
    (* <- lang_en;; <- name_en;;*);
    [Барановка]
    (* <- lang_ru;; <- name_ru;; <- name;;*);
=>nrel_admin_level:   //информация об административном уровне
    [10]
    (*<-concept_admin_level;;*);
=>nrel_country:
    belarus;
=>nrel_region:   
    minsk_region;   //системный идентификатор минского региона
=>nrel_district:
    barysaw_district;   //системный идентификатор минского района
=>nrel_selsoviet:
    glivinskij_selsoviet;;   //системный идентификатор гливинского сельсовета
```

#### ИНФОРМАЦИЯ ОБ АДМИНИСТРАТИВНОМ УРОВНЕ:
* страна - admin_level = 2
* столица - admin_level = 4
* области - admin_level = 4
* областные центры - admin_level = 6
* районы - admin_level = 6
* районные центры - admin_level = 8
* поселки городского типа - admin_level = 10
* деревни - admin_level = 10
* сельсовет - admin_level = 8
* район города - admin_level = 9


#### Отношения и понятия в базе

Отношение/Понятие - Значение

1. concept_country - страна
2. concept_region - область
3. concept_capital - столица
4. concept_city - город
5. concept_district - район
6. concept_city_district - район города
7. concept_admin_level - административный уровень
8. concept_administrative_unit - административно-территориальная единица(страна, город, область, столица, район, район города)
9. concept_openstreetmap_tag - OpenStreetMap tag
10. concept_map_object - Объект на карте, не являющийся административно-территориальной единицей
11. nrel_admin_level - `concept_administrative_unit => concept_admin_level`
12. nrel_country - `concept_administrative_unit(admin_level = > 2) => concept_country`
13.  nrel_region - `concept_administrative_unit(admin_level >4) => concept_region`
14. nrel_capital - `concept_country => concept_capital`
15. nrel_city - `concept_administrative_unit(admin_level > 8) => concept_city`
16. nrel_district - `concept_administrative_unit(admin_level > 6) => concept_district (исключение столица и областные центры)`
17. nrel_city_district - `concept_map_object => concept_city_district`
