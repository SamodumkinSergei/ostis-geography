import wptools
import re
import threading
from queue import Queue
from deep_translator import (GoogleTranslator)

from src.loaders.WikiDataLoader import WikiDataLoader


class WikiDataWithContextLoader(WikiDataLoader):
    def __init__(self):
        super().__init__()
        self._lock = threading.Lock()
        self._THREADS_NUM = 16
        self._relations = ['P31',  # instance_of
                           'P1552',  # has_quality
                           'P361',  # part_of
                           'P527',  # has_parts
                           'P2283',  # uses
                           'P111',  # measure_physical_quantity
                           'P1889',  # different_from
                           'P1269',  # facet_of
                           'P1542',  # has_effect
                           'P1557',  # manifestation_of
                           'P461',  # opposite_of
                           'P1382',  # partially_coincident_with
                           'P1344',  # participant_in
                           'P129',  # physically_interacts_with
                           'P1056',  # product_or_material_produced
                           'P3342',  # significant_person
                           'P2579',  # studied_by
                           'P495',  # country_of_origin
                           'P425',  # field_of_this_occupation
                           'P279']  # subclass_of

    def _load_object(self, obj, obj_type, languages):
        en_page = wptools.page(wikibase=obj, skip=['labels'], silent=True)
        en_page.get_wikidata()

        requested_pages = {}

        for lang in languages:
            new_page = wptools.page(wikibase=obj, lang=lang, skip=['labels', 'imageinfo'], silent=True)
            requested_pages[lang] = new_page

        for lang, page in requested_pages.items():
            page.get_wikidata()

        try:
            obj_id = re.sub(r"\+|-|–|/|:|\s", '_',
                            re.sub(r"'s?|\(|\)|,", '', en_page.data['title']))
        except KeyError:
            obj_id = obj

        with self._lock:
            result_labels = {}
            result_descriptions = {}

            temp = re.sub(r"\[", '(', en_page.data['label'])
            result_labels['en'] = re.sub(r"]", ')', temp)
            result_descriptions['en'] = en_page.data['description']

            for lang, page in requested_pages.items():
                if page.data['label'] is None:
                    result_labels[lang] = GoogleTranslator(source='en', target=lang).translate(text=result_labels['en'])
                else:
                    temp = re.sub(r"\[", '(', page.data['label'])
                    result_labels[lang] = re.sub(r"]", ')', temp)

            for lang, page in requested_pages.items():
                if page.data['description'] is None and result_descriptions['en'] is not None and len(
                        result_descriptions['en']) < 1000:  # Google Translate has limit 5000 symbols
                    result_descriptions[lang] = GoogleTranslator(source='en', target=lang).translate(
                        text=result_descriptions['en'])
            self._info[obj_type][obj] = {
                'identifier': obj_id.lower(),
                'label': result_labels,
                'description': result_descriptions
            }
            self._add_image_url(en_page, obj_type, obj)

    def _thread_fun(self, queue, languages):
        while True:
            obj, obj_type = queue.get()
            try:
                self._load_object(obj, obj_type, languages)
            except:
                print('Some Error at pulling data. It can cause problems when building the base, so be careful. '
                      'Perhaps you should change the requested entities ')
            queue.task_done()

    def _resolve_ids(self):
        for triplet in self._info['triplets']:
            _, rlt, ent = triplet
            if rlt.startswith('P'):
                triplet[1] = self._info['relations'][rlt]['identifier']
            if ent.startswith('Q'):
                triplet[2] = self._info['entities'][ent]['identifier']

        temp_ent = self._info['entities']
        self._info['entities'] = {}
        for ent in temp_ent:
            self._info['entities'][temp_ent[ent]['identifier']] = temp_ent[ent]

        temp_rlt = self._info['relations']
        self._info['relations'] = {}
        for rlt in temp_rlt:
            self._info['relations'][temp_rlt[rlt]['identifier']] = temp_rlt[rlt]

    def _load_entity(self, entity, lang='en'):
        super()._load_entity(entity, lang=lang)
        self._page = wptools.page(wikibase=self._page.data['wikibase'], lang='en', skip=[
            'labels', 'imageinfo'], silent=True)
        self._page.get_wikidata()
        page_title = re.sub(r"\+|-|–|/|:|\s", '_',
                            re.sub(r"'s?|\(|\)|,", '', self._page.data['title']))
        loading_queue = Queue()

        for _ in range(self._THREADS_NUM):
            threading.Thread(target=self._thread_fun, args=[
                loading_queue, self._languages], daemon=True).start()

        context = self._page.data['claims']
        for rlt, ents in context.items():
            if rlt in self._relations:
                loading_queue.put([rlt, 'relations'])
                for ent in ents:
                    if type(ent) is str:
                        if ent.startswith('Q'):
                            loading_queue.put([ent, 'entities'])
                            self._info['triplets'].append([page_title, rlt, ent])
                        else:
                            if set(re.findall(r'\.\w*$', ent)) & {'.jpg', '.svg', '.png', '.map'}:
                                continue
                            self._info['triplets'].append([page_title, rlt, '[%s]' % ent])

        loading_queue.join()
        self._resolve_ids()

    def _set_languages(self, languages):
        self._languages = languages
