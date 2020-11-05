#pragma once

#include "PhysicsEngine.h"
#include "MyPhysicsEngine.h"
#include "BasicActors.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	//Two semi circle meshes, pointing in different directions
	/*	//Small Curve coords
	//bottom of curve
	PxVec3(0.0f, -1.0f, -2.5f),		//0
	PxVec3(0.77f, -1.0f , -2.37f),	//1
	PxVec3(1.5f, -1.0f, -2.0f),		//2
	PxVec3(2.00f, -1.0f, -1.47f),	//3
	PxVec3(2.37f, -1.0f, -0.77f),	//4
	PxVec3(2.5f, -1.0f, 0.0f),		//5
	PxVec3(2.37f, -1.0f, 0.77f),	//6
	PxVec3(2.0f, -1.0f, 1.47f),		//7
	PxVec3(1.47f, -1.0f, 2.0f),		//8
	PxVec3(0.77f, -1.0f, 2.37f),	//9
	PxVec3(0.0f, -1.0f, 2.5f),		//10
	//top of curve
	PxVec3(0.0f, 1.0f, -2.5f),		//11
	PxVec3(0.77f, 1.0f, -2.37f),	//12
	PxVec3(1.47f, 1.0f, -2.0f),		//13
	PxVec3(2.0f, 1.0f, -1.47f),		//14
	PxVec3(2.37f, 1.0f, -.77f),		//15
	PxVec3(2.5f, 1.0f, 0.0f),		//16
	PxVec3(2.37f, 1.0f, 0.77f),		//17
	PxVec3(2.0f, 1.0f, 1.47f),		//19
	PxVec3(1.47f, 1.0f, 2.0f),		//20
	PxVec3(0.77f, 1.0f, 2.37f),		//21
	PxVec3(0.0f, 1.0f, 2.5f)		//22
	*/
	static PxVec3 curve_1_verts[] = {
		//bottom of curve
		PxVec3(0.0f, -1.0f, -25.0f),	//0
		PxVec3(-07.7f, -1.0f, -23.7f),	//1
		PxVec3(-15.f, -1.0f, -20.f),	//2
		PxVec3(-20.0f, -1.0f, -14.7f),	//3
		PxVec3(-23.7f, -1.0f, -07.7f),	//4
		PxVec3(-25.0f, -1.0f, 0.0f),	//5
		PxVec3(-23.7f, -1.0f, 07.7f),	//6
		PxVec3(-20.0f, -1.0f, 14.7f),	//7
		PxVec3(-14.7f, -1.0f, 20.0f),	//8
		PxVec3(-07.7f, -1.0f, 23.7f),	//9
		PxVec3(0.0f, -1.0f, 25.0f),		//10
		//top of curve
		PxVec3(0.0f, 1.0f, -25.0f),		//11
		PxVec3(-07.7f, 1.0f, -23.7f),	//12
		PxVec3(-14.7f, 1.0f, -20.0f),	//13
		PxVec3(-20.0f, 1.0f, -14.7f),	//14
		PxVec3(-23.7f, 1.0f, -7.7f),	//15
		PxVec3(-25.0f, 1.0f, 0.0f),		//16
		PxVec3(-23.7f, 1.0f, 07.7f),	//17
		PxVec3(-20.0f, 1.0f, 14.7f),	//19
		PxVec3(-14.7f, 1.0f, 20.0f),	//20
		PxVec3(-07.7f, 1.0f, 23.7f),	//21
		PxVec3(0.0f, 1.0f, 25.0f)		//22
	};
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 curve_1_trigs[] = { 12, 11, 0, 1, 13, 12, 1, 2, 14, 13, 2, 3, 15, 14, 3, 4, 16, 15, 4, 5, 17, 16, 5, 6, 18, 17, 6, 7, 19, 18, 7, 8, 20, 19, 8, 9, 21, 20, 9, 10, };

	class Curve_1 : public ConvexMesh
	{
	public:
		Curve_1(PxTransform pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(curve_1_verts), end(curve_1_verts)), pose, density)
		{
		}
	};

	static PxVec3 curve_2_verts[] = {
		//bottom of curve
		PxVec3(0.0f, -1.0f, -25.0f),	//0
		PxVec3(07.7f, -1.0f, -23.7f),	//1
		PxVec3(15.f, -1.0f, -20.f),	//2
		PxVec3(20.0f, -1.0f, -14.7f),	//3
		PxVec3(23.7f, -1.0f, -07.7f),	//4
		PxVec3(25.0f, -1.0f, 0.0f),	//5
		PxVec3(23.7f, -1.0f, 07.7f),	//6
		PxVec3(20.0f, -1.0f, 14.7f),	//7
		PxVec3(14.7f, -1.0f, 20.0f),	//8
		PxVec3(07.7f, -1.0f, 23.7f),	//9
		PxVec3(0.0f, -1.0f, 25.0f),		//10
		//top of curve
		PxVec3(0.0f, 1.0f, -25.0f),		//11
		PxVec3(07.7f, 1.0f, -23.7f),	//12
		PxVec3(14.7f, 1.0f, -20.0f),	//13
		PxVec3(20.0f, 1.0f, -14.7f),	//14
		PxVec3(23.7f, 1.0f, -7.7f),	//15
		PxVec3(25.0f, 1.0f, 0.0f),		//16
		PxVec3(23.7f, 1.0f, 07.7f),	//17
		PxVec3(20.0f, 1.0f, 14.7f),	//19
		PxVec3(14.7f, 1.0f, 20.0f),	//20
		PxVec3(07.7f, 1.0f, 23.7f),	//21
		PxVec3(0.0f, 1.0f, 25.0f)		//22
	};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 curve_2_trigs[] = { 12, 11, 0, 1, 13, 12, 1, 2, 14, 13, 2, 3, 15, 14, 3, 4, 16, 15, 4, 5, 17, 16, 5, 6, 18, 17, 6, 7, 19, 18, 7, 8, 20, 19, 8, 9, 21, 20, 9, 10, };

	class Curve_2 : public ConvexMesh
	{
	public:
		Curve_2(PxTransform pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(curve_2_verts), end(curve_2_verts)), pose, density)
		{
		}
	};

	static PxVec3 pyramid_verts[] = { PxVec3(0, 1, 0), PxVec3(1, 0, 0), PxVec3(-1, 0, 0), PxVec3(0, 0, 1), PxVec3(0, 0, -1) };
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = { 1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1 };
	//pyramid
	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts), end(pyramid_verts)), pose, density)
		{
		}
	};
	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts), end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs), end(pyramid_trigs)), pose)
		{
		}
	};
	//A class showing the use of springs (distance joints).
	class Trampoline
	{
		vector<DistanceJoint*> springs;
		Box *bottom, *top;
	public:

		Trampoline(PxVec3 position, const PxVec3& dimensions = PxVec3(1.f, 1.f, 1.f), PxReal stiffness = 10.0f, PxReal damping = 1.0f)
		{
			//Trampoline in the Z axis
			PxReal thickness = 0.1f;
			bottom = new Box(PxTransform(PxVec3(position.x, position.y, position.z)), PxVec3(dimensions.x, dimensions.y, thickness));
			top = new Box(PxTransform(PxVec3(position.x, position.y, position.z - (dimensions.z - thickness))), PxVec3(dimensions.x, dimensions.y, thickness));
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, dimensions.y, thickness)), top, PxTransform(PxVec3(dimensions.x, dimensions.y, dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, -dimensions.y, thickness)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, dimensions.y, thickness)), top, PxTransform(PxVec3(-dimensions.x, dimensions.y, dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, -dimensions.y, thickness)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, dimensions.z)));

			//trampoline in the Y axis
			/*
			bottom = new Box(PxTransform(PxVec3(0.f, thickness, 0.f)), PxVec3(dimensions.x, thickness, dimensions.z));
			top = new Box(PxTransform(PxVec3(0.f, dimensions.y + thickness, 0.f)), PxVec3(dimensions.x, thickness, dimensions.z));
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, -dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, -dimensions.z)));
			*/

			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
			}
		}
		void SetBottomKinematic(bool)
		{
			bottom->SetKinematic(true);
		}
		void SetTopKinematic(bool)
		{
			top->SetKinematic(true);
		}
		void SetBottomMaterial()
		{
			bottom->Material(CreateMaterial(0.0f, 0.0f, 1.0f));
		}
		void SetTopMaterial()
		{
			top->Material(CreateMaterial(0.0f, 0.0f, 1.0f));
		}
		void AddToScene(Scene* scene)
		{
			scene->Add(bottom);
			scene->Add(top);
		}

		~Trampoline()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}
	};

	//Compund Actor
	class CompoundShape : public DynamicActor
	{
	public:
		CompoundShape(PxTransform pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(0.0f, 0.0f, 30.0f)));
		}
	};

	class StaticBox : public StaticActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		StaticBox(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};
	class GameBoard : public StaticActor
	{
	public:
		GameBoard(PxTransform pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(0.5f, .5f, 0.5f), PxReal density = 1.0f)
			: StaticActor(pose)
		{
			//Base
			CreateShape(PxBoxGeometry(50.0f, 1.0f, 100.0f), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));

			//Walls
			//Bottom
			CreateShape(PxBoxGeometry(PxVec3(48.0f, 1.0f, 1.0f)), density);
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-3.0f, 2.0f, 100.0f)));
			//Top
			CreateShape(PxBoxGeometry(PxVec3(48.0f, 1.0f, 8.0f)), density);
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-1.0f, 2.0f, -93.0f)));
			
			//Sides
			CreateShape(PxBoxGeometry(PxVec3(1.0f, 1.0f, 101.0f)), density);
			GetShape(3)->setLocalPose(PxTransform(PxVec3(50.0f, 2.0f, 0.0f)));

			CreateShape(PxBoxGeometry(PxVec3(1.0f, 1.0f, 101.0f)), density);
			GetShape(4)->setLocalPose(PxTransform(PxVec3(-50.0f, 2.0f, 0.0f)));

			//Plunger
			CreateShape(PxBoxGeometry(PxVec3(1.0f, 1.5f, 15.0f)), density);
			GetShape(5)->setLocalPose(PxTransform(PxVec3(45.9f, 2.0f, 115.0f)));
			CreateShape(PxBoxGeometry(PxVec3(1.0f, 1.5f, 15.0f)), density);
			GetShape(6)->setLocalPose(PxTransform(PxVec3(50.0f, 2.0f, 115.0f)));
			CreateShape(PxBoxGeometry(PxVec3(3.0f, 3.0f, 1.0f)), density);
			GetShape(7)->setLocalPose(PxTransform(PxVec3(48.0f, 2.0f, 130.0f)));
			CreateShape(PxBoxGeometry(PxVec3(3.0f, 1.0f, 15.0f)), density);
			GetShape(8)->setLocalPose(PxTransform(PxVec3(48.0f, 4.1f, 115.0f)));
			CreateShape(PxBoxGeometry(PxVec3(3.0f, 1.0f, 15.0f)), density);
			GetShape(9)->setLocalPose(PxTransform(PxVec3(48.0f, 0.0f, 115.0f)));

			//Ball return slope
			CreateShape(PxBoxGeometry(PxVec3(49.0f, 1.0f, 1.0f)), density);
			GetShape(10)->setLocalPose(PxTransform(PxVec3(-2.0f, 2.0f, 92.6f), PxQuat(-(PxPi / 20), PxVec3(0.0f, 1.0f, 0.0f))));

			//PlungerSlide-Table
			CreateShape(PxBoxGeometry(PxVec3(1.0f, 1.0f, 60.0f)), density);
			GetShape(11)->setLocalPose(PxTransform(PxVec3(45.9f, 2.0f, 36.0f)));

			//stuff to bounce off of
			CreateShape(PxBoxGeometry(PxVec3(12.5f, 1.0f, 1.0f)), density);
			GetShape(12)->setLocalPose(PxTransform(PxVec3(27.5f, 2.0f, 73.5f), PxQuat((PxPi / 16), PxVec3(0.0f, 1.0f, 0.0f))));
			
			CreateShape(PxBoxGeometry(PxVec3(15.0f, 1.0f, 1.0f)), density);
			GetShape(13)->setLocalPose(PxTransform(PxVec3(-30.0f, 2.0f, 73.0f), PxQuat(-(PxPi / 16), PxVec3(0.0f, 1.0f, 0.0f))));

			CreateShape(PxBoxGeometry(PxVec3(7.5f, 1.0f, 1.0f)), density);
			GetShape(14)->setLocalPose(PxTransform(PxVec3(-43.0f, 2.0f, 49.5f), PxQuat(-(PxPi / 16), PxVec3(0.0f, 1.0f, 0.0f))));

			CreateShape(PxBoxGeometry(PxVec3(5.0f, 1.0f, 1.0f)), density);
			GetShape(15)->setLocalPose(PxTransform(PxVec3(41.0f, 2.0f, 50.0f), PxQuat((PxPi / 16), PxVec3(0.0f, 1.0f, 0.0f))));

			//Ball Chute...
			//Manually, until I can figure out mesh...
			//To do...
			//Top of curve
			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 1.0f)), density);
			GetShape(16)->setLocalPose(PxTransform(PxVec3(49.0f, 2.0f, -25.0f), PxQuat(0.1f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 1.0f)), density);
			GetShape(17)->setLocalPose(PxTransform(PxVec3(48.7f, 2.0f, -27.0f), PxQuat(0.2f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 1.0f)), density);
			GetShape(18)->setLocalPose(PxTransform(PxVec3(48.25f, 2.0f, -28.9f), PxQuat(0.3f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 1.0f)), density);
			GetShape(19)->setLocalPose(PxTransform(PxVec3(47.6f, 2.0f, -30.75f), PxQuat(0.4f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 1.0f)), density);
			GetShape(20)->setLocalPose(PxTransform(PxVec3(47.25f, 2.0f, -31.6f), PxQuat(0.4f, PxVec3(0.0f, 1.0f, 0.0f))));

			//Bottom of curve
			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 1.0f)), density);
			GetShape(21)->setLocalPose(PxTransform(PxVec3(46.65f, 2.0f, -25.0f), PxQuat(0.1f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 1.0f)), density);
			GetShape(22)->setLocalPose(PxTransform(PxVec3(46.35f, 2.0f, -27.0f), PxQuat(0.2f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 1.0f)), density);
			GetShape(23)->setLocalPose(PxTransform(PxVec3(45.87f, 2.0f, -28.9f), PxQuat(0.3f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 1.0f)), density);
			GetShape(24)->setLocalPose(PxTransform(PxVec3(45.2f, 2.0f, -30.75f), PxQuat(0.4f, PxVec3(0.0f, 1.0f, 0.0f))));

			//Curve roof
			CreateShape(PxBoxGeometry(PxVec3(1.0f, 0.1f, 1.0f)), density);
			GetShape(25)->setLocalPose(PxTransform(PxVec3(47.65f, 3.2f, -25.0f), PxQuat(0.1f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(1.0f, 0.1f, 1.0f)), density);
			GetShape(26)->setLocalPose(PxTransform(PxVec3(47.35f, 3.2f, -27.0f), PxQuat(0.2f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(1.0f, 0.1f, 2.0f)), density);
			GetShape(27)->setLocalPose(PxTransform(PxVec3(46.87f, 3.2f, -29.0f), PxQuat(0.3f, PxVec3(0.0f, 1.0f, 0.0f))));
			CreateShape(PxBoxGeometry(PxVec3(1.0f, 0.1f, 2.0f)), density);
			GetShape(28)->setLocalPose(PxTransform(PxVec3(46.2f, 3.2f, -31.0f), PxQuat(0.4f, PxVec3(0.0f, 1.0f, 0.0f))));

			CreateShape(PxBoxGeometry(PxVec3(3.0f, 0.1f, 1.0f)), density);
			GetShape(29)->setLocalPose(PxTransform(PxVec3(48.0f, 3.2f, -25.0f)/*, PxQuat(0.1f, PxVec3(0.0f, 1.0f, 0.0f))*/));
			CreateShape(PxBoxGeometry(PxVec3(3.0f, 0.1f, 1.0f)), density);
			GetShape(30)->setLocalPose(PxTransform(PxVec3(48.0f, 3.2f, -27.0f)/*, PxQuat(0.2f, PxVec3(0.0f, 1.0f, 0.0f))*/));
			CreateShape(PxBoxGeometry(PxVec3(3.0f, 0.1f, 1.0f)), density);
			GetShape(31)->setLocalPose(PxTransform(PxVec3(48.0f, 3.2f, -29.0)/*, PxQuat(0.3f, PxVec3(0.0f, 1.0f, 0.0f))*/));
			CreateShape(PxBoxGeometry(PxVec3(3.0f, 0.1f, 1.0f)), density);
			GetShape(32)->setLocalPose(PxTransform(PxVec3(48.0f, 3.2f, -31.0f)/*, PxQuat(0.4f, PxVec3(0.0f, 1.0f, 0.0f))*/));

			CreateShape(PxBoxGeometry(PxVec3(3.0f, 0.1f, 1.0f)), density);
			GetShape(33)->setLocalPose(PxTransform(PxVec3(48.0f, 3.2f, -23.0f)/*, PxQuat(0.1f, PxVec3(0.0f, 1.0f, 0.0f))*/));

			CreateShape(PxBoxGeometry(PxVec3(0.1f, 1.0f, 3.7f)), density);
			GetShape(34)->setLocalPose(PxTransform(PxVec3(45.0f, 2.0f, -27.5f)));

			CreateShape(PxBoxGeometry(PxVec3(1.0f, 1.0f, 34.5f)), density);
			GetShape(35)->setLocalPose(PxTransform(PxVec3(48.0f, 2.0f, -66.5f)));

			//More slide roof
			CreateShape(PxBoxGeometry(PxVec3(3.0f, 0.1f, 10.0f)), density);
			GetShape(36)->setLocalPose(PxTransform(PxVec3(48.0f, 3.2f, 90.0f)/*, PxQuat(0.1f, PxVec3(0.0f, 1.0f, 0.0f))*/));

			//More things to bounce off of
			//CreateShape(PxBoxGeometry(5.0f, 1.0f, 5.0f), density);
			//GetShape(36)->setLocalPose(PxTransform(PxVec3(0.0f, 3.0f, 0.0f), PxQuat(PxPi/4, PxVec3(0.0f, 1.0f, 0.0f))));
		}
	};
}