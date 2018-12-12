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
    float mFrameUpdateTime;
    float mElapsedFrameTime;
    int mCurrentFrameIndex;
    glm::vec2 mTexPoint;
    glm::vec3 mPosition;
    glm::vec3 mVelocity;
    glm::vec4 mColor;
    float mSpeed;
    float mLifetime;
    float mSize;
    float mCameraDistance;

    void Reset();
    void Update(float dt);
    inline bool IsAlive(){return mLifetime > 0.0f;}
    bool operator < (Particle& other)
    {
        return this->mCameraDistance > other.mCameraDistance;
    }
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
    int GetLastUsedParticle();
    void CreateNewParticles(int number);
    void SortParticles();
private:
    const int POOL_SIZE = 30;
    int mParticleCount;
    std::vector<Particle> mParticles;
    ParticlesRenderer mRenderer;;
    std::vector<glm::vec4> mPositionScale;
    std::vector<glm::vec4> mColors;
    std::vector<glm::vec2> mTexCoords;
    std::vector<int> mDeadIndices;
    //for transforming
    glm::mat4 mModel;
    glm::mat4 mView;
    Camera mCamera;
    ParticleTextureAtlas mAtlas;

};




#endif //BURNOUTENGINE_PARTICLESYSTEM_HPP
