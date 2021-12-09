# Group G #
Members:
* Thomas Sedlmeyr
* Philip Haitzer
* Daniel Braun

# Code #
* Link:     https://github.com/ThomasSedlmeyr/PSEMolDyn_GroupG
* Branch:   main
* Revision: 8cef2511fe24bbe21c3527f73ab7fcbabdaff2b6
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
  * t_end : specifies end time of simulation
  * delta_t : specifies stepsize for calculation
  * calcType : G for Gravitation Simulation, LJ for LennardJones Simulation
  * baseNameOutputFiles : specifies the output name
  * writeFrequency : specifies the write frequency
  * gravInput : path to input file for Gravitation Simulation, can otherwise be left blank
  * paramsLJ : 
    * epsilon, mass, rho, h : double value for the corresponding parameter
    * domainSizeX, domainSizeY, domainSizeZ : domain size of corresponding coordinates
    * particlesContainerType : 1 for direct sum, 2 for linked cells
    * cutoffRadius : corresponding cuttoff radius for linked cells algorithm
  * boundaryConditions :
    * top, right, bottom, left, front, back : for either one pick 1 for outflow, 2 for reflection, 3 for reflection with improved implementation
  * particles : specify as many bodies as needed here
    * body : 
      * bodyType : Cuboid, Sphere or Tetrahedron
      * position : initial position
      * velocity : initial velocity
      * objectSpecificFormat : 
        * for Cuboid : particles per dimension, e.g. "8,8,1"
        * for Tetrahedron : numberParticles per edge, e.g. "15"
        * for Sphere : radius, e.g. "10"

* optional : when performing a 
  * Gravitation Simulation : tags in paramsLJ and boundaryConditions can all be put to 0, particlesLJ can be left empty
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