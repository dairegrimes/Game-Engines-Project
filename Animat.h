#pragma once
#include "Game.h"
#include "PhysicsController.h"
#include "PhysicsFactory.h"
#include <btBulletDynamicsCommon.h>

namespace BGE
{
	class Animat:
		public Game
	{
	private:

		float speed;
		
	public:
		Animat(void);
		~Animat(void);
		bool Initialise();
		void Update(float timeDelta);
		void Cleanup();
		void CreateWall();		
	};
}
