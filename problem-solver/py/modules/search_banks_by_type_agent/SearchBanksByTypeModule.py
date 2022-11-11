from sc_kpm import ScModule
from .SearchBanksByTypeAgent import SearchBanksByTypeAgent


class SearchBanksByTypeModule(ScModule):
    def __init__(self):
        super().__init__(SearchBanksByTypeAgent())
