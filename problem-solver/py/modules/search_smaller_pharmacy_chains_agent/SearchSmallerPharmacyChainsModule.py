from sc_kpm import ScModule
from .SearchSmallerPharmacyChainsAgent import SearchSmallerPharmacyChainsAgent

class SearchSmallerPharmacyChainsModule(ScModule):

    def __init__(self):
        super().__init__(SearchSmallerPharmacyChainsAgent())
