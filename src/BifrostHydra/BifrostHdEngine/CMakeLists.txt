#-
#*****************************************************************************
# Copyright 2022 Autodesk, Inc.
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

set(hd_Engine_headers
    Container.h
    Engine.h
    JobTranslationData.h
    Parameters.h
    Requirement.h
    Runtime.h
    ValueTranslationData.h
)

file(COPY ${hd_Engine_headers} DESTINATION ${CMAKE_BINARY_DIR}/common/include/BifrostHydra/Engine )

add_library( BifrostHdEngineHeaders INTERFACE )
target_include_directories( BifrostHdEngineHeaders 
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/common/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )

install(DIRECTORY ${CMAKE_BINARY_DIR}/common/include/BifrostHydra/Engine DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/BifrostHydra)

set(src_files
    Container.cpp
    Engine.cpp
    JobTranslationData.cpp
    Parameters.cpp
    Requirement.cpp
    Runtime.cpp
    ValueTranslationData.cpp
)

add_library( BifrostHdEngine SHARED ${src_files} )
target_link_libraries( BifrostHdEngine PUBLIC
    BifrostHdTranslators
    BifrostHdEngineHeaders
    Amino::SDK::Preview
    Bifrost::Object::Preview
    BifrostGraph::Executor::Preview
)

target_link_libraries( BifrostHdEngine PRIVATE 
    Bifrost::Geometry::Preview
    hd
)

install(TARGETS BifrostHdEngine 
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )


# bifusd_install_headers(
#     hdEngineHeadersInstall
#     SOURCE ${CMAKE_CURRENT_SOURCE_DIR}
#     FILES ${hd_Engine_headers}
#     DESTINATION "BifrostHydra/Engine"
# )
# 
# set(private_libs
#     Amino::Core
#     BifrostGraph::Executor
#     Bifrost::Object
#     InternalBifrost::AminoSDK
#     hd
#     hdEngineHeadersInstall
#     BifrostHdTranslators
# )
# 
# bifusd_set_extra_rpaths(extra_rpaths)
# 
# bifusd_create_shared_lib(
#     BifrostHdEngine "BIFROST_HD_ENGINE_BUILD_DLL" # TODO: add export file
#     PUBLIC_INSTALL
#     PUBLIC_DEFINITIONS     $<${BIFUSD_IS_MSC}: BOOST_LIB_TOOLSET="vc141">
#     PRIVATE_DEFINITIONS    $<${BIFUSD_IS_DEBUG}: TBB_USE_DEBUG BOOST_DEBUG_PYTHON BOOST_LINKING_PYTHON>
#     PRIVATE_OPTIONS        $<${BIFUSD_IS_MSC}:/wd4251 /wd4273>
#     SRC_FILES              ${src_files}
#     PRIVATE_LINK_LIBS      ${private_libs}
#     EXTRA_RPATH            ${extra_rpaths}
# )

add_subdirectory(translation)
add_subdirectory(config)
