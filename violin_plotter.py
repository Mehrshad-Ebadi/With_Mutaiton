import matplotlib.pyplot as plt
import numpy as np

# Load data from the "Alive.txt" file
the_additional = 'st_2000,nn_1000,mu_0.100000,ref_env_=0.400000'
num_run = '/numrun_0/'
address = './Outputs/' + the_additional + '/' + num_run
alive_file_path = address + 'Alive.txt'
alive_data = np.loadtxt(alive_file_path)

# Load data from the "du_Alive.txt" file
du_alive_file_path = address + 'du_Alive.txt'
du_alive_data = np.loadtxt(du_alive_file_path)

# Organize the data into groups of 500 steps for both datasets
alive_grouped_data = [alive_data[i:i + 500, 1] for i in range(0, len(alive_data), 500)]
du_alive_grouped_data = [du_alive_data[i:i + 500, 1] for i in range(0, len(du_alive_data), 500)]

# Set the width of each violin
width = 0.4

# Create a combined violin plot for both datasets
fig, ax = plt.subplots()

# Plot for "Alive.txt"
ax.violinplot(alive_grouped_data, positions=np.arange(1, len(alive_grouped_data) + 1) - width/2, showmeans=False, showmedians=True, widths=width)

# Plot for "du_Alive.txt"
ax.violinplot(du_alive_grouped_data, positions=np.arange(1, len(du_alive_grouped_data) + 1) + width/2, showmeans=False, showmedians=True, widths=width)

# Customize labels and title
ticks_positions = np.arange(1, len(alive_grouped_data) + 1)
ticks_labels = [f'{int(i*500/1000)}k' for i in ticks_positions]
plt.tick_params(axis='x', which='both', labelsize=8)
plt.xticks(ticks_positions, ticks_labels, rotation='vertical')  # Set rotation to 'vertical'
plt.xlabel('Time steps')
plt.ylabel('S')
#plt.title('Violin Plot for S')

# Show the plot
plt.savefig('./diagrams/violin.png', dpi=700)
