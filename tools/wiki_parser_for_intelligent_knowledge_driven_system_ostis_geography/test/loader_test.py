import json
import unittest
from unittest.mock import MagicMock

import requests
from assertpy import assert_that

from src.loaders.WikiDataWithContextLoader import WikiDataWithContextLoader
from test.util.response import response


# Side effects for mocking
class SideEffect:
    # WikiData considered as consistent data source, so we don't suppose to handle error codes
    @staticmethod
    def wptools_page_side_effect(*args):
        url = args[0].upper()
        if url.__contains__("WBGETENTITIES"):
            if url.__contains__("VULPECULA") or url.__contains__("Q10519"):
                print("Vupecula")
                with open("responses/vulpecula.json", "rb") as vupecula_json:
                    return response(200, vupecula_json.read())
            if url.__contains__("P31"):
                print("P31")
                with open("responses/P31.json", "rb") as P31_json:
                    return response(200, P31_json.read())
            if url.__contains__("Q8928"):
                print("Q8928")
                with open("responses/constellation.json", "rb") as constellation_json:
                    return response(200, constellation_json.read())
        else:
            pass


class WikiDataWithContextLoaderTest(unittest.TestCase):
    # noinspection PyMethodMayBeStatic
    def test_entities_is_being_loaded_correctly(self):
        # Arrange
        loader = WikiDataWithContextLoader()
        # We need to set only english to mock fewer data
        loader._set_languages(['en'])
        # Mocking internal get method as the most easy way to mock request
        requests.get = MagicMock(side_effect=SideEffect.wptools_page_side_effect)

        # Act
        loader.load_entities(["Vulpecula"])

        # Assert
        assert_that(json.dumps(json.loads(loader.get_json()), indent=4)).is_equal_to(
            """{
    "entities": {
        "Vulpecula": {
            "identifier": "Vulpecula",
            "label": {
                "en": "Vulpecula"
            },
            "description": {
                "en": "constellation in the northern celestial hemisphere"
            }
        },
        "constellation": {
            "identifier": "constellation",
            "label": {
                "en": "constellation"
            },
            "description": {
                "en": "one of the 88 divisions of the celestial sphere, defined by the IAU, many of which derive from traditional asterisms"
            }
        }
    },
    "relations": {
        "instance_of": {
            "identifier": "instance_of",
            "label": {
                "en": "instance of"
            },
            "description": {
                "en": "that class of which this subject is a particular example and member; different from P279 (subclass of); for example: K2 is an instance of mountain; volcano is a subclass of mountain (and an instance of volcanic landform)"
            }
        }
    },
    "triplets": [
        [
            "Vulpecula",
            "instance_of",
            "constellation"
        ]
    ]
}"""
        )


if __name__ == '__main__':
    unittest.main()
