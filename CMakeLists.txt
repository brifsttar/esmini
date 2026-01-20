message(
    STATUS "CMake version: "
           ${CMAKE_VERSION})

cmake_minimum_required(
    VERSION 3.10 # include_guard command was introduced
    # VERSION 3.11 for VS 2017 generator, 3.14 for VS 2019, 3.21 for VS 2022
    FATAL_ERROR)

# ############################# Project generate options ###########################################################

project(
    esmini
    DESCRIPTION "esmini"
    LANGUAGES C
              CXX)

set(ENABLE_COLORED_DIAGNOSTICS
    OFF
    CACHE BOOL
          "Enable colorful diagnostic messages from the compiler in console")

set(ENABLE_WARNINGS_AS_ERRORS
    OFF
    CACHE BOOL
          "Make compile warnings be treated as errors")

set(ENABLE_CCACHE
    OFF
    CACHE BOOL
          "Enable CCACHE")

set(ENABLE_COVERAGE
    OFF
    CACHE BOOL
          "Enable code coverage (Will force no optimizations)")

set(ENABLE_SANITIZERS
    OFF
    CACHE BOOL
          "Enable sanitizers (Only valid for Linux and Mac OS)")

# static code analysis not in works yet, need prep e.g. excluding external modules
set(ENABLE_STATIC_ANALYSIS
    OFF
    CACHE BOOL
          "Enable CppCheck and clang-tidy")

set(ENABLE_INCLUDE_WHAT_YOU_USE
    ON
    CACHE BOOL
          "Enable iwyu")

set(DOWNLOAD_EXTERNALS
    ON
    CACHE BOOL
          "Download external packages")

set(USE_OSG
    ON
    CACHE BOOL
          "If projects that depend on osg should be compiled.")

set(USE_OSI
    ON
    CACHE BOOL
          "If code that depend on osi should be compiled.")

set(USE_SUMO
    ON
    CACHE BOOL
          "If code that depend on sumo should be compiled.")

set(USE_GTEST
    ON
    CACHE BOOL
          "If unit test suites based on googletest should be compiled.")

set(DYN_PROTOBUF
    OFF
    CACHE BOOL
          "Set for dynamic linking of protobuf library (.so/.dll)")

set(USE_IMPLOT
    ON
    CACHE BOOL
          "If implot for real-time plotting should be compiled.")

set(BUILD_ODRPLOT
    ON
    CACHE BOOL
          "If odrplot should be compiled.")

set(BUILD_REPLAYER
    ON
    CACHE BOOL
          "If replayer should be compiled.")

set(BUILD_EXAMPLES
    ON
    CACHE BOOL
          "If examples should be compiled.")

set(ESMINI_BUILD_VERSION
    "N/A - client build"
    CACHE STRING
          "Esmini CI Build Version")

set(CMAKE_BUILD_TYPE
    "Release"
    CACHE STRING
          "build mode")
set(FMT_INSTALL
    OFF
    CACHE BOOL
          "If FMT should be installed")

# ############################### Setting project rules ############################################################

set_property(
    GLOBAL
    PROPERTY USE_FOLDERS
             ON)

include(support/cmake/rule/project_options.cmake)

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set (ANDROID TRUE)
    set (LINUX TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LINUX TRUE)
    set(ANDROID FALSE)
else()
    set(LINUX FALSE)
    set(ANDROID FALSE)
endif()

if(NOT
   (LINUX
    OR ANDROID
    OR APPLE
    OR MINGW
    OR MSVC))
    message(FATAL_ERROR "Unrecognized platform therefore there isn't an installation directory. Stopping the cmake process.")
endif()

# ############################### Loading common packages ############################################################

include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/common/color.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/common/locations.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/common/definitions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/common/flags.cmake)

set_project_internal_paths()
set_project_external_paths()
set_project_os_specific_paths()
set_project_includes()
set_project_library_paths()
set_definitions()
set_special_build_flags()

# ############################### Loading utils packages ##############################################################

include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/utils/get_subdirectories.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/utils/set_folder.cmake)

# ############################### Downloading cloud packages #########################################################

if(USE_OSG)
    include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/external/osg.cmake)
    set_osg_libs()
endif()

if(USE_OSI)
    include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/external/osi.cmake)
    set_osi_libs()
endif()

if(USE_SUMO)
    include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/external/sumo.cmake)
    set_sumo_libs()
endif()

if(USE_IMPLOT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/support/cmake/external/implot.cmake)
    set_implot_libs()
endif()

# ############################### Add submodules #####################################################################

set(YAML_LIBRARIES
    yaml)
set(FMT_LIBRARIES
    fmt)
set(CMAKE_POSITION_INDEPENDENT_CODE
    ON)
set(FMT_SHARED
    OFF)

if(LINUX AND NOT ANDROID)
    set(FMT_LIBRARIES
        ${FMT_LIBRARIES}
        "-lstdc++fs")
endif()

add_subdirectory(externals/fmt)
# target_compile_options( fmt PRIVATE -fPIC)
# ############################### OTHERS #############################################################################

# Add variables to global scope, e.g. when esmini is used as submodule
set(EXTERNALS_PUGIXML_PATH
    ${EXTERNALS_PUGIXML_PATH}
    CACHE INTERNAL
          "")
set(EXTERNALS_EXPR_PATH
    ${EXTERNALS_EXPR_PATH}
    CACHE INTERNAL
          "")
set(EXTERNALS_YAML_PATH
    ${EXTERNALS_YAML_PATH}
    CACHE INTERNAL
          "")
set(EXTERNALS_FMT_PATH
    ${EXTERNALS_FMT_PATH}
    CACHE INTERNAL
          "")

# ############################### Compiling targets ##################################################################

add_subdirectory(EnvironmentSimulator)
