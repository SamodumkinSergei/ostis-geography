import json
import os
import re

from jinja2 import Environment, FileSystemLoader

relations_map = {
    'has_parts': 'nrel_basic_decomposition',
    'has_quality': 'nrel_inclusion',
    'part_of': None
}


def json_to_scs(raw_info, save_dir):
    result_triplets = []
    try:
        os.mkdir(save_dir)
    except FileExistsError:
        pass
    os.chdir(save_dir)

    info = json.loads(raw_info)
    jinja_env = Environment(loader=FileSystemLoader(os.path.realpath(
        '{}/../templates'.format(os.path.dirname(os.path.realpath(__file__))))))

    template = jinja_env.get_template('triplets.scs')
    if len(info['triplets']) != 0:
        result_triplets = []
        for entity1, rel, entity2 in info['triplets']:

            if rel.lower() in relations_map:
                if relations_map[rel.lower()] is not None:
                    result_triplets.append(
                        ['concept_' + entity1.lower(), relations_map[rel.lower()], 'concept_' + entity2.lower()])
            else:
                result_triplets.append(
                    ['concept_' + entity1.lower(), 'nrel_' + rel.lower(), 'concept_' + entity2.lower()])
        scs = open('triplets.scs', 'at', encoding='utf-8')
        scs.write(template.render(triplets=result_triplets))
        scs.close()

    try:
        os.mkdir('entities')
    except FileExistsError:
        pass
    os.chdir('entities')
    # try:
    #     os.mkdir('images')
    # except FileExistsError:
    #     pass
    template = jinja_env.get_template('entity.scs')
    for ent in info['entities'].values():
        translate_entity(ent, template)
    os.chdir('..')

    try:
        os.mkdir('relations')
    except FileExistsError:
        pass
    os.chdir('relations')
    template = jinja_env.get_template('relation.scs')
    for idtf, rlt in info['relations'].items():
        if idtf not in relations_map:
            translate_relation(rlt, template, result_triplets)
    os.chdir('..')


def translate_entity(entity, template):
    prepare_info(entity)
    entity['identifier'] = 'concept_' + entity['identifier'].lower()

    rendered_tmpl = template.render(identifier=entity['identifier'], labels=entity['label'].items(
    ), has_descr=(len(entity['description'].items()) > 0), descriptions=entity['description'].items())

    scs = open('{}.scs'.format(entity['identifier']), 'wt', encoding='utf-8')
    scs.write(rendered_tmpl)
    scs.close()


def prepare_info(info):
    fixed_description = {}
    for lang, descr in info['description'].items():
        if descr is not None:
            clear_ids = re.sub(r" \[[P|Q]\d+]", '', descr)
            temp = re.sub(r"\[", '(', clear_ids)
            fixed_description[lang] = re.sub(r"]", ')', temp)
    info['description'] = fixed_description

    fixed_labels = {}
    for lang, descr in info['label'].items():
        if descr is not None:
            fixed_labels[lang] = descr
    info['label'] = fixed_labels


def translate_relation(relation, template, triplets):
    prepare_info(relation)
    relation['identifier'] = 'nrel_' + relation['identifier'].lower()
    first_domain = set()
    second_domain = set()

    for entity1, rel, entity2 in triplets:
        if rel == relation['identifier']:
            first_domain.add(entity1)
            second_domain.add(entity2)

    scs = open('{}.scs'.format(relation['identifier']), 'wt', encoding='utf-8')
    scs.write(template.render(identifier=relation['identifier'], labels=relation['label'].items(
    ), descriptions=relation['description'].items(), first_domain=list(first_domain),
                              second_domain=list(second_domain)))
    scs.close()
