Efficient Group-Based Hilbert Coding and Decoding Algorithms

The repository contains two folders: 2D and 3D.
The 2D folder contains four files: CHM_8.bin, CSM_8.bin, HCM_8.bin, and HSM_8.bin, which correspond to the four computed 8-order state views, i.e., CHM, CSM, HCM, and HSM, respectively.
The 3D folder contains four files: CHM_4.bin, CSM_4.bin, HCM_4.bin, and HSM_4.bin, which correspond to the four computed 4-order state views, i.e., CHM, CSM, HCM, and HSM, respectively.

Meanwhile Group_K.cpp provides the generation of the K-order state-views CHM_k, CSM_k, HCM_k, and HSM_k, and the order K can be modified by yourself. It can be opened and executed separately through Group_K.cpp.

As an example for 2D: (the corresponding generation steps for 3D are the same).
The steps to open and execute FVFG.cpp are as follows:
1, First create a new project; 
2. Add the FVFG.cpp file to that project; 
3. Open the local folder where the FVFG.cpp file is stored; 
4. Copy the four files CHM_8.bin, CSM_8.bin, HCM_8.bin and HSM_8.bin to the local folder where the FVFG.cpp file is stored; 
5、Execute the FVFG.cpp file in the compiler, such as visual studio 2022, Visual Studio Code, and so on;

In the main function, we first load four 8th order state views from four files (same for 3D) and then call the following four algorithms respectively:
en_FVFG:  the virtual-filling based group encoding algorithm
de_FVFG:  the virtual-filling based group decoding algorithm

Note that do not change the group size parameter g in the main function unless you have already generated a state view for the specific g.
