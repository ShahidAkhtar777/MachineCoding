from logistics.base_logistics import Logistics
from transport.ship import Ship

class SeaLogistics(Logistics):
    def create_transport(self):
        return Ship()