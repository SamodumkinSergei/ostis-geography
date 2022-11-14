import argparse

from sc_kpm import ScServer

from modules.lakes_module.LakesModule import LakesModule
from modules.open_street_map_module.OpenStreetMapModule import OpenStreetMapModule
from modules.search_banks_by_type_agent.SearchBanksByTypeModule import SearchBanksByTypeModule
from modules.search_banks_by_city_agent.SearchBanksByCityModule import SearchBanksByCityModule
from modules.street_translator_module.StreetTranslatorModule import StreetTranslatorModule
from modules.search_kindergartens_by_region_agent.SearchKindergartensByRegionModule import SearchKindergartensByRegionModule
from modules.search_kindergartens_by_district_agent.SearchKindergartensByDistrictModule import SearchKindergartensByDistrictModule
from modules.search_pharmacies_by_chain_agent.SearchPharmaciesByChainModule import SearchPharmaciesByChainModule
from modules.search_smaller_pharmacy_chains_agent.SearchSmallerPharmacyChainsModule import SearchSmallerPharmacyChainsModule
from modules.search_larger_pharmacy_chains_agent.SearchLargerPharmacyChainsModule import SearchLargerPharmacyChainsModule

import logging.config
from pathlib import Path

from sc_kpm import KPM_LOGGER_NAME

SC_SERVER_HOST = "host"
SC_SERVER_PORT = "port"

SC_SERVER_HOST_DEFAULT = "localhost"
SC_SERVER_PORT_DEFAULT = "8090"

logging.config.dictConfig(
    dict(
        version=1,
        disable_existing_loggers=False,
        formatters={
            "common_formatter": {
                "format": "%(asctime)s | %(levelname)s | %(name)s | %(message)s",
                "datefmt": "[%d-%b-%y %H:%M:%S]",
            }
        },
        handlers={
            "stream_handler": {
                "class": "logging.StreamHandler",
                "level": logging.INFO,
                "formatter": "common_formatter",
            },
            "file_handler": {
                "class": "logging.FileHandler",
                "level": logging.DEBUG,
                "filename": Path(__file__).resolve().parent.joinpath("py_sc_kpm.log"),
                "formatter": "common_formatter",
            },
        },
        loggers={
            KPM_LOGGER_NAME: {
                "handlers": ["stream_handler", "file_handler"],
                "level": logging.DEBUG,
            }
        },
    )
)

def main(args: dict):
    server = ScServer(f"ws://{args[SC_SERVER_HOST]}:{args[SC_SERVER_PORT]}")

    with server.connect():
        modules = [
            LakesModule(),
            OpenStreetMapModule(),
            SearchBanksByTypeModule(),
            SearchBanksByCityModule(),
            StreetTranslatorModule(),
            SearchKindergartensByDistrictModule(),
            SearchKindergartensByRegionModule(),
            SearchPharmaciesByChainModule(),
            SearchSmallerPharmacyChainsModule(),
            SearchLargerPharmacyChainsModule()
        ]
        server.add_modules(*modules)

        with server.register_modules():
            server.wait_for_sigint()
            server.remove_modules(*modules)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '--host', type=str, dest=SC_SERVER_HOST, default=SC_SERVER_HOST_DEFAULT, help="Sc-server host")
    parser.add_argument(
        '--port', type=int, dest=SC_SERVER_PORT, default=SC_SERVER_PORT_DEFAULT, help="Sc-server port")
    args = parser.parse_args()

    main(vars(args))
