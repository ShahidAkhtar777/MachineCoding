class Logistics:
    def create_transport(self):
        pass

    def plan_delivery(self, distance_km):
        transport = self.create_transport()
        transport.deliver(distance_km)