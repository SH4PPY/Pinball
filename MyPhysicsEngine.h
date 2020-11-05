#pragma once

#include "BasicActors.h"
#include "PhysicsEngine.h"
#include "MyActors.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;
	static int score = 0;
	static string objectName = "";

	static int lives = 5;
	//static bool gameEnd = false;

	struct FilterGroup
	{
		enum Enum
		{
			ACTOR0 = (1 << 0),	//Ball
			ACTOR1 = (1 << 1),	//bumper_1
			ACTOR2 = (1 << 2),	//bumper_2
			ACTOR3 = (1 << 3),	//bumper_3
			ACTOR4 = (1 << 4),	//bumper_4
			ACTOR5 = (1 << 5),	//bumper_5
			ACTOR6 = (1 << 6)	//return slope
			//add more if you need
		};
	};
	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		bool trigger;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						trigger = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			//cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					//cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
					//Used to manage collisons, to add score
					objectName = pairHeader.actors[1]->getName();
					if (objectName == "bumper_1" || objectName == "bumper_2" || objectName == "bumper_3" || objectName == "bumper_4" || objectName == "bumper_5")
					{
						score += 10;
						cerr << "Score: " << score << endl;	
					}
					//used to reset the score, if the ball collides with the return slope
					else if (objectName == "returnSlope")
					{
						score -= score;
						//gameEnd = true;
						//lives -= 1;
						//if (lives <= 0)
						//{
						//	score = 0;
						//	//gameEnd = true;
						//}
					}
					/*if (enableScore == false)
					{
						enableScore == true;
					}*/
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					//cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
//		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
			//pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
		PxPhysics* physics;
		PxFoundation* foundation;
		MySimulationEventCallback* my_callback;

		Trampoline* trampoline;
		Plane* plane;
		Cloth* cloth;
		Sphere* ball;
		Cloth* curtain;

		Box* returnSlope;
		Pyramid* pyramid;
		Curve_1* curve_1;
		Curve_2* curve_2;

		StaticBox* bumper_1;
		StaticBox* bumper_2;
		StaticBox* bumper_3;
		StaticBox* bumper_4;
		StaticBox* bumper_5;

		Box* spinner_1;
		Box* spinner_2;
		Box* spinner_3;
		Box* spinner_4;
		RevoluteJoint* spinnerJoint_1;
		RevoluteJoint* spinnerJoint_2;
		RevoluteJoint* spinnerJoint_3;
		RevoluteJoint* spinnerJoint_4;

	public:
		int scoreUpdate = 0;
		int livesUpdate;
		GameBoard* board;
		CompoundShape* plunger;

		Box* flipper_Left;
		Box* flipper_Right;
		RevoluteJoint* flipperJoint_Left;
		RevoluteJoint* flipperJoint_Right;

		Box* flipper_Left_2;
		Box* flipper_Right_2;
		RevoluteJoint* flipperJoint_Left_2;
		RevoluteJoint* flipperJoint_Right_2;

		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene(CustomFilterShader) {};

		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);

			//cloth visualisation
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_HORIZONTAL, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_VERTICAL, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_BENDING, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_SHEARING, 1.0f);
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			//Materials
			//setting the global dynamic friction
			GetMaterial()->setDynamicFriction(0.2f);
			//Creating multiple Materials
			for (int i = 0; i < 5; i++)
			{
				CreateMaterial(0.0f, 0.0f, 0.0f);
			}

			GetMaterial(0)->setRestitution(0.0f); //no bounce
			GetMaterial(1)->setRestitution(0.5f); //some bounce
			//For the Ball
			GetMaterial(2)->setRestitution(1.0f); //more bounce + no friction
			GetMaterial(2)->setDynamicFriction(0.0f);
			
			GetMaterial(3)->setRestitution(1.0f); //more bounce
			//Return Slope
			GetMaterial(4)->setRestitution(0.0f); //no bounce
			GetMaterial(4)->setDynamicFriction(0.0f); //No friction
			GetMaterial(4)->setStaticFriction(0.0f);

			//Initialise and set the customised event callback
			
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);
			//the pinball
			ball = new Sphere(PxTransform(PxVec3(47.0f, 2.0f, 100.f)));
			ball->Color(PxVec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
			ball->Material(GetMaterial(2));
			Add(ball);
			//plane for Y axis reference
			plane = new Plane();
			plane->Color(PxVec3(100.f/255.f,100.f/255.f,100.f/255.f));
			Add(plane);
			//plunger
			plunger = new CompoundShape(PxTransform(PxVec3(48.0f, 1.01f, 105.0f)), PxVec3(1.0f, 1.0f, 1.0f));
			plunger->Color(PxVec3(0.f / 255.f, 0.f / 255.f, 255.f / 255.f));
			plunger->Material(GetMaterial(0));
			Add(plunger);
			//Spinners
			spinner_1 = new Box(PxTransform(PxVec3(-15.0f, 3.0f, 0.0f)), PxVec3(1.0f, 5.0f, 0.1f));
			spinner_1->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
			spinnerJoint_1 = new RevoluteJoint(NULL, PxTransform(PxVec3(-15.0f, 3.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), spinner_1, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
			Add(spinner_1);
			spinnerJoint_1->DriveVelocity(1.5f);

			spinner_2 = new Box(PxTransform(PxVec3(15.0f, 3.0f, 0.0f)), PxVec3(1.0f, 5.0f, 0.1f));
			spinner_2->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
			spinnerJoint_2 = new RevoluteJoint(NULL, PxTransform(PxVec3(15.0f, 3.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), spinner_2, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
			Add(spinner_2);
			spinnerJoint_2->DriveVelocity(-1.5f);

			spinner_3 = new Box(PxTransform(PxVec3(-25.0f, 3.0f, 0.0f)), PxVec3(1.0f, 5.0f, 0.1f));
			spinner_3->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
			spinnerJoint_3 = new RevoluteJoint(NULL, PxTransform(PxVec3(-25.0f, 3.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), spinner_3, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
			Add(spinner_3);
			spinnerJoint_3->DriveVelocity(-1.5f);

			spinner_4 = new Box(PxTransform(PxVec3(25.0f, 3.0f, 0.0f)), PxVec3(1.0f, 5.0f, 0.1f));
			spinner_4->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
			spinnerJoint_4 = new RevoluteJoint(NULL, PxTransform(PxVec3(25.0f, 3.0f, 0.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), spinner_4, PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
			Add(spinner_4);
			spinnerJoint_4->DriveVelocity(1.5f);

			//flippers position, rotation, size
			//Lower Flippers
			flipper_Left = new Box(PxTransform(PxVec3(-15.2f, 3.0f, 75.0f)), PxVec3(1.0f, 5.0f, 0.1f));
			flipper_Left->Color(PxVec3(255.f / 255.f, 255.f / 255.f, 0.f / 255.f));
			flipper_Left->Material(GetMaterial(0));
			flipperJoint_Left = new RevoluteJoint(NULL, PxTransform(PxVec3(-15.2f, 3.0f, 75.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), flipper_Left, PxTransform(PxVec3(0.0f, 5.0f, 0.0f)));
			Add(flipper_Left);
			flipperJoint_Left->SetLimits(-(PxPi/4),(PxPi/4));
			flipperJoint_Left->DriveVelocity(-1.0f);
			
			flipper_Right = new Box(PxTransform(PxVec3(15.2f, 3.0f, 75.0f)), PxVec3(1.0f, 5.0f, 0.1f));
			flipper_Right->Color(PxVec3(255.f / 255.f, 255.f / 255.f, 0.f / 255.f));
			flipper_Right->Material(GetMaterial(0));
			flipperJoint_Right = new RevoluteJoint(NULL, PxTransform(PxVec3(15.2f, 3.0f, 75.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), flipper_Right, PxTransform(PxVec3(0.0f, -5.0f, 0.0f)));
			Add(flipper_Right);		
			flipperJoint_Right->SetLimits(-(PxPi/4),(PxPi/4));
			flipperJoint_Right->DriveVelocity(1.0f);

			//Upper Flippers
			flipper_Left_2 = new Box(PxTransform(PxVec3(-35.5f, 3.0f, 50.0f)), PxVec3(1.0f, 5.0f, 0.1f));
			flipper_Left_2->Color(PxVec3(255.f / 255.f, 255.f / 255.f, 0.f / 255.f));
			flipper_Left_2->Material(GetMaterial(0));
			flipperJoint_Left_2 = new RevoluteJoint(NULL, PxTransform(PxVec3(-35.5f, 3.0f, 50.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), flipper_Left_2, PxTransform(PxVec3(0.0f, 5.0f, 0.0f)));
			Add(flipper_Left_2);
			flipperJoint_Left_2->SetLimits(-(PxPi/4), (PxPi/4));
			flipperJoint_Left_2->DriveVelocity(-1.0f);

			flipper_Right_2 = new Box(PxTransform(PxVec3(35.5f, 3.0f, 50.0f)), PxVec3(1.0f, 5.0f, 0.1f));
			flipper_Right_2->Color(PxVec3(255.f / 255.f, 255.f / 255.f, 0.f / 255.f));
			flipper_Right_2->Material(GetMaterial(0));
			flipperJoint_Right_2 = new RevoluteJoint(NULL, PxTransform(PxVec3(35.5f, 3.0f, 50.0f), PxQuat(PxPi / 2, PxVec3(0.0f, 0.0f, 1.0f))), flipper_Right_2, PxTransform(PxVec3(0.0f, -5.0f, 0.0f)));
			Add(flipper_Right_2);
			flipperJoint_Right_2->SetLimits(-(PxPi/4), (PxPi/4));
			flipperJoint_Right_2->DriveVelocity(1.0f);
			
			//Board elements
			board = new GameBoard(PxTransform(PxVec3(0.0f, 1.0f, 0.0f)/*, PxQuat(PxPi/32, PxVec3(1.0f, 0.0f, 0.0f))*/));
			board->Color(PxVec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f), 0);
			board->Material(GetMaterial(4), 0);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 1);
			board->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f), 2);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 3);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 4);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 10);
			board->Material(GetMaterial(4), 10);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 11);
			board->Color(PxVec3(0.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 12);
			board->Material(GetMaterial(4), 12);
			board->Color(PxVec3(0.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 13);
			board->Material(GetMaterial(4), 13);
			board->Color(PxVec3(0.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 14);
			board->Material(GetMaterial(4), 14);
			board->Color(PxVec3(0.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 15);
			board->Material(GetMaterial(4), 15);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 16);
			//Top of curve
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 17);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 18);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 19);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 20);
			//Bottom of curve
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 21);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 22);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 23);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 24);
			//Curve Roof
			board->Color(PxVec3(0.0f / 255.0f, 155.0f / 255.0f, 0.0f / 255.0f), 25);
			board->Color(PxVec3(0.0f / 255.0f, 175.0f / 255.0f, 0.0f / 255.0f), 26);
			board->Color(PxVec3(0.0f / 255.0f, 200.0f / 255.0f, 0.0f / 255.0f), 27);
			board->Color(PxVec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f), 28);
			//Curve roof part 2
			board->Color(PxVec3(0.0f / 255.0f, 155.0f / 255.0f, 0.0f / 255.0f), 29);
			board->Color(PxVec3(0.0f / 255.0f, 175.0f / 255.0f, 0.0f / 255.0f), 30);
			board->Color(PxVec3(0.0f / 255.0f, 200.0f / 255.0f, 0.0f / 255.0f), 31);
			board->Color(PxVec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f), 32);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 33);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 34);
			board->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f), 35);
			Add(board);

			//Points bumpers
			//These bumpers are used to generate score, the longer the player keeps the ball bouncing around the bumpers the higher the score
			bumper_1 = new StaticBox(PxTransform(PxVec3(0.0f, 3.0f, 0.0f), PxQuat(PxPi / 4, PxVec3(0.0f, 1.0f, 0.0f))), PxVec3(5.0f, 1.0f, 5.0f));
			bumper_1->Color(PxVec3(0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f));
			bumper_1->Material(GetMaterial(3));
			bumper_1->Name("bumper_1");
			Add(bumper_1);

			bumper_2 = new StaticBox(PxTransform(PxVec3(25.0f, 3.0f, -30.0f), PxQuat(PxPi / 4, PxVec3(0.0f, 1.0f, 0.0f))), PxVec3(4.0f, 1.0f, 4.0f));
			bumper_2->Color(PxVec3(0.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
			bumper_2->Material(GetMaterial(3));
			bumper_2->Name("bumper_2");
			Add(bumper_2);

			bumper_3 = new StaticBox(PxTransform(PxVec3(-25.0f, 3.0f, -30.0f), PxQuat(PxPi / 4, PxVec3(0.0f, 1.0f, 0.0f))), PxVec3(4.0f, 1.0f, 4.0f));
			bumper_3->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
			bumper_3->Material(GetMaterial(3));
			bumper_3->Name("bumper_3");
			Add(bumper_3);

			bumper_4 = new StaticBox(PxTransform(PxVec3(0.0f, 3.0f, 50.0f), PxQuat(PxPi / 4, PxVec3(0.0f, 1.0f, 0.0f))), PxVec3(4.0f, 1.0f, 4.0f));
			bumper_4->Color(PxVec3(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f));
			bumper_4->Material(GetMaterial(3));
			bumper_4->Name("bumper_4");
			Add(bumper_4);

			bumper_5 = new StaticBox(PxTransform(PxVec3(0.0f, 3.0f,-60.0f), PxQuat(PxPi / 4, PxVec3(0.0f, 1.0f, 0.0f))), PxVec3(4.0f, 1.0f, 4.0f));
			bumper_5->Color(PxVec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
			bumper_5->Material(GetMaterial(3));
			bumper_5->Name("bumper_5");
			Add(bumper_5);

			//Semi-Circle Meshes
			curve_1 = new Curve_1(PxTransform(47.0f, 3.0f, -85.0f));
			curve_1->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f));
			curve_1->SetKinematic(true);
			Add(curve_1);

			curve_2 = new Curve_2(PxTransform(-49.0f, 3.0f, -85.0f));
			curve_2->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f));
			curve_2->SetKinematic(true);
			Add(curve_2);

			/*curtain = new Cloth(PxTransform(PxVec3(43.75f, 4.0f, -34.5f), PxQuat(0.4f, PxVec3(0.0f, 1.0f, 0.0f))), PxVec2(2.0f, 3.0f), PxU32(10.0f), PxU32(10.0f), true);
			curtain->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f));
			Add(curtain);*/

			//Top bouncy bit
			trampoline = new Trampoline(PxVec3(-1.0f, 3.0f, -80.0f), PxVec3(23.0f, 1.0f, 5.0f));
			trampoline->SetTopKinematic(true);
			trampoline->SetBottomMaterial();
			trampoline->AddToScene(this);

			//Cloth at the ball chute exit, Throws collision error messages if added...
			cloth = new Cloth(PxTransform(PxVec3(43.75f, 4.0f, -34.5f), PxQuat(0.4f, PxVec3(0.0f, 1.0f, 0.0f))), PxVec2(2.0f, 3.0f), PxU32(5.0f), PxU32(5.0f), true);
			cloth->Color(PxVec3(255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f));
			Add(cloth);

			//Ball return slope
			returnSlope = new Box(PxTransform(PxVec3(-2.0f, 3.0f, 92.5f), PxQuat(-(PxPi / 20), PxVec3(0.0f, 1.0f, 0.0f))), PxVec3(49.0f, 1.0f, 1.0f));
			returnSlope->Color(PxVec3(155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f));
			returnSlope->SetKinematic(true);
			returnSlope->Name("returnSlope");
			returnSlope->Material(GetMaterial(4));
			Add(returnSlope);

			//setting custom cloth parameters
			((PxCloth*)cloth->Get())->setStretchConfig(PxClothFabricPhaseType::eBENDING, PxClothStretchConfig(1.0f));
			((PxCloth*)cloth->Get())->setStretchConfig(PxClothFabricPhaseType::eVERTICAL, PxClothStretchConfig(1.0f));
			((PxCloth*)cloth->Get())->setStretchConfig(PxClothFabricPhaseType::eHORIZONTAL, PxClothStretchConfig(1.0f));

			//Collision filters
			ball->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1 | FilterGroup::ACTOR2 | FilterGroup::ACTOR3 | FilterGroup::ACTOR4 | FilterGroup::ACTOR5 | FilterGroup::ACTOR6);
			bumper_1->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR0);
			bumper_2->SetupFiltering(FilterGroup::ACTOR2, FilterGroup::ACTOR0);
			bumper_3->SetupFiltering(FilterGroup::ACTOR3, FilterGroup::ACTOR0);
			bumper_4->SetupFiltering(FilterGroup::ACTOR4, FilterGroup::ACTOR0);
			bumper_5->SetupFiltering(FilterGroup::ACTOR5, FilterGroup::ACTOR0);
			//Collision to set the score to zero is the ball falls below the flippers
			returnSlope->SetupFiltering(FilterGroup::ACTOR6, FilterGroup::ACTOR0);
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
			//Waking up the flippers
			PxQuat fl = flipper_Left->GetShape()->getLocalPose().q;
			flipper_Left->Get()->isRigidDynamic()->wakeUp();
			PxQuat fr = flipper_Right->GetShape()->getLocalPose().q;
			flipper_Right->Get()->isRigidDynamic()->wakeUp();
			PxQuat fl2 = flipper_Left_2->GetShape()->getLocalPose().q;
			flipper_Left_2->Get()->isRigidDynamic()->wakeUp();
			PxQuat fr2 = flipper_Right_2->GetShape()->getLocalPose().q;
			flipper_Right_2->Get()->isRigidDynamic()->wakeUp();
			//Used to update the score into a global variable to be used in VisualDebugger.cpp to show the score on the HUD
			scoreUpdate = score;
			livesUpdate = lives;
			//used to set the score to zero if the ball collides with the return slope
			//if (gameEnd = true)
			//{
			//	score = 0;
			//	gameEnd = false;
			//}
		}
		/// An example use of key release handling
		void ExampleKeyReleaseHandler()
		{
			cerr << "I am realeased!" << endl;
		}
		/// An example use of key presse handling
		void ExampleKeyPressHandler()
		{
			cerr << "I am pressed!" << endl;
		}
	};
}