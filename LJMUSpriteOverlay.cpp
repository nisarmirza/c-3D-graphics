#include "LJMUSpriteOverlay.h"
#include "Entity3D.h"
#include "Node3D.h"
#include "Texture2dConfigDX11.h"
#include "Log.h"
#include "IParameterManager.h"
#include "PipelineManagerDX11.h"
#include "Texture2dDX11.h"

using namespace LJMUDX;
using namespace Glyph3;

///////////////////////////
// Constructor for our Sprite
// Overlay Class. 
///////////////////////////
LJMUSpriteOverlay::LJMUSpriteOverlay(RendererDX11& prenderer, ResourcePtr prtt, std::wstring ptexture)
{
	this->_obj_rendertarget = prtt;
	ResourceDX11* tptr_res = prenderer.GetResourceByIndex(this->_obj_rendertarget->m_iResource);

	if (tptr_res->GetType() == RT_TEXTURE2D)
	{
		Texture2dDX11* ttex = (Texture2dDX11*)tptr_res;
		D3D11_TEXTURE2D_DESC tdesc = ttex->GetActualDescription();

		D3D11_VIEWPORT tviewport;
		tviewport.Width = static_cast<float>(tdesc.Width);
		tviewport.Height = static_cast<float>(tdesc.Height);
		tviewport.MinDepth = 0.0f;
		tviewport.MaxDepth = 1.0f;
		tviewport.TopLeftX = 0;
		tviewport.TopLeftY = 0;
		this->_obj_viewport = prenderer.CreateViewPort(tviewport);
	}

	//Create the Sprite Font and the Sprite Renderer (SpriteBatch) for our Sprite Elements
	this->_obj_ptr_default = prenderer.LoadTexture(ptexture);	
	this->_obj_spritebatch = new SpriteRendererDX11();
	this->_obj_spritebatch->Initialize();
}

///////////////////////////
// Destructor For our Sprite
// Overlay Class
///////////////////////////
LJMUSpriteOverlay::~LJMUSpriteOverlay()
{
	SAFE_DELETE(this->_obj_spritebatch);
}

///////////////////////////
// Queue the Render Tasks
///////////////////////////
void LJMUSpriteOverlay::QueuePreTasks(RendererDX11* prenderer)
{
	prenderer->QueueTask(this);
}

///////////////////////////
// Execute our Sprite Rendering
// Task
///////////////////////////
void LJMUSpriteOverlay::ExecuteTask(PipelineManagerDX11* ppipelinemanager, IParameterManager* pparamManager)
{
	//If we have any Sprite elements to draw
	if (this->_list_Sprite.size() > 0)
	{
		// Set the parameters for rendering this view
		ppipelinemanager->ClearRenderTargets();
		ppipelinemanager->OutputMergerStage.DesiredState.RenderTargetViews.SetState(0,this->_obj_rendertarget->m_iResourceRTV);
		ppipelinemanager->ApplyRenderTargets();

		ppipelinemanager->RasterizerStage.DesiredState.ViewportCount.SetState(1);
		ppipelinemanager->RasterizerStage.DesiredState.Viewports.SetState(0,this->_obj_viewport);
		ppipelinemanager->RasterizerStage.DesiredState.RasterizerState.SetState(0);

		// Set default states for these stages
		ppipelinemanager->OutputMergerStage.DesiredState.DepthStencilState.SetState(0);
		ppipelinemanager->OutputMergerStage.DesiredState.BlendState.SetState(0);

		//Loop over each Sprite element and use the spritebatch to draw them
		for (auto tentry : this->_list_Sprite)
		{
			ResourcePtr ttexture = tentry.Sprite == nullptr ? this->_obj_ptr_default : tentry.Sprite;
			//Use the RenderSprite function of our Sprite Batch to draw the Sprite
			this->_obj_spritebatch->Render(ppipelinemanager, pparamManager,ttexture,tentry.xform, tentry.colour);
		}

		//Clear our list of Sprite entries each frame
		this->_list_Sprite.clear();
	}
}

///////////////////////////
// Add a Sprite Entry with
// the given parameters
///////////////////////////
void LJMUSpriteOverlay::drawSprite(Matrix4f& pxform, Vector4f& pcolour, ResourcePtr ptexture)
{
	this->_list_Sprite.push_back(LJMUSpriteEntry(ptexture, pxform, pcolour));
}

///////////////////////////
// Get the Name of this Task
///////////////////////////
std::wstring LJMUSpriteOverlay::GetName()
{
	return(L"LJMUSpriteOverlay");
}

///////////////////////////
// Resize the Viewport
///////////////////////////
void LJMUSpriteOverlay::Resize(UINT pwidth, UINT pheight)
{
	RendererDX11::Get()->ResizeViewport(this->_obj_viewport,pwidth,pheight);
}


//------------INTERFACE METHODS---------------------------------------------------

///////////////////////////
//
///////////////////////////
void LJMUSpriteOverlay::SetRenderParams(IParameterManager* pParamManager)
{
	//NO RENDER PARAMS NEEDED
}

///////////////////////////
//
///////////////////////////
void LJMUSpriteOverlay::SetUsageParams(IParameterManager* pParamManager)
{
	//NO USAGE PARAMS NEEDED
}

///////////////////////////
//
///////////////////////////
void LJMUSpriteOverlay::Update(float ptime)
{
	//NOTHING TO UPDAATE
}