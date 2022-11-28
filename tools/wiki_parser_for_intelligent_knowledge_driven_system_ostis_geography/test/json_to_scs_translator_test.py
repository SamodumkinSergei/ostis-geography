import unittest

from assertpy import assert_that

from src.translators.JsonToScsTranslator import json_to_scs
from test.util.directory_comparison import are_dir_trees_equal


class JsonToScsTranslatorTest(unittest.TestCase):
    def test_json_to_scs_translation(self):
        # Arrange
        json = """{
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
        # Act
        # Saving files to the test directory
        json_to_scs(json, "translation_result")
        # Assert
        # Deep compare generated files and correct translation
        assert_that(are_dir_trees_equal("correct_translation_result", "correct_translation_result")).is_true()


if __name__ == '__main__':
    unittest.main()
