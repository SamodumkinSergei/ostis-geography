import json
from abc import ABC, abstractmethod


class BaseLoader(ABC):
    def __init__(self):
        self._info = {'entities': {}, 'relations': {}, 'triplets': []}

    @abstractmethod
    def _load_entity(self, entity, lang='en'):
        pass

    def load_entities(self, entities, lang='en'):
        for entity in entities:
            self._load_entity(entity, lang=lang)

    def get_json(self):
        return json.dumps(self._info, ensure_ascii=False)
