CMAKE_MINIMUM_REQUIRED (VERSION 3.3)
INCLUDE ("${CMAKE_SOURCE_DIR}/cmake-common/sac2c-variables.cmake")
INCLUDE ("${CMAKE_SOURCE_DIR}/cmake-common/resolve-sac2c-dependencies.cmake")

# C files relatively to thes CMakeLists.txt.
SET (C_DEPS_SRC
    dislin/src/page.c
    dislin/src/header.c
)

# SaC files relatively to this CMakeLists.txt.
SET (SAC_SRC
    dislin/DislinSystem.sac
    dislin/DislinQuick.sac
    dislin/DislinPlot3d.sac
    dislin/DislinPage.sac
    dislin/DislinCanvas.sac
    dislin/DislinBars.sac
    Dislin.sac
)

# TODO(artem) We may want to introduce a mechanism of generating depenencies
#             on a given sac2c versoin.  That is, recompiler all modules if
#             sac2c version changes.


# For every C source, compile an object file maintaining the right location
# in the binary dir so that sac files can pick it up.
# XXX do we ever pass some extra flags, etc to C files?
FOREACH(name ${C_DEPS_SRC})
  SET (src "${CMAKE_CURRENT_SOURCE_DIR}/${name}")
  
  GET_FILENAME_COMPONENT (dir ${name} DIRECTORY)
  
  GET_FILENAME_COMPONENT (dst ${name} NAME_WE)
  SET (dst "${CMAKE_CURRENT_BINARY_DIR}/${dir}/${dst}${OBJEXT}")
  
  MESSAGE ("generating target for `${name}'"
           "dir=`${dir}', dst=`${dst}'")
  
  # Make sure that we put the object file in the same location where
  # the source file was.
  FILE (MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${dir}")

  ADD_CUSTOM_COMMAND (
    OUTPUT "${dst}"
    MAIN_DEPENDENCY "${src}"
    IMPLICIT_DEPENDS C "${src}"
    COMMAND ${SAC2C} -v0 -noprelude -cc ccmod -o "${dst}" "${src}"
    COMMENT "Generating ${dst}"
  )
ENDFOREACH(name)

# Make a directory for sac2c output
FILE (MAKE_DIRECTORY "${DLL_BUILD_DIR}/${TARGET_ENV}/${SBI}")

# For every sac file, compile Tree and Mod files.
FOREACH (name ${SAC_SRC})
    SET (src "${CMAKE_CURRENT_SOURCE_DIR}/${name}")
    # sac2c requires computes objectfiles relatively to the working directory
    # of the call to sac2c.
    GET_FILENAME_COMPONENT (dir "${CMAKE_CURRENT_BINARY_DIR}/${name}" DIRECTORY)
    GET_FILENAME_COMPONENT (dst ${name} NAME_WE)
    SET (mod
        "${DLL_BUILD_DIR}/${TARGET_ENV}/${SBI}/lib${dst}Mod${MODEXT}")
    SET (tree
        "${DLL_BUILD_DIR}/tree/${TARGET_ENV}/lib${dst}Tree${TREE_DLLEXT}")

    RESOLVE_SAC_DEPENDENCIES ("${name}" "${SAC_SRC}" moddep_list)

    MESSAGE ("dependencies of ${name} => `${moddep_list}'")

    ADD_CUSTOM_COMMAND (
        OUTPUT ${mod} ${tree}
        COMMAND
            ${SAC2C} -v0 -linksetsize ${LINKSETSIZE} -o ${DLL_BUILD_DIR} ${src}
        WORKING_DIRECTORY
            ${dir}
        DEPENDS ${moddep_list}
        COMMENT "Building ${name} module for target `${TARGET}'")

    # Install compiled Tree/Mod parts of the compiled module
    # to the corresponding locations.
    INSTALL (
        FILES ${mod}
        DESTINATION ${INSTALL_MOD_DIR}/${TARGET_ENV}/${SBI})
    INSTALL (
        FILES ${tree}
        DESTINATION ${INSTALL_TREE_DIR}/tree/${TARGET_ENV})

    # Make a call to the command that compiles the module a part
    # of the default build process.
    ADD_CUSTOM_TARGET (${TARGET}-module-${dst} ALL DEPENDS ${mod} ${tree})
ENDFOREACH (name)

