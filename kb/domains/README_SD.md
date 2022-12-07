<h1 align="center">What is a Subject Domain? 🦄 </h1>
<p>
  <a href="https://www.gnu.org/licenses/gpl-3.0.html" target="_blank">
    <img alt="GPLv3" src="https://img.shields.io/badge/License-GPLv3-yellow.svg" />
  </a>
</p>

## Description, structure, hierarchy

> The subject domain is the result of integration (union) of partial semantic neighborhoods that describe all the entities of a given class under study and have the same (common) subject of study (that is, the same set of relations that should belong to the bundles that are part of the integrable semantic neighborhoods).

Subject domain is a structure that includes:
1. the main studied (described) objects - primary and secondary;
2. different classes of objects under study;
3. various ligaments, the components of which are the objects under study (both primary and secondary), and also, possibly, other such ligaments - that is, ligaments (as well as objects of study) can have a different structural level;
4. different classes of the above connections (that is, relations);
2. different classes of objects that are neither objects of study nor the above links, but are components of these links.

At the same time, all classes declared by the concepts under study must be fully represented within the framework of a given subject domain, along with their elements, elements of elements, etc. up to the terminal elements.

## 🔎 Formal concept clarification of the subject domain
If a certain subject domain is explicitly introduced within the sc-model of the knowledge base, then it is treated as an sc-structure, for which the sc-node denoting it is explicitly introduced in the knowledge base, which, in turn, is connected by the sc-arc of the main type included in it with the sc-node denoting the class of sc-structures that are subject domains. 
After that, in the specified sc-structure, it is necessary to explicitly set the roles of some nodes that are part of this scstructure. These roles include:
- maximum class of objects under study, i.e., the set of all studied objects and only them. In each subject domain, there is only one key node that performs this role;
- class of objects under study. Each subject domain can have any number of such classes;
- class of secondary objects built on the basis of the objects under study;
- class of auxiliary objects, through the links with which are described some characteristics of the objects under study;
- relation, each link of which connects only the studied objects or secondary objects built on the basis of the researched;
- relation, each link of which connects the objects under study with auxiliary.

>Example:
```sh
section_subject_domain_of_intelligent_study_systems = [*
	subject_domain_of_intelligent_study_systems
<- sc_node_struct;
	=> nrel_main_idtf:
   [Предметная область интеллектуальных обучающих систем]
   (* <- lang_ru;; *);
   [Subject domain of intelligent study systems]
   (* <- lang_en;; *);
	<- subject_domain;
	-> rrel_maximum_studied_object_class:
   concept_intelligent_study_system;
	-> rrel_not_maximum_studied_object_class:
   concept_lab_work;
	-> rrel_explored_relation:
   nrel_knowledge_base;
*];;
```


## 🧠 Structuring concepts in Subject Domain
The logical hierarchy of concepts is an ontology that includes a description of the system of definitions of concepts of a given subject domain with an indication of a set of concepts through which each defined concept of the subject domain under consideration is defined.
The concept under study can be:
1. the class of primary elements of this subject domain;
2. relation (classes of links) linking the elements of this subject domain - the level of hierarchy of these elements can be different;
3. class of structures, all elements of which are elements of a given;
subject domain, i.e. a class of substructures of a given subject domain.

## 🎯 Creation of a specific Subject Domain in the KB directory
The first and most important step in designing a knowledge base is to refine structures of the described subject domain or several interconnected subject domains.
The refinement of such a structure is, first of all, the refinement of the class of objects under study, the subject of study, the entire family of signature elements.

To build a knowledge base for a specific intellectual system, it is necessary to divide all the knowledge presented in a certain domain of activity into thematic subject domains, and in each subject domain it is necessary to highlight:
- the maximum class of research objects,
- non-maximal classes of objects of study,
- set of studied relations (if any).

## 📍 Structure
### section_subjdomain_
Main folder of your Subject Domain. To formalize the structure of the Subject Domain you should select classes of objects of study as well as relations.
### concepts
Your Subject Domain's concepts. Put your concept_ files here. When describing concepts, set notes, explanations and definitions to them.
### relations
Your Subject Domain's relations. Put your nrel_ and rrel_ files here. For formalized relations, you should specify properties and domains.

## 💡Algorithm for selecting a specific Subject Domain in the KB directory
1. In the kb/domains/ folder, create a new directory section_subjdomain_your_domain
2. Allocate sub-directories for concepts (concepts) and relations (relations (rrel & nrel)). The concepts directory can also contain an instances sub-directory. In the relations directory - sub-directories for role and non-role relations.

The whole hierarcly should look the following way:
```sh
kb/
extra/
    - section_subject_domain_of_intelligent_study_systems/
              - section_subject_domain_of_intelligent_study_systems.scs
           - concepts/
       - relations/
```

## 💁‍♀️Tips
- Your Subject Domain's folder name should clearly state what it contains.
- In case you are using images, png and jpg are the only acceprable formats (no jpeg). Images can be stored in a separate direcrory.
- To leave a comment in the knowledge base source files, you can use /**...* */.
- Sc-element names must be written in Latin and meet SC-code syntax requirements.
- After updating your Subject Domain content do not forger to rebuild knowledge base.

## After all, your kb directory will look like this
```sh
kb/
extra/
    - section_subject_domain_of_intelligent_study_systems/ 
              - section_subject_domain_of_intelligent_study_systems.scs
           - concepts/
         - concept_intelligent_study_system.scs
       - relations/
         - nrel_lab_workshop.scs
```

## 🤝 Contributing

Contributions, issues and feature requests are welcome!
