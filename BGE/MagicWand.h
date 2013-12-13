#pragma once
#include "Camera.h"
#include "PhysicsController.h"
#include <btBulletDynamicsCommon.h>
#include "PhysicsFactory.h"
#include "FountainEffect.h"

namespace BGE
{

class MagicWand :
	public PhysicsController, public btMotionState 
	{


	private:
		PhysicsController * touching;
	public:
		MagicWand(PhysicsFactory * physicsFactory);
		~MagicWand(void);

		bool Initialise();
		void MagicWand::Update(float timeDelta);

		void getWorldTransform(btTransform &worldTrans) const;
		void setWorldTransform(const btTransform &worldTrans);
		PhysicsFactory * physicsFactory;
		float elapsed;
		float fireRate;
		shared_ptr<FountainEffect> magicBox;
	

	};

}

