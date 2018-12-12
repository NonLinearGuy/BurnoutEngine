#include"ParticlesRenderer.h"

//Third Party headers
#include<glm/gtc/matrix_transform.hpp>

#include"Texture2D.h"

	ParticlesRenderer::ParticlesRenderer()
	{
		
	}

	ParticlesRenderer::~ParticlesRenderer()
	{
		glDeleteBuffers(1, &mVBO);
		glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1,&mVBOPositions);
        glDeleteBuffers(1,&mVBOColors);
	}


	void ParticlesRenderer::Init()
	{
	mShaderProgram.Create("shaders/debug.vs",
			"shaders/debug.fs");
		float attribs[] = {
				-0.5f,-.5f,0.0f,
				0.5f,-0.5f,0.0f,
				0.5f,0.5f,0.0f,
				-0.5f,0.5f,0.0f
		};

		int indices[] = {0,1,3,1,2,3};

		glGenVertexArrays(1,&mVAO);
		glBindVertexArray(mVAO);

		glGenBuffers(1,&mVBO);
		glBindBuffer(GL_ARRAY_BUFFER,mVBO);
		glBufferData(GL_ARRAY_BUFFER,sizeof(attribs),attribs,GL_STATIC_DRAW);

		glGenBuffers(1,&mEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

		glBindVertexArray(0);
	}



	void ParticlesRenderer::Render(int numOfInstances,
		const std::vector<glm::vec4>& positions,
		const std::vector<glm::vec4>& colors,
		const std::vector<glm::vec2>& texCoords
	)
	{
        glGenBuffers(1,&mVBOPositions);
		glGenBuffers(1, &mVBOColors);
		glGenBuffers(1,&mVBOTex);

		glBindVertexArray(mVAO);

        glBindBuffer(GL_ARRAY_BUFFER, mVBOPositions);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)* positions.size(), positions.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribDivisor(1, 1);

		//Scale and Rotation
		glBindBuffer(GL_ARRAY_BUFFER, mVBOColors);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*colors.size(), colors.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(2, 1);

		//Scale and Rotation
		glBindBuffer(GL_ARRAY_BUFFER, mVBOTex);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*texCoords.size(), texCoords.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(3, 1);


		glBindVertexArray(mVAO);
		glDrawElementsInstanced(GL_TRIANGLES,6,GL_UNSIGNED_INT,0,numOfInstances);
		glBindVertexArray(0);

        glDeleteBuffers(1, &mVBOPositions);
		glDeleteBuffers(1, &mVBOColors);
		glDeleteBuffers(1, &mVBOTex);
	}
