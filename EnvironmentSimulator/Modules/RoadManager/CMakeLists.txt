# ############################### Setting targets ####################################################################

set(TARGET
    RoadManager)

# ############################### Loading desired rules ##############################################################

include(${CMAKE_SOURCE_DIR}/support/cmake/rule/disable_static_analysis.cmake)
include(${CMAKE_SOURCE_DIR}/support/cmake/rule/disable_iwyu.cmake)
include(${CMAKE_SOURCE_DIR}/support/cmake/rule/enable_fpic.cmake)

if(MSVC)
    add_definitions("/wd4482")
endif()

# ############################### Setting target files ###############################################################

set(SOURCES
    RoadManager.cpp
    odrSpiral.cpp
    LaneIndependentRouter.cpp)

add_library(
    pugixml_lib
    ${EXTERNALS_PUGIXML_PATH}/pugixml.cpp)

set(INCLUDES
    RoadManager.hpp
    odrSpiral.h
    LaneIndependentRouter.hpp)

# ############################### Creating library ###################################################################


add_library ( RoadManager SHARED ${SOURCES} ${SRC_ADDITIONAL} ${INCLUDES} )
target_include_directories(
    ${TARGET}
    PRIVATE ${COMMON_MINI_PATH})

target_include_directories(
    ${TARGET}
    SYSTEM
    PUBLIC ${EXTERNALS_PUGIXML_PATH}
           ${EXTERNALS_FMT_INCLUDES}
           ${ROAD_MANAGER_PATH})
add_compile_definitions( ROADMANAGER_EXPORT )
target_link_libraries ( RoadManager CommonMini pugixml_lib fmt)
set_target_properties( RoadManager
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}../../../../lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}../../../../lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}../../../../bin"
)
disable_static_analysis(${TARGET})
disable_iwyu(${TARGET})
enable_fpic(${TARGET})
