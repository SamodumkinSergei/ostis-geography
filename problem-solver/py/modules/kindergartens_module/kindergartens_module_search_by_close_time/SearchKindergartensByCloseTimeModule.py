from sc_kpm import ScModule
from .SearchKindergartensByCloseTimeAgent import SearchKindergartensByCloseTimeAgent


class SearchKindergartensByCloseTimeModule(ScModule):

    def __init__(self):
        super().__init__(SearchKindergartensByCloseTimeAgent())