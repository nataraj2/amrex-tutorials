# AMReX Tutorial: Single Vortex Example

## Installation and Setup

1. **Install AMReX**  
   Follow the instructions from the [AMReX repository](https://github.com/AMReX-Codes/amrex) to install AMReX.

2. **Navigate to Tutorials Directory**  
   `cd amrex/Tutorials`

3. **Clone the Example Repository**  
   `git clone https://github.com/nataraj2/amrex-tutorials.git`

4. **Checkout the branch**
	```
    cd amrex-tutorials
    git checkout advection_fortan_restart
	```

4. **Change Directory to the Example Code**  
   `cd ExampleCodes/FortranInterface/Advection_F/Exec/SingleVortex`

## Compilation and Execution

- Compile and run the example code.

The code uses the routines `Restart.cpp`, `restart_mod.F90`, and `Restart.H` located in the `Source` directory.

### Restart Options

Here are the restart options found in the `inputs` file:
```
amr.check_file = chk      # root name of checkpoint file  
amr.check_int  = 5        # number of timesteps between checkpoint files  
#amr.restart = chk00100    # specify checkpoint file for restart
```
- `amr.check_int` specifies the frequency of writing checkpoint. `amr.restart` specifies the restart file for doing a restart. 
Once the initial run is complete, you can uncomment the `amr.restart` option and run again.

