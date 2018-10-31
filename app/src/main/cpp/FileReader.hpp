//
// Created by Ankit Singh on 31-10-2018.
//

#ifndef BURNOUTENGINE_FILEREADER_HPP
#define BURNOUTENGINE_FILEREADER_HPP

#include<android/asset_manager.h>
#include<android_native_app_glue.h>
#include<string>

class FileReader
{
public:

    static AAssetManager* sAssetManager;

    static FileReader* GetInstance()
    {
        static FileReader instance;
        return &instance;
    }

    AAsset* Open(const std::string& path);

private:

    FileReader()
    {

    }
};


#endif //BURNOUTENGINE_FILEREADER_HPP
