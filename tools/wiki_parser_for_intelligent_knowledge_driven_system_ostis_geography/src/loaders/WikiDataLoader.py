from BaseLoader import BaseLoader
import wptools
import re


class WikiDataLoader(BaseLoader):
    def __init__(self):
        super().__init__()
        self._page = None

    def _add_label_and_description(self, page, page_lang, ent_type, title):
        self._info[ent_type][title]['label'][page_lang] = page.data['label']
        self._info[ent_type][title]['description'][page_lang] = page.data['description']

    def _add_image_url(self, page, ent_type, title):
        if page.images():
            self._info[ent_type][title]['image_url'] = page.images()[
                0]['url']

    def _load_entity(self, entity, lang='en'):
        if entity.startswith('Q') and entity[1:].isnumeric():
            self._page = wptools.page(wikibase=entity, lang=lang,
                                      skip=['labels'], silent=True)
            ent_type = 'entities'
            self._page.get_wikidata()
        elif entity.startswith('P') and entity[1:].isnumeric():
            self._page = wptools.page(wikibase=entity, lang=lang, skip=[
                'labels', 'imageinfo'], silent=True)
            ent_type = 'relations'
            self._page.get_wikidata()
        else:
            self._page = wptools.page(
                entity, skip=['labels'], lang=lang, silent=True)
            try:
                self._page.get_wikidata()
            except LookupError:
                self._page = wptools.page(entity.capitalize(), skip=[
                                          'labels'], lang=lang, silent=True)
                try:
                    self._page.get_wikidata()
                except LookupError:
                    self._page = wptools.page(entity.title(), skip=[
                                              'labels'], lang=lang, silent=True)
                    self._page.get_wikidata()
            ent_type = 'entities' if self._page.data['wikibase'].startswith(
                'Q') else 'relations'

        title = ''
        if lang != 'en':
            en_page = wptools.page(wikibase=self._page.data['wikibase'], lang='en', skip=[
                                   'labels', 'imageinfo'], silent=True)
            en_page.get_wikidata()
            title = re.sub(r"\+|-|–|/|:|\s", '_',
                           re.sub(r"'s?|\(|\)|,", '', en_page.data['title']))
            self._info[ent_type][title] = {
                'identifier': en_page.data['title'],
                'label': {},
                'description': {}
            }
            self._add_label_and_description(en_page, 'en', ent_type, title)
        elif lang == 'en':
            title = re.sub(r"\+|-|–|/|:|\s", '_',
                           re.sub(r"'s?|\(|\)|,", '', self._page.data['title']))
            self._info[ent_type][title] = {
                'identifier': self._page.data['title'],
                'label': {},
                'description': {}
            }
            self._add_label_and_description(self._page, 'en', ent_type, title)

        if lang != 'de':
            de_page = wptools.page(wikibase=self._page.data['wikibase'], lang='de', skip=[
                                   'labels', 'imageinfo'], silent=True)
            de_page.get_wikidata()
            self._add_label_and_description(de_page, 'de', ent_type, title)
        elif lang == 'de':
            self._add_label_and_description(self._page, 'de', ent_type, title)

        if lang != 'ru':
            ru_page = wptools.page(wikibase=self._page.data['wikibase'], lang='ru', skip=[
                                   'labels', 'imageinfo'], silent=True)
            ru_page.get_wikidata()
            self._add_label_and_description(ru_page, 'ru', ent_type, title)
        elif lang == 'ru':
            self._add_label_and_description(self._page, 'ru', ent_type, title)

        self._add_image_url(self._page, ent_type, title)
