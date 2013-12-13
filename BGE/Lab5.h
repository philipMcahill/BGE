#pragma once
#include "Game.h"
#include "GameComponent.h"
#include "FountainEffect.h"

#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include <btBulletDynamicsCommon.h>

#define NUM_FOUNTAINS 10
#define FOUNTAIN_RADIUS 50.0f
#define FOUNTAIN_HEIGHT 10.0f

#define NUM_enemies 10

using namespace std;

namespace BGE
{
	class Lab5 :
		public Game
	{
	public:
		Lab5(void);
		~Lab5(void);

		
		shared_ptr<GameComponent> ship2;
		shared_ptr<GameComponent> ship1;
		shared_ptr<GameComponent> ship3;
		shared_ptr<GameComponent> ship4;
		float elapsed;
		bool Initialise();
		void Update(float timeDelta);
		vector<shared_ptr<FountainEffect>> fountains;
		shared_ptr<FountainEffect> buddhaFountain0;
		shared_ptr<FountainEffect> magicMissile;
	

		float fountainTheta;
		glm::quat fromQuaternion;
		glm::quat toQuaternion;
		bool slerping;
		float t;
		float ySpeed;
		bool below;

		std::shared_ptr<PhysicsFactory> physicsFactory;
		btDiscreteDynamicsWorld * dynamicsWorld;

	};
}

