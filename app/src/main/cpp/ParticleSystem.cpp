//
// Created by Ankit Singh on 11-11-2018.
//

#include "ParticleSystem.hpp"
#include"Random.h"
#include"android/log.h"
#include<algorithm>
#include"Camera.hpp"


//PARTICLE

void Particle::Reset() {
    mPosition = glm::vec3(Random::GetInstance()->GetOnXZ(-0.1f,0.1f));
    mVelocity.x = Random::GetInstance()->Real(-.2,.2);
    mVelocity.y =  1.0f;
    mSize = .5f;
    mLifetime = Random::GetInstance()->Real(1.0f,2.0f);
    mSpeed = Random::GetInstance()->Real(.2f,.7f);
    mColor = glm::vec4(Random::GetInstance()->GetPointOnUnitSphere(),1.0f);
    mCameraDistance = 0;
    mTexPoint = glm::vec2(0.0f);
    mElapsedFrameTime = 0.0f;
    mCurrentFrameIndex = -1;
    mFrameUpdateTime = mLifetime / 64.0f;
}

void Particle::Update(float dt)
{
    mLifetime -= dt;
    mSpeed -= (.1f *dt);
    mPosition += mVelocity * (mSpeed * dt);
    mColor.a-=dt;
}



//MANAGER
ParticleManager::ParticleManager()
{
    mParticles.reserve(POOL_SIZE);
    mPositionScale.reserve(POOL_SIZE);
    mColors.reserve(POOL_SIZE);
    mTexCoords.reserve(POOL_SIZE);
    mDeadIndices.reserve(POOL_SIZE);
}

ParticleManager::~ParticleManager() {

}

void ParticleManager::Init() {
    mRenderer.Init();

    mAtlas.Load("textures/fire.png",8,8);

    mModel = glm::mat4();
    mModel = glm::translate(mModel,glm::vec3(0.0f,0.0f,1.0f));
    for(int i =0 ; i< POOL_SIZE ; ++i)
    {
        Particle p;
        mParticles.push_back(p);
        mPositionScale.push_back(glm::vec4(0.0f));
        mColors.push_back(glm::vec4(0.0f));
        mDeadIndices.push_back(i);
        mTexCoords.push_back(glm::vec2(0.0f));
    }

    for(int i =0 ; i< POOL_SIZE ; ++i)
    {
        mParticles[i].Reset();
    }
}

void ParticleManager::Destroy() {
    mParticles.clear();
    mColors.clear();
    mPositionScale.clear();
    mTexCoords.clear();
}


void ParticleManager::CreateNewParticles(int number)
{
    if(mDeadIndices.empty()) return;

    if(mDeadIndices.size() < number)
        number = mDeadIndices.size();
    int i = 0;
    auto iter = mDeadIndices.begin();
    for(int i = 0  ; i < number ; i++)
    {
        Particle& p = mParticles[*iter];
        p.Reset();
        iter = mDeadIndices.erase(iter);
    }
}


void ParticleManager::SortParticles()
{
    auto sortHelper = [](Particle& one, Particle& two)->bool
    {
        return one.mCameraDistance > two.mCameraDistance;
    };
    std::sort(mParticles.begin(), mParticles.end(),sortHelper);
}

void ParticleManager::Tick(const Camera& camera,double Deltatime)
{
    mCamera = camera;
    mParticleCount = 0;
    for (int i = 0; i < POOL_SIZE; i++)
    {
        auto &particle = mParticles[i];
            if(particle.mLifetime > 0.0f)
            {
                particle.mPosition += particle.mVelocity * (particle.mSpeed * float(Deltatime));
               // particle.mColor.a-=Deltatime;
                particle.mLifetime-=Deltatime;

                particle.mElapsedFrameTime += Deltatime;


                if(particle.mElapsedFrameTime > particle.mFrameUpdateTime)
                {
                    particle.mElapsedFrameTime = 0;
                    particle.mCurrentFrameIndex++;
                    particle.mTexPoint.x = (particle.mCurrentFrameIndex % mAtlas.GetCols()) * mAtlas.GetNormSize().x;
                    particle.mTexPoint.y = (particle.mCurrentFrameIndex / mAtlas.GetCols()) * mAtlas.GetNormSize().y;
                    if(particle.mCurrentFrameIndex >= mAtlas.GetFrames())
                        particle.mCurrentFrameIndex = mAtlas.GetFrames() - 1;
                }
            }
            else
            {
               particle.Reset();
            }
    }
    mView = camera.GetView();
   /* mView[0][0] = mModel[0][0];
    mView[0][1] = mModel[1][0];
    mView[0][2] = mModel[2][0];
    mView[1][0] = mModel[0][1];
    mView[1][1] = mModel[1][1];
    mView[1][2] = mModel[2][1];
    mView[2][0] = mModel[0][2];
    mView[2][1]=  mModel[1][2];
    mView[2][2] = mModel[2][2];*/

    //SortParticles();
}

void ParticleManager::SetShaderValues()
{
    mRenderer.GetShader().SetMat4("view",mView);
    mRenderer.GetShader().SetMat4("model",mModel);
    mRenderer.GetShader().Set1i("atlas",0);
    mRenderer.GetShader().SetVec2("frameSize",mAtlas.GetNormSize());
}
void ParticleManager::Render()
{
    for(auto& particle : mParticles)
    {
        glm::vec4 camPos = glm::vec4(particle.mPosition,1.0f) * mView;
        particle.mCameraDistance = glm::length(mCamera.GetPosition() - glm::vec3(camPos));
    }
    SortParticles();
    for(int mParticleCount = 0 ; mParticleCount < mParticles.size() ; mParticleCount++)
    {
        auto& particle = mParticles[mParticleCount];
        mPositionScale[mParticleCount].x = particle.mPosition.x;
        mPositionScale[mParticleCount].y = particle.mPosition.y;
        mPositionScale[mParticleCount].z = particle.mPosition.z;
        mPositionScale[mParticleCount].w = particle.mSize;
        mColors[mParticleCount] = particle.mColor;
        mTexCoords[mParticleCount] = particle.mTexPoint;
    }
    mRenderer.GetShader().Use();
    SetShaderValues();
    mAtlas.BindToUnit(GL_TEXTURE0);
    mRenderer.Render(mParticles.size(),mPositionScale,mColors,mTexCoords);
 }

