from sc_kpm import ScModule
from .GetLakesByAreaAgent import GetLakesByAreaAgent


class LakesModule(ScModule):
    def __init__(self):
        super().__init__(GetLakesByAreaAgent())
