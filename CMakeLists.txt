cmake_minimum_required(VERSION 3.15)

include(CMakePackageConfigHelpers)


set(TARGET cmakeRelPkg)

project(${TARGET} CXX)

add_library(${TARGET}
    src/cmake-rel-pkg.cpp
    include/cmake-rel-pkg.h)


# Cause the configuration to appear as part of the filename
set_target_properties(${TARGET}
    PROPERTIES DEBUG_POSTFIX "${ARG_OPT_PREFIX}D")
set_target_properties(${TARGET}
    PROPERTIES RELEASE_POSTFIX "${ARG_OPT_PREFIX}R")
set_target_properties(${TARGET}
    PROPERTIES RELWITHDEBINFO_POSTFIX "${ARG_OPT_PREFIX}RD")



# using target_include_directories so include paths work correctly for local
# and relocated builds.
target_include_directories(${TARGET}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )


set(TARGET_EXPORT  ${TARGET}_Targets)


# Generate the package configuration file. Notice I just used 'cmake' folder
# instead of 'cmake/<pkg-name>' folder. Also setting variables to be used in
# the configuration.
set(MY_PKG_BASE ${TARGET})
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}Config.cmake"
    INSTALL_DESTINATION cmake
    )

# install the config file
install(FILES "${PROJECT_BINARY_DIR}/${TARGET}Config.cmake" DESTINATION cmake)



# install the target and create export-set
install(TARGETS ${TARGET}
        EXPORT ${TARGET_EXPORT}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


# Create the ***Targets.cmake file for find_package()
#   ***Targets.cmake is used in the .in file from
#   configure_package_config_file() step and install them to cmake
install(EXPORT ${TARGET_EXPORT}
    FILE "${TARGET}Targets.cmake"
    DESTINATION cmake)


# install the header files
install(FILES include/cmake-rel-pkg.h DESTINATION include)


install(TARGETS ${TARGET})
