#pragma once
#include "GameComponent.h"
#include "FountainEffect.h"
#include "ParticleEffect.h"

namespace BGE
{
class FireFountain :
		public GameComponent
{
	public:
		FireFountain(void);
		~FireFountain(void);
			//void Initialise();
			void Update(float timeDelta);
	};
}

