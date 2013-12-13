#include "Assignment_main.h"
#include "Content.h"
#include "PhysicsController.h"
#include "Sphere.h"
#include "PhysicsCamera.h"
#include "Box.h"
#include "Cylinder.h"
#include "Steerable3DController.h"
#include "Ground.h"
#include "Content.h"
#include <btBulletDynamicsCommon.h>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/norm.hpp>
#include "VectorDrawer.h"
#include "MagicWand.h"
#include "FountainEffect.h"

using namespace BGE;

Assignment_main::Assignment_main(void)
{
	physicsFactory = NULL;
	dynamicsWorld = NULL;
	broadphase = NULL;
	dispatcher = NULL;
	solver = NULL;
	fullscreen = false;

}

Assignment_main::~Assignment_main(void)
{
}


std::shared_ptr<GameComponent> station;

bool Assignment_main::Initialise() 
{

	int j = 0;

	// Set up the collision configuration and dispatcher
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
    // The world.
	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	broadphase = new btAxisSweep3(worldMin,worldMax);
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,0,0));

	physicsFactory = make_shared<PhysicsFactory>(dynamicsWorld);

	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();
	


	//sparkle on end of wand
	magicsparkle = make_shared<FountainEffect>(nunParticals);
	magicsparkle->position = glm::vec3(-30, 0, 0);
	magicsparkle->diffuse = glm::vec3(0,0, 10);
	Attach(magicsparkle);



	/*magicBox = make_shared<FountainEffect>(0);
	magicBox->position = glm::vec3(0, 0, 0);
	magicBox->diffuse = glm::vec3(1,0, 0);
	Attach(magicBox);*/




	fountainTheta = 0.0f;

	for (int i = 0 ; i < num_enmies ; i ++)
	{

	

		fountainTheta = ((glm::pi<float>() * 2.0f) / num_enmies) * i;
			shared_ptr<PhysicsController> box4 = physicsFactory->CreateBox(1,1,1, glm::vec3(glm::sin(fountainTheta) * RADIUS, HEIGHT,
			- glm::cos(fountainTheta) * RADIUS), glm::quat());

			
			

		if (i % 2 == 0)
		{
			
				if (j % 2 == 0)
				{	

					magicsparkle = make_shared<FountainEffect>(100);
					magicsparkle->position = glm::vec3(-30, 0, 0);
					magicsparkle->diffuse = glm::vec3(0,0, 10);

					Attach(magicsparkle);		


					magicsparkle->Attach(box4);

				}
				else
				
				{

					magicsparkle = make_shared<FountainEffect>(100);
					magicsparkle->position = glm::vec3(-30, 0, 0);
					magicsparkle->diffuse = glm::vec3(0,1, 0);

					Attach(magicsparkle);		


					magicsparkle->Attach(box4);

				}
				j++;


		}
		
	}
	fountainTheta = 0.0f;

	
		
	//shared_ptr<PhysicsController> box1 = physicsFactory->CreateBox(1,1,4, glm::vec3(5, 5, 0), glm::quat());

	//std::shared_ptr<VectorDrawer> vectorDrawer= make_shared<VectorDrawer>();
	//vectorDrawer->scale = glm::vec3(5,5,10);
	//magicsparkle->Attach(vectorDrawer);

	//magicsparkle->Attach(box1);
	
	


	
	if (!Game::Initialise()) {
		return false;
	}

	return true;
}

void BGE::Assignment_main::Update(float timeDelta)
{



	//magicsparkle -> position = camera->position + camera->look;

	

	


	dynamicsWorld->stepSimulation(timeDelta,100);
	
	Game::Update(timeDelta);

	
}

void BGE::Assignment_main::Cleanup()
{
	Game::Cleanup();
}
