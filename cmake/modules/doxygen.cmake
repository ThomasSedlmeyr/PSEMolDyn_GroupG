# make doc_doxygen optional if someone does not have / like doxygen
option(BUILD_DOXYGEN "Build Doxygen(Default=ON)" ON)
if (BUILD_DOXYGEN)
    find_package(Doxygen)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    set(DOXYGEN_OUTPUT_DIRECTORY ../doxys_documentation)

    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_CLASS_DIAGRAMS YES)
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_CLASS_GRAPH YES)
    set(DOXYGEN_COLLABORATION_GRAPH YES)
    set(DOXYGEN_UML_LOOK YES)
    set(DOXYGEN_TEMPLATE_RELATIONS YES)
    set(DOXYGEN_DOT_TRANSPARENT YES)
    #README.md has to be in INPUT files for USE_MD_FILE_AS_MAINPAGE to work
    doxygen_add_docs(doc_doxygen src README.md)
endif (BUILD_DOXYGEN)