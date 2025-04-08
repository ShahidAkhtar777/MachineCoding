# course_management/course/course_factory.py

from abc import ABC, abstractmethod
from typing import List
from modules.module import Module, MathModule, ScienceModule, HistoryModule
from courses.course import Course


class CourseFactory(ABC):
    """
    The CourseFactory class declares the factory method that is supposed to return an
    object of a Course class. The CourseFactory's subclasses usually provide the
    implementation of this method.
    """

    @abstractmethod
    def create_course(self) -> Course:
        pass


class MathCourseFactory(CourseFactory):
    def create_course(self) -> Course:
        modules = [
            MathModule("Algebra", "Basic Algebra concepts"),
            MathModule("Calculus", "Introduction to Calculus")
        ]
        return Course("Math 101", "Basic Mathematics", "3 months", modules)


class ScienceCourseFactory(CourseFactory):
    def create_course(self) -> Course:
        modules = [
            ScienceModule("Physics", "Fundamentals of Physics"),
            ScienceModule("Chemistry", "Basics of Chemistry")
        ]
        return Course("Science 101", "Basic Science", "3 months", modules)


class HistoryCourseFactory(CourseFactory):
    def create_course(self) -> Course:
        modules = [
            HistoryModule("Ancient History", "Overview of ancient civilizations"),
            HistoryModule("Modern History", "History of the modern world")
        ]
        return Course("History 101", "Basic History", "3 months", modules)
