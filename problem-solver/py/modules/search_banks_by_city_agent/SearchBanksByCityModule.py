from sc_kpm import ScModule
from .SearchBanksByCityAgent import SearchBanksByCityAgent


class SearchBanksByCityModule(ScModule):

    def __init__(self):
        super().__init__(SearchBanksByCityAgent())
