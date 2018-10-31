//
// Created by Ankit Singh on 31-10-2018.
//

#include "FileReader.hpp"

AAssetManager* FileReader::sAssetManager = nullptr;

AAsset* FileReader::Open(const std::string& path)
{
    assert(sAssetManager != nullptr);
    return AAssetManager_open(sAssetManager,path.c_str(),AASSET_MODE_UNKNOWN);
}