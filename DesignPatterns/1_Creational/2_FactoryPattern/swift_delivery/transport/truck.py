from transport.base import Transport

class Truck(Transport):
    def deliver(self, distance_km: float):
        cost = distance_km * 5
        time = distance_km / 60
        print(f"🚛 Truck delivering {distance_km}km | Cost: ${cost} | Time: {time:.2f} hrs")
