//
// Created by Ankit Singh on 28-10-2018.
//

#ifndef BURNOUTENGINE_SHADERPROGRAM_HPP
#define BURNOUTENGINE_SHADERPROGRAM_HPP

#include<string>
#include<GLES3/gl3.h>
#include<EGL/egl.h>
#include<glm/glm.hpp>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    char* LoadShader(const char* path);
    GLuint CompileShader(const char* shaderCode,const std::string& type);

    void Create(const std::string& vsPath,const std::string& fsPath);
    void Use();
    void Delete(){glDeleteProgram(mProgramID);}

    void Set1i(const std::string& varName,int value);
    void Set1f(const std::string& varName,float value);
    void SetVec3(const std::string& varName,const glm::vec3& value);
    void SetMat4(const std::string& varName,glm::mat4& model);

private:

    static const int MAX_BUFFER_SIZE = 1024;
    GLuint mProgramID;
};


#endif //BURNOUTENGINE_SHADERPROGRAM_HPP
