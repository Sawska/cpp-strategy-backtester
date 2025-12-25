import csv
import random
import math

filename = "data/market_data.csv"
lines = 1000

price = 100.0
mean_price = 100.0
theta = 0.1       
sigma = 1.0       
dt = 1.0          

timestamp = 1600000000

print(f"Generating {lines} ticks using Ornstein-Uhlenbeck process...")
print(f"Target Mean: {mean_price}, Reversion Speed (theta): {theta}")

with open(filename, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(["timestamp", "price", "quantity", "side"])
    
    for i in range(lines):
        timestamp += 1
        
        drift = theta * (mean_price - price) * dt
        shock = sigma * random.gauss(0, 1) 
        
        price += drift + shock
        
        if price < 0.01: price = 0.01

        side = "buy" if (drift + shock) > 0 else "sell"
        
        writer.writerow([
            timestamp, 
            round(price, 2), 
            1.0, 
            side
        ])

print(f"Done! File {filename} created.")