//
// Created by Ankit Singh on 11-11-2018.
//

#ifndef BURNOUTENGINE_PARTICLESYSTEM_HPP
#define BURNOUTENGINE_PARTICLESYSTEM_HPP

#include<Renderable.hpp>
#include<Texture2D.h>
#include<string>
#include<glm/glm.hpp>
#include<vector>
#include<ParticlesRenderer.h>
#include<Camera.hpp>

namespace MathUtils
{
    template<typename Type>
    inline Type Lerp(Type start,Type end, float weight)
    {
        return (start + ((end - start) * weight));
    }
}


class ParticleTextureAtlas : public Texture2D
{
public:
    void Load(const std::string& path,int rows,int cols)
    {
        Texture2D::CreateTexture(path);
        mRows = rows;
        mCols = cols;
        mFrameSize = glm::vec2(mSize.x/float(cols),mSize.y/float(rows));
        mNormFrameSize.x = mFrameSize.x/mSize.x;
        mNormFrameSize.y = mFrameSize.y/mSize.y;
    }
    inline int GetRows(){return mRows;}
    inline int GetCols(){return mCols;}
    inline int GetFrames(){return mRows * mCols;}
    inline glm::vec2 GetFrameSize(){return mFrameSize;}
    inline glm::vec2 GetNormSize(){return mNormFrameSize;}
private:
    int mRows;
    int mCols;
    glm::vec2 mFrameSize;
    glm::vec2 mNormFrameSize;
};

struct Particle
{
    int mCurrentFrame;
    glm::vec4 mPosition;
    glm::vec2 mScale;
    float mAlpha;
    int mTexUnit;
    glm::vec4 mVelocity;
    float mElapsedTime;
    float mLifeTime;
    float mRegionUpdateTime;
    float mRegionUpdateElapsed;
    glm::vec2 DUDV;

    glm::vec4 mInitialVelocity;
    glm::vec4 mFinalVelocity;
    glm::vec2 mMinScale;
    glm::vec2 mMaxScale;

    ParticleTextureAtlas mTextureAtlas;

    bool IsAlive()
    {
        return mElapsedTime <= mLifeTime;
    }

    void Reset();

    void Update(float dt);
};


class ParticleManager
{
public:
    ParticleManager();
    ~ParticleManager();
    void Init();
    void Destroy();
    void Tick(const Camera& camera,double Deltatime);
    void SetShaderValues();
    inline ShaderProgram GetShader(){return mRenderer.GetShader();}
    void Render();
private:
    const int POOL_SIZE = 500;
    std::vector<Particle> mParticles;
    ParticlesRenderer mRenderer;;
    std::vector<glm::vec3> mPositions;
    std::vector<glm::vec4> mValues;
    std::vector<glm::vec2> mTexCoords;
    glm::mat4 mModel;
    glm::mat4 mView;
    ParticleTextureAtlas mFire;
    ParticleTextureAtlas mSmoke;
};




#endif //BURNOUTENGINE_PARTICLESYSTEM_HPP
