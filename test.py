import networkx as nx
G=nx.complete_graph(4)
pos=nx.spring_layout(G)
pos_higher = {}

for k, v in pos.items():
    if(v[1]>0):
        pos_higher[k] = (v[0]-0.1, v[1]+0.1)
    else:
        pos_higher[k] = (v[0]-0.1, v[1]-0.1)

labels={0:'A',1:'B',2:'C',3:'D'}
nx.draw(G)
nx.draw_networkx_labels(G, pos_higher,labels)
