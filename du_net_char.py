import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import os
import warnings
from networkx.algorithms.similarity import graph_edit_distance

class Network:
    def __init__(self, name, adjacency_matrix):
        self.name = name
        self.adjacency_matrix = adjacency_matrix
        self.graph = self.create_graph()

    def create_graph(self):
        # Convert adjacency matrix to a directed networkx graph
        edges = []
        for i in range(len(self.adjacency_matrix)):
            for j in range(len(self.adjacency_matrix[i])):
                if self.adjacency_matrix[i][j] != 0:
                    edges.append((i, j, self.adjacency_matrix[i][j]))
        graph = nx.DiGraph()
        graph.add_weighted_edges_from(edges)
        return graph
    
    def calculate_mean_degree(self, degree_type):
        # Calculate the mean degree for the specified type (in-degree or out-degree)
        degrees = getattr(self.graph, degree_type)()
        if len(degrees) == 0:
            return 0  # Avoid division by zero, return 0 if no nodes
        mean_degree = sum(dict(degrees).values()) / len(degrees)
        return round(mean_degree, 3)

    def plot_network(self, step, output_directory='./du_graph/'):
        with warnings.catch_warnings():
            warnings.filterwarnings("ignore", category=DeprecationWarning)
            plt.figure(figsize=(8, 6))
            pos = nx.spring_layout(self.graph)  # You can use other layouts based on your preference

            # Draw nodes
            nx.draw(self.graph, pos, with_labels=True, node_color='skyblue', node_size=200, font_size=10, font_color='black')

            # Set edge colors based on weight sign
            edge_colors = ['red' if self.graph[i][j]['weight'] < 0 else 'black' if self.graph[i][j]['weight'] == 0 else 'blue' for i, j in self.graph.edges()]

            # Draw edges with labels
            edge_labels = {(i, j): self.graph[i][j]['weight'] for i, j in self.graph.edges()}
            nx.draw_networkx_edges(self.graph, pos, edgelist=list(self.graph.edges()), edge_color=edge_colors)
            nx.draw_networkx_edge_labels(self.graph, pos, edge_labels=edge_labels, font_color='black', font_size=8, verticalalignment='bottom')  # Set verticalalignment to 'bottom'

            plt.title(f"{self.name} Network - Step {step}")
            plt.savefig(os.path.join(output_directory, f"{self.name}_network_step_{step}.png"))
            plt.close()

    def calculate_cluster_coefficient(self):
        if len(self.graph.nodes) == 0:
            return 0  # Return 0 if the graph is empty

        cluster_coefficient = nx.average_clustering(self.graph)
        return round(cluster_coefficient, 3)
    
def plot_specific_network(networks_by_step, step_to_plot, network_number_to_plot):
    for step, network_instance_list in networks_by_step.items():
        if step == step_to_plot:
            for i, network_instance in enumerate(network_instance_list):
                if i + 1 == network_number_to_plot:
                    network_instance.plot_network(step)

def write_network_analysis(file_path, networks_by_step, step_to_plot, network_number_to_plot):
    #with open(file_path, 'a') as output_file:
    #    output_file.write("step,net,Mn_ideg,Mn_odeg,cl_c\n")

        #for step, network_instances in networks_by_step.items():
        #    for network_instance in network_instances:
        #        average_in_degree = network_instance.calculate_mean_degree('in_degree')
        #        average_out_degree = network_instance.calculate_mean_degree('out_degree')
        #        cluster_coefficient = network_instance.calculate_cluster_coefficient()
        #        #output_file.write(f"{step},{network_instance.name},{average_in_degree},{average_out_degree},{diameter},{cluster_coefficient}\n")
        #        output_file.write(f"{step},{network_instance.name},{average_in_degree},{average_out_degree},{cluster_coefficient}\n")
    
    plot_specific_network(networks_by_step, step_to_plot, network_number_to_plot)

def read_multiple_networks(file_path):
    networks = {}
    current_network = None
    current_network_name = None
    current_step = None

    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if line.startswith("st."):
                # Process the previous network (if any) and update the current step
                if current_network_name and current_network:
                    network_instance = Network(current_network_name, current_network)
                    if current_step not in networks:
                        networks[current_step] = []
                    networks[current_step].append(network_instance)

                # Update the current step
                current_step = int(line.split('.')[1])
                current_network = None

            elif line == '---':
                # Process the current network
                if current_network_name and current_network:
                    network_instance = Network(current_network_name, current_network)
                    if current_step not in networks:
                        networks[current_step] = []
                    networks[current_step].append(network_instance)
                    current_network = None

            else:
                if line.startswith("Network"):
                    current_network_name = line
                else:
                    row = [float(value) for value in line.split()]
                    if current_network is None:
                        current_network = []
                    current_network.append(row)

        # Add the last network
        if current_network_name and current_network:
            network_instance = Network(current_network_name, current_network)
            if current_step not in networks:
                networks[current_step] = []
            networks[current_step].append(network_instance)

    return networks

'''
def calculate_ged(networks_by_step):
    num_networks = sum(len(networks) for networks in networks_by_step.values())
    ged_matrix = np.zeros((num_networks, num_networks))

    networks_list = [network for networks in networks_by_step.values() for network in networks]

    for i in range(num_networks):
        for j in range(i + 1, num_networks):
            ged_value = graph_edit_distance(networks_list[i].graph, networks_list[j].graph)
            ged_matrix[i, j] = ged_value
            ged_matrix[j, i] = ged_value

    return ged_matrix

def save_ged_matrix(ged_matrix, output_file_path):
    with open(output_file_path, 'w') as output_file:
        # Write the header
        output_file.write("Step\t")
        for i in range(ged_matrix.shape[0]):
            output_file.write(f"Network_{i}\t")
        output_file.write("\n")

        # Write the GED matrix
        for step, row in enumerate(ged_matrix):
            output_file.write(f"{step}\t")
            for value in row:
                output_file.write(f"{value:.4f}\t")
            output_file.write("\n")
'''
file_path = './History/du_Network.txt'

networks_by_step = read_multiple_networks(file_path)

# Specify the output file path
output_file_path = './Outputs/00du_Net_analysis.txt'
step_to_plot = 2000
network_number_to_plot = 900

# Calculate and write the network analysis parameters to the output file
write_network_analysis(output_file_path, networks_by_step, step_to_plot, network_number_to_plot)

#ged_matrix = calculate_ged(networks_by_step)
#output_ged_file_path = './Outputs/GED_matrix.txt'
#save_ged_matrix(ged_matrix, output_ged_file_path)
