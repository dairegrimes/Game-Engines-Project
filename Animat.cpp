#include "Animat.h"
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
#include "Utils.h"

using namespace BGE;

Animat::Animat(void)
{
}

Animat::~Animat(void)
{
}

shared_ptr<PhysicsController> cyl;
std::shared_ptr<GameComponent> station;

bool Animat::Initialise()
{

	Game::dynamicsWorld->setGravity(btVector3(0, -20, 0));
	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();
	legPos1 =		18;
	wheelPos =		14;
	spin =			100;
	speed =			0.5;


	shared_ptr<PhysicsController> body = physicsFactory->CreateBox(8, 5, 40, glm::vec3(0, 0, 0), glm::quat());

	shared_ptr<PhysicsController> head = physicsFactory->CreateBox(8, 5, 5, glm::vec3(0, 7, 17), glm::quat());
	btHingeConstraint * hinge5 = new btHingeConstraint(*body->rigidBody, *head->rigidBody, btVector3(0, 7, 17), btVector3(0, 2, 0), btVector3(0, 0, 0), btVector3(1, 0, 0), true);


	shared_ptr<PhysicsController> leg1 = physicsFactory->CreateBox(3, 10, 1, glm::vec3(9, 0, legPos1), glm::quat());
	btHingeConstraint * hinge1 = new btHingeConstraint(*body->rigidBody, *leg1->rigidBody, btVector3(9, 0, legPos1), btVector3(0, 2, 0), btVector3(0, 0, 0), btVector3(1, 0, 0), true);

	shared_ptr<PhysicsController> leg2 = physicsFactory->CreateBox(3, 10, 1, glm::vec3(-9, 0, legPos1), glm::quat());
	btHingeConstraint * hinge2 = new btHingeConstraint(*body->rigidBody, *leg2->rigidBody, btVector3(-9, 0, legPos1), btVector3(0, 2, 0), btVector3(0, 0, 0), btVector3(1, 0, 0), true);

	shared_ptr<PhysicsController> leg3 = physicsFactory->CreateCylinder(5, 3, glm::vec3(9, 0, -wheelPos), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	btHingeConstraint * hinge3 = new btHingeConstraint(*body->rigidBody, *leg3->rigidBody, btVector3(9, 0, -wheelPos), btVector3(1, 0, 0), btVector3(0, 0, 0), btVector3(0, 1, 0), true);

	shared_ptr<PhysicsController> leg4 = physicsFactory->CreateCylinder(5, 3, glm::vec3(-9, 0, -wheelPos), glm::angleAxis(90.0f, glm::vec3(0, 0, 1)));
	btHingeConstraint * hinge4 = new btHingeConstraint(*body->rigidBody, *leg4->rigidBody, btVector3(-9, 0, -wheelPos), btVector3(1, 0, 0), btVector3(0, 0, 0), btVector3(0, 1, 0), true);

	
	hinge1->setLimit(0, speed);
	hinge2->setLimit(0, speed);

	hinge1->enableAngularMotor(true, spin, spin);
	hinge2->enableAngularMotor(true, spin, spin);
	
	dynamicsWorld->addConstraint(hinge1);
	dynamicsWorld->addConstraint(hinge2);
	dynamicsWorld->addConstraint(hinge3);
	dynamicsWorld->addConstraint(hinge4);
	dynamicsWorld->addConstraint(hinge5);
	
	

	if (!Game::Initialise()) 
	{
		return false;
	}

	camera->transform->position = glm::vec3(0, 20, 40);

	return true;
}

void BGE::Animat::Update(float timeDelta)
{
	Game::Update(timeDelta);
}

void BGE::Animat::Cleanup()
{
	Game::Cleanup();
}
