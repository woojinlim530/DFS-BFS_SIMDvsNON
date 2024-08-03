import os
import subprocess
import numpy as np
import matplotlib.pyplot as plt
from openpyxl import Workbook
from openpyxl.utils.dataframe import dataframe_to_rows
import pandas as pd

# Define the executable and number of runs
executable = "./new2deque"
num_runs = 10
sizes = [10, 50, 100, 500, 1000]  # Example sizes; adjust as needed

# Prepare Excel workbook
wb = Workbook()
ws = wb.active
ws.title = "Performance Data"
ws.append(["Size", "Time (s)", "Cache Misses", "Cache References", "Branch Misses", "Branches"])

# Run the executable and collect data
for size in sizes:
    for _ in range(num_runs):
        # Run the executable and collect stats
        command = f"perf stat -e cache-misses,cache-references,branch-misses,branches {executable} {size}"
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        
        # Parse the output
        lines = result.stderr.split('\n')
        cache_misses = int(lines[0].split()[0].replace(',', ''))
        cache_references = int(lines[1].split()[0].replace(',', ''))
        branch_misses = int(lines[2].split()[0].replace(',', ''))
        branches = int(lines[3].split()[0].replace(',', ''))
        time = float(result.stdout.split()[0].split()[0])
        
        # Append data to Excel
        ws.append([size, time, cache_misses, cache_references, branch_misses, branches])

# Save the workbook
wb.save("performance_data.xlsx")

# Load data for regression analysis
df = pd.read_excel("performance_data.xlsx")

# Calculate cache miss and branch miss percentages
df['Cache Miss %'] = df['Cache Misses'] / df['Cache References'] * 100
df['Branch Miss %'] = df['Branch Misses'] / df['Branches'] * 100

# Regression analysis
x = df['Size']
cache_miss_y = df['Cache Miss %']
branch_miss_y = df['Branch Miss %']

# Plot Cache Miss Percentage vs Size
plt.figure()
plt.scatter(x, cache_miss_y, color='blue', label='Cache Miss %')
plt.xlabel('Size')
plt.ylabel('Cache Miss %')
plt.title('Cache Miss Percentage vs Size')
plt.legend()
plt.grid(True)

# Fit regression line
m, b = np.polyfit(x, cache_miss_y, 1)
plt.plot(x, m*x + b, color='blue', linestyle='--')

# Plot Branch Miss Percentage vs Size
plt.figure()
plt.scatter(x, branch_miss_y, color='red', label='Branch Miss %')
plt.xlabel('Size')
plt.ylabel('Branch Miss %')
plt.title('Branch Miss Percentage vs Size')
plt.legend()
plt.grid(True)

# Fit regression line
m, b = np.polyfit(x, branch_miss_y, 1)
plt.plot(x, m*x + b, color='red', linestyle='--')

# Save plots
plt.savefig("performance_plots.png")
plt.show()
