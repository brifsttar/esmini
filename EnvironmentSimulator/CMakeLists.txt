set ( ROADMANAGER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Modules/RoadManager" )
set ( COMMON_MINI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Modules/CommonMini")
set( CMAKE_VERBOSE_MAKEFILE true )

if (APPLE)
  set ( TIME_LIB "" )
elseif (UNIX)
  set ( TIME_LIB "" )
elseif (WIN32)
  if (WINSDK7_1)
    message ("Configuring for Windows SDK v7.1 x64")
    set ( SOCK_LIB Ws2_32.lib )
    set ( TIME_LIB winmm.lib )
  elseif ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    message ("Configuring for Windows SDK v10 win32")
    set ( SOCK_LIB Ws2_32.lib )
    set ( TIME_LIB "" )
  elseif ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    message ("Configuring for Windows SDK v10 x64")
    set ( SOCK_LIB Ws2_32.lib )
    set ( TIME_LIB "" )
  else ()
    message ("Unknown configuration")
  endif ()
endif (APPLE)

if(APPLE)
  SET(CMAKE_CXX_FLAGS "-std=c++14 -pthread -flto -Wl,-dead_strip")
elseif(UNIX)

include(CheckCXXCompilerFlag)

  # Check for standard to use
  check_cxx_compiler_flag(-std=c++14 HAVE_FLAG_STD_CXX14)
  if(HAVE_FLAG_STD_CXX14)
      SET(CXX_STD_FLAG "-std=c++14")
  else()
     check_cxx_compiler_flag(-std=c++1y HAVE_FLAG_STD_CXX1Y)
     if(HAVE_FLAG_STD_CXX1Y)
       SET(CXX_STD_FLAG "-std=c++1y")
     else()
       message ("Need compiler support for c++14 \(or 1y as the beta was called\)")
     endif()
  endif()

  set (CMAKE_C_FLAGS "-std=c11 ${CMAKE_C_FLAGS}")

  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(CMAKE_CXX_FLAGS "${CXX_STD_FLAG} -pthread -fPIC -Wl,-strip-all")
  elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_CXX_FLAGS "${CXX_STD_FLAG} -march=native -O0 -pthread -fPIC")
  else()
    SET(CMAKE_CXX_FLAGS "${CXX_STD_FLAG} -pthread -fPIC -Wl,-strip-all")
  endif()
else() #not UNIX

  # Get rid of historical macros preventing SUMO integration
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D NOMINMAX ")

  if ((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1910))
    # suppress warning 4127 (conditional expression is constant) to avoid harmless warning from Google protobuf header
    # suppress warning 4100 (unreferenced formal parameter) to allow function headers with unreferenced parameters for increased readability
    add_compile_options(/permissive- /W4 /wd4127 /wd4100)
  endif ()
endif() #Endif UNIX

add_subdirectory(Modules/CommonMini)
add_subdirectory(Modules/RoadManager)

set ( ModulesFolder Modules )

set_target_properties (RoadManager PROPERTIES FOLDER ${ModulesFolder} )
set_target_properties (CommonMini PROPERTIES FOLDER ${ModulesFolder} )
