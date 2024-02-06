import numpy as np
import matplotlib.pyplot as plt
import os as os
import shutil as sh
import glob

#pattern = './Outputs/*/numrun_0/Alive.txt'
#directories = glob.glob(pattern)
#
#for directory in directories:
#    # Extract the dynamic part from the directory path
#    dynamic_part = directory.split('/')[-2]
#
#addres = f'{directory}/Alive.txt'
#du_addres = f'{directory}/du_Alive.txt'
the_additional = 'st_1000,nn_1000,mu_0.100000,ref_env_=0.000000'
time = np.array(range(2001),dtype=float)
alive = np.array(range(2001),dtype=float)

num_run = '/numrun_' + str(0) + '/'
address = './Outputs/' + the_additional + '/' + num_run
Z = np.loadtxt(address + "envi.txt")
time = Z[:,0]
du_alive = np.array(range(2001),dtype=float)
uni = np.array(range(2001),dtype=float)
du_uni = np.array(range(2001),dtype=float)
edge = np.array(range(2001),dtype=float)
du_edge = np.array(range(2001),dtype=float)
iso = np.array(range(2001),dtype=float)
du_iso = np.array(range(2001),dtype=float)
number_simulation = 2
for i in range (0,number_simulation):

    num_run = '/numrun_' + str(i) + '/'
    address = './Outputs/' + the_additional + '/' + num_run
    x = np.loadtxt(address + "Alive.txt")
    y = np.loadtxt(address + "du_Alive.txt")
    k = np.loadtxt(address + "uni.txt")
    h = np.loadtxt(address + "du_uni.txt")
    j = np.loadtxt(address + "edge.txt")
    q = np.loadtxt(address + "du_edge.txt")
    n = np.loadtxt(address + "iso.txt")
    m = np.loadtxt(address + "du_iso.txt")
    
    alive = x[:, 1]
    du_alive = y[:, 1]
    uni = k[:, 1]
    du_uni = h[:, 1]
    edge = j[:, 1]
    du_edge = q[:, 1]
    iso = n[:, 1]
    du_iso = m[:, 1]

alive = alive / number_simulation
du_alive = du_alive / number_simulation
uni = uni / number_simulation
du_uni = du_uni / number_simulation
edge = edge / number_simulation
du_edge = du_edge / number_simulation
iso = iso / number_simulation
du_iso = du_iso / number_simulation

plt.scatter(time, alive,label='non-duplicated',color='blue', alpha=0.7, s=1)
plt.scatter(time, du_alive,label='duplicated',color='orange', alpha=0.3, s=1)

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


plt.plot(time, uni,label='non-duplicated',color='blue')
plt.plot(time, du_uni,label='duplicated',color='orange', alpha=0.6)
plt.yscale('log')
plt.xscale('log')
#plt.xlim(0,400)
plt.xlabel("log [Time steps]")
plt.ylabel("log[Number of Unique networks]")
plt.grid()
plt.savefig('./diagrams/un.png',dpi=400)
plt.close()

plt.plot(time, edge,label='non-duplicated_edges',color='blue')
plt.plot(time, du_edge,label='duplicated_edges',color='orange', alpha=0.6)
plt.xlabel("Time step")
plt.ylabel("Edges")
plt.grid()
plt.savefig('./diagrams/edge.png',dpi=400)
plt.close()



plt.scatter(time, iso,label='non-duplicated_n_iso',color='blue', s=2)
plt.scatter(time, du_iso,label='duplicated_n_iso',color='orange', alpha=0.6, s=2)
plt.xlabel("Time step")
plt.ylabel("number of isolated")
plt.grid()
plt.savefig('./diagrams/iso.png',dpi=400)
plt.close()