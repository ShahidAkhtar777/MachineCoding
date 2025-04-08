# course_management/module/module.py

from abc import ABC, abstractmethod


class Module(ABC):
    """
    The Module interface declares the operations that all concrete modules
    must implement.
    """

    def __init__(self, title: str, content: str):
        self.title = title
        self.content = content

    @abstractmethod
    def get_description(self) -> str:
        pass


class MathModule(Module):
    def __init__(self, title: str, content: str):
        super().__init__(title, content)

    def get_description(self) -> str:
        return f"Math Module: {self.title} - {self.content}"


class ScienceModule(Module):
    def __init__(self, title: str, content: str):
        super().__init__(title, content)

    def get_description(self) -> str:
        return f"Science Module: {self.title} - {self.content}"


class HistoryModule(Module):
    def __init__(self, title: str, content: str):
        super().__init__(title, content)

    def get_description(self) -> str:
        return f"History Module: {self.title} - {self.content}"
