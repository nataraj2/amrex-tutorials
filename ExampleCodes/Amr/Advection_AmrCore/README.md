# Zalesak Disk Advection with AMReX

This repository provides an example of the **Zalesak disk test case** using the **AMReX framework** for advection simulations.


To install ASCENT

```sh
git clone https://github.com/spack/spack.git 
. spack/share/spack/setup-env.sh
spack install ascent
spack load ascent
spack load conduit
```
Add in ~/.bashrc
```sh
export PATH=$(spack location -i ascent)/bin:$PATH
export LD_LIBRARY_PATH=$(spack location -i ascent)/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$(spack location -i conduit)/lib:$LD_LIBRARY_PATH
```
```sh
source ~/.bashrc
```


```sh
git clone --recursive https://github.com/AMReX-Codes/amrex.git
cd amrex/Tutorials
git clone --recursive https://github.com/nataraj2/amrex-tutorials.git
cd amrex-tutorials/
git checkout zalesak_disk
cd ExampleCodes/Amr/Advection_AmrCore/Exec
make -j8
mpirun -np 4 main3d.gnu.MPI.ex inputs
```
<img src="Images/Zalesak_0level.gif?raw=true&v=100" alt="Zalesak 0 Level" width="50%" height="50%" loop="true" autoplay="true"><img src="Images/Zalesak_2level.gif?raw=true&v=100" alt="Zalesak 2 Level" width="50%" height="50%" loop="true" autoplay="true">


