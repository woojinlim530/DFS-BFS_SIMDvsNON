import subprocess
import pandas as pd

# Define the node size
node_size = 100000

# Define the executables and number of runs
executables = ["new2deque", "new2queue", "new2ll", "new2simd"]
data_structure_abbreviations = ["dq", "q", "ll", "simd"]
num_runs = 2

# Dictionary to hold the results
results = {"Type_Run": []}
results[node_size] = []

# Run the command multiple times for each executable and node size
for exec_name, ds_abbr in zip(executables, data_structure_abbreviations):
    for run in range(1, num_runs + 1):
        run_label = f"{ds_abbr}{run}"
        results["Type_Run"].append(run_label)
        # Run the executable with the specified node size
        command = f"./{exec_name}"
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        # Extract the time from the output
        output = result.stdout
        time_str = output.split()[-2]  # Assuming the time value is always the second last item in the output
        results[node_size].append(float(time_str))

# Create a DataFrame and populate it with the results
df = pd.DataFrame(results)

# Save the DataFrame to an Excel file
output_file = "timing_data.xlsx"
df.to_excel(output_file, index=False)

print(f"Times saved to {output_file}")
