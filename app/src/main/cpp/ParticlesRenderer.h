#ifndef INC_PARTICLE_RENDERER_H
#define INC_PARTICLE_RENDERER_H


//C++ Headers
#include<memory>
#include<vector>

//Third Party Headers
#include<GLES3/gl3.h>
#include<glm/glm.hpp>
#include<ShaderProgram.hpp>

class Texture2D;


class ParticlesRenderer
{
private:
    ShaderProgram mShaderProgram;
    GLuint mVAO;
    GLuint mVBO;
    GLuint mEBO;
	GLuint mVBOPositions;
    GLuint mVBOColors;
    GLuint mVBOTex;
public:
    ParticlesRenderer();
    void Init();
    void Render(int numOfInstance,
				const std::vector<glm::vec4>& positions,
				const std::vector<glm::vec4>& colors,
				const std::vector<glm::vec2>& texCoords);
	inline ShaderProgram GetShader(){return mShaderProgram;}
    ~ParticlesRenderer();
};	//End of class
#endif

