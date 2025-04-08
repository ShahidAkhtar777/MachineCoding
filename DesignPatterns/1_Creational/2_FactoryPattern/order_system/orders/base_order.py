class Order:
    def __init__(self, items):
        self.items = items

    def process(self):
        raise NotImplementedError("Must override in subclass")
