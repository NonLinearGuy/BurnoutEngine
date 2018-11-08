//Declaration header
#include"SpriteRenderer.h"



	SpriteRenderer::SpriteRenderer()
	{

		mShader.Create("shaders/sprite_renderer_vs.glsl","shaders/sprite_renderer_fs.glsl");

		float points[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);


		/*
		I am  going to need same amount of texture
		coords as points so allocating 2*sizeof(points) buffer
		so that you can store texture coordinates later.
		*/

		glBufferData(GL_ARRAY_BUFFER, sizeof(points) * 2, 0, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(points)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}
	void SpriteRenderer::Init()
	{
		mShader.Create("shaders/sprite_renderer_vs.glsl","shaders/sprite_renderer_fs.glsl");

		float points[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);


		/*
		I am  going to need same amount of texture
		coords as points so allocating 2*sizeof(points) buffer
		so that you can store texture coordinates later.
		*/

		glBufferData(GL_ARRAY_BUFFER,sizeof(points)*2, 0, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER,mVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(points)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);


	}



	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
	}

	void SpriteRenderer::DrawImage(
		const Texture2D& pTexture,
		const glm::vec2& pPos,
		const glm::vec2& pSize,
		const glm::vec4& pColor,
		float pRotationInRadians
	)

	{
		glm::mat4 model = glm::mat4();

		model = glm::translate(model, glm::vec3(pPos, 0.0f));
        model = glm::scale(model, glm::vec3(pSize, 0.0f));


		float texCoords[] =
		{
			0.0f,0.0f,
			1.0f,0.0f,
			0.0f,1.0f,
			1.0f,1.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates pSize is same as vertices pSize
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mShader.Use();

		/*mShader.SetMat4("model", model);
		mShader.Set1i("use_color", 0);
		mShader.Set1i("sampler0", 0);
		glActiveTexture(GL_TEXTURE0);
		pTexture.Bind();
		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);*/

	}






	


	void SpriteRenderer::DrawImageRegion(
		const Texture2D& pTexture,
		const glm::vec2& pSrcPos,
		const glm::vec2& pSrcDim,
		const glm::vec2& pPos,
		const glm::vec2& pSize,
		float pRotationInRadians
	)

	{

		glm::mat4 model = glm::mat4();
		model = glm::translate(model, glm::vec3(pPos, 0.0f));
		model = glm::scale(model, glm::vec3(pSize, 0.0f));

		//Mapping values from one range to other
		float dw = pSrcDim.x / pTexture.GetSize().x;
		float dh = pSrcDim.y / pTexture.GetSize().y;
		float dx = pSrcPos.x / pTexture.GetSize().x;
		float dy = pSrcPos.y / pTexture.GetSize().y;

		float texCoords[] =
		{
			dx,dy,
			dx + dw,dy,
			dx,dy + dh,
			dx + dw,dy + dh
		};


		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates size is same as vertices size
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mShader.Use();

		mShader.SetMat4("model", model);

		mShader.Set1i("sampler0", 0);
		mShader.Set1i("use_color", 0);

		glActiveTexture(GL_TEXTURE0);
		//pTexture.Bind();

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
		pTexture.Unbind();
	}


