# make doc_doxygen optional if someone does not have / like doxygen
find_package(Doxygen)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
set(DOXYGEN_OUTPUT_DIRECTORY ../doxys_documentation)
doxygen_add_docs(doc_doxygen src README.md)