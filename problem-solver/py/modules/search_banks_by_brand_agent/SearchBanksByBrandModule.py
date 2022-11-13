from sc_kpm import ScModule
from .SearchBanksByBrandAgent import SearchBanksByBrandAgent


class SearchBanksByBrandModule(ScModule):

    def __init__(self):
        super().__init__(SearchBanksByBrandAgent())
