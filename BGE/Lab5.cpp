#include "Lab5.h"
#include "Content.h"
#include "VectorDrawer.h"
#include<iostream>  

#include "LazerBeam.h"
#include "FountainEffect.h"
#include "LazerBeam.h"
#include "FireFountain.h"




#include "PhysicsGame1.h"
#include "PhysicsController.h"
#include "PhysicsCamera.h"
#include "Box.h"
#include "Steerable3DController.h"
#include "Ground.h"
#include "Content.h"
#include <btBulletDynamicsCommon.h>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/norm.hpp>
#include "VectorDrawer.h"

using namespace BGE;

Lab5::Lab5(void)
{
	elapsed = 10000;
}


Lab5::~Lab5(void)
{
}

bool Lab5::Initialise()
{
	
	bool below = false;

	//GameComponent shipArray[];
	std::list<GameComponent> enemylist;
	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);	

	ship1 = make_shared<GameComponent>();
	ship1->Attach(Content::LoadModel("cobramk3", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0,1,0))));
	ship1->position = glm::vec3(-10, 15, -10);
	ship1->Attach(make_shared<VectorDrawer>());
	Attach(ship1);

	ship1->position.y = 21;

	ship3 = make_shared<GameComponent>();
	ship3->Attach(Content::LoadModel("cobramk3", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0,1,0))));
	ship3->position = glm::vec3(-15, 5, -10);
	ship3->Attach(make_shared<VectorDrawer>());
	Attach(ship3);


	
	//ship2->drawMode = GameComponent::single_material;



	riftEnabled = false;
	fullscreen = false;
	width = 800;
	height = 600;

	// 500 in the constructor indicates the number of particles in the effect. 
	// You may need to compile in release mode or reduce the number of particles to get an acceptable framerate
	/*shared_ptr<FountainEffect> centFountain = make_shared<FountainEffect>(500);
	centFountain->position.x = centFountain->position.y = 0;
	centFountain->position.y = FOUNTAIN_HEIGHT;
	centFountain->diffuse = glm::vec3(1,1,0);

	Attach(centFountain);*/

	buddhaFountain0 = make_shared<FountainEffect>(10);
	buddhaFountain0->position = glm::vec3(-30, 0, 0);
	buddhaFountain0->diffuse = glm::vec3(1,1, 1);
	Attach(buddhaFountain0);

	magicMissile =  make_shared<FountainEffect>(100);
	Attach(magicMissile);

	// make a circle of fountains
	
	
	//fountainTheta = 0.0f; 
	//for (int i = 0 ; i < NUM_FOUNTAINS ; i ++)
	//{
	//	fountainTheta = ((glm::pi<float>() * 2.0f) / NUM_FOUNTAINS) * i;
	//	shared_ptr<FountainEffect> fountain = make_shared<FountainEffect>(500);
	//	if (i % 2 == 0)
	//	{
	//		fountain->diffuse = glm::vec3(1,0,0);
	//	}
	//	else
	//	{
	//		fountain->diffuse = glm::vec3(0,1,0);
	//	}
	//	
	//	fountain->position.x = glm::sin(fountainTheta) * FOUNTAIN_RADIUS;
	//	fountain->position.z = - glm::cos(fountainTheta) * FOUNTAIN_RADIUS;
	//	fountain->position.y = FOUNTAIN_HEIGHT;
	//	fountains.push_back(fountain);
	//	Attach(fountain);
	//}



		
	/*	ship4->diffuse= glm::vec3(1.0f,0.0f,0.0f);
		ship4->specular = glm::vec3(1.2f, 1.2f, 1.2f);
		ship4->position = glm::vec3(5, 2, -10);*/
		//Attach(ship4);

	fountainTheta = 0.0f;

	for (int i = 0 ; i < NUM_FOUNTAINS ; i ++)
	{
		fountainTheta = ((glm::pi<float>() * 2.0f) / NUM_FOUNTAINS) * i;
		ship4 = make_shared<GameComponent>();
		ship4->Attach(Content::LoadModel("cobramk3", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0,1,0))));
		ship4->Attach(make_shared<VectorDrawer>());

		ship4->position.x = glm::sin(fountainTheta) * FOUNTAIN_RADIUS;
		ship4->position.z = - glm::cos(fountainTheta) * FOUNTAIN_RADIUS;
		ship4->position.y = FOUNTAIN_HEIGHT;
	
		Attach(ship4);
	}



	fountainTheta = 0.0f;
	
		ship2 = make_shared<GameComponent>();
		ship2->Attach(Content::LoadModel("cobramk3", glm::rotate(glm::mat4(1), 180.0f, glm::vec3(0,1,0))));
		ship2->Attach(make_shared<VectorDrawer>());
		ship2->diffuse= glm::vec3(1.0f,0.0f,0.0f);
		ship2->specular = glm::vec3(1.2f, 1.2f, 1.2f);
		ship2->position = glm::vec3(5, 2, -10);
		Attach(ship2); 
	
	
	

	t = 0.0f;

	Game::Initialise();

	camera->GetController()->position = glm::vec3(0, 4, 0);
	return true;
}




void Lab5::Update(float timeDelta)
{	

		
		//player
	
		buddhaFountain0 -> position = camera->position + camera->look;

	
	

	if (keyState[SDL_SCANCODE_Z])
	{
		shared_ptr<FireFountain> lazer = make_shared<FireFountain>();
		lazer->position = camera->position + camera->look;
		lazer->look = camera->look;
		Attach(lazer);
		elapsed = 0.0f;
	}

	
			

		




		//enemy code

		slerping = true;
		fromQuaternion = ship2->orientation;

		glm::vec3 toCamera = camera->position - ship2->position;
		toCamera = glm::normalize(toCamera);
		glm::vec3 axis = glm::cross(GameComponent::basisLook, toCamera);
		axis = glm::normalize(axis);
		float theta = glm::acos(glm::dot(toCamera, GameComponent::basisLook));
		toQuaternion = glm::angleAxis(glm::degrees(theta), axis);
	

		if (slerping)
	{
		ship2->orientation = glm::mix(fromQuaternion, toQuaternion, t);
		t += timeDelta;
		if (t > 1.0f)
		{
			t = 0.0f;
			slerping = false;
		}
	}








	//ship1->position.x = glm::sin(fountainTheta) * -30;
	//ship1->position.z = glm::cos(fountainTheta) * 30;
	






		

		if (ship1->position.y > 20) 
		
		{ 
			
			below = true;
		
		} else
			
			if(ship1->position.y < 5) 
			
			{ 
				
				below = false;
			} 
		
		if(below)

		{ 

			
			ship1->FlyDown(speed * timeDelta); 

		} else 

		{ 
			
			ship1->Fly(speed * timeDelta);
		
		}










	//ship1->FlyDown(speed * timeDelta);

	//if (ship1->position.y > 50)
	//{

	//	
	//	ship1->FlyDown(speed * timeDelta);
	//	//ship1->position.y = 50;
	//	
	//}

	//else if (ship1->position.y < 5)
	//{

	//	
	//	ship1->Fly(speed * timeDelta);
	//	//ship1->position.y = 5;
	//	
	//}


















	if (keyState[SDL_SCANCODE_Z])
	{
		ship4->Fly(speed * timeDelta);
	}

		if (keyState[SDL_SCANCODE_X])
	{
		ship4->FlyDown(speed * timeDelta);
	}
		

	

		ship3->Strafe(speed * timeDelta);

	if (slerping)
	{
		ship3->orientation = glm::mix(fromQuaternion, toQuaternion, t);
		t += timeDelta;
		if (t > 1.0f)
		{
			t = 0.0f;
			slerping = false;
		}
		
	}





	

	Game::Update(timeDelta);

}
