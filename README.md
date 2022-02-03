# Group G #
Members:
* Thomas Sedlmeyr
* Philip Haitzer
* Daniel Braun

# Code #
* Link:     https://github.com/ThomasSedlmeyr/PSEMolDyn_GroupG
* Branch:   main
* Revision: 617c6bcb77f630c0d060157fa8a12b98d296dfcb
* Compiler: g++ 11.1.0

# Run Instructions #
## Standard Run of default input file ##
* compile with all options
* run ./MolSim
* see in the following section on how to change the xml-file to your liking

## Run with own xml file ##
* compile with all options
* run with the input flag
  * -h : help page
  * -input : provides path to xml input file

* example runs:
  * ./MolSim -input ../src/XML_Parser/input.xml

* xml-file must be formatted correctly according to schema
* you can use and change the default file in ../src/XML_Parser/input.xml
  * generalParams :
    * t_end : specifies end time of simulation
    * delta_t : specifies stepsize for calculation
    * writeFrequency : specifies the write frequency
    * dimensionType : 2D or 3D as Type for simulation
    * parallelType : you can choose from two parallel types (first, second, notParallel)
    * g_grav : gravitational force (0 if not used)
    * useGravity : yes or no
    * gravDirection : direction of gravitational force
    * calcType : G for Gravitation Simulation, LJ for LennardJones Simulation
    * baseNameOutputFiles : specifies the output name
    * cutoffRadius : corresponding calculated cuttoff radius for linked cells algorithm
    * gravInput : path to input file for Gravitation Simulation, can otherwise be left blank
    * loadCheckpoint : yes or no
    * makeCheckpoint : yes or no
    * pathInCheckpoint : path for input checkpoint file
    * pathOutCheckpoint : path for file to write output checkpoints
    * domainSizeX, domainSizeY, domainSizeZ : domain size of corresponding coordinates
    * thermostatType : different types of thermostats (regular, only fluid)
    * useThermostat : yes or no
    * useBrownianMotion : yes or no (for initialisation with brownian motion)
    * T_init : initial temperature
    * T_target : target temperature
    * delta_T : max temperature difference in one scaling step
    * n_thermostat : time steps after which thermostat is applied periodically
    * useVelDensProfiling : create CSV file every 1000 iterations about density and velocity downwards (not possible to be used with Gravitation simulation)
    * numberOfBins : number of bins that the domain is supposed to be grouped into (greater 0)
    * pathToAnalysisFolder : path to folder for analysis files
    * crystallization_r_c : only to be set for crystallization
    * crystallization_r_l : only to be set for crystallization
  *boundaryConditions:
    * top, right, bottom, left, front, back : outflowType, reflectingType, betterReflectingType or periodicType
  * particles : specify as many bodies as needed here
    * body : 
      * bodyType : Cuboid, Sphere, Tetrahedron, Membrane
      * position : initial position
      * velocity : initial velocity
      * objectSpecificFormat : 
        * for Cuboid : particles per dimension, e.g. "8,8,1"
        * for Tetrahedron : numberParticles per edge, e.g. "15"
        * for Sphere : radius, e.g. "10"
        * for Membrane : e.g. "n_50,50,1 r_2.2 k_300 f_0.8 p_(17,24),(17,25),(18,24),(18,25) t_150"
          * obligatory : n, r, k
          * optional : f, p, t (when there is no lifting, all must be omitted then)
          * n : number of particles per dimension
          * r : average bond length of molecule pair (double)
          * k : stiffness constant (double)
          * f : force lifting membrane (double)
          * p : points to be lifted (coordinates, see example)
          * t : time for lifting to last for (int)
      * epsilon : value for epsilon
      * mass : value for mass
      * rho : value for rho
      * h : mesh width of grid
      * bodyState : moving, fixed (membrane must be moving)

* optional : when performing a Gravitation Simulation 
  * other tags in generalParams and boundaryConditions can all be put to 0, particlesLJ can be left empty

## Run with predefined xml-files ##
### Run of Gravitation Simulation ###
* compile with all options
* run ./MolSim -input ../XMLinputFiles/Gravitation.xml
* alternatively you can change the default xml file
  * switch calcType to G
  * set gravInput to the input file path ../eingabe-sonne.txt
    * for additional planets specify the path ../eingabe-sonnen_system.txt

### Run of 'Simulation of a falling drop - Wall' ###
* compile with all options
* 2D Mode: run ./MolSim -input ../XMLinputFiles/FallingRaindropWall_2D.xml
* 3D Mode: run ./MolSim -input ../XMLinputFiles/FallingRaindropWall_3D.xml

### Run of 'Collision of two bodies' ###
* compile with all options
* run ./MolSim -input ../XMLinputFiles/CollisionOfTwoBodies.xml
 
### Run of 'Simulation of the Rayleigh-Taylor instability' ###
* compile with all options
* run ./MolSim -input ../XMLinputFiles/RayleighTaylor_(small|large).xml

### Run of 'Simulation of a falling drop - Liquid Part 1' ###
* compile with all options
* run ./MolSim -input ../XMLinputFiles/FallingDropLiquid_makeCheckpoint.xml
* creates Checkpoint which can be used for Part 2
 
### Run of 'Simulation of a falling drop - Liquid Part 2' ###
* compile with all options
* run ./MolSim -input ../XMLinputFiles/FallingDropLiquid_loadCheckpoint.xml

### Run of 'Simulation of the Rayleigh-Taylor instability' ###
* compile with all options
* run on of the following
  * run ./MolSim -input ../XMLinputFiles/RayleighTaylor_3D.xml
  * run ./MolSim -input ../XMLinputFiles/RayleighTaylor_large.xml
  * run ./MolSim -input ../XMLinputFiles/RayleighTaylor_small.xml

### Run of 'Simulation of a membrane' ###
* compile with all options
* run ./MolSim -input ../XMLinputFiles/Membrane.xml

### Run of 'Nano-scale flow simulation' ###
* compile with all options
* run ./MolSim -input ../XMLinputFiles/NanoScaleFlow.xml

### Run of 'Crystallization of Argon' ###
* compile with all options
* for equilibration
  * run ./MolSim -input ../XMLinputFiles/Crystallization_equilibrate.xml
* for cooling
  * run ./MolSim -input ../Crystallization_cooling.xml
  * run ./MolSim -input ../Crystallization_supercooling.xml

## Crating a doxygen ##
* compile with BUILD_DOXYGEN=ON
* run make doc_doxygen

## Execute Tests ##
* compile with all options
* run make or make Tests
* run ctest in build directory

# Media #
## Videos ##
* [Animation of the Membrane] (https://youtu.be/yGJPIwb_p5c)
* [Rayleigh Taylor 3D] (https://youtu.be/6lqAMLsCMuI)
* [Cooling Argon] (https://youtu.be/H75T12H-Yig)
* [Super Cooling Argon] (https://youtu.be/P0fYduY6CYk)
* [Extra Nano Flow Simulations] (https://youtu.be/lVIDD30yHl8)
                                (https://youtu.be/gRUX0L14Klg)
                                (https://youtu.be/BeIFKaWc6MI)
