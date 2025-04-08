from logistics.base_logistics import Logistics
from transport.truck import Truck

class RoadLogistics(Logistics):
    def create_transport(self):
        return Truck()
