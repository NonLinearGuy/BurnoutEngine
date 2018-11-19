//
// Created by Ankit Singh on 11-11-2018.
//

#include "ParticleSystem.hpp"
#include"Random.h"
#include"android/log.h"
#include<algorithm>


//PARTICLE

void Particle::Reset() {
    mPosition = glm::vec3(0.0f,0.0f,0.0f);
    mVelocity = Random::GetInstance()->GetPointOnUnitSphere();
    mSize = .4;
    mLifetime = Random::GetInstance()->Real(2.0f,4.0f);
    mSpeed = Random::GetInstance()->Real(.5f,.9f);
    mColor = glm::vec4(Random::GetInstance()->GetPointOnUnitSphere(),1.0f);
    mCameraDistance = 100.0f;
}

void Particle::Update(float dt) {
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
    mDeadIndices.reserve(POOL_SIZE);
}

ParticleManager::~ParticleManager() {

}

void ParticleManager::Init() {
    mRenderer.Init();
    mModel = glm::mat4();
    mModel = glm::translate(mModel,glm::vec3(0.0f,1.0f,0.0f));
    mModel = glm::scale(mModel,glm::vec3(0.5f));
    for(int i =0 ; i< POOL_SIZE ; ++i)
    {
        Particle p;
        mParticles.push_back(p);
        mPositionScale.push_back(glm::vec4(0.0f));
        mColors.push_back(glm::vec4(0.0f));
        mDeadIndices.push_back(i);
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
    std::sort(mParticles.begin(),mParticles.end(),sortHelper);
}

void ParticleManager::Tick(const Camera& camera,double Deltatime)
{
    int newParticles = 2;
    CreateNewParticles(newParticles);
    SortParticles();
    mParticleCount = 0;
    for (int i = 0; i < POOL_SIZE; i++)
    {
        auto &particle = mParticles[i];
            if(particle.mLifetime > 0.0f)
            {
                particle.mSpeed -= (.1f *Deltatime);
                particle.mPosition += particle.mVelocity * (particle.mSpeed * float(Deltatime));
               // particle.mColor.a-=Deltatime;
                particle.mLifetime-=Deltatime;
                particle.mCameraDistance = glm::length(camera.GetPosition() - particle.mPosition);

                mPositionScale[mParticleCount].x = particle.mPosition.x;
                mPositionScale[mParticleCount].y = particle.mPosition.y;
                mPositionScale[mParticleCount].z = particle.mPosition.z;
                mPositionScale[mParticleCount].w = particle.mSize;
                mColors[mParticleCount] = particle.mColor;
                mParticleCount++;
            }
            else
            {
                mDeadIndices.push_back(i);
                particle.mCameraDistance = -1.0f;
            }

    }

    mView = camera.GetView();
    mModel[0][0] = mView[0][0];
    mModel[0][1] = mView[1][0];
    mModel[0][2] = mView[2][0];
    mModel[1][0] = mView[0][1];
    mModel[1][1] = mView[1][1];
    mModel[1][2] = mView[2][1];
    mModel[2][0] = mView[0][2];
    mModel[2][1]=  mView[1][2];
    mModel[2][2] = mView[2][2];

  //  SortParticles();
}

void ParticleManager::SetShaderValues()
{
    mRenderer.GetShader().SetMat4("view",mView);
    mRenderer.GetShader().SetMat4("model",mModel);
}
void ParticleManager::Render()
{
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    mRenderer.GetShader().Use();
    SetShaderValues();
    mRenderer.Render(mParticleCount,mPositionScale,mColors);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

