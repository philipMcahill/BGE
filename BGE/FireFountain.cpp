#include "FireFountain.h"
#include "FountainEffect.h"
#include "ParticleEffect.h"



using namespace BGE;


FireFountain::FireFountain(void)
{
}


FireFountain::~FireFountain(void)
{
}


//void FireFountain::Initialise()
//{
//	
//	//buddhaFountain0 = make_shared<FountainEffect>(100);
//	position = glm::vec3(-30, 0, 0);
//	diffuse = glm::vec3(1,1, 0);
//	
//
//}

void FireFountain::Update( float timeDelta)
{

	float width = 500;
	float height = 500;
	float speed = 5.0f;
	if ((position.x < - (width / 2)) || (position.x > width / 2) || (position.z < - (height / 2)) || (position.z > height / 2) || (position.y < 0) || (position.y > 100))
	{
		alive = false;
	}
	position += look * speed;

}