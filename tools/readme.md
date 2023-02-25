# Design automation tools and components for knowledge base

Automated design system - automated
system implementing information technology for performing functions design
is an organizational and technical system intended
for automation of the design process, consisting of staff and
complex of technical, software and other means of automation of its activities.  

# Purpose of creating automated design system:  
* reduction of design and planning course;  
* reduction of design terms;  
* reducing the cost of design and manufacturing, reducing  
operating costs;  
* improve the quality and techno-economic state of results
design;  
* reduced field simulation and testing costs.

In this project, design automation tools are presented in the form of 2 services: 
Street translator and translator, to automate the process of creating sks files for the section_subjdomain_openstreetmap/subject_domain_belarus/hospitals.

# Street translator
How to use guide

Street translator accepts three arguments
1. Name of the area to assign concepts to;  
2. Name of the area to search in russian;  
3. Number of files to create.  

For example, in order to parse 100 streets of Hrodna, you should do this:  

./StreetTranslator hrodna Гродно 100

Translated output will be in streets_{0} folder.

Example of filling SCs file:  

vulica_Moscanka_brest <- concept_way;<br/>
=>nrel_main_idtf:<br/>
[вуліца Мошчанка]<br/>
(* <- lang_by;; <- name_by;;*);<br/>
[vulica Moščanka]<br/>
(* <- lang_en;; <- name_en;;*);<br/>
[улица Мощёнка]<br/>
(* <- lang_ru;; <- name_ru;; <- name;;*);<br/>
=>nrel_search_area:<br/>
brest;;<br/>

# Translator

This is a program based on python. The main functionality is to fill the knowledge base with knowledge about hospitals in Belarus.  
It is implemented by generating SCs files and saving them along the path ../kb/section_subjdomain_openstreetmap/subject_domain_belarus/hospitals/. The translator makes it much easier and faster to fill the knowledge base.  

Example of filling SCs file:  

marinogorskaja_tsentralnaja_rajonnaja_bolnitsa <- concept_hospital;<br/>
=> nrel_main_idtf:<br/>
[Марьиногорская центральная районная больница]<br/>
(* <- lang_ru;; <- name_ru;; <- name;;*);;<br/>
