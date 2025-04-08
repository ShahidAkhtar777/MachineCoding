from .base_order import Order

class DeliveryOrder(Order):
    def process(self):
        print(f"🚚 Processing delivery order: {self.items}")
