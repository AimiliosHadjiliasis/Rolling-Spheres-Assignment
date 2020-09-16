#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;

//States of balls movement:
#define rightMovement 0
#define upMovement 1
#define leftMovement 2
#define downMovement 3 

//State of movement
#define anticlockwise 0
#define clockwise 1


class Sphere
{
public:

	/***************************/
	//		Public Methods:
	/***************************/

	//Constructor and Destructor:
	Sphere(I3DEngine* engine, IMesh* mesh, int state, int skinState, int x, 
			int y, int z, float speed, float rotationSpeed, int movementRotation);
	~Sphere();

	//Methods:
	void SkinChanger();
	void CreateModelAndSetPossition();
	void SphereMovementAntiClockwise();
	void SphereMovementClockwise();
	void SphereMovementChangerState();


private:
	/**************************/
	//		Variables:
	/**************************/
	int m_x, m_y, m_z;
	int m_skinState;
	int m_movementState;
	float m_sphereSpeed;
	float m_sphereRotationSpeed;
	int m_movementRotation;
	IMesh* sphereMesh;
	IModel* sphereModel;
	I3DEngine* myEngine;

	/*************************/
	//	  Private Methods:
	/*************************/
	void SkinStateSetter();
	void UpAndDownMovement();
	void IncreaseDecreaseSpeed();
};
