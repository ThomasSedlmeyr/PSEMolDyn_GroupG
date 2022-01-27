# Group G #
Members:
* Thomas Sedlmeyr
* Philip Haitzer
* Daniel Braun

# Code #
* Link:     https://github.com/ThomasSedlmeyr/PSEMolDyn_GroupG
* Branch:   main
* Revision: c2513be44ddf32fcfa142493d3ee3caa400a2fac
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
    * particlesContainerType : directSum or linkedCell
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

* optional : when performing a 
  * Gravitation Simulation : other tags in generalParams and boundaryConditions can all be put to 0, particlesLJ can be left empty
  * LennardJones Simulation - direct Sum : cutoffRadius can be put to zero

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
* run on f the following
  * run ./MolSim -input ../XMLinputFiles/RayleighTaylor_3D.xml
  * run ./MolSim -input ../XMLinputFiles/RayleighTaylor_large.xml
  * run ./MolSim -input ../XMLinputFiles/RayleighTaylor_small.xml

### Run of 'Simulation of a membrane' ###
* compile with all options
* run ./MolSim -input ../XMLinputFiles/Membrane.xml

### Run of 'Nano-scale flow simulation' ###
* compile with all options
* run ./MolSim -input ../XMLinputFiles/NanoScaleFlow.xml

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
* [Simulation of a falling drop - Wall 2D] (https://youtu.be/4SnxIbpA4Ls)
* [Simulation of a falling drop - Wall 3D] (https://youtu.be/SpSl7pDTNRo)
* [Simulation of the Rayleigh-Taylor instability] (https://youtu.be/Xhbvmt33hQg)
* [Simulation of a falling drop - Liquid] (https://youtu.be/zm5DIcyTuBw)