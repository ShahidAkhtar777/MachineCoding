from orders.takeaway_order import TakeawayOrder
from .base_factory import OrderFactory

class TakeawayFactory(OrderFactory):
    def create_order(self, items):
        return TakeawayOrder(items)
