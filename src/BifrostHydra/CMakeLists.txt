#-
#*****************************************************************************
# Copyright 2023 Autodesk, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#*****************************************************************************
#+

# Build with USD and Bifrost Preview SDK - WIP

cmake_minimum_required(VERSION 3.20)

set( project_name "BifrostUSDHydra")

message(STATUS "CMake version: ${CMAKE_VERSION}")

# BIFROST_LOCATION must be passed-in or defined by an environment variable.
# Passed-in on the CMake command line overrides the environemnt variable.
if( NOT BIFROST_LOCATION )
    if( DEFINED ENV{BIFROST_LOCATION} )
        set( BIFROST_LOCATION $ENV{BIFROST_LOCATION})
    else()
        message( FATAL_ERROR "${project_name}: BIFROST_LOCATION cmake variable must be defined.")
    endif()
endif()

if( NOT USD_LOCATION )
    if( DEFINED ENV{USD_LOCATION} )
        set( USD_LOCATION $ENV{USD_LOCATION})
    else()
        message( FATAL_ERROR "${project_name}: USD_LOCATION cmake variable must be defined.")
    endif()
endif()


# Project Name
project(
    ${project_name} 
    VERSION 1.0.0
    LANGUAGES CXX
)

include(CMakePrintHelpers)
include(GNUInstallDirs)

# Require C++17
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Bifrost setup and utilities...
include(${BIFROST_LOCATION}/sdk/cmake/setup.cmake)

# Verbose CMake
set( CMAKE_VERBOSE_MAKEFILE TRUE)

cmake_print_variables( USD_LOCATION )
# Find Bifrost
find_package(BifrostPreview REQUIRED SDK)
# find_package(BifrostExtra REQUIRED)
find_package(pxr REQUIRED NO_DEFAULT_PATH PATHS "${USD_LOCATION}")

# Build
add_subdirectory(BifrostHdTranslators)
add_subdirectory(BifrostHdEngine)
add_subdirectory(BifrostHdGraph)
