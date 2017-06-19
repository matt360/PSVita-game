#include "player.h"
#include <system/debug_log.h>

Player::Player() :
	player_body_(nullptr)
{
	set_type(PLAYER);
}

Player::~Player()
{
}

void Player::InitPlayer(PrimitiveBuilder* primitve_builder, b2World* world)
{
	// setup the mesh for the player
	set_mesh(primitve_builder->GetDefaultCubeMesh());

	// create a physics body for the player
	b2BodyDef player_body_def;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position = b2Vec2(0.0f, 4.0f);

	player_body_ = world->CreateBody(&player_body_def);

	// create the shape for the player
	b2PolygonShape player_shape;
	// if cube 1x1, need to pass half of both dimensions
	player_shape.SetAsBox(0.5f, 0.5f);

	// create the fixture
	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;

	// create the fixture on the rigid body
	player_body_->CreateFixture(&player_fixture_def);

	// update visuals from simulation data
	UpdateFromSimulation(player_body_);

	// create a connection between the rigid body and GameObject
	player_body_->SetUserData(this);
}

void Player::DecrementHealth()
{
	// impuls working here
	//player_body_->ApplyAngularImpulse(100.0f, true);
	/*player_body_->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 0.1f), true);*/
	gef::DebugOut("Player has taken damage.\n");
}