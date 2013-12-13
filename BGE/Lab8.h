#pragma once
#include "Game.h"
#include "GameComponent.h"
#include "FountainEffect.h"

#define NUM_FOUNTAINS 10
#define FOUNTAIN_RADIUS 50.0f
#define FOUNTAIN_HEIGHT 60.0f

using namespace std;

namespace BGE
{
	class Lab8 :
		public Game
	{
	public:
		Lab8(void);
		~Lab8(void);

		shared_ptr<GameComponent> ship1;
		shared_ptr<GameComponent> ship3;
		float elapsed;
		bool Initialise();
		void Update(float timeDelta);

		vector<shared_ptr<FountainEffect>> fountains;
		float fountainTheta;

		glm::vec3 force;
		float mass;
	};
}

