from logistics.road_logistics import RoadLogistics
from logistics.sea_logistics import SeaLogistics
from logistics.air_logistics import AirLogistics

def run():
    distance = 1500

    print("\n--- Road Logistics ---")
    RoadLogistics().plan_delivery(distance)

    print("\n--- Sea Logistics ---")
    SeaLogistics().plan_delivery(distance)

    print("\n--- Air Logistics ---")
    AirLogistics().plan_delivery(distance)

if __name__ == "__main__":
    run()
