from sc_kpm import ScModule
from .SearchLargerPharmacyChainsAgent import SearchLargerPharmacyChainsAgent

class SearchLargerPharmacyChainsModule(ScModule):

    def __init__(self):
        super().__init__(SearchLargerPharmacyChainsAgent())
