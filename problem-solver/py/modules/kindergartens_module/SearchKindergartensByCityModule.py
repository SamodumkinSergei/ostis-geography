from sc_kpm import ScModule
from .SearchKindergartensByCityAgent import SearchKindergartensByCityAgent


class SearchKindergartensByCityModule(ScModule):

    def __init__(self):
        super().__init__(SearchKindergartensByCityAgent())