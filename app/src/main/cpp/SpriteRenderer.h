#ifndef INC_SpriteRenderer_H
#define INC_SpriteRenderer_H

//C++ headers
#include<memory>
#include<vector>


//Third party headers
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<GLES3/gl3.h>

//shady_engine headers
#include"ShaderProgram.hpp"
#include"Texture2D.h"

	class SpriteRenderer
	{
	private:
		ShaderProgram mShader;
		GLuint mVAO;
		GLuint mVBO;
	public:
		SpriteRenderer();
		~SpriteRenderer();

		ShaderProgram GetShader()
		{
			return mShader;

		}
		void Init();

		void DrawImage(const Texture2D& pTexture,
			const glm::vec2& pPos,
			const glm::vec2& pSize,
			const glm::vec4& pColor,
			float pRotationInRadians
		);
		
		void DrawImageRegion(const Texture2D& pTexture,
			const glm::vec2& pSrcPos, 
			const glm::vec2& pSrcDim, 
			const glm::vec2& pPos, 
			const glm::vec2& pSize,
			float pRotationInRadians
		);

	}; // End of class SpriteRenderer

#endif