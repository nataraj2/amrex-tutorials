# Zalesak Disk Advection with AMReX

This repository provides an example of the **Zalesak disk test case** using the **AMReX framework** for advection simulations.

Ensure you have the following installed on your system:  
- A C++ compiler supporting C++14 or newer (e.g., GCC, Clang, or Intel)  
- MPI (e.g., OpenMPI or MPICH)  
- GNU Make  
- CMake (if needed for dependencies)  
- Git  

Clone the main **AMReX** repository and its submodules:  

```sh
git clone --recursive https://github.com/AMReX-Codes/amrex.git
```

Navigate to the tutorials directory:  

```sh
cd amrex/Tutorials
```

Clone the custom tutorial repository:  

```sh
git clone --recursive https://github.com/nataraj2/amrex-tutorials.git
```

Switch to the correct branch:  

```sh
cd amrex-tutorials/
git checkout zalesak_disk
```

Navigate to the appropriate example directory and compile the code:  

```sh
cd ExampleCodes/Amr/Advection_AmrCore/Exec
make -j8
```

Run the simulation using **MPI** with 4 processes:  

```sh
mpirun -np 4 main3d.gnu.MPI.ex inputs
```

The `inputs` file contains runtime parameters for the simulation. Adjust `-np 4` based on the available CPU cores for optimal performance. Modify the `make` command based on your system's compiler setup if needed.

## References

- [AMReX Documentation](https://amrex-codes.github.io/)  
- [AMReX GitHub Repository](https://github.com/AMReX-Codes/amrex)  
