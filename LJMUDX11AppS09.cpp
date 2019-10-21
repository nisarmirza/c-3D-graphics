//------------Include the Application Header File----------------------------
#include "LJMUDX11AppS09.h"

//------------DX TK AND STD/STL Includes-------------------------------------
#include <sstream>
#include <iomanip>
#include <iostream>

//------------Include Hieroglyph Engine Files--------------------------------

//Include the Logging System
#include "Log.h"

//Include the Event System
#include "EventManager.h"
#include "EvtFrameStart.h"
#include "EvtChar.h"
#include "EvtKeyUp.h"
#include "EvtKeyDown.h"
#include "ScriptManager.h"

//Include the DirectX Rendering Components
#include "PipelineManagerDX11.h"
#include "BlendStateConfigDX11.h"
#include "BufferConfigDX11.h"
#include "DepthStencilStateConfigDX11.h"
#include "RasterizerStateConfigDX11.h"
#include "SwapChainConfigDX11.h"
#include "Texture2dConfigDX11.h"
#include "MaterialGeneratorDX11.h"

#include "FirstPersonCamera.h"

//Add a Using Directive to avoid typing Glyph3 for basic constructs
using namespace Glyph3;
//Include our own application Namespace
using namespace LJMUDX;

LJMUDX11AppS09 AppInstance;

//---------CONSTRUCTORS-------------------------------------------------------
LJMUDX11AppS09::LJMUDX11AppS09()
{
	this->_curr_obj = 0;

	this->Object_2_direction = 0;

	this->acceleration = 0.002;
	this->speed = 0.03;
	totaltime = 0;
}

//---------METHODS------------------------------------------------------------

//////////////////////////////////////
// Get the Window Name of this Application
//////////////////////////////////////
std::wstring LJMUDX11AppS09::GetName()
{
	return(std::wstring(L"5108COMP: Tutorial 9 - Loading Texture "));
}

/////////////////////////////////////
// Assemble our Input Layouts for this
// Stage of the Pipeline.
/////////////////////////////////////
void LJMUDX11AppS09::inputAssemblyStage()
{
	//-----SETUP OUR GEOMETRY FOR THIS SCENE-----------------------------------------
	this->_texture = RendererDX11::Get()->LoadTexture(L"Tiles.png");

	this->_Sprite_tex = RendererDX11::Get()->LoadTexture(L"Face.png");

	//Setup Floor
	GeometryActor* tboard = new GeometryActor();
	tboard->SetColor(Vector4f(0.1f, 0.4f, 0.1f, 1.0f));
	tboard->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(50.0f, 0.1f, 50.0f));
	tboard->UseSolidMaterial();
	tboard->GetNode()->Position() = Vector3f(0.0f, -5.0f, 0.0f);
	this->m_pScene->AddActor(tboard);

	for (int i = 0; i < 5; i++)
	{
		//Create our Geometry Actor object
		GeometryActor* tactor = new GeometryActor();

		//Set up the Object's Material and Colour Settings
		Vector3f tcolor = Vector3f::Random();
		tcolor.Clamp();
		Vector4f tfullcolor;
		tfullcolor.x = tcolor.x;
		tfullcolor.y = tcolor.y;
		tfullcolor.z = tcolor.z;
		tfullcolor.w = 1;
		tactor->SetColor(tfullcolor);

		
		

		//Create our Primitive, specifying the Local Space lccation and size of object
		if (i % 3 == 0)
		{
			tactor->DrawBox(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(3.0f, 3.0f, 3.0f));
		}
		else if (i % 3 == 1)
		{
			tactor->DrawCylinder(Vector3f(0.0f, -3.0f, 0.0f), Vector3f(0.0f, 3.0f, 0.0f), 3, 3);
		}
		else 
		{
			//tactor->DrawSphere(Vector3f(0.0f, 0.0f, 0.0f), 3.0f, 20, 20);
			tactor->DrawSphere(Vector3f(5.0f, 5.0f, 5.0f), 4.0f, 20, 20);
		}
		
			
		

		//Use Texture Mapping instead of Colors
		
		tactor->SetColor(Vector4f(1, 1, 1, 1));
		tactor->UseTexturedMaterial(this->_texture);

	/*	tactor->UseSolidMaterial();*/

		//Add the Actor to our List of Actors
		this->_objects.push_back(tactor);
		//Add the Actor to the Scene so that it is rendered
		this->m_pScene->AddActor(tactor);

		TextActor* ttext = new TextActor();
		ttext->SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		ttext->GetNode()->Position() = tactor->GetNode()->Position() + Vector3f(0, 15, 0);
		ttext->SetLineJustification(LineJustification::CENTER);
		ttext->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
		this->_text_elems.push_back(ttext);
		this->m_pScene->AddActor(ttext);
	}


	//-------Setup Object Settings------------------------------------------
	/*
	this->_objects[0]->GetNode()->Position() = Vector3f(0.0f, 0.0f, 0.0f);
	this->_objects[0]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[0]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[1]->GetNode()->Position() = Vector3f(0.0f, 0.0f, 0.0f);
	this->_objects[1]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[1]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[2]->GetNode()->Position() = Vector3f(0.0f, 0.0f, 0.0f);
	this->_objects[2]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[2]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[3]->GetNode()->Position() = Vector3f(0.0f, 0.0f, 0.0f);
	this->_objects[3]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[3]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[4]->GetNode()->Position() = Vector3f(0.0f, 0.0f, 0.0f);
	this->_objects[4]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[4]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));
	*/

	
	float angle = 45;
	const float LOCAL_PI = 3.14159265;
	const float DEG_TO_RAD = LOCAL_PI / 180.0f;

	float u = 50.0f, v = 10.0f, w = 20.0f;
	float L = (u*u + v * v + w * w);
	angle = angle * DEG_TO_RAD;

	float u2 = u * u;
	float v2 = v * v;
	float w2 = w * w;

	float rm11 = (u2 + (v2 + w2) * cos(angle)) / L;
	float rm12 = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
	float rm13 = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;

	float rm21 = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
	float rm22 = (v2 + (u2 + w2) * cos(angle)) / L;
	float rm23 = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;

	float rm31 = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
	float rm32 = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
	float rm33 = (w2 + (u2 + v2) * cos(angle)) / L;

	Matrix3f trot1(rm11, rm12, rm13, rm21, rm22, rm23, rm31, rm32, rm33);

	this->_objects[0]->GetNode()->Rotation() = trot1;

	this->_objects[0]->GetNode()->Position() = Vector3f(0.0f, 50.0f, 0.0f);
	//this->_objects[0]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	//this->_objects[0]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[1]->GetNode()->Position() = Vector3f(0.0f, 0.0f, 50.0f);
	this->_objects[1]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[1]->GetNode()->Rotation().RotationZYX(Vector3f(-90.0f, 0, 0));

	this->_objects[2]->GetNode()->Position() = Vector3f(0.0f, 0.0f, 0.0f);
	this->_objects[2]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	this->_objects[2]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));

	this->_objects[3]->GetNode()->Position() = Vector3f(30.0f, 40.0f, 0.0f);
	this->_objects[3]->GetNode()->Scale() = Vector3f(1.0f, 1.0f, 1.0f);
	//this->_objects[3]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 0));
	const float local_PI = 3.14159265f;
	/*const float DEG_TO_RAD = local_PI / 180.0f;*/
	float trotx = 30.0 * DEG_TO_RAD;
	float troty = 45.0 * DEG_TO_RAD;
	this->_objects[3]->GetNode()->Rotation().RotationX(trotx);
	this->_objects[3]->GetNode()->Rotation().RotationY(troty);

	Matrix3f ro_x(true);
	ro_x.RotationX(trotx);
	Matrix3f ro_y(true);
	ro_x.RotationY(troty);

	this->_objects[3]->GetNode()->Rotation() = ro_x;

	this->_objects[4]->GetNode()->Position() = Vector3f(0.0f, 0.0f, 0.0f);
	this->_objects[4]->GetNode()->Scale() = Vector3f(2.0f, 2.0f, 2.0f);
	this->_objects[4]->GetNode()->Rotation().RotationZYX(Vector3f(0, 0, 45.0f));

	this->_light = new PointLight();
	this->_light->SetAmbient(Vector4f(0.2f, 0.2f, 0.2f, 1.0f));
	this->_light->SetDiffuse(Vector4f(0.6f, 0.6f, 0.6f, 1.0f));
	this->_light->SetSpecular(Vector4f(0.6f, 0.6f, 0.6f, 1.0f));
	this->_light->GetNode()->Position() = Vector3f(0.0f, 100.0f, 25.0f);
	this->m_pScene->AddLight(this->_light);
}

////////////////////////////////////
// Initialise our DirectX 3D Scene
////////////////////////////////////
void LJMUDX11AppS09::Initialize()
{
	//Call the Input Assembly Stage to setup the layout of our Engine Objects
	this->inputAssemblyStage();

	this->_obj_camera = new FirstPersonCamera();
	this->_obj_camera->SetEventManager(&this->EvtManager);

	Vector3f tcamerapos(0.0f, 50.0f, -100.0f);
	this->_obj_camera->Spatial().SetTranslation(tcamerapos);

	this->_render_view = new ViewPerspective(*this->_obj_renderer11,
		this->_tgt_render, this->_tgt_depth);
	this->_render_view->SetBackColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
	this->_obj_camera->SetCameraView(this->_render_view);

	this->_render_text = new LJMUTextOverlay(*this->_obj_renderer11,
		this->_tgt_render,
		std::wstring(L"Cambria"),
		25);

	this->_obj_camera->SetOverlayView(this->_render_text);

	float twidth = this->_obj_window->GetWidth();
	float theight = this->_obj_window->GetHeight();
	this->_obj_camera->SetProjectionParams(0.1f, 1000.0f, twidth / theight, static_cast<float>(GLYPH_PI) / 4.0f);

	this->m_pScene->AddCamera(this->_obj_camera);

	// ---------------- SPRITE RENDERING -----------------------
	// Construct a sptite Overlay
	this->_obj_sprite_cam = new Camera;
	//Construct the sprite Overlay
	this->_render_sprite = new LJMUSpriteOverlay(*this->_obj_renderer11,
		this->_tgt_render,
		std::wstring(L"Tiles.png"));
	//Asscoiate the overal with sprite camera
	this->_obj_sprite_cam->SetOverlayView(this->_render_sprite);

	this->m_pScene->AddCamera(this->_obj_sprite_cam);
}

///////////////////////////////////
// Update the State of our Game and 
// Output the Results to Screen (Render)
/////////////////////////////////// 
void LJMUDX11AppS09::Update()
{
	this->m_pTimer->Update();
	EvtManager.ProcessEvent(EvtFrameStartPtr(new EvtFrameStart(this->m_pTimer->Elapsed())));

	//----------START RENDERING---------------------------------------------------------
	this->_render_text->writeText(std::wstring(L"Nisar's World"), Matrix4f::TranslationMatrix(5.0f, 5.0f, 0.0f), Vector4f(255.0f, 128.0f, 100.0f, 10.0f));

	/*for (int i = 0; i < 5; i++)
	{
		Matrix3f trotationA;
		Matrix3f trotationB;

		trotationA.RotationX(m_pTimer->Elapsed());
		trotationB.RotationY(-m_pTimer->Elapsed());

		if (i % 2 == 0)
			this->_objects[i]->GetNode()->Rotation() *= trotationA;
		else
			this->_objects[i]->GetNode()->Rotation() *= trotationB;
	}*/
	//---------3D Scene Updates---------------------------------------------------------

	float ttpf = this->m_pTimer->Elapsed();
	//static float tposx = 0;
	//static float tposy = 0;
	//tposx += 3 * ttpf;
	//tposy += 4 * ttpf;

	////if (tposx > 10 && tposy > 10)
	////{
	////	tposx = 0;
	////	tposy = 0;
	////}

	////this->_objects[4]->GetNode()->Position() = Vector3f(tposx, tposy, 0) ;

	//Vector3f ttranslate(tposx, tposy, 0);
	//
	//if (ttranslate.Magnitude() > 50.0f)
	//{
	//tposx = 0;
	//tposy = 0;
	//}
	/////
	//this->_objects[0]->GetNode()->Position() += ttranslate;

	// 1. Linear Interpolation
	static float tposx1 = 0;
	static float tposy1 = 0;
	static float tposz1 = 0;
	
	//Given Point 
	Vector3f point(50.0f, 50.0f, 50.0f);

	tposx1 = this->_objects[4]->GetNode()->Position().x;
	tposy1 = this->_objects[4]->GetNode()->Position().y;
	tposz1 = this->_objects[4]->GetNode()->Position().z;

	//tposx += 0.03;
	//tposy += 0.03;
	//tposz += 0.03;

	/*if (tposx > point.x && tposy > point.x && tposz > point.x)
	{
		tposx = 0;
		tposy = 0;
		tposz = 0;
	}*/

	if (tposx1 <= point.x && tposx1 >= 0.0)
	{
		if (this->Object_2_direction == 0)
		{
			//this->speed += this->acceleration;
			tposx1 += this->speed;
			tposy1 += this->speed;
			tposz1 += this->speed;
		}
		else if (this->Object_2_direction == 1)
		{
			//this->speed += this->acceleration;
			tposx1 -= this->speed;
			tposy1 -= this->speed;
			tposz1 -= this->speed;
		}
	}

	if (tposx1 > point.x)
	{
		tposx1 -= this->speed;
		tposy1 -= this->speed;
		tposz1 -= this->speed;
		this->Object_2_direction = 1;
	}
	else if (tposx1 < 0.0)
	{
		tposx1 += this->speed;
		tposy1 += this->speed;
		tposz1 += this->speed;
		this->Object_2_direction = 0;
	}

	this->_objects[4]->GetNode()->Position() = Vector3f(tposx1, tposy1, tposz1);

	//2. Interpolation of a circle trajectory
	//static float tposx = 0;
	//static float tposy = 0;
	//static float tposz = 0;
	//static float radius = sqrt(800);

	//Vector3f circle_centre(20.0, 20.0, 0.0);

	//tposx = this->_objects[2]->GetNode()->Position().x;
	//tposy = this->_objects[2]->GetNode()->Position().y;
	//tposz = this->_objects[2]->GetNode()->Position().z;

	//// To set the boundry of circle
	//if (tposx >= (20.0 - radius) && tposx <= (20.0 + radius))
	//{
	//	if (tposx >= (20.0 - radius) && tposx <= 20.0 && tposy <= 20 && tposy >= (20.0 - radius))
	//	{
	//		tposx += 0.03;
	//		tposy = -sqrt((radius * radius) - (tposx - 20.0) * (tposx - 20.0)) + 20;
	//	}
	//	else if (tposx > (20.0 - radius) && tposx <= (20.0 + radius) && tposy <= 20 && tposy >= (20.0 - radius))
	//	{
	//		tposx += 0.03;
	//		tposy = -sqrt((radius * radius) - (tposx - 20.0) * (tposx - 20.0)) + 20;
	//	}
	//	else if (tposx > (20.0 - radius) && tposx <= (20.0 + radius) && tposy > 20 && tposy <= (20.0 + radius))
	//	{
	//		tposx += 0.03;
	//		tposy = sqrt((radius * radius) - (tposx - 20.0) * (tposx - 20.0)) + 20;
	//	}
	//	else if (tposx >= (20.0 - radius) && tposx <= 20.0 && tposy > 20 && tposy <= (20.0 + radius))
	//	{
	//		tposx -= 0.03;
	//		tposy = sqrt((radius * radius) - (tposx - 20.0) * (tposx - 20.0)) + 20;
	//	}
	//	
	//}
	//if (tposx > (20.0 + radius))
	//{
	//	tposx -= 0.03;
	//	tposy = sqrt((radius * radius) - (tposx - 20.0) * (tposx - 20.0)) + 20;
	//}
	//else if (tposx < (20.0 - radius))
	//{
	//	tposx += 0.03;
	//	tposy = -sqrt((radius * radius) - (tposx - 20.0) * (tposx - 20.0)) + 20;
	//}
	////tposx = this->_objects[2]->GetNode()->Position().x;
	//tposz = this->_objects[2]->GetNode()->Position().z;

	//this->_objects[2]->GetNode()->Position() = Vector3f(tposx, tposy, tposz);


	// 3. Interpolation of a ellipse trajectory
	Timer t = Timer();
	t.Elapsed();
	std::clock_t start;
	start = clock();
	double duration;
	
	static float tposx;
	start = tposx;
	static float tposy;
	start = tposy;
	static float tposz = 0;
	//static float xradius = sqrt(800);
	static float yradius = sqrt(400);
	static float zradius = sqrt(200);

	totaltime += ttpf;

	tposy = yradius * cos(totaltime);
	tposz = zradius * sin(totaltime);
	 


	this->_objects[2]->GetNode()->Position().x = tposy;
	this->_objects[2]->GetNode()->Position().y = tposz;
	
	
	//tposx = this->_objects[2]->GetNode()->Position().x;
	//tposy = this->_objects[2]->GetNode()->Position().y;
	//tposz = this->_objects[2]->GetNode()->Position().z;

	//
	//

	//// To set the boundry of circle 
	//if (tposx >= 0 && tposx <= 40.0)
	//{
	//	if (tposx >= 0 && tposx <= 20.0 && tposy <= 0 && tposy >= -10.0)
	//	{
	//		tposx += 0.03;
	//		tposy = -sqrt(100 - (tposx - 20.0) * (tposx - 20.0) / 4);
	//	}
	//	else if (tposx > 20.0 && tposx <= 40.0 && tposy <= 0 && tposy >= -10.0)
	//	{
	//		tposx += 0.03;
	//		tposy = -sqrt(100 - (tposx - 20.0) * (tposx - 20.0) / 4);
	//	}
	//	else if (tposx > 20.0 && tposx <= 40.0 && tposy > 0 && tposy <= 10.0)
	//	{
	//		tposx -= 0.03;
	//		tposy = sqrt(100 - (tposx - 20.0) * (tposx - 20.0) / 4);
	//	}
	//	else if (tposx >= 0 && tposx <= 20.0 && tposy > 0 && tposy <= 10.0)
	//	{
	//		tposx -= 0.03;
	//		tposy = sqrt(100 - (tposx - 20.0) * (tposx - 20.0) / 4);
	//	}
	//}

	//


	//if (tposx > 40.0)
	//{
	//	tposx -= 0.03;
	//	tposy = sqrt(100 - (tposx - 20.0) * (tposx - 20.0) / 4);
	//}
	//else if (tposx < 0.0)
	//{
	//	tposx -= 0.03;
	//	tposy = sqrt(100 - (tposx - 20.0) * (tposx - 20.0) / 4);
	//}
	//
	//tposz = this->_objects[2]->GetNode()->Position().z;

	this->_objects[2]->GetNode()->Position() = Vector3f(tposx, tposy, tposz);

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "printf: " << duration << '\n';

	static float trotx = 0;
	static float troty = 0;
	static float trotz = 0;
	const float LOCAL_PI = 3.14159265f;
	const float DEG_TO_RAD = LOCAL_PI / 180.0f;
	trotx += 180 * ttpf * DEG_TO_RAD;
	troty += 90 * ttpf * DEG_TO_RAD;
	trotz += 360 * ttpf * DEG_TO_RAD;

	Matrix3f trot11, trot22, trot33;
	trot11.RotationX(trotx);
	trot22.RotationY(troty);
	trot33.RotationZ(trotz);

	//this->_objects[4]->GetNode()->Rotation() = trot1;
	//this->_objects[3]->GetNode()->Rotation() = trot2;
	this->_objects[3]->GetNode()->Rotation() = trot11 * trot22 * trot33;

	//Relative Change
	Matrix3f trelrot1;
	trelrot1.RotationY(180 * ttpf * DEG_TO_RAD);
	this->_objects[1]->GetNode()->Rotation() *= trelrot1;

	float angle = 0;
	//	const float LOCAL_PI = 3.14159265f;
	//const float DEG_TO_RAD = LOCAL_PI / 180.0f;

	float u = 25.0f, v = 25.0f, w = 30.0f;
	float L = (u*u + v * v + w * w);
	angle += 180 * DEG_TO_RAD * ttpf;

	float u2 = u * u;
	float v2 = v * v;
	float w2 = w * w;


	float rm11 = (u2 + (v2 + w2) * cos(angle)) / L;
	float rm12 = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
	float rm13 = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;

	float rm21 = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
	float rm22 = (v2 + (u2 + w2) * cos(angle)) / L;
	float rm23 = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;

	float rm31 = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;
	float rm32 = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;
	float rm33 = (w2 + (u2 + v2) * cos(angle)) / L;

	Matrix3f trot1(rm11, rm12, rm13, rm21, rm22, rm23, rm31, rm32, rm33);

	this->_objects[0]->GetNode()->Rotation() *= trot1;

	int i = 0;
	for (auto it = this->_text_elems.begin(); it != this->_text_elems.end(); ++it)
	{
		TextActor* ttext = *(it);
		ttext->SetText(this->outputDebugMatrix(*this->_objects[i]));
		ttext->SetColor(this->_objects[i]->GetColor());
		ttext->GetNode()->Position() = this->_objects[i]->GetNode()->Position() + Vector3f(0, 15, 0);
		i++;
	}

	//----------2D Text Rendering-------------------------------------------------------
	Matrix4f ttextpos = Matrix4f::Identity();
	float tx = 30.0f;	float ty = 30.0f;
	static Vector4f twhiteclr(1.0f, 1.0f, 1.0f, 1.0f);
	static Vector4f tyellowclr(1.0f, 1.0f, 0.0f, 1.0f);

	ttextpos.SetTranslation(Vector3f(tx, ty, 0.0f));
	this->_render_text->writeText(this->outputDebugInfoAll(), ttextpos, twhiteclr);

	tx = this->_obj_window->GetWidth() - 400.0f;
	ty = 30.0f;
	ttextpos.SetTranslation(Vector3f(tx, ty, 0.0f));

	std::wstringstream tcurrobjout;
	tcurrobjout << "Object " << this->_curr_obj + 1 << " Matrix \n";
	std::wstring tmatrixtext = tcurrobjout.str();
	tmatrixtext.append(this->outputDebugMatrix(*this->_objects[this->_curr_obj]));
	tmatrixtext.append(L"\n");
	tmatrixtext.append(this->outputDebugTransform(*this->_objects[this->_curr_obj], Vector3f(0, 0, 0)));
	tmatrixtext.append(L"\n");
	tmatrixtext.append(L"Press '2' or '3'!!");
	this->_render_text->writeText(tmatrixtext, ttextpos, tyellowclr);

	Matrix4f ttextpos2 = Matrix4f::Identity();
	float tx2 = 30.0f;	float ty2 = 190.0f;
	static Vector4f twhiteclr2(1.0f, 1.0f, 1.0f, 1.0f);
	static Vector4f tyellowclr2(1.0f, 1.0f, 0.0f, 1.0f);
	ttextpos2.SetTranslation(Vector3f(tx2, ty2, 0.0f));

	this->_render_text->writeText(this->outputFPSInfo(), ttextpos2, twhiteclr2);

	//----------------2D Sprite Rendering ------------------
	if (this->_sprite_visible)
	{

		Matrix4f tspritexform = Matrix4f::Identity();
		this->_render_sprite->drawSprite(tspritexform, Vector4f(1, 1, 1, 1));
		Matrix4f tspritexform2 = Matrix4f::Identity();
		tspritexform2.SetTranslation(Vector3f(50, 50, 0));
		this->_render_sprite->drawSprite(tspritexform2, Vector4f(1, 1, 1, 1), this->_Sprite_tex);
		tspritexform2.SetTranslation(Vector3f(50, 50, 0));
		//this->_render_sprite->Resize(200, 200);
		

	}

	//-----------Scene Updates----------------------------------------------------------
	this->m_pScene->Update(m_pTimer->Elapsed());
	this->m_pScene->Render(this->_obj_renderer11);

	//--------END RENDERING-------------------------------------------------------------
	this->_obj_renderer11->Present(this->_obj_window->GetHandle(), this->_obj_window->GetSwapChain());
}

///////////////////////////////////
// Configure the DirectX 11 Programmable
// Pipeline Stages and Create the Window
// Calls 
///////////////////////////////////
bool LJMUDX11AppS09::ConfigureEngineComponents()
{
	// The application currently supplies the 
	int twidth = 1366;
	int theight = 768;

	// Set the render window parameters and initialize the window
	this->_obj_window = new Win32RenderWindow();
	this->_obj_window->SetPosition(25, 25);
	this->_obj_window->SetSize(twidth, theight);
	this->_obj_window->SetCaption(this->GetName());
	this->_obj_window->Initialize(this);


	// Create the renderer and initialize it for the desired device
	// type and feature level.
	this->_obj_renderer11 = new RendererDX11();

	if (!this->_obj_renderer11->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0))
	{
		Log::Get().Write(L"Could not create hardware device, trying to create the reference device...");

		if (!this->_obj_renderer11->Initialize(D3D_DRIVER_TYPE_REFERENCE, D3D_FEATURE_LEVEL_10_0))
		{
			ShowWindow(this->_obj_window->GetHandle(), SW_HIDE);
			MessageBox(this->_obj_window->GetHandle(), L"Could not create a hardware or software Direct3D 11 device!", L"5002 MATH - Session 06", MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
			this->RequestTermination();
			return(false);
		}
		// If using the reference device, utilize a fixed time step for any animations.
		this->m_pTimer->SetFixedTimeStep(1.0f / 10.0f);
	}

	// Create a swap chain for the window that we started out with.  This
	// demonstrates using a configuration object for fast and concise object
	// creation.
	SwapChainConfigDX11 tconfig;
	tconfig.SetWidth(this->_obj_window->GetWidth());
	tconfig.SetHeight(this->_obj_window->GetHeight());
	tconfig.SetOutputWindow(this->_obj_window->GetHandle());
	this->_swap_index = this->_obj_renderer11->CreateSwapChain(&tconfig);
	this->_obj_window->SetSwapChain(this->_swap_index);

	//Create Colour and Depth Buffers
	this->_tgt_render = this->_obj_renderer11->GetSwapChainResource(this->_swap_index);

	Texture2dConfigDX11 tdepthconfig;
	tdepthconfig.SetDepthBuffer(twidth, theight);
	this->_tgt_depth = this->_obj_renderer11->CreateTexture2D(&tdepthconfig, 0);

	// Bind the swap chain render target and the depth buffer for use in rendering.  
	this->_obj_renderer11->pImmPipeline->ClearRenderTargets();
	this->_obj_renderer11->pImmPipeline->OutputMergerStage.DesiredState.RenderTargetViews.SetState(0, this->_tgt_render->m_iResourceRTV);
	this->_obj_renderer11->pImmPipeline->OutputMergerStage.DesiredState.DepthTargetViews.SetState(this->_tgt_depth->m_iResourceDSV);
	this->_obj_renderer11->pImmPipeline->ApplyRenderTargets();

	D3D11_VIEWPORT tviewport;
	tviewport.Width = static_cast< float >(twidth);
	tviewport.Height = static_cast< float >(theight);
	tviewport.MinDepth = 0.0f;
	tviewport.MaxDepth = 1.0f;
	tviewport.TopLeftX = 0;
	tviewport.TopLeftY = 0;

	int tvpindex = this->_obj_renderer11->CreateViewPort(tviewport);
	this->_obj_renderer11->pImmPipeline->RasterizerStage.DesiredState.ViewportCount.SetState(1);
	this->_obj_renderer11->pImmPipeline->RasterizerStage.DesiredState.Viewports.SetState(0, tvpindex);
	return(true);
}

//////////////////////////////////
//Handle Input Events in the Application
//////////////////////////////////
bool LJMUDX11AppS09::HandleEvent(EventPtr pevent)
{
	eEVENT e = pevent->GetEventType();

	if (e == SYSTEM_KEYBOARD_KEYDOWN)
	{
		EvtKeyDownPtr tkey_down = std::static_pointer_cast<EvtKeyDown>(pevent);
		unsigned int  tkeycode = tkey_down->GetCharacterCode();

		if (tkeycode == '2')
			this->_curr_obj++;
		if (this->_curr_obj >= this->_objects.size())
			this->_curr_obj = 0;
		
		if (tkeycode == '3')
			this->_sprite_visible = !this->_sprite_visible;
	}
	else if (e == SYSTEM_KEYBOARD_KEYUP)
	{
		EvtKeyUpPtr tkey_up = std::static_pointer_cast<EvtKeyUp>(pevent);
		unsigned int tkeycode = tkey_up->GetCharacterCode();
	}

	return(Application::HandleEvent(pevent));
}

//////////////////////////////////
// Destroy Resources created by the engine
//////////////////////////////////
void LJMUDX11AppS09::ShutdownEngineComponents()
{
	if (this->_obj_renderer11)
	{
		this->_obj_renderer11->Shutdown();
		delete this->_obj_renderer11;
	}

	if (this->_obj_window)
	{
		this->_obj_window->Shutdown();
		delete this->_obj_window;
	}
}

//////////////////////////////////
// Shutdown the Application
//////////////////////////////////
void LJMUDX11AppS09::Shutdown()
{
	//NOTHING TO DO HERE
}

//////////////////////////////////
// Take a Screenshot of the Application
//////////////////////////////////
void LJMUDX11AppS09::TakeScreenShot()
{
	if (this->m_bSaveScreenshot)
	{
		this->m_bSaveScreenshot = false;
		this->_obj_renderer11->pImmPipeline->SaveTextureScreenShot(0, this->GetName());
	}
}

//////////////////////////////////////
// Output our Frame Rate
//////////////////////////////////////
std::wstring LJMUDX11AppS09::outputFPSInfo()
{
	std::wstringstream out;
	out << L"FPS: " << m_pTimer->Framerate();
	return out.str();
}

/////////////////////////////////////////
// Output our Debug Information
/////////////////////////////////////////
std::wstring LJMUDX11AppS09::outputDebugInfo(const GeometryActor& pactor)
{
	std::wstringstream out;
	Vector3f ttrans = pactor.GetNode()->Position();
	Vector3f tscale = pactor.GetNode()->Scale();
	out << L"Translation: [ ";
	out << std::fixed;
	out.precision(2);
	out << ttrans.x << " " << ttrans.y << " " << ttrans.z;
	out << "] ";
	out << L"Scale [";
	out << tscale.x << " " << tscale.y << " " << tscale.x;
	out << "] ";
	out << L"Dist [" << ttrans.Magnitude() << "]";
	return out.str();
}

///////////////////////////////////////////
// Output our Debug World Matrix
///////////////////////////////////////////
std::wstring LJMUDX11AppS09::outputDebugMatrix(const GeometryActor& pactor)
{
	std::wstringstream out;
	Matrix4f twm = pactor.GetNode()->WorldMatrix();

	twm.MakeTranspose();

	out << std::fixed << std::setprecision(2);
	out << std::setw(10) << twm[Matrix4f::m11] << std::setw(10) << twm[Matrix4f::m12]
		<< std::setw(10) << twm[Matrix4f::m13] << std::setw(10) << twm[Matrix4f::m14] << std::endl;
	out << std::setw(10) << twm[Matrix4f::m21] << std::setw(10) << twm[Matrix4f::m22]
		<< std::setw(10) << twm[Matrix4f::m23] << std::setw(10) << twm[Matrix4f::m24] << std::endl;
	out << std::setw(10) << twm[Matrix4f::m31] << std::setw(10) << twm[Matrix4f::m32]
		<< std::setw(10) << twm[Matrix4f::m33] << std::setw(10) << twm[Matrix4f::m34] << std::endl;
	out << std::setw(10) << twm[Matrix4f::m41] << std::setw(10) << twm[Matrix4f::m42]
		<< std::setw(10) << twm[Matrix4f::m43] << std::setw(10) << twm[Matrix4f::m44] << std::endl;
	return out.str();
}



std::wstring LJMUDX11AppS09::outputDebugTransform(const Matrix4f& pmatrix, Vector3f ppoint)
{
	std::wstringstream out;
	Vector4f tvector;

	//Calculate our Transformed Homogenous Vector using
	//Matrix Multiplication (our Vector is a Row Vector, so use
	//Column Matrix Multiplication)
	tvector.x = (ppoint.x * pmatrix[0]) + (ppoint.y * pmatrix[4])
		+ (ppoint.z * pmatrix[8]) + (1 * pmatrix[12]);

	tvector.y = (ppoint.x * pmatrix[1]) + (ppoint.y * pmatrix[5])
		+ (ppoint.z * pmatrix[9]) + (1 * pmatrix[13]);

	tvector.z = (ppoint.x * pmatrix[2]) + (ppoint.y * pmatrix[6])
		+ (ppoint.z * pmatrix[10]) + (1 * pmatrix[14]);

	tvector.w = (ppoint.x * pmatrix[3]) + (ppoint.y * pmatrix[7])
		+ (ppoint.z * pmatrix[11]) + (1 * pmatrix[15]);

	//Output the Transformed Vector
	out << std::fixed << std::setprecision(2);
	out << L"[";
	out << tvector.x << " " << tvector.y << " " << tvector.z;
	out << "]";
	//Return the Formatted String
	return out.str();
}

///////////////////////////////////
// Transform the given point,by the
// given Actor's World Matrix.
///////////////////////////////////
std::wstring LJMUDX11AppS09::outputDebugTransform(const GeometryActor& pobject, Vector3f ppoint)
{
	return this->outputDebugTransform(pobject.GetNode()->WorldMatrix(), ppoint);
}

/////////////////////////////////////////
// Output our Debug Information
/////////////////////////////////////////
std::wstring LJMUDX11AppS09::outputDebugInfoAll()
{
	std::wstringstream out;

	int i = 1;
	for (auto it = this->_objects.begin(); it != this->_objects.end(); ++it)
	{
		GeometryActor* pactor = *it;
		Vector3f ttrans = pactor->GetNode()->Position();
		Vector3f tscale = pactor->GetNode()->Scale();
		out << "Object " << i << ": ";
		out << L"Translation: [ ";
		out << std::fixed;
		out.precision(2);
		out << ttrans.x << " " << ttrans.y << " " << ttrans.z;
		out << "] ";
		out << L"Scale [";
		out << tscale.x << " " << tscale.y << " " << tscale.x;
		out << "] ";
		out << L"Dist [" << ttrans.Magnitude() << "]";
		out << std::endl;
		i++;
	}
	return out.str();
}