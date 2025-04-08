from orders.dinein_order import DineInOrder
from .base_factory import OrderFactory

class DineInFactory(OrderFactory):
    def create_order(self, items):
        return DineInOrder(items)
