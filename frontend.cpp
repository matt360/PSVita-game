#include "frontend.h"
// gef headers
#include <system/platform.h>
#include <system/debug_log.h>

#include <graphics/font.h>

#include <graphics/sprite_renderer.h>
#include <graphics/sprite.h>

#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <audio/audio_manager.h>

#include <maths/vector4.h>
// extra headers
#include "load_texture.h"

#ifdef _WIN32
// only on windows platforms
#include <Windows.h>
#include <platform/d3d11/input/keyboard_d3d11.h>
#include <platform/d3d11/input/touch_input_manager_d3d11.h>
#endif 

Frontend::Frontend(gef::Platform& platform, GAMESTATE* gamestate) :
	platform_(platform),
	gamestate_(gamestate),
	input_manager_(nullptr),
	button_icon_(nullptr)
{
}


Frontend::~Frontend()
{
}

void Frontend::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void Frontend::CleanUpFont()
{
	delete font_;
	font_ = nullptr;
}

void Frontend::FrontendInit()
{
	// initialise input manager
	input_manager_ = gef::InputManager::Create(platform_);
	// initlalise sprite renderer
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// initialise audio manager
	//audio_manager_ = gef::AudioManager::Create();

	// initialise button icon
	button_icon_ = CreateTextureFromPNG("playstation-cross-dark-icon.png", platform_);

	InitFont();
}

void Frontend::FrontendRelease()
{
	delete input_manager_;
	input_manager_ = nullptr;

	delete sprite_renderer_;
	sprite_renderer_ = nullptr;

	/*delete audio_manager_;
	audio_manager_ = nullptr;*/

	delete button_icon_;
	button_icon_ = nullptr;

	CleanUpFont();
}

void Frontend::FrontendUpdate(float frame_time)
{
	// get the latest date from the input devices
	if (input_manager_)
	{
		input_manager_->Update();

		const gef::SonyController* controller = input_manager_->controller_input()->GetController(0);


		if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS)
		{
			// release any resources for the frontend
			FrontendRelease();

			// update the current state for the game state machine
			(*gamestate_) = GAME; // get the object that gamestate points to
			//GameInit();
		}
	} // !input_manager_

}

void Frontend::FrontendRender()
{
	sprite_renderer_->Begin();

	// render "PRESS" text
	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_.width()*0.5f, platform_.height()*0.5f - 56.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"PRESS");

	// Render button icon
	gef::Sprite button;
	button.set_texture(button_icon_);
	button.set_position(gef::Vector4(platform_.width()*0.5f, platform_.height()*0.5f, -0.99f));
	button.set_height(32.0f);
	button.set_width(32.0f);
	sprite_renderer_->DrawSprite(button);


	// render "TO START" text
	font_->RenderText(
		sprite_renderer_,
		gef::Vector4(platform_.width()*0.5f, platform_.height()*0.5f + 32.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"TO START");


	DrawHUD();

	sprite_renderer_->End();
}

void Frontend::DrawHUD()
{
	if (font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
	} // !font_
}