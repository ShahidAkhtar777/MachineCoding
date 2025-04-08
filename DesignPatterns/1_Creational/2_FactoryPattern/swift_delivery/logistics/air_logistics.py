from logistics.base_logistics import Logistics
from transport.airplane import Airplane

class AirLogistics(Logistics):
    def create_transport(self):
        return Airplane()
