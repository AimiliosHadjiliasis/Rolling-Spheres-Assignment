// Project 1 Rolling Spheres.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "Sphere.h"
#include <iostream>
#include <sstream>
using namespace tle;

//Movement Rotation of Spheres:
#define anticlockwise 0
#define clockwise 1

//Game states:
#define paused 0
#define unpaused 1

void GameControls(I3DEngine* myEngine)
{
	/***************************************************/
	//	Method that allows the user to Exit the game:
	/***************************************************/
	if (myEngine->KeyHit(Key_Escape))
	{
		myEngine->Stop();
	}
}

void CameraControls(I3DEngine* myEngine, ICamera* camera)
{
	/***************************************************/
	//	Mehtod that allows the user to move the camera:
	/***************************************************/
	// (1) Forward Movement:
	if (myEngine->KeyHeld(Key_W))
	{
		camera->MoveZ(0.2);
	}
	// (2) Backward Moement:
	if (myEngine->KeyHeld(Key_S))
	{
		camera->MoveZ(-0.2);
	}
	// (3) Righward Movement:
	if (myEngine->KeyHeld(Key_A))
	{
		camera->MoveX(-0.2);
	}
	// (4) Leftward Movement:
	if (myEngine->KeyHeld(Key_D))
	{
		camera->MoveX(0.2);
	}
}

void ClockwiseMovement(I3DEngine* myEngine, Sphere& sphere1, Sphere& sphere2, Sphere& sphere3, int& movementRotation)
{
	/********************************************************/
	//		Method that move the Sphere object Clockwise:
	/********************************************************/
	sphere1.SphereMovementClockwise();
	sphere2.SphereMovementClockwise();
	sphere3.SphereMovementClockwise();
	//Change State:
	if (myEngine->KeyHit(Key_R))
	{
		movementRotation = anticlockwise;
		sphere1.SphereMovementChangerState();
		sphere2.SphereMovementChangerState();
		sphere3.SphereMovementChangerState();
	}
}

void AntiClockwiseMovement(I3DEngine* myEngine, Sphere& sphere1, Sphere& sphere2, Sphere& sphere3, int& movementRotation)
{
	/********************************************************/
	//	Method that move the Sphere object Anti-Clockwise:
	/********************************************************/
	sphere1.SphereMovementAntiClockwise();
	sphere2.SphereMovementAntiClockwise();
	sphere3.SphereMovementAntiClockwise();

	//Change State:
	if (myEngine->KeyHit(Key_R))
	{
		movementRotation = clockwise;
		sphere1.SphereMovementChangerState();
		sphere2.SphereMovementChangerState();
		sphere3.SphereMovementChangerState();
	}
}

void SkinChanger(I3DEngine* myEngine, Sphere& sphere1, Sphere& sphere2, Sphere& sphere3)
{
	/*************************************************************/
	//	Method that allows the user to change skin to the 
	//	spheres in clockwise order when the C button is pressed
	/*************************************************************/
	if (myEngine->KeyHit(Key_C))
	{
		sphere1.SkinChanger();
		sphere2.SkinChanger();
		sphere3.SkinChanger();
	}
}

void UnPausedState(int& movementRotation, I3DEngine* myEngine, Sphere& sphere1, Sphere& sphere3, Sphere& sphere2, ICamera* camera)
{
	/**********************************************************************/
	//	Method that contains everyrhing when the game is in un-paused
	//	state. In this case it controlls the movment of the spheres,
	//	and allows the user to change the skin of the spheres and control
	//	the cammera using the WASD keys.
	/**********************************************************************/
	switch (movementRotation)
	{
	case anticlockwise:
	{
		AntiClockwiseMovement(myEngine, sphere1, sphere2, sphere3, movementRotation);
		break;
	}
	case clockwise:
	{
		ClockwiseMovement(myEngine, sphere1, sphere2, sphere3, movementRotation);
		break;
	}
	default:
		break;
	}

	//Method calls that allow the user to change the skin of the spheres
	//and control the camera using the WASD keys.
	SkinChanger(myEngine, sphere1, sphere2, sphere3);
	CameraControls(myEngine, camera);
}

void PausedState(IFont* fontMesh)
{
	/**********************************************************************/
	//	Method that contains everyrhing when the game is in paused
	//	state. In this case it's just print the Paused text in the screen
	/**********************************************************************/
	stringstream p;
	p << "PAUSED";
	fontMesh->Draw(p.str(), 120, 200, kWhite);
}

void GameManager(int& pauseState, IFont* fontMesh, I3DEngine* myEngine, int& movementRotation, 
					Sphere& sphere1, Sphere& sphere3, Sphere& sphere2, ICamera* camera)
{
	/**********************************************************************/
	//	Method that is used as a game manager, of the game. This method
	//	contains what is done and what is not, when the game is in the 
	//	Paused or in Un-Paused state.
	/**********************************************************************/
	switch (pauseState)
	{
	case paused:
	{
		//What is doing:
		PausedState(fontMesh);

		//Change State:
		if (myEngine->KeyHit(Key_P))
		{
			pauseState = unpaused;
		}
		break;
	}
	case unpaused: //unpaused
	{
		//What is doing:
		UnPausedState(movementRotation, myEngine, sphere1, sphere3, sphere2, camera);

		//Change State:
		if (myEngine->KeyHit(Key_P))
		{
			pauseState = paused;
		}
		break;
	}
	default:
		break;
	}


	GameControls(myEngine);
}

void main()
{
	/**************************************************************************/
	//			Engine Initialisation and set media folder Location:
	/**************************************************************************/
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();
	myEngine->AddMediaFolder( "C:\\Program Files (x86)\\TL-Engine\\Media" );
	myEngine->AddMediaFolder("./media");

	/**************************************************/
	//				Movement Variables:
	/**************************************************/
	float dt = myEngine->Timer();
	float spheresVelocity = 2;
	float rotationVelocity = 4;
	float spheresSpeed = spheresVelocity * dt;
	float rotationSpeed = rotationVelocity * dt;

	/**************************************************************************/
	//						 Set up your scene here:			  
	/**************************************************************************/

	/******************************************/
	//		Backdrop and FontMesh Setup:
	/******************************************/
	ISprite* backdropSprite = myEngine->CreateSprite("ins.PNG", 850, 30, 0);
	IFont* fontMesh = myEngine->LoadFont("Monotype Corsiva", 200);

	/******************************************/
	//				CAMERA SETUP:
	/******************************************/
	ICamera* camera = myEngine->CreateCamera(kManual, 60, 120, -200);
	camera->RotateLocalX(20);

	
	/******************************************/
	//				FLOOR SETUP:
	/******************************************/
	IMesh* floorMesh = myEngine->LoadMesh("Floor.x");
	IModel* floor = floorMesh->CreateModel();
	
	/******************************************/
	//		Initialize Spheres Meshe:
	/******************************************/
	IMesh* sphereMesh = myEngine->LoadMesh("sphere.x");
	
	/******************************************/
	//			Sphere 1 Setup:
	/******************************************/
	int x1 = -50; int y1 = 10; int z1 = 0;
	int sphere1State = 0;
	int sphere1SkinState = 0;
	int sphere1MovementRotation = 0;
	Sphere sphere1 = Sphere(myEngine, sphereMesh, sphere1State, sphere1SkinState, x1, y1, z1,
									spheresSpeed, rotationSpeed,sphere1MovementRotation);
	sphere1.CreateModelAndSetPossition();
	
	/******************************************/
	//			Sphere 2 Setup:
	/******************************************/
	int x2 = 50; int y2 = 10; int z2 = 50;
	int sphere2State = 1;
	int sphere2SkinState = 1;
	int sphere2MovementRotation = 0;
	Sphere sphere2 = Sphere(myEngine, sphereMesh, sphere2State, sphere2SkinState, x2, y2, z2,
									spheresSpeed, rotationSpeed, sphere2MovementRotation);
	sphere2.CreateModelAndSetPossition();

	/******************************************/
	//			Sphere 3 Setup:
	/******************************************/
	int x3 = 25; int y3 = 10; int z3 = 0;
	int sphere3State = 0;
	int sphere3SkinState = 2;
	int sphere3MovementRotation = 0;
	Sphere sphere3 = Sphere(myEngine, sphereMesh, sphere3State, sphere3SkinState,x3,y3,z3,
									spheresSpeed, rotationSpeed, sphere3MovementRotation);
	sphere3.CreateModelAndSetPossition();

	/******************************************/
	//	Different states Initialization:
	/******************************************/
	int pauseState = paused;
	int movementRotation = anticlockwise;


	/**************************************************************************/
	//							 Game main Loop:			  
	/**************************************************************************/
	while (myEngine->IsRunning())
	{
		/*****************************************/
		//		Method that draws the Scene:
		/*****************************************/
		myEngine->DrawScene();

		/*****************************************/
		//		Method that enables the game:
		/*****************************************/
		GameManager(pauseState, fontMesh, myEngine, movementRotation, sphere1, sphere3, sphere2, camera);
	}

	/**********************************************************/
	//	Delete the 3D engine now we are finished with it:
	/**********************************************************/
	myEngine->Delete();
}
