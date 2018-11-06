//Declaration header

#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

#include"Texture2D.h"

	Texture2D::Texture2D()
	{

	}


	Texture2D::~Texture2D()
	{
		//glDeleteTextures(1,&mID);
		//stbi_image_free(mImage);
	}



	Texture2D::Texture2D(const std::string& path)
	{
		int width,height;
		int channels;
		unsigned char* image = stbi_load(path.c_str(),&width,&height,&channels,0);
		mImage = image;
		mSize = glm::vec2(width, height);
		mFormat = channels == 4? GL_RGBA : GL_RGB;
		glGenTextures(1, &mID);
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, width, height, 0, mFormat, GL_UNSIGNED_BYTE, image);
		Unbind();
	}

	GLuint Texture2D::CreateTexture(const std::string& path)
	{
		int width,height;
		int channels;
		unsigned char* image = stbi_load(path.c_str(),&width,&height,&channels,0);
		mImage =image;
		mSize = glm::vec2(width, height);
		mFormat = channels == 4? GL_RGBA : GL_RGB;

		glGenTextures(1,&mID);
	
		Bind();
	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,mSize.x,mSize.y,0,GL_RGBA,GL_UNSIGNED_BYTE,mImage);

		Unbind();

		return mID;
	}


	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D,mID);
	}


	void Texture2D::Unbind()const
	{
		glBindTexture(GL_TEXTURE_2D,0);
	}