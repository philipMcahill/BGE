#pragma once
#include "Game.h"
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include <btBulletDynamicsCommon.h>

#include "PhysicsController.h"
#include "Sphere.h"
#include "PhysicsCamera.h"
#include "Box.h"
#include "Cylinder.h"
#include "Steerable3DController.h"
#include "Ground.h"
#include "Content.h"


#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/norm.hpp>
#include "VectorDrawer.h"

#include "MagicWand.h"
#include "FountainEffect.h"
#include "GameComponent.h"

#define num_enmies 20
#define RADIUS 40.0f
#define HEIGHT 10.0f

namespace BGE
{
	class Assignment_main :
		public Game
	{
	private:



		btBroadphaseInterface* broadphase;
 
		// Set up the collision configuration and dispatcher
		btDefaultCollisionConfiguration * collisionConfiguration;
		btCollisionDispatcher * dispatcher;
 
		// The actual physics solver
		btSequentialImpulseConstraintSolver * solver;

	public:
		Assignment_main(void);
		~Assignment_main(void);
		bool Initialise();
		void Update(float timeDelta);
		void Cleanup();
		void CreateWall();

		float fountainTheta;
		glm::quat fromQuaternion;
		glm::quat toQuaternion;
		bool slerping;
		float t;
		float ySpeed;
		bool below;
		float what;
		float x;
		float y;
		float z;

		shared_ptr<FountainEffect> magicsparkle;
		shared_ptr<FountainEffect> magicBox;
		shared_ptr<PhysicsController> box4;
		
		// The world.
		std::shared_ptr<PhysicsFactory> physicsFactory;
		btDiscreteDynamicsWorld * dynamicsWorld;
	};
}
