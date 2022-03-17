Морозов Александр, группа 821703

Тема: Отделения почты

Список понятий:

1) Иерархия и типы (4 понятия):

1.1) Общее понятие - почтовое учреждение (concept_post_institution)
1.2) Международное отделение пункта почтовой связи (concept_international_post_office)
1.3) Почтовое отделение (concept_post_office)
1.4) Отделене бизнес почты (concept_business_post)


2) Почтовые компании(брэнды) (4 понятий):

2.1)Белпочта (belpost_brand)
2.2)Fedex (fedex_brand)
2.3)UPS (UPS_brand)
2.4)DHL (DHL_brand)
2.5) Концепт брэнда компании(брэнда) учреждения (concept_post_office_company)
2.6) 4 брэндов РБ, включая частные и государственные 
2.8) Отношение управления в соответсвии с тегами OSM (nrel_operator)

3) Почтовые отделения (105 понятия):

3.1) Минск - 105 отделений 

![](https://github.com/Morozov-Alexander/ostis-geography/blob/pis/docs/concept.png)

4) Потенциально используемые понятия (1 понятие):

4.1) Улица (nrel_street) - отношение, связывающее банковское отделение и concept_way (здание/улица).
Требуется переработка и формализация семантических окрестностей, вместе с поятийным аппаратом


Три агента:
1. Поиск отделений почты по типу
	
На вход подаётся тип почтового отделения (?<-concept_post_institution).
	
На выход:
	
![](https://github.com/Morozov-Alexander/ostis-geography/blob/pis/docs/type.png)
	
2. Поиск отделений почты по управляющему брэнду
	
На вход подаётся название компании(брэнда).
	
На выход:
	
![](https://github.com/Morozov-Alexander/ostis-geography/blob/pis/docs/brand.png)
	
3. Поиск отделений почты по городу дислокации
	
На вход подаётся название города.
	
На выход:
	
![](https://github.com/Morozov-Alexander/ostis-geography/blob/pis/docs/city.png)
