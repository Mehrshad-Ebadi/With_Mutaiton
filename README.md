# With_Mutation

This package is a continuation of the [SC-as-aGRNs](https://github.com/Mehrshad-Ebadi/SC-as-aGRNs) project.  
It builds on the same principles to generate **artificial gene regulatory networks (aGRNs)** and then duplicates them to model **whole genome duplication (WGD)**.  

After duplication, the package creates four different environments and places the aGRNs in them to measure various **local- and global-scale properties** of these networks.  

The key differences from the previous package are:  
- **Mutation mechanism:** Each node can add or remove a downstream connection, or change the weight of an existing connection.  
- **Self-regulation & feedback loops:** This package introduces a new method to model these, which was not possible in the previous version.  
---

## Requirements
1. `make` (Makefile)  
2. C/C++ compiler (version 11 or higher recommended)  
3. At least **8 GB of RAM** for a network of 100 nodes  

⚠️ **For MPI version:**  
- `openmpi` is required.  
- The MPI code is written for **13 processes**.  
- If you want to run the code with a different number of processes, you must either modify the code or run it on a system with at least 13 processors.  

---

## Running the Code
On **Linux**:  
1. Navigate to the project directory.  
2. Compile the code by running:  

   ```bash
   make
   ```  

3. After compilation, the executable will be saved at:  

   ```
   ./../(all versions)/Exe/Final.out
   ```

---

## Workflow

1. **Generate networks**
   - If you already have networks, skip this step.  
   - Otherwise, use the [previous package](https://github.com/Mehrshad-Ebadi/SC-as-aGRNs) to generate them.

2. **Configure parameters**  
   Edit `./input/data.txt` and set:
   - **Network size**  
   - **Number of time steps**  
   - **Number of networks** in the pool  
   - **Environment scenario:**  
     - `1` → Gaussian input (Concentrated fluctuating environment)  
     - `2` → Uniform input (Strongly fluctuating environment)  
     - `3` → Linear input (Gradually changing environment)  
     - `4` → Single input (Stable environment)  
   - **Mutation rate**  
   - **Starting input value** (for environment calculations)  
   - **Final input value** (for environment calculations)  
   - **Number of runs**, depending on your needs and available CPU cores  

3. **Compile the code**

   ```bash
   make
   ```

4. **Run the executable**

   ```bash
   ./Exe/Final.out
   ```
