#pragma once

#include <string>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <ghc/filesystem.hpp>


template <class Archive>
std::string save_minimal(const Archive &, const ghc::filesystem::path & p) {
    return p.string();
}

template <class Archive>
void load_minimal(const Archive &, ghc::filesystem::path& p, const std::string& value) {
    p = ghc::filesystem::path{value};
}