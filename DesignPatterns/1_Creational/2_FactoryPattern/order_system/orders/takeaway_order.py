from .base_order import Order

class TakeawayOrder(Order):
    def process(self):
        print(f"🥡 Processing takeaway order: {self.items}")
