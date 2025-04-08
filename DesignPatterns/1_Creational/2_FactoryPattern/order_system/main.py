from factories.delivery_factory import DeliveryFactory
from factories.dinein_factory import DineInFactory
from factories.takeaway_factory import TakeawayFactory

def process_order(factory, items):
    order = factory.create_order(items)
    order.process()

if __name__ == "__main__":
    process_order(DeliveryFactory(), ["Pizza", "Soda"])
    process_order(DineInFactory(), ["Pasta", "Wine"])
    process_order(TakeawayFactory(), ["Burger", "Fries"])
