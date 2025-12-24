import csv
import random

filename = "data/market_data.csv"
lines = 1000
current_price = 100.0
timestamp = 1600000000

with open(filename, 'w') as f:
    writer = csv.writer(f)
    writer.writerow(["timestamp", "price", "quantity", "side", "is_market_maker"])
    
    for i in range(lines):
        timestamp += 1
        current_price += random.uniform(-2.0, 2.0) 
        writer.writerow([timestamp, round(current_price, 2), 1.0, "buy", "true"])

print(f"Generated {lines} ticks.")