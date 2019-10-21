#pragma once

#include "Task.h"
#include "SpriteFontLoaderDX11.h"
#include "SpriteRendererDX11.h"

namespace LJMUDX
{
	class Entity3D;

	using namespace Glyph3;

	/////////////////////////
	// Simple Structure to
	// represent a Sprite Entry
	// and its properties.
	/////////////////////////
	struct LJMUSpriteEntry
	{
		ResourcePtr	    Sprite;
		Matrix4f		xform;
		Vector4f		colour;

		LJMUSpriteEntry() {};
		LJMUSpriteEntry(ResourcePtr ptexture, Matrix4f& pxform, Vector4f& pcolour)
		{
			this->Sprite	= ptexture;
			this->xform		= pxform;
			this->colour	= pcolour;
		};
	};

	/////////////////////////////////////////
	// LJMUSpriteOVERLAY.H
	// Class to simplify drawing of Sprite elements
	// using SpriteFont instances.
	//
	
	/////////////////////////////////////////
	class LJMUSpriteOverlay : public Task
	{
	public:
		//--------CONSTRUCTORS/DESTRUCTORS----------------------------------------------------
		LJMUSpriteOverlay(RendererDX11& Renderer, ResourcePtr RenderTarget,std::wstring pdefaulttex);
		virtual ~LJMUSpriteOverlay();

		//-------TASK INTERFACE IMPLEMENTATION-----------------------------------------------
		virtual void Update(float ptime);
		virtual void QueuePreTasks(RendererDX11* pRenderer);
		virtual void ExecuteTask(PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager);
		virtual void Resize(UINT pwidth, UINT pheight);
		virtual std::wstring GetName();
		virtual void SetRenderParams(IParameterManager* pParamManager);
		virtual void SetUsageParams(IParameterManager* pParamManager);

		//--------PUBLIC METHODS-------------------------------------------------------------
		void drawSprite(Matrix4f& pxform, Vector4f& pcolour,ResourcePtr ptexture = nullptr);

		//--------CLASS MEMBERS--------------------------------------------------------------
	protected:
		Vector4f						_colour;
		int								_obj_viewport;
		ResourcePtr						_obj_rendertarget;
		ResourcePtr						_obj_ptr_default;
		SpriteRendererDX11*				_obj_spritebatch;
		std::vector<LJMUSpriteEntry>	_list_Sprite;
	};
};