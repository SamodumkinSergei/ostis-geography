from sc_kpm import ScModule
from .SearchKindergartensByRegionAgent import SearchKindergartensByRegionAgent


class SearchKindergartensByRegionModule(ScModule):

    def __init__(self):
        super().__init__(SearchKindergartensByRegionAgent())