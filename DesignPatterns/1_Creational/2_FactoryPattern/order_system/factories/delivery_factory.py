from orders.delivery_order import DeliveryOrder
from .base_factory import OrderFactory

class DeliveryFactory(OrderFactory):
    def create_order(self, items):
        return DeliveryOrder(items)
