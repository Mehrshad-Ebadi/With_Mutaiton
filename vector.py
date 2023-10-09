from turtle import color
import numpy as np
import matplotlib.pyplot as plt
import os as os
import shutil as sh
import seaborn as sns

sh.rmtree('./VECTOR_SPACE')
os.mkdir('./VECTOR_SPACE')
address = './angles/'
File = 'phase_'
du = 'du_'
prop = dict(arrowstyle="-|>,head_width=0.4,head_length=0.8",shrinkA=0,shrinkB=0)
for i in range (0,1000):
    boz = address + File + str(i) + '.txt'
    du_boz = address + du + File + str(i) + '.txt'
    data1x = list()
    du_data1x = list()
    data1y = list()
    du_data1y = list()
    data = np.loadtxt(boz)
    du_data = np.loadtxt(du_boz) 
    h = round(np.var(data),2)
    hh = round(np.var(du_data),2)    
    saving_address = './VECTOR_SPACE/'
    for g in range (0,len(data)):
        data1x.append(data[g][0])
        data1y.append(data[g][1])
    
    for  g in range (0,len(du_data)):
        du_data1x.append(du_data[g][0])
        du_data1y.append(du_data[g][1])
    
    txt = 'Non-Duplictaed,' + ' var=' + str(h)
    du_txt = 'Duplicated,' + ' var=' + str(hh)
    #for Joze in range (0, len(data1x)):
        #plt.arrow(data1x[Joze], data1y[Joze], (du_data1x[Joze] - data1x[Joze]), (du_data1y[Joze] - data1y[Joze]), color='red', head_width=0.05)
    plt.scatter(data1x, data1y, color='Blue')
    plt.scatter(du_data1x, du_data1y, color='orange')
    #plt.legend() 
    plt.xlabel("Activation value of Gene 1")
    plt.ylabel("Activation value of Gene 2")
    saving_address = saving_address + File + str(i) + '.png'
    plt.savefig(saving_address,dpi=400)
    plt.close('all')
    