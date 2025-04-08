from transport.base import Transport

class Ship(Transport):
    def deliver(self, distance_km: float):
        cost = distance_km * 9
        time = distance_km / 80
        print(f"🚢 Ship delivering {distance_km}km | Cost: ${cost} | Time: {time:.2f} hrs")
