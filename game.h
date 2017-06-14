#ifndef _GAME_H
#define _GAME_H

#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <input/input_manager.h>
#include <audio/audio_manager.h>
#include <box2d/Box2D.h>
#include "scene_app.h"
#include "game_object.h"
#include "free_camera.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
} // gef


class Game
{
public:
	Game(gef::Platform& platform);
	~Game();

	void GameInit();
	void GameRelease();
	void UpdateSimulation(float frame_time);
	void GameUpdate(float frame_time);
	void GameRender();
private:
	SceneApp* scene_app_;

	gef::Platform& platform_;

	gef::Renderer3D* renderer_3d_;
	PrimitiveBuilder* primitive_builder_;

	// create the physics world
	b2World* world_;

	// player variables
	Player player_;
	b2Body* player_body_;

	// ground variables
	gef::Mesh* ground_mesh_;
	GameObject ground_;
	b2Body* ground_body_;

	// camera variables
	Camera* camera_;

	// audio variables
	int sfx_id_;
	int sfx_voice_id_;
};

#endif // !_GAME_H
