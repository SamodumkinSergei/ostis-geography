import argparse

from loaders.WikiDataWithContextLoader import WikiDataWithContextLoader
from translators.JsonToScsTranslator import json_to_scs


def parse(entities, save_dir='sc_out'):
    loader = WikiDataWithContextLoader()
    loader.load_entities(entities)
    json_to_scs(loader.get_json(), save_dir)

def args_parser_init():
    parser = argparse.ArgumentParser(
        description='Module for parsing external sources into SC-code')
    parser.add_argument('entities', metavar='ENT', type=str,
                        nargs='+', help="Searched entities")
    parser.add_argument('--dir', default='sc_out', type=str,
                        help='Enter directory to save scs files')
    return parser


if __name__ == "__main__":
    parser = args_parser_init()
    args = parser.parse_args()
    parse(args.entities, args.dir)



