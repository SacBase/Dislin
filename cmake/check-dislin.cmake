INCLUDE (CheckIncludeFiles)
INCLUDE (CheckLibraryExists)

FIND_LIBRARY (DISLIN_LIB      "dislin")
IF (DISLIN_LIB)
    GET_FILENAME_COMPONENT (DISLIN_PATH  ${DISLIN_LIB} PATH)
    CHECK_LIBRARY_EXISTS (${DISLIN_LIB} "disini" ${DISLIN_PATH} DISLIN_FOUND)
    CHECK_INCLUDE_FILES ("dislin.h" HAVE_DISLIN_H)
ENDIF ()

IF (NOT DISLIN_LIB OR NOT DISLIN_FOUND OR NOT HAVE_DISLIN_H)
    MESSAGE (FATAL_ERROR
             "The dislin library is either not found or is not operational"
             "on the given system")
ENDIF ()
