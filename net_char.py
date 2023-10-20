import numpy as np
import networkx as nx
from igraph import Graph

step = 0
with open('./temp.txt', 'r') as file:
    content = file.read()
    step = float(content)

exten = '.txt'
Results = './Results/Net_'
save_path = './net_track/00Net_analysis.txt'

for I in range (0,10000):

    i = str(I)
    file_path = Results + i + exten
    
    adjacency_matrix = np.loadtxt(file_path)
    adjacency_matrix = np.abs(adjacency_matrix)
    G = nx.DiGraph(adjacency_matrix)
    num_nodes = len(G.nodes())
    num_edges = len(G.edges())
    
    average_in_degree = round(sum(dict(G.in_degree(weight='weight')).values()) / num_nodes, 3)
    average_out_degree = round(sum(dict(G.out_degree(weight='weight')).values()) / num_nodes, 3)

    try:
        average_degree = round(sum(dict(G.degree()).values()) / num_nodes, 3)
    except:
        average_degree = None
    
    try:
        clustering_coefficient = round(nx.average_clustering(G), 3)
    except:
        clustering_coefficient = None
    
    try:
        diameter = round(nx.diameter(G), 3)

    except:
        diameter=None
        try:
            diameter = round(nx.diameter(G.to_undirected(), weight='weight'), 3)
        except:
            diameter=None
        
    
    with open(save_path, 'a') as file:
           
        file.write(f"{step},{I},{average_in_degree},{average_out_degree},{diameter},{clustering_coefficient}")
    del G
    file = open(save_path, 'a')
    file.write('\n')
