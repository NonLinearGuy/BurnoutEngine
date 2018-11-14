//
// Created by Ankit Singh on 11-11-2018.
//

#include "ParticleSystem.hpp"
#include"Random.h"
#include"android/log.h"
#include<algorithm>


//PARTICLE

void Particle::Reset() {
    mPosition = Random::GetInstance()->GetOnXZ(-.15f,.15f);
    mPosition.y = -.2f;
    mLifeTime = Random::GetInstance()->Real(1.5f,2.0f);
    mElapsedTime = 0.0f;
    mScale = glm::vec2(0.0f);
    mTexUnit = Random::GetInstance()->Integer(0,1);
    mAlpha = 1.0f;
    mVelocity = glm::vec4(0.0f);
    mRegionUpdateTime = mLifeTime/float(mTextureAtlas.GetFrames());
    mRegionUpdateElapsed = 0.0f;
    mCurrentFrame = 0;

    //min and max

    mMinScale = glm::vec2(1.0f);
    mMaxScale = glm::vec2(2.0f);

    mInitialVelocity.x = 0.0f;
    mInitialVelocity.y = Random::GetInstance()->Real(.5,2.0f);

    mFinalVelocity.x = 0.0f;
    mFinalVelocity.y =  0.0f;

    DUDV = glm::vec2(0.0f);

    mCurrentFrame = 0.0f;
}

void Particle::Update(float dt) {
        float weight = mElapsedTime / mLifeTime;
        mScale = MathUtils::Lerp<glm::vec2>(mMinScale,mMaxScale,weight);
        mVelocity = MathUtils::Lerp<glm::vec4>(mInitialVelocity,mFinalVelocity,weight);
        mPosition += (mVelocity * dt);
        mRegionUpdateElapsed += dt;
        mElapsedTime += dt;

    if(mRegionUpdateElapsed > mRegionUpdateTime)
        {
            mRegionUpdateElapsed = 0.0f;
            mCurrentFrame++;
            if(mCurrentFrame > mTextureAtlas.GetFrames()) {
                mCurrentFrame = mTextureAtlas.GetFrames();
            }

            int col = mCurrentFrame % mTextureAtlas.GetCols();
            int row = mCurrentFrame / mTextureAtlas.GetCols();

            //col = col > mTextureAtlas.GetCols() - 1 ? col - 1 : col;
            //row = row  > mTextureAtlas.GetRows() - 1 ? row - 1 : row;

            DUDV.x = ((mTextureAtlas.GetFrameSize().x * col) / mTextureAtlas.GetSize().x);
            DUDV.y = ((mTextureAtlas.GetFrameSize().y * row) / mTextureAtlas.GetSize().y);
        }

        if (mElapsedTime > mLifeTime)
        {
            Reset();
        }
}


//MANAGER
ParticleManager::ParticleManager() {
    mParticles.reserve(POOL_SIZE);
    mPositions.reserve(POOL_SIZE);
    mTexCoords.reserve(POOL_SIZE);
    mValues.reserve(POOL_SIZE);

}

ParticleManager::~ParticleManager() {

}

void ParticleManager::Init() {
    mFire.Load("textures/fire.png",8,8);
    mSmoke.Load("textures/smoke.png",8,8);

    mRenderer.Init();
    mModel = glm::mat4();
    mModel = glm::translate(mModel,glm::vec3(0.0f,0.0f,-4.0f));
    for(int i =0 ; i< POOL_SIZE ; ++i)
    {
        Particle p;
        int texUnit = Random::GetInstance()->Integer(0,1);
        p.mTexUnit = texUnit;
        if( 0 == texUnit )
            p.mTextureAtlas = mFire;
        else
            p.mTextureAtlas = mSmoke;
        mParticles.push_back(p);
        mPositions.push_back(glm::vec3(0.0f));
        mValues.push_back(glm::vec4(1.0f));
        mTexCoords.push_back(glm::vec2(0.0f));
    }

    for(int i =0 ; i< POOL_SIZE ; ++i)
    {
        mParticles[i].Reset();
    }
}

void ParticleManager::Destroy() {
    mParticles.clear();
    mPositions.clear();
    mValues.clear();
    mTexCoords.clear();
}



void ParticleManager::Tick(const Camera& camera,double Deltatime)
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        auto &particle = mParticles[i];
        particle.Update(Deltatime);
        mPositions[i] = glm::vec3(particle.mPosition);
        mTexCoords[i] = particle.DUDV;
        mValues[i].x = particle.mScale.x;
        mValues[i].y = particle.mScale.y;
        mValues[i].z = particle.mAlpha;
        mValues[i].w = particle.mTexUnit;
    }

    /* auto sortHelper = [camera](glm::vec3 position1, glm::vec3 position2)
        {
            float p1Distance = glm::length(camera.GetPosition() - position1);
            float p2Distance = glm::length(camera.GetPosition() - position2);

            return p1Distance < p2Distance;
        };

        std::sort(mPositions.begin(),mPositions.end(),sortHelper);*/

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
}

void ParticleManager::SetShaderValues()
{
    mRenderer.GetShader().SetMat4("view",mView);
    mRenderer.GetShader().SetMat4("model",mModel);
    mRenderer.GetShader().Set1i("fire",0);
    mRenderer.GetShader().Set1i("smoke",1);
    mRenderer.GetShader().SetVec2("frameSize",mFire.GetNormSize());
}
void ParticleManager::Render()
{
    mRenderer.GetShader().Use();
    SetShaderValues();
    mFire.BindToUnit(GL_TEXTURE0);
    mSmoke.BindToUnit(GL_TEXTURE1);
    mRenderer.Render(POOL_SIZE,mTexCoords,mPositions,mValues);
}

