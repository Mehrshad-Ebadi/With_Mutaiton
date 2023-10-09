import numpy as np
import matplotlib.pyplot as plt
import os as os
import shutil as sh

sh.rmtree('./diagrams')
os.mkdir("./diagrams")
X = np.loadtxt("./Outputs/Alive.txt")
#Y = np.loadtxt("./Outputs/du_Alive.txt")

#for i in range (0,len(X)):
#    X[i][1] = X[i][1] / 10000

#for i in range (0,len(Y)):
#    Y[i][1]  = Y[i][1] / 10000
plt.scatter([i[0] for i in X], [i[1] for i in X],label='non-duplicated',color='blue')
#plt.scatter([i[0] for i in Y], [i[1] for i in Y],label='duplicated',color='orange', alpha=0.6)
plt.xlabel("Input value (Environment changes)")
plt.ylabel("S")
plt.legend()
plt.savefig('./diagrams/survivebility.png',dpi=400)
plt.close()