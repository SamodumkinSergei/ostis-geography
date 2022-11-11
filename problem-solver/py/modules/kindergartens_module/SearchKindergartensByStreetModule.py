from sc_kpm import ScModule
from .SearchKindergartensByStreetAgent import SearchKindergartensByStreetAgent


class SearchKindergartensByStreetModule(ScModule):

    def __init__(self):
        super().__init__(SearchKindergartensByStreetAgent())