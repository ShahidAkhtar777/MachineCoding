from .base_order import Order

class DineInOrder(Order):
    def process(self):
        print(f"🍽️ Processing dine-in order: {self.items}")
