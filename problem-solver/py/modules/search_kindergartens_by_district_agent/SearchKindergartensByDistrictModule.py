from sc_kpm import ScModule
from .SearchKindergartensByDistrictAgent import SearchKindergartensByDistrictAgent


class SearchKindergartensByDistrictModule(ScModule):

    def __init__(self):
        super().__init__(SearchKindergartensByDistrictAgent())