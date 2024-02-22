import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import os
import warnings
from sklearn.metrics.pairwise import cosine_similarity


class Network:
    def __init__(self, name, adjacency_matrix):
        self.name = name
        self.adjacency_matrix = adjacency_matrix
        self.graph = self.create_graph()
        self.mean_in_degree = None
        self.mean_out_degree = None
        self.num_isolated_nodes = None
        self.num_nodes = None
        self.num_edges = None

    def create_graph(self):
        G = nx.DiGraph()  # Instantiate as a directed graph
        for i in range(len(self.adjacency_matrix)):
            for j in range(len(self.adjacency_matrix[i])):
                if self.adjacency_matrix[i][j] != 0:
                    G.add_edge(i, j, weight=self.adjacency_matrix[i][j])
            if all(val == 0 for val in self.adjacency_matrix[i]):
                G.add_node(i)
        return G

    def calculate_degrees(self):
        in_degrees = [self.graph.in_degree(node) for node in self.graph.nodes()]
        out_degrees = [self.graph.out_degree(node) for node in self.graph.nodes()]
        self.mean_in_degree = np.mean(in_degrees)
        self.mean_out_degree = np.mean(out_degrees)
    
    def calculate_num_nodes(self):
        self.num_nodes = len(self.graph.nodes())

    def calculate_num_edge(self):
        self.num_edges = self.graph.number_of_edges()
        
    def calculate_isolated_nodes(self):
        self.num_isolated_nodes = len(list(nx.isolates(self.graph)))

    def get_vector_representation(self):
        return np.array([self.mean_in_degree, self.mean_out_degree, self.num_isolated_nodes])

class Step:
    def __init__(self, step_number):
        self.step_number = step_number
        self.networks = []

    def add_network(self, network):
        self.networks.append(network)
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


file_path = './Outputs/st_2000,nn_500,mu_0.200000,ref_env_=-0.100000/numrun_0/'
address = file_path + 'History.txt'

steps = read_multiple_networks(address)

for i in range (len(steps)):
    for j in range(len(steps[i].networks)):
        steps[i].networks[j].calculate_degrees()
        steps[i].networks[j].calculate_isolated_nodes()
        steps[i].networks[j].calculate_num_nodes()
        steps[i].networks[j].calculate_num_edge()

saving = file_path + 'similarity.txt'

with open(saving, 'w') as file:
    for i in range(len(steps)):
        cos_sum = 0
        num_vectors = 0
        for j in range(len(steps[i].networks)):
            deg = (steps[i].networks[j].mean_in_degree + steps[i].networks[j].mean_out_degree) / 2.0
            spec1 = [deg, steps[i].networks[j].num_edges, steps[i].networks[j].num_isolated_nodes]
            
            for h in range(j, len(steps[i].networks)):    
                deg2 = (steps[i].networks[h].mean_in_degree + steps[i].networks[h].mean_out_degree) / 2.0
                spec2 = [deg2, steps[i].networks[h].num_edges, steps[i].networks[h].num_isolated_nodes]
                
                cos_similarity = cosine_similarity([spec1], [spec2])
                cos_sum += cos_similarity[0][0]
                #print(cos_similarity)
                num_vectors += 1
            
        average_cosine_similarity = round(cos_sum / num_vectors if num_vectors != 0 else 0 ,4)
        print (average_cosine_similarity)
        
        file.write(f"{i}\t{average_cosine_similarity}\n")
        file.flush()

address = file_path + 'History_du.txt'

for i in range (len(steps)):
    for j in range(len(steps[i].networks)):
        steps[i].networks[j].calculate_degrees()
        steps[i].networks[j].calculate_isolated_nodes()
        steps[i].networks[j].calculate_num_nodes()
        steps[i].networks[j].calculate_num_edge()

saving = file_path + 'similarity_du.txt'

with open(saving, 'w') as file:
    for i in range(len(steps)):
        cos_sum = 0
        num_vectors = 0
        for j in range(len(steps[i].networks)):
            deg = (steps[i].networks[j].mean_in_degree + steps[i].networks[j].mean_out_degree) / 2.0
            spec1 = [deg, steps[i].networks[j].num_edges, steps[i].networks[j].num_isolated_nodes]
            
            for h in range(j, len(steps[i].networks)):    
                deg2 = (steps[i].networks[h].mean_in_degree + steps[i].networks[h].mean_out_degree) / 2.0
                spec2 = [deg2, steps[i].networks[h].num_edges, steps[i].networks[h].num_isolated_nodes]
                
                cos_similarity = cosine_similarity([spec1], [spec2])
                cos_sum += cos_similarity[0][0]
                #print(cos_similarity)
                num_vectors += 1
            
        average_cosine_similarity = round(cos_sum / num_vectors if num_vectors != 0 else 0 ,4)
        print (average_cosine_similarity)
        
        file.write(f"{i}\t{average_cosine_similarity}\n")
        file.flush()
