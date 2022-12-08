wiki-data-parser-for-ostis-geography
============

About
------------

This is a set of loaders and translators for extracting knowledge from external sources. 
This project is based on [data2sc-parser](https://github.com/ostis-apps/data2sc-parser)

How it works
------------

You input entities to get from external source. Loader make requests to source and gives all info in JSON format. After that info in JSON translates to SCS and saves to directory you choose.

Requirements
------------

For requirements installation use

    pip3 install -r requirements.txt

---

About Wikipedia Tools
------------

Recommend to use [this](https://github.com/Flombik/wptools) version of Wikipedia tools.

To install use:

    git clone https://github.com/Flombik/wptools.git
    cd wptools
    pip3 install -U .

Usage
------------

    python3 src/wikidata_parse.py human gender "human body" humanity society biosphere

* Input all entities titles with a space
* Don't forget to choose directory for saving scs files and images. Make it with `--dir` attribute (by default its 'sc_out')

Example with attributes

    python3 src/parse.py human --dir=output_dir

For help enter

    python3 src/parse.py --help

Example
-----------

For example, I need to create a knowledge base about a person. What do I need to do for this? 

First step. load entity "human":

    python3 src/wikidata_parse.py human 

Second step. analysing of dependencies. Copy folder src/sc_out to the KB folder and build the base. 
After that you can find your entity and check connected entities like gender, biosphere, society and other. 

Third step. pull out all the dependencies you want to see in the ostis. :

    python3 src/wikidata_parse.py human gender society biosphere

Fourth step. Check your knowledge base.





Architecture
------------

You can see 3 sections:

* `entities`
* `relations`
* `triplets`

In `entities` section stores info about all entities which was loaded from external sources. Each entity include `identifier`, `label` and `description`. `label` and `description` include information in different languages. If loaded entity has image in `image_url` stores URL for loading this image.

In `relations` section stores info about relations. All the same as in `entities` section but relations usually don't have images.

In `triplets` section stores relations between entities. It is represented in form of triplets, where the first element is the entity from which a relation goes to the second entity. Second element is the relation that connect two entities. Third element is second entity.

After loading data JSON file translating by JsonToScsTranslator and all info saves to SCs files.

Problems
------------

Sometimes identifiers contain non-ascii symbols. And this is a reason, why base rise error during build.

You can also find red lines in console "Note: Wikidata item missing 'instance of' (P31)". It can be ignored. 

In some cases there is a problem with pulling data. It can be ignored, but sometimes it causes base build errors. 
You should change some entities from you arguments to fix it.

For expert users
------------
You can specify additional relations in the list self._relations of class WikiDataContextLoader. 
Also, you can specify relations mapping in dict relations_map in the file JsonToScsTranslator. 
Mapping dictionary is used to swap Wikidata relations with OSTIS relations.

In the method WikiDataContextLoader.getEntity you can add languages to additional_languages list to get scs with
identifier in your language. 


ToDo 
------------

* Generation of sections 
* Fix images 
* Move all config variables to config file
* Add questions generator 
* Add answers generator 
* clean code)))))