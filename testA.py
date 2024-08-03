import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Sample data: Replace these lists with your actual data
sizes = [10, 10, 10, 10, 10, 10, 3000, 3000, 3000, 4000, 4000, 4000]
times = [0.02, 0.018, 0.019, 0.045, 0.043, 0.047, 0.067, 0.065, 0.066, 0.089, 0.088, 0.09]

# Create a DataFrame
data = {'size': sizes, 'time': times}
df = pd.DataFrame(data)

# Set up the plot
plt.figure(figsize=(10, 6))

# Plot the regression line with seaborn
sns.regplot(x='size', y='time', data=df, ci=None)

# Add titles and labels
plt.title('BFS Execution Time vs Number of Nodes')
plt.xlabel('Number of Nodes')
plt.ylabel('Execution Time (seconds)')

# Show the plot
plt.show()
