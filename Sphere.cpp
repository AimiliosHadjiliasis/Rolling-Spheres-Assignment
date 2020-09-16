#include "Sphere.h"

//Constructor:
Sphere::Sphere(I3DEngine* engine, IMesh* mesh, int state, int skinState, int x, int y,
					int z, float speed, float rotationSpeed, int movementRotation)
{
	sphereMesh = mesh;
	m_movementState = state;
	m_skinState = skinState;
	m_x = x;
	m_y = y;
	m_z = z;
	myEngine = engine;
	m_sphereSpeed = speed;
	m_sphereRotationSpeed = rotationSpeed;
	m_movementRotation = movementRotation;
}

//Destructor:
Sphere::~Sphere() {}

void Sphere::SkinStateSetter()
{
	/******************************************************/
	//	Mehtod that sets the skin to the spheres based 
	//	on their skin state that is passed from the main
	//	file in the initialization of the object.
	/******************************************************/
	if (m_skinState == 0)
	{
		sphereModel->SetSkin("blue.png");
	}
	else if (m_skinState == 1)
	{
		sphereModel->SetSkin("violet.PNG");
	}
	else if (m_skinState == 2)
	{
		sphereModel->SetSkin("indigo.png");
	}
}

void Sphere::SkinChanger()
{
	/**************************************************************/
	//	Method that changes the skin of the sphere objects in
	//	Clockwise order, when the user presses the C button.
	//	How it works: when the user presses the C button the 
	//	object state, changes to the next one. 
	//	(E.g) when the game beggins the object sphere one i.e, has 
	//	the value of 0. Then if the user press the C button, the 
	//	that value becomes 1 so the skin of that object changes.
	/**************************************************************/
	if (m_skinState == 0)
	{
		m_skinState = 1;
		sphereModel->SetSkin("violet.PNG");
	}
	else if (m_skinState == 1)
	{
		m_skinState = 2;
		sphereModel->SetSkin("indigo.PNG");
	}
	else if (m_skinState == 2)
	{
		m_skinState = 0;
		sphereModel->SetSkin("blue.PNG");
	}
}

void Sphere::CreateModelAndSetPossition()
{
	/************************************************************/
	//	Method that creates the model of the object in the 
	//	possition that is passed in the main file (x,y,z) pos
	//	and also sets the skin of the object.
	/************************************************************/
	sphereModel = sphereMesh->CreateModel(m_x, m_y, m_z);
	SkinStateSetter();
}

void Sphere::UpAndDownMovement()
{
	/************************************************************/
	//	Method that is moving the sphere objects UP and Down
	//	when the user press the Up/Down keys. The object can be
	//	moved until a speciffic point (min=10 and max=40)
	/************************************************************/
	if (myEngine->KeyHeld(Key_Up) && sphereModel->GetLocalY() <= 40)
	{
		sphereModel->MoveY(0.02);
	}
	if (myEngine->KeyHeld(Key_Down) && sphereModel->GetLocalY() >= 10)
	{
		sphereModel->MoveY(-0.02);
	}
}

void Sphere::IncreaseDecreaseSpeed()
{
	/**************************************************************/
	//	Method that increses and decreases the movement speed and 
	//	the rotation speed of the sphere objects with the use of 
	//	the X/Z button respectively. The increment and decrement
	//	of these values can be up to a specific float point 
	//	(min speed = 0.1 // max speed = 0.5)
	/**************************************************************/
	if (myEngine->KeyHeld(Key_X) && m_sphereSpeed <= 0.5) 
	{
		m_sphereSpeed += 0.001;
		m_sphereRotationSpeed += 0.001;
	}
	if (myEngine->KeyHeld(Key_Z) && m_sphereSpeed >= 0.1) 
	{
		m_sphereSpeed -= 0.001;
		m_sphereRotationSpeed -= 0.001;
	}
}

void Sphere::SphereMovementAntiClockwise()
{
	/*************************************************************/
	//	Mehtod that controls the movement of the spheres when 
	//	they are moving in clockwise order.
	/*************************************************************/
	float maxX = 50;
	float maxZ = 100;
	float minX = 0;
	float minZ = 0;
	float maxY = 11;

	switch (m_movementState)
	{
	case rightMovement: 
	{
		/***********************************************/
		//	Allow the user to move the sphere objects 
		//	up and down and also increase their speed
		/***********************************************/
		UpAndDownMovement();
		IncreaseDecreaseSpeed();

		/******************************************************/
		//	In case that the object is not touching the
		//	ground then the spheres are rotating while they
		//	are moving
		/******************************************************/
		if (sphereModel->GetLocalY() <= maxY)
		{
			sphereModel->RotateZ(-m_sphereRotationSpeed);
		}

		/*************************/
		//	Move the sphere:
		/*************************/
		sphereModel->MoveX(m_sphereSpeed);	

		/*****************************/
		//		Change State:
		/*****************************/
		if (sphereModel->GetLocalX() >= maxX)
		{
			m_movementState = upMovement;
		}
		break;
	}
	case upMovement: 
	{
		/***********************************************/
		//	Allow the user to move the sphere objects 
		//	up and down and also increase their speed
		/***********************************************/
		UpAndDownMovement();
		IncreaseDecreaseSpeed();
		
		/******************************************************/
		//	In case that the object is not touching the
		//	ground then the spheres are rotating while they
		//	are moving
		/******************************************************/
		if (sphereModel->GetLocalY() <= maxY)
		{
			sphereModel->RotateX(m_sphereRotationSpeed);
		}

		/*************************/
		//	Move the sphere:
		/*************************/
		sphereModel->MoveZ(m_sphereSpeed);

		/*****************************/
		//		Change State:
		/*****************************/
		if (sphereModel->GetLocalZ() >= maxZ)
		{
			m_movementState = leftMovement;
		}
		break;
	}
	case leftMovement: 
	{
		/***********************************************/
		//	Allow the user to move the sphere objects 
		//	up and down and also increase their speed
		/***********************************************/
		UpAndDownMovement();
		IncreaseDecreaseSpeed();

		/******************************************************/
		//	In case that the object is not touching the
		//	ground then the spheres are rotating while they
		//	are moving
		/******************************************************/
		if (sphereModel->GetLocalY() <= maxY)
		{
			sphereModel->RotateZ(m_sphereRotationSpeed);
		}

		/*************************/
		//	Move the sphere:
		/*************************/
		sphereModel->MoveX(-m_sphereSpeed);	

		/*****************************/
		//		Change State:
		/*****************************/
		if (sphereModel->GetLocalX() <= -maxX)
		{
			m_movementState = downMovement;
		}
		break;
	}
	case downMovement: 
	{
		/***********************************************/
		//	Allow the user to move the sphere objects 
		//	up and down and also increase their speed
		/***********************************************/
		UpAndDownMovement();
		IncreaseDecreaseSpeed();

		/******************************************************/
		//	In case that the object is not touching the
		//	ground then the spheres are rotating while they
		//	are moving
		/******************************************************/
		if (sphereModel->GetLocalY() <= maxY)
		{
			sphereModel->RotateX(-m_sphereRotationSpeed);
		}

		/*************************/
		//	Move the sphere:
		/*************************/
		sphereModel->MoveZ(-m_sphereSpeed);	

		/*****************************/
		//		Change State:
		/*****************************/
		if (sphereModel->GetLocalZ() <= minZ)
		{
			m_movementState = rightMovement;
		}
		break;
	}
	default:
		break;
	}
}

void Sphere::SphereMovementClockwise()
{
	/*************************************************************/
	//	Mehtod that controls the movement of the spheres when 
	//	they are moving in anti-clockwise order.
	/*************************************************************/
	float maxX = 50;
	float maxZ = 100;
	float minX = 0;
	float minZ = 0;
	float maxY = 11;

	switch (m_movementState)
	{

	case upMovement:
	{
		/***********************************************/
		//	Allow the user to move the sphere objects 
		//	up and down and also increase their speed
		/***********************************************/
		UpAndDownMovement();
		IncreaseDecreaseSpeed();
		
		/******************************************************/
		//	In case that the object is not touching the
		//	ground then the spheres are rotating while they
		//	are moving
		/******************************************************/
		if (sphereModel->GetLocalY() <= maxY)
		{
			sphereModel->RotateX(m_sphereRotationSpeed);
		}

		/*************************/
		//	Move the sphere:
		/*************************/
		sphereModel->MoveZ(m_sphereSpeed);	

		/*****************************/
		//		Change State:
		/*****************************/
		if (sphereModel->GetLocalZ() >= maxZ)
		{
			m_movementState = rightMovement;
		}
		break;
	}
	case rightMovement:
	{
		/***********************************************/
		//	Allow the user to move the sphere objects 
		//	up and down and also increase their speed
		/***********************************************/
		UpAndDownMovement();
		IncreaseDecreaseSpeed();
		
		/******************************************************/
		//	In case that the object is not touching the
		//	ground then the spheres are rotating while they
		//	are moving
		/******************************************************/
		if (sphereModel->GetLocalY() <= maxY)
		{
			sphereModel->RotateZ(-m_sphereRotationSpeed);
		}

		/*************************/
		//	Move the sphere:
		/*************************/
		sphereModel->MoveX(m_sphereSpeed);

		/*****************************/
		//		Change State:
		/*****************************/
		if (sphereModel->GetLocalX() >= maxX)
		{
			m_movementState = downMovement;
		}
		break;
	}
	case downMovement:
	{
		/***********************************************/
		//	Allow the user to move the sphere objects 
		//	up and down and also increase their speed
		/***********************************************/
		UpAndDownMovement();
		IncreaseDecreaseSpeed();
		
		/******************************************************/
		//	In case that the object is not touching the
		//	ground then the spheres are rotating while they
		//	are moving
		/******************************************************/
		if (sphereModel->GetLocalY() <= maxY)
		{
			sphereModel->RotateX(-m_sphereRotationSpeed);
		}
		
		/*************************/
		//	Move the sphere:
		/*************************/
		sphereModel->MoveZ(-m_sphereSpeed);	

		/*****************************/
		//		Change State:
		/*****************************/
		if (sphereModel->GetLocalZ() <= minZ)
		{
			m_movementState = leftMovement;
		}
		break;
	}
	case leftMovement:
	{
		/***********************************************/
		//	Allow the user to move the sphere objects 
		//	up and down and also increase their speed
		/***********************************************/
		UpAndDownMovement();
		IncreaseDecreaseSpeed();
		
		/******************************************************/
		//	In case that the object is not touching the
		//	ground then the spheres are rotating while they
		//	are moving
		/******************************************************/
		if (sphereModel->GetLocalY() <= maxY)
		{
			sphereModel->RotateZ(m_sphereRotationSpeed);
		}

		/*************************/
		//	Move the sphere:
		/*************************/
		sphereModel->MoveX(-m_sphereSpeed);	

		/*****************************/
		//		Change State:
		/*****************************/
		if (sphereModel->GetLocalX() <= -maxX)
		{
			m_movementState = upMovement;
		}
		break;
	}

	default:
		break;
	}
}

void Sphere::SphereMovementChangerState()
{
	/****************************************************************/
	//	Method that changes the movement of the sphere objects when
	//	the user presses the R button. This is done in the main code
	//	file. However this method ensures that the objects will get 
	//	the correct movement when they are changing rotation movement 
	//	state (i.e.) from clockwise to anti-clockwise and vice versa
	/****************************************************************/
	switch (m_movementState)
	{
	case rightMovement:
	{
		m_movementState = leftMovement;
		break;
	}
	case leftMovement:
	{
		m_movementState = rightMovement;
		break;
	}
	case upMovement:
	{
		m_movementState = downMovement;
		break;
	}
	case downMovement:
	{
		m_movementState = upMovement;
		break;
	}
	default:
		break;
	}

}

