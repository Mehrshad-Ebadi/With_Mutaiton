import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
import shutil as sh
import os as os
import graphviz

sh.rmtree('normal_pic')
os.mkdir('./normal_pic')
for i in range(0,20000):
    I = str(i)
    passwand = ".txt"
    address = "./Results/Net_" + I + passwand
    adrs = "./normal_pic/Net_"
    
    
    try:
        num = np.loadtxt(address)
        
    except:
        print("no such file or directory")
    else:
    
        G = nx.from_numpy_array(num, create_using=nx.DiGraph, parallel_edges=False)
        edge_labels = nx.get_edge_attributes(G, "weight")
        #FF = input(edge_labels)
        poss = nx.nx_pydot.graphviz_layout(G, prog='circo')
        nx.draw_networkx_edge_labels(G, poss, edge_labels, font_size=8)
        nx.draw_networkx(G, with_labels=True, pos=poss, node_color="#00b4d9", font_size=8)
        j = adrs + I + ".jpg"
        plt.savefig(j,format='jpeg', dpi=400)
        plt.close('all')
        
        
