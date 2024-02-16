import numpy as np
import networkx as nx
from sklearn.metrics.pairwise import cosine_similarity

class Network:
    def __init__(self, name, adjacency_matrix):
        self.name = name
        self.adjacency_matrix = adjacency_matrix
        self.graph = self.create_graph()
        self.mean_in_degree = None
        self.mean_out_degree = None
        self.mean_weight_sum = None
        self.num_isolated_nodes = None

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

    def calculate_degrees(self):
        # Calculate mean in-degree, mean out-degree, and mean sum of weights
        in_degrees = [self.graph.in_degree(node) for node in self.graph.nodes()]
        out_degrees = [self.graph.out_degree(node) for node in self.graph.nodes()]
        weights = [data['weight'] for _, _, data in self.graph.edges(data=True)]
        self.mean_in_degree = np.mean(in_degrees)
        self.mean_out_degree = np.mean(out_degrees)
        self.mean_weight_sum = np.mean(weights)

    def calculate_isolated_nodes(self):
        # Calculate the number of isolated nodes
        self.num_isolated_nodes = len(list(nx.isolates(self.graph)))

    def get_vector_representation(self):
        print (np.array([self.mean_in_degree, self.mean_out_degree, self.mean_weight_sum, self.num_isolated_nodes]))
        return np.array([self.mean_in_degree, self.mean_out_degree, self.mean_weight_sum, self.num_isolated_nodes])

class Step:
    def __init__(self, step_number):
        self.step_number = step_number
        self.networks = []

    def add_network(self, network):
        self.networks.append(network)

# Read networks from the file and store them in Step objects
def read_multiple_networks(file_path):
    steps = []
    current_step = None

    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if line.startswith("st."):
                if current_step:
                    steps.append(current_step)
                step_number = int(line.split('.')[1])
                current_step = Step(step_number)
            elif line.startswith("Network"):
                network_name = line
                adjacency_matrix = []
            elif line == '---':
                network_instance = Network(network_name, adjacency_matrix)
                current_step.add_network(network_instance)
            else:
                row = [float(value) for value in line.split()]
                adjacency_matrix.append(row)

    if current_step:
        steps.append(current_step)

    return steps

def calculate_cosine_similarity(vectors, steps):
    for step_idx, step in enumerate(steps):
        print(f"Step {step.step_number}:")
        for network_idx, network in enumerate(step.networks):
            print(f"{len(vectors)}")
    similarities = cosine_similarity(vectors)
    return similarities

# Calculate subtraction sum for each step and save them in a single text file
def save_cosine_similarities(file_path, steps, cosine_similarities):
    with open(file_path, 'w') as file:
        for step_idx, step in enumerate(steps):
            file.write(f"Step {step.step_number}\n")
            for i in range(len(step.networks)):
                for j in range(i+1, len(step.networks)):
                    similarity = cosine_similarities[step_idx][i][j]
                    file.write(f"{step.step_number}\t{similarity}\n")
            file.write('\n')

# Read networks from the file
file_path = './Outputs/st_1000,nn_1000,mu_0.500000,ref_env_=0.000000/numrun_0/History.txt'
steps = read_multiple_networks(file_path)

# Calculate cosine similarity between network vectors
vectors = []
for step in steps:
    for network in step.networks:
        network.calculate_degrees()
        network.calculate_isolated_nodes()  # Add calculation of isolated nodes
        vectors.append(network.get_vector_representation())

cosine_similarities = calculate_cosine_similarity(vectors, steps)

# Specify the output file path
output_file_path = './Cosine_Similarities.txt'

# Save cosine similarities to a file
save_cosine_similarities(output_file_path, steps, cosine_similarities)
