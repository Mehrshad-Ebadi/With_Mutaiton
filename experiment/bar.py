import matplotlib.pyplot as plt
import numpy as np

# Read the generated data from the output file
with open("output.txt", "r") as file:
    data = [round(float(line.strip()), 2) for line in file.readlines()]

# Plot the frequency distribution
plt.figure(figsize=(10, 6))
plt.hist(data, bins=np.arange(min(data), max(data) + 0.1, 0.1), edgecolor='black')
plt.xlabel('Generated Numbers')
plt.ylabel('Frequency')
plt.title('Frequency Distribution of Generated Numbers')
plt.grid(True)
plt.show()
