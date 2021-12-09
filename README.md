# Group G #
Members:
* Thomas Sedlmeyr
* Philip Haitzer
* Daniel Braun

# Code #
* Link:     https://github.com/ThomasSedlmeyr/PSEMolDyn_GroupG
* Branch:   main
* Revision: 9014be933e5cd41f708aad6455a303f4ee5acd68 
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
  * baseNameOutputFiles : G for Gravitation Simulation, LJ for LennardJones Simulation, FallingDrop_2D for FallingRaindrop Simulation
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
        * for Sphere : radius

* optional : when performing a 
  * Gravitation Simulation : tags in paramsLJ and boundaryConditions can all be put to 0, particlesLJ can be left empty
  * LennardJones Simulation - direct Sum : cutoffRadius can be put to zero

## Run with predefined xml-files ##
### Run of Gravitation Simulation ###
* compile with all options
* run ./MolSim -input ../src/XMLinputFiles/Gravitation.xml
* alternatively you can change the default xml file
  * switch calcType to G
  * set baseNameOutputFiles to Grav
  * set gravInput to the input file path ../eingabe-sonne.txt
    * for additional planets specify the path ../eingabe-sonnen_system.txt

### Run of 'Simulation of a falling drop - Wall' ###
* compile with all options
* run ./MolSim -input ./src/XMLinputFiles/FallingRaindrop_2D.xml

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
## Videos ##
* TODO
