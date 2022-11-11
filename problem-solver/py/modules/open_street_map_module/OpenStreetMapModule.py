from sc_kpm import ScModule
from .OpenStreetMapAgent import OpenStreetMapAgent


class OpenStreetMapModule(ScModule):
    def __init__(self):
        super().__init__(OpenStreetMapAgent())