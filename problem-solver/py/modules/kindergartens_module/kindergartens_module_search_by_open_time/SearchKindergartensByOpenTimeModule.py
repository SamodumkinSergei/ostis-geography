from sc_kpm import ScModule
from .SearchKindergartensByOpenTimeAgent import SearchKindergartensByOpenTimeAgent


class SearchKindergartensByOpenTimeModule(ScModule):

    def __init__(self):
        super().__init__(SearchKindergartensByOpenTimeAgent())