from sc_kpm import ScModule
from .StreetTranslatorExecuteAgent import StreetTranslatorExecuteAgent


class StreetTranslatorModule(ScModule):
    def __init__(self):
        super().__init__(StreetTranslatorExecuteAgent())
