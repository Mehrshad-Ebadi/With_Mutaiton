import matplotlib.pyplot as plt
import numpy as np

a = list()
b = list()
numb_run = 1

for i in range(numb_run):
    addres = f'./Outputs/st_2000,nn_1000,mu_0.100000,ref_env_=0.000000/numrun_{i}/Alive.txt'
    alive_data = np.loadtxt(addres)

    du_addres = f'./Outputs/st_2000,nn_1000,mu_0.100000,ref_env_=0.000000/numrun_{i}/du_Alive.txt'
    du_alive_data = np.loadtxt(du_addres)

    a.append(alive_data)
    b.append(du_alive_data)

a = np.mean(a, axis=0)
b = np.mean(b, axis=0)
print (a)
u = input("thanks")
# Organize the data into groups of 500 steps for both datasets
alive_grouped_data = [a[i:i + 500, 1] for i in range(0, len(a), 500)]
du_alive_grouped_data = [b[i:i + 500, 1] for i in range(0, len(b), 500)]

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


plt.scatter([i[0] for i in a], [i[1] for i in a],label='non-duplicated',color='blue', alpha=0.7, s=1)
plt.scatter([i[0] for i in b], [i[1] for i in b],label='duplicated',color='orange', alpha=0.3, s=1)
plt.xlabel("Time Steps")
plt.ylabel("S")
plt.savefig('./diagrams/scatter.png', dpi=700)