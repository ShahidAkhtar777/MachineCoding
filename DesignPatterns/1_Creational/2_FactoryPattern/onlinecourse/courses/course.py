from modules.module import Module
from typing import List


class Course:
    """
    The Course class represents a course with a title, name, duration, and modules.
    """
    def __init__(self, title: str, name: str, duration: str, modules: List[Module]):
        self.title = title
        self.name = name
        self.duration = duration
        self.modules = modules

    def get_details(self) -> str:
        module_descriptions = "\n".join([module.get_description() for module in self.modules])
        return (f"Name: {self.name}\n"
                f"Duration: {self.duration}\n"
                f"Title: {self.title}\n"
                f"Modules:\n{module_descriptions}")
