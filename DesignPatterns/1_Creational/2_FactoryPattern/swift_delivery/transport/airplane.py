from transport.base import Transport

class Airplane(Transport):
    def deliver(self, distance_km: float):
        cost = distance_km * 20
        time = distance_km / 150
        print(f"✈️ Airplane delivering {distance_km}km | Cost: ${cost} | Time: {time:.2f} hrs")
