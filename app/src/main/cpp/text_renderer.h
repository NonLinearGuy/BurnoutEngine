#ifndef INC_SHADY_ENGINE_TEXT_RENDERER_H
#define INC_SHADY_ENGINE_TEXT_RENDERER_H




//C++ headers
#include<iostream>
#include<map>
#include<string>
#include<cstdarg>
#include<memory>
#include<vector>


//Third party headers
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"ShaderProgram.hpp"
#include"Texture2D.h"


	class text_renderer
	{

	private:

		struct character
		{
			glm::ivec2 position;
			glm::ivec2 size;
			glm::ivec2 offsets;
			int advanceX;

		};
		std::map<char, character> mCharacters;
		Texture2D mTextureAtlas;
		ShaderProgram mShader;
		GLuint mVAO;
		GLuint mVBO;


		//data needed for instancing 
		std::vector<glm::vec2> mOffsets;
		std::vector<glm::vec2> mScalers;
		std::vector<glm::vec4> mTexCoords;

		GLuint mVBOOffsets;
		GLuint mVBOTexCoords;
		GLuint mVBOScalers;


	public:
		
		//Constructors
		text_renderer();
		//Destructor
		~text_renderer();
		/*
			initializes essential data for rendering text
		*/
		void init(const Texture2D pTextureAtlas,
			const std::string& pPath);
		/*
			Renders text with a color
		*/
		void text(
			const glm::vec2& pPosition,
			float pSize, 
			const glm::vec3& pColor,
			const char* pFormat, 
			...
		);

	};
#endif