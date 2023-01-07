//-
// Copyright 2022 Autodesk, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//+

#ifndef BIFROST_HD_ENGINE_H
#define BIFROST_HD_ENGINE_H

#include <AminoJob.h>
#include <Bifrost/Object/Object.h>

#include <pxr/imaging/hd/sceneIndex.h>

#include <memory>

namespace BifrostHd {

/// \class Engine
///
/// Interface to access the Bifrost Graph and parameters stored
/// in a HdSceneIndexPrim of type hydraGenerativeProcedural
///

using Output =
    std::pair<std::string, Amino::Array<Amino::Ptr<Bifrost::Object>>>;

class Engine {
public:
    Engine();

    ~Engine();

    void setInputScene(pxr::HdSceneIndexBaseRefPtr inputScene);
    void setInputs(pxr::HdSceneIndexPrim const& prim);

    Amino::Job::State execute(const double frame = 0);
    const Output&     output();

public:
    /// Disabled
    /// \{
    Engine(const Engine&)            = delete;
    Engine(Engine&&)                 = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&)      = delete;
    /// \}

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace BifrostHd

#endif // BIFROST_HD_ENGINE_H
