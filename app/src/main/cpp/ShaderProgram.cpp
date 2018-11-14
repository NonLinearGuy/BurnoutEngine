//
// Created by Ankit Singh on 28-10-2018.
//

#include "ShaderProgram.hpp"
#include<cstdio>
#include<android_native_app_glue.h>
#include<FileReader.hpp>
#include<glm/gtc/type_ptr.hpp>


ShaderProgram::ShaderProgram()
{

}


ShaderProgram::~ShaderProgram()
{

}


char* ShaderProgram::LoadShader(const char *path)
{

}

GLuint ShaderProgram::CompileShader(const char *path,const std::string& type)
{
    AAsset* asset =   FileReader::GetInstance()->Open(path);
    assert(asset != NULL);
    char buffer[MAX_BUFFER_SIZE];
    memset(buffer,0,MAX_BUFFER_SIZE);
-   AAsset_read(asset,buffer,MAX_BUFFER_SIZE);
    AAsset_close(asset);


    GLuint id = -1;

    if("frag" == type)
        id = glCreateShader(GL_FRAGMENT_SHADER);
    else
        id = glCreateShader(GL_VERTEX_SHADER);
    const char* shaderCode = (const char*) &buffer[0];
    glShaderSource(id,1,&shaderCode,NULL);
    glCompileShader(id);
    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        int a=0;
    }

    return id;
}

void ShaderProgram::Create(const std::string &vsPath, const std::string &fsPath)
{
    GLuint vId = CompileShader(vsPath.c_str(),"");
    GLuint fId = CompileShader(fsPath.c_str(),"frag");


    mProgramID = glCreateProgram();
   glAttachShader(mProgramID,vId);
    glAttachShader(mProgramID,fId);
    glLinkProgram(mProgramID);

    int success;
    char infoLog[512];
    glGetShaderiv(mProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(mProgramID, 512, NULL, infoLog);
        int a=0;
    }

    glDeleteShader(vId);
    glDeleteShader(fId);
}

void ShaderProgram::Use()
{
    glUseProgram(mProgramID);
}

void ShaderProgram::Set1i(const std::string &varName, int value) {

    GLuint location = glGetUniformLocation(mProgramID,varName.c_str());
    glUniform1i(location,value);
}

void ShaderProgram::Set1f(const std::string &varName, float value) {
    GLuint location = glGetUniformLocation(mProgramID,varName.c_str());
    glUniform1f(location,value);
}

void ShaderProgram::SetVec3(const std::string &varName, const glm::vec3 &value) {
    GLuint location = glGetUniformLocation(mProgramID,varName.c_str());
    glUniform3f(location,value.x,value.y,value.z);
}

void ShaderProgram::SetMat4(const std::string &varName, glm::mat4 &mat) {
    GLuint location = glGetUniformLocation(mProgramID,varName.c_str());
    glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(mat));
}

void ShaderProgram::SetVec2(const std::string &varName, const glm::vec2 &value) {
    GLuint location = glGetUniformLocation(mProgramID,varName.c_str());
    glUniform2f(location,value.x,value.y);
}

