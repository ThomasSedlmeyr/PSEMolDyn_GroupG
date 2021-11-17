# Group G #
Members:
* Thomas Sedlmeyr
* Philip Haitzer
* Daniel Braun

# Code #
* Link:     https://github.com/ThomasSedlmeyr/PSEMolDyn_GroupG
* Branch:   main
* Revision: 9dc027e71be040175c7c6a8e0fec8294a1ab9212
* Compiler: g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 11.1

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
    * -param_path : file for parameters epsilon, mass, rho, mesh width (h)
    * -particles_path : file for parameters of bodies (position, velocity, number of particles per dimension)
  * for Gravitation Simulation:
    * -input : input file (coordinates, velocity, mass)

* example runs:
  * ./MolSim -calcType 2 -param_path ../ParamsLennardJonesSimulation.txt -particles_path ../TwoCuboidsLJ.txt -t_end 5 -delta_t 0.0002
  * ./MolSim -calcType 1 -input ../eingabe-sonne.txt -t_end 1000 -delta_t 0.014

## Crating a doxygen ##
* compile with BUILD_DOXYGEN=ON
* run make doc_doxygen

## Run with test ##
* change variable runTest in MolSim.cpp to true
* TODO

# Media #
## Videos ##
* https://www.youtube.com/watch?v=hQs3Ax64O4M
* https://youtu.be/b3tPPH1S0P8
* https://youtu.be/J2yViHKYwHM
* TODO