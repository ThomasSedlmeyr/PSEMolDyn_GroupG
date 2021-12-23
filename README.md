# Group G #
Members:
* Thomas Sedlmeyr
* Philip Haitzer
* Daniel Braun

# Code #
* Link:     https://github.com/ThomasSedlmeyr/PSEMolDyn_GroupG
* Branch:   main
* Revision: 8e1fe85d301e094e0bd5321c52849098d78c1001
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
    * g_grav : gravitational force (0 if not used)
    * useGravity : yes or no
    * calcType : G for Gravitation Simulation, LJ for LennardJones Simulation
    * baseNameOutputFiles : specifies the output name
    * particlesContainerType : directSum or linkedCell
    * cutoffRadius : corresponding calculated cuttoff radius for linked cells algorithm
    * gravInput : path to input file for Gravitation Simulation, can otherwise be left blank
    * loadCheckpoint : yes or no
    * makeCheckpoint : yes or no
    * pathInCheckpoint : path for input checkpoint file
    * pathOutCheckpoint : path for file to write output checkpoints
    * domainSizeX, domainSizeY, domainSizeZ : domain size of corresponding coordinates
    * useThermostat : yes or no
    * useBrownianMotion : yes or no (for initialisation with brownian motion)
    * T_init : initial temperature
    * T_target : target temperature
    * delta_T : max temperature difference in one scaling step
    * n_thermostat : time steps after which thermostat is applied periodically
  *boundaryConditions:
    * top, right, bottom, left, front, back : outflowType, reflectingType, betterReflectingType or periodicType
  * particles : specify as many bodies as needed here
    * body : 
      * bodyType : Cuboid, Sphere or Tetrahedron
      * position : initial position
      * velocity : initial velocity
      * objectSpecificFormat : 
        * for Cuboid : particles per dimension, e.g. "8,8,1"
        * for Tetrahedron : numberParticles per edge, e.g. "15"
        * for Sphere : radius, e.g. "10"
      * epsilon : value for epsilon
      * mass : value for mass
      * rho : value for rho
      * h : mesh width of grid

* optional : when performing a 
  * Gravitation Simulation : other tags in generalParams and boundaryConditions can all be put to 0, particlesLJ can be left empty
  * LennardJones Simulation - direct Sum : cutoffRadius can be put to zero

## Run with predefined xml-files ##
### Run of Gravitation Simulation ###
* compile with all options
* run ./MolSim -input ../src/XMLinputFiles/Gravitation.xml
* alternatively you can change the default xml file
  * switch calcType to G
  * set gravInput to the input file path ../eingabe-sonne.txt
    * for additional planets specify the path ../eingabe-sonnen_system.txt

### Run of 'Simulation of a falling drop - Wall' ###
* compile with all options
* run ./MolSim -input ./src/XMLinputFiles/FallingRaindrop_2D.xml
* for 3D Simulation, change boolean is2D in Sphere.cpp to false, change dimension of Brownian Motion initialization 
to 3 in LennardJonesSimulation.cpp and use FallingRaindrop_3D.xml as input

### Run of 'Collision of two bodies' ###
* compile with all options
* run ./MolSim -input ./src/XMLinputFiles/CollisionOfTwoBodies.xml

## Crating a doxygen ##
* compile with BUILD_DOXYGEN=ON
* run make doc_doxygen

## Execute Tests ##
* compile with all options
* run make or make Tests
* run ctest in build directory

# Media #
## Diagram ##
* ![Performance Comparison](PerformanceComparison.png)
## Videos ##
* [Collision of two bodies] (https://youtu.be/t2qEI6jBcac)
* [Simulation of a falling drop 2D] (https://youtu.be/4SnxIbpA4Ls)
* [Simulation of a falling drop 3D] (https://youtu.be/SpSl7pDTNRo)