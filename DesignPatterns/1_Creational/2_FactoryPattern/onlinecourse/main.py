# course_management/main.py

from factories.course_factory import MathCourseFactory, ScienceCourseFactory, HistoryCourseFactory, CourseFactory


def client_code(factory: CourseFactory) -> None:
    """
    The client code works with an instance of a concrete factory, albeit through
    its base interface. As long as the client keeps working with the factory via
    the base interface, you can pass it any factory's subclass.
    """

    course = factory.create_course()
    print(f"Client: I'm not aware of the factory's class, but it still works.\n"
          f"{course.get_details()}", end="")


if __name__ == "__main__":
    print("App: Launched with the MathCourseFactory.")
    client_code(MathCourseFactory())
    print("\n")

    print("App: Launched with the ScienceCourseFactory.")
    client_code(ScienceCourseFactory())
    print("\n")

    print("App: Launched with the HistoryCourseFactory.")
    client_code(HistoryCourseFactory())
