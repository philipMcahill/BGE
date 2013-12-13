#include "MagicWand.h"
#include "Game.h"
#include "PhysicsGame1.h"
#include "Box.h"
#include <iostream>
#include <sstream>
#include "Utils.h"
#include "FountainEffect.h"
using namespace BGE;






MagicWand::MagicWand(PhysicsFactory * physicsFactory):PhysicsController()
{

	elapsed = 10000.0f;
	fireRate = 5.0f;
	touching = NULL;
	tag = "Magic wand";
	this->physicsFactory = physicsFactory;


}

bool MagicWand::Initialise()
{

	magicBox = make_shared<FountainEffect>(100);
	magicBox->position = glm::vec3(1, 0, 0);
	magicBox->diffuse = glm::vec3(1,1, 1);
	Attach(magicBox);


		return true;
}

MagicWand::~MagicWand(void)
{


}


void MagicWand::getWorldTransform(btTransform &worldTrans) const
{

	worldTrans.setOrigin(GLToBtVector(parent->position));
	worldTrans.setRotation(GLToBtQuat(parent->orientation));

}

void MagicWand::setWorldTransform(const btTransform &worldTrans)
{

}


void MagicWand::Update(float timeDelta)
{
	
	const Uint8 * keyState = Game::Instance()->GetKeyState();
	Game * game = Game::Instance();

	float moveSpeed = speed;
	float timeToPass = 1.0f / fireRate;

	string what = "Nothing";



		if (keyState[SDL_SCANCODE_R])
	{
		float dist = 1000.0f;
		if (touching == NULL)
		{		
			// Has to be some distance in front of the camera otherwise it will collide with the camera all the time
			btVector3 rayFrom = GLToBtVector(parent->position + (parent->look * 4.0f)); 
			btVector3 rayTo = GLToBtVector(parent->position + (parent->look * dist));

			btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);
			physicsFactory->dynamicsWorld->rayTest(rayFrom, rayTo, rayCallback);
			
			if (rayCallback.hasHit())
			{
				touching = reinterpret_cast<PhysicsController*>(rayCallback.m_collisionObject->getUserPointer());
				
				if (touching->parent == game->GetGround().get())
				{
					
					touching = NULL;
				}
			}
		}



		if (touching != NULL)
		{
		
			float powerfactor = 4.0f; // Higher values causes the targets moving faster to the holding point.
            float maxVel = 3.0f;      // Lower values prevent objects flying through walls.
			float holdDist = 6.0f;

            // Calculate the hold point in front of the camera
			glm::vec3 holdPos = parent->position + (parent->look * holdDist);

            glm::vec3 v = holdPos; // direction to move the Target
            v += powerfactor; // powerfactor of the GravityGun

 			
			//touching->Fly(powerfactor);
			touching->rigidBody->setGravity(GLToBtVector(v));
			touching->rigidBody->activate();

			what = touching->tag;

		}

	}
	else
	{    
		touching = NULL;
	}



	if (keyState[SDL_SCANCODE_E])
	{
		float dist = 1000.0f;
		if (touching == NULL)
		{		
			// Has to be some distance in front of the camera otherwise it will collide with the camera all the time
			btVector3 rayFrom = GLToBtVector(parent->position + (parent->look * 4.0f)); 
			btVector3 rayTo = GLToBtVector(parent->position + (parent->look * dist));

			btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);
			physicsFactory->dynamicsWorld->rayTest(rayFrom, rayTo, rayCallback);
			
			if (rayCallback.hasHit())
			{
				touching = reinterpret_cast<PhysicsController*>(rayCallback.m_collisionObject->getUserPointer());
				
				if (touching->parent == game->GetGround().get())
				{
					
					touching = NULL;
				}
			}
		}



		if (touching != NULL)
		{
		
			float powerfactor = 4.0f; // Higher values causes the targets moving faster to the holding point.
            float maxVel = 3.0f;      // Lower values prevent objects flying through walls.
			float holdDist = 6.0f;

            // Calculate the hold point in front of the camera
			glm::vec3 holdPos = parent->position + (parent->look * holdDist);

            glm::vec3 v = holdPos; // direction to move the Target
            v -= powerfactor; // powerfactor of the GravityGun

 			
			touching->rigidBody->setGravity(GLToBtVector(v));   
			touching->rigidBody->activate();

			what = touching->tag;

		}

	}
	else
	{    
		touching = NULL;
	}




	if (keyState[SDL_SCANCODE_W])
	{
		float dist = 1000.0f;
		if (touching == NULL)
		{		
			// Has to be some distance in front of the camera otherwise it will collide with the camera all the time
			btVector3 rayFrom = GLToBtVector(parent->position + (parent->look * 4.0f)); 
			btVector3 rayTo = GLToBtVector(parent->position + (parent->look * dist));

			btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);
			physicsFactory->dynamicsWorld->rayTest(rayFrom, rayTo, rayCallback);
			
			if (rayCallback.hasHit())
			{
				touching = reinterpret_cast<PhysicsController*>(rayCallback.m_collisionObject->getUserPointer());
				
				if (touching->parent == game->GetGround().get())
				{
					
					touching = NULL;
				}
			}
		}



		if (touching != NULL)
		{
		
			float powerfactor = 4.0f; // Higher values causes the targets moving faster to the holding point.
            float maxVel = 3.0f;      // Lower values prevent objects flying through walls.
			float holdDist = 6.0f;

            // Calculate the hold point in front of the camera
			glm::vec3 holdPos = parent->position + (parent->look * holdDist);

            glm::vec3 v = holdPos; // direction to move the Target
           // v += powerfactor; // powerfactor of the GravityGun

            if (v.length() > maxVel)
            {
                
				v = glm::normalize(v);
                v *= maxVel; // just set correction-velocity to the maximum
            }
			
			touching->rigidBody->setAngularVelocity(GLToBtVector(v));   
			touching->rigidBody->activate();

			what = touching->tag;

		}

	}
	else
	{    
		touching = NULL;
	}
	
	if (keyState[SDL_SCANCODE_Q])
	{
		float dist = 1000.0f;
		if (touching == NULL)
		{		
			// Has to be some distance in front of the camera otherwise it will collide with the camera all the time
			btVector3 rayFrom = GLToBtVector(parent->position + (parent->look * 4.0f)); 
			btVector3 rayTo = GLToBtVector(parent->position + (parent->look * dist));

			btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);
			physicsFactory->dynamicsWorld->rayTest(rayFrom, rayTo, rayCallback);
			
			if (rayCallback.hasHit())
			{
				touching = reinterpret_cast<PhysicsController*>(rayCallback.m_collisionObject->getUserPointer());
				
				if (touching->parent == game->GetGround().get())
				{
					
					touching = NULL;
				}
			}
		}



		if (touching != NULL)
		{
		
			float powerfactor = 4.0f; // Higher values causes the targets moving faster to the holding point.
            float maxVel = 3.0f;      // Lower values prevent objects flying through walls.
			float holdDist = 6.0f;

            // Calculate the hold point in front of the camera
			glm::vec3 holdPos = parent->position + (parent->look * holdDist);

            glm::vec3 v = holdPos; // direction to move the Target
           // v += powerfactor; // powerfactor of the GravityGun

            if (v.length() > maxVel)
            {
                
				v = glm::normalize(v);
                v *= maxVel; // just set correction-velocity to the maximum
            }
			
			touching->rigidBody->translate(GLToBtVector(v));   
			touching->rigidBody->activate();

			what = touching->tag;

		}

	}
	else
	{    
		touching = NULL;
	}

	

	stringstream ss;
	ss << "Touching up: " << what;
	game->PrintText(ss.str());

	
}

