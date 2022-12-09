from sc_kpm import ScModule
from .SearchCollegeByRegionAgent import SearchCollegeByRegionAgent


class SearchCollegeByRegionModule(ScModule):
    def __init__(self):
        super().__init__(SearchCollegeByRegionAgent())