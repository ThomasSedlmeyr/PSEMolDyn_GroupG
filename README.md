# Group G #
Members:
* Thomas Sedlmeyr
* Philip Haitzer
* Daniel Braun

# Code #
* Link:     https://github.com/ThomasSedlmeyr/PSEMolDyn_GroupG
* Branch:   main
* Revision: e9486507bbc6a6669ce3457c33672ab95d6e7576

# Run Instructions #
## Standard Run ##
* compile with all options
* run ./MolSim eingabe-sonne.txt

## Run with passing optional command line arguments ##
* compile with all options
* pass desired values for t_end and delta_t
* example run: ./MolSim eingabe-sonne.txt -t_end 1000 -delta_t 0.014
* for additional planets use eingabe-sonnen_system.txt

## Crating a doxygen ##
* compile with BUILD_DOXYGEN=ON
* run make doc_doxygen

## Run with test ##
* change variable runTest to true

# Media #
## Videos ##
* https://www.youtube.com/watch?v=hQs3Ax64O4M
* https://www.youtube.com/watch?v=JlyPV9d5dWk
* https://youtu.be/J2yViHKYwHM