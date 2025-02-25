# Zalesak Disk Advection with AMReX

This repository provides an example of the **Zalesak disk test case** using the **AMReX framework** for advection simulations.

```sh
git clone --recursive https://github.com/AMReX-Codes/amrex.git
cd amrex/Tutorials
git clone --recursive https://github.com/nataraj2/amrex-tutorials.git
cd amrex-tutorials/
git checkout zalesak_disk
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
