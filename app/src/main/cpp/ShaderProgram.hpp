//
// Created by Ankit Singh on 28-10-2018.
//

#ifndef BURNOUTENGINE_SHADERPROGRAM_HPP
#define BURNOUTENGINE_SHADERPROGRAM_HPP

#include<string>
#include<GLES3/gl3.h>
#include<EGL/egl.h>
class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    char* LoadShader(const char* path);
    GLuint CompileShader(const char* shaderCode,const std::string& type);

    void Create(const std::string& vsPath,const std::string& fsPath);
    void Use();
private:

    static const int MAX_BUFFER_SIZE = 1024;
    GLuint mProgramID;
};


#endif //BURNOUTENGINE_SHADERPROGRAM_HPP
