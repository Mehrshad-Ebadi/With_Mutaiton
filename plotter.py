import numpy as np
import matplotlib.pyplot as plt
import os as os
import shutil as sh

sh.rmtree('./diagrams')
os.mkdir("./diagrams")
X = np.loadtxt("./Outputs/Alive.txt")
Y = np.loadtxt("./Outputs/du_Alive.txt")
Z = np.loadtxt("./Outputs/envi.txt")

#for i in range (0,len(X)):
#    X[i][1] = X[i][1] / 10000

#for i in range (0,len(Y)):
#    Y[i][1]  = Y[i][1] / 10000
#plt.scatter([i[0] for i in X], [i[1] for i in X],label='non-duplicated',color='blue', s=1)
#plt.scatter([i[0] for i in Y], [i[1] for i in Y],label='duplicated',color='orange', alpha=0.6, s=1)

plt.plot([i[0] for i in X], [i[1] for i in X],label='non-duplicated',color='blue')
plt.plot([i[0] for i in Y], [i[1] for i in Y],label='duplicated',color='orange', alpha=0.6)

#plt.bar([i[0] for i in X], [i[1] for i in X],label='non-duplicated',color='blue')
#plt.bar([i[0] for i in Y], [i[1] for i in Y],label='duplicated',color='orange', alpha=0.5)

#plt.hist([i[1] for i in X], bins=30, label='non-duplicated', color='blue')
#plt.hist([i[1] for i in Y], bins=30, label='duplicated', color='orange', alpha=0.7)

plt.xlabel("Time Steps")
plt.ylabel("S")
plt.legend()
plt.savefig('./diagrams/survivebility.png',dpi=400)
plt.close()

plt.plot([i[0] for i in Z], [i[1] for i in Z],color='black', lw=0.2)
plt.xlabel("Time steps")
plt.ylabel("Input value")
plt.savefig('./diagrams/env.png',dpi=400)
plt.close()