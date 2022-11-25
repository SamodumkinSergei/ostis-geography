from sc_kpm import ScModule
from .SearchUniversityByRegionAgent import SearchUniversityByRegionAgent


class SearchUniversityByRegionModule(ScModule):
    def __init__(self):
        super().__init__(SearchUniversityByRegionAgent())
