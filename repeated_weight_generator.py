import numpy as np
import matplotlib.pyplot as plt
import os as os
import shutil as sh

sh.rmtree('./diagrams')
os.mkdir("./diagrams")
for p in range (0,500):
    savving_address = "./diagrams/topology_"
    I = str(p)
    extension = ".txt"
    imgage_extension = ".png"
    address = "./Outputs/output_"
    du_address = "./Outputs/du_Output_"
    address = address + I + extension
    du_address = du_address + I + extension
    File = np.loadtxt(address)
    
    for i in range (0, File.size):
        File[i] = round(File[i], 5)
    du_File = np.loadtxt(du_address)
    
    for i in range (0, du_File.size):
        du_File[i] = round(du_File[i], 5)
    #print (File, du_File)
    original = np.unique(File)
    du_original = np.unique(du_File)
    Count = np.zeros(original.size)
    du_Count = np.zeros(du_original.size)
    #print ("done!")
    
    for i in range(0, original.size):
        Count[i] = np.count_nonzero(File == original[i])
        #print (Count[i], original[i])
    #print ("done!")    
    for j in range(0, du_original.size):
        du_Count[j] = np.count_nonzero(du_File == du_original[j])
        #print (du_Count[j], du_original[j])
        
        
       
    savving_address = savving_address + I + imgage_extension
    #print ("it is finished!!")
    #plt.legend("Non-Duplicated")
    #plt.scatter(original, Count, label='non-Duplicated')
    #plt.scatter(du_original, du_Count,label='Duplicated',alpha=0.6)
    plt.plot(original, Count, label='non-Duplicated')
    plt.plot(du_original, du_Count,label='Duplicated',alpha=0.6)
    #plt.scatter(original, Count, label='non-Duplicated', s=0.5)
    #plt.scatter(du_original, du_Count,label='Duplicated', s=1)
    plt.legend() 
    #plt.ylim(0, 200)
    plt.xlabel("The Output Weight")
    plt.ylabel("Number of Times the Weight is Repeated")
    plt.savefig(savving_address,dpi=400)
    plt.close('all')
    print (savving_address)
    
        
        
    
        
