########################################################################################################################
### This is a Emscripten build for gameboycore-web
### Must invoke with CMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake
########################################################################################################################

cmake_minimum_required(VERSION 3.0.0)

project(cosmos-web-core)

set(CMAKE_CXX_STANDARD 11)

set(EMSCRIPTEN_ROOT $ENV{EMSDK}/upstream/emscripten)
message ("EMSCRIPTEN_ROOT: ${EMSCRIPTEN_ROOT}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${EMSCRIPTEN_ROOT}/cmake/Modules")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${EMSCRIPTEN_ROOT}/cmake/Modules")

########################################################################################################################
### External Dependencies                                                                                            ###
########################################################################################################################

set(COSMOS_SOURCE "$ENV{HOME}/cosmos/source")
message ("COSMOS_SOURCE: ${COSMOS_SOURCE}")
set(COSMOS_CXX_FLAGS "-Os -Wmaybe-uninitialized -Wtype-limits -Wall -pedantic -std=c++11 -U__STRICT_ANSI__ -Wno-invalid-offsetof -Wno-format -Wno-date-time")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
message("Setting Standard to c++11")
add_compile_definitions(USE_LINUX_LIBRARIES)
include_directories(${COSMOS_SOURCE}/core/libraries/)
add_subdirectory(${COSMOS_SOURCE}/core/libraries/support   ${CMAKE_BINARY_DIR}/libraries/support/)
add_subdirectory(${COSMOS_SOURCE}/core/libraries/math      ${CMAKE_BINARY_DIR}/libraries/math/)



########################################################################################################################
### CosmosCore Web                                                                                                  ###
########################################################################################################################

add_subdirectory(source)

# Create the final executable
add_executable(${PROJECT_NAME}
    source/cosmos_web_core_bindings.cpp
)
target_link_libraries(${PROJECT_NAME}
    # Link to our library
    cosmos_web_core_bindings
)
