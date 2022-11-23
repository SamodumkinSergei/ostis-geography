from sc_kpm import ScModule
from .SearchPharmaciesByChainAgent import SearchPharmaciesByChainAgent

class SearchPharmaciesByChainModule(ScModule):

    def __init__(self):
        super().__init__(SearchPharmaciesByChainAgent())
