# Group G #
Members:
* Thomas Sedlmeyr
* Philip Haitzer
* Daniel Braun

# Code #
* Link:     https://github.com/ThomasSedlmeyr/PSEMolDyn_GroupG
* Branch:   main
* Revision: dcb6f77d73ee6cbb35cc188ac071bd0c2fc1c99e 
* Compiler: g++ 11.1.0

# Run Instructions #
## Standard Run of 'Collision of two bodies' ##
* compile with all options
* run ./MolSim
* Simulation will by default be executed with parameters from worksheet 2

## Run of Gravitation Simulation ##
* compile with all options
* run ./MolSim -calcType 1
* for additional planets use eingabe-sonnen_system.txt as input file

## Run with passing optional command line arguments ##
* compile with all options
* pass desired values, all have dafault values (see help page)
  * -h : help page
  * -t_end : end time of simulation
  * -delta_t : stepsize
  * -calcType : 2 for 'Collision of two bodies' (default), 1 for Gravitation Simulation
  * for Lennard Jones Simulation:
    * -param_path : file for parameters epsilon, mass, rho, mesh width (h), see ParamsLennardJonesSimulation.txt as example
    * -particles_path : file for parameters of bodies (position, velocity, number of particles per dimension), see TwoCuboidsLJ.txt as example
  * for Gravitation Simulation:
    * -input : input file (coordinates, velocity, mass)

* example runs:
  * ./MolSim -calcType 2 -param_path ../ParamsLennardJonesSimulation.txt -particles_path ../TwoCuboidsLJ.txt -t_end 5 -delta_t 0.0002
  * ./MolSim -calcType 1 -input ../eingabe-sonne.txt -t_end 1000 -delta_t 0.014

## Crating a doxygen ##
* compile with BUILD_DOXYGEN=ON
* run make doc_doxygen

## Execute Tests ##
* compile with all options
* run make or make Tests
* run ctest in build directory

# Media #
## Videos ##
* https://youtu.be/oYmyFnacXVY
* https://youtu.be/01wl6HPkouk
