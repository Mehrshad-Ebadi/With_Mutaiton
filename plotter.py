import numpy as np
import matplotlib.pyplot as plt
import os as os
import shutil as sh
import glob

sh.rmtree('./diagrams')
os.mkdir("./diagrams")
#pattern = './Outputs/*/numrun_0/Alive.txt'
#directories = glob.glob(pattern)
#
#for directory in directories:
#    # Extract the dynamic part from the directory path
#    dynamic_part = directory.split('/')[-2]
#
#addres = f'{directory}/Alive.txt'
#du_addres = f'{directory}/du_Alive.txt'
the_additional = 'st_1000,nn_1000,mu_0.200000,ref_env_=0.000000'
num_run = '/numrun_0/'
address = './Outputs/' + the_additional + '/' + num_run
X = np.loadtxt(address + "Alive.txt")
Y = np.loadtxt(address + "du_Alive.txt")
Z = np.loadtxt(address + "envi.txt")
K = np.loadtxt(address + "uni.txt")
H = np.loadtxt(address + "du_uni.txt")
J = np.loadtxt(address + "edge.txt")
Q = np.loadtxt(address + "du_edge.txt")
j = np.loadtxt(address + "iso.txt")
q = np.loadtxt(address + "du_iso.txt")

plt.scatter([i[0] for i in X], [i[1] for i in X],label='non-duplicated',color='blue', alpha=0.7, s=1)
plt.scatter([i[0] for i in Y], [i[1] for i in Y],label='duplicated',color='orange', alpha=0.3, s=1)

#plt.plot([i[0] for i in X], [i[1] for i in X],label='non-duplicated',color='blue')
#plt.plot([i[0] for i in Y], [i[1] for i in Y],label='duplicated',color='orange', alpha=0.6)



#plt.bar([i[0] for i in X], [i[1] for i in X],label='non-duplicated',color='blue')
#plt.bar([i[0] for i in Y], [i[1] for i in Y],label='duplicated',color='orange', alpha=0.5)

#plt.hist([i[1] for i in X], bins=30, label='non-duplicated', color='blue')
#plt.hist([i[1] for i in Y], bins=30, label='duplicated', color='orange', alpha=0.7)

plt.xlabel("Time Steps")
plt.ylabel("S")
plt.legend()
plt.grid()
plt.savefig('./diagrams/survivebility.png',dpi=400)
plt.close()

plt.plot([i[0] for i in Z], [i[1] for i in Z],color='black', lw=0.2)
plt.xlabel("Time steps")
plt.ylabel("Input value")
plt.grid()
plt.savefig('./diagrams/env.png',dpi=400)
plt.close()


plt.plot([i[0] for i in K], [i[1] for i in K],label='non-duplicated',color='blue')
plt.plot([i[0] for i in H], [i[1] for i in H],label='duplicated',color='orange', alpha=0.6)
plt.yscale('log')
plt.xscale('log')
#plt.xlim(0,400)
plt.xlabel("log [Time steps]")
plt.ylabel("log[Number of Unique networks]")
plt.grid()
plt.savefig('./diagrams/un.png',dpi=400)
plt.close()

plt.plot([i[0] for i in J], [i[1] for i in J],label='non-duplicated_edges',color='blue')
plt.plot([i[0] for i in Q], [i[1] for i in Q],label='duplicated_edges',color='orange', alpha=0.6)
plt.xlabel("Time step")
plt.ylabel("Edges")
plt.grid()
plt.savefig('./diagrams/edge.png',dpi=400)
plt.close()



plt.scatter([i[0] for i in j], [i[1] for i in j],label='non-duplicated_n_iso',color='blue', s=2)
plt.scatter([i[0] for i in q], [i[1] for i in q],label='duplicated_n_iso',color='orange', alpha=0.6, s=2)
plt.xlabel("Time step")
plt.ylabel("number of isolated")
plt.grid()
plt.savefig('./diagrams/iso.png',dpi=400)
plt.close()