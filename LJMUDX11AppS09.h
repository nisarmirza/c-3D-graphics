#pragma once

#include "Application.h"

#include "Win32RenderWindow.h"
#include "RendererDX11.h"

#include "ViewPerspective.h"
//Hieroglyph Includes
#include "Camera.h"
#include "Scene.h"
#include "GeometryActor.h"
#include "TextActor.h"
#include "PointLight.h"

//STL Includes
#include <vector>

//LJMU Framework Includes
#include "LJMUTextOverlay.h"
#include "LJMUSpriteOverlay.h"

using namespace Glyph3;

namespace LJMUDX
{
	//////////////////////////////////////
	//LJMUDX11AppS09.H
	//Class Application for a DirectX 11
	//Driven Application using the DirectX Toolkit
	//Hieroglyph 3 Rendering Engine and LUA.
	//
	//This is the Directed Study session for 5002MATH
	//
	//AUTHORS:  DR CHRIS CARTER
	//			DR PO YANG
	//////////////////////////////////////
	class LJMUDX11AppS09 : public Application //Inherit from the Hieroglyph Base Class
	{

	public:
		//------------CONSTRUCTORS------------------------------------------------
		LJMUDX11AppS09();	//Standard Empty Constructor which builds the object

	public:
		//------------INHERITED METHODS-------------------------------------------
		virtual void Initialize();	//Initialise the DirectX11 Scene
		virtual void Update();		//Update the DirectX Scene
		virtual void Shutdown();	//Shutdown the DirectX11 Scene

		virtual bool ConfigureEngineComponents();	//Initialise Hieroglyph and DirectX TK Modules
		virtual void ShutdownEngineComponents();	//Destroy Hieroglyph and DirectX TK Modules

		virtual void TakeScreenShot();				//Allow a screenshot to be generated

		virtual bool HandleEvent(EventPtr pEvent);	//Handle an I/O Event
		virtual std::wstring GetName();				//Get the Name of this App Instance

		//------------CUSTOM METHODS-----------------------------------------------
		void inputAssemblyStage();					//Stage to setup our VB and IB Info

		std::wstring outputFPSInfo();
		std::wstring outputDebugInfo(const GeometryActor& pactor);
		std::wstring outputDebugInfoAll();

		std::wstring outputDebugMatrix(const GeometryActor& pactor);

		std::wstring outputDebugTransform(const Matrix4f& pmatrix, Vector3f ppoint);
		std::wstring outputDebugTransform(const GeometryActor& pactor, Vector3f ppoint);

	protected:
		//-------------CLASS MEMBERS-----------------------------------------------
		RendererDX11*			_obj_renderer11;	//Pointer to our DirectX 11 Device
		Win32RenderWindow*		_obj_window;		//Pointer to our Windows-Based Window

		int						_swap_index;		//Index of our Swap Chain 
		ResourcePtr				_tgt_render;		//Pointer to the GPU Render Target for Colour
		ResourcePtr				_tgt_depth;			//Pointer to the GPU Render Target for Depth

		//--------------HIEROGLYPH OBJECTS-----------------------------------------
		ViewPerspective*			_render_view;

		std::vector<GeometryActor*>	_objects;
		std::vector<TextActor*>		_text_elems;
		GeometryActor*				_floor;
		PointLight*					_light;
		ResourcePtr					_texture;
		ResourcePtr					_Sprite_tex;

		LJMUSpriteOverlay*			_render_sprite;
		Camera*						_obj_sprite_cam;

		Camera*						_obj_camera;
		LJMUTextOverlay*            _render_text;
		unsigned int				_curr_obj;
		bool						_sprite_visible;
		//------------------- Object Animation Control -------------------------
		int							Object_2_direction;
		float						acceleration;
		float						speed;
		float						totaltime;
	};

}
/*


*/