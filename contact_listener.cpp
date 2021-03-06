#include "contact_listener.h"
#include "player.h"
#include "ground.h"
#include "pickup.h"

ContactListener::ContactListener() :
	current_ground_(nullptr)
{
}

ContactListener::~ContactListener()
{
	delete current_ground_;
	current_ground_ = nullptr;

	dying_pickups_scheduled_for_removal_.~set();
}

void ContactListener::BeginContact(b2Contact * contact)
{
	// pointers for body A and body B
	Player* player = nullptr;
	GameObject* game_object = nullptr;

	// a pointer from the physics object to the entity in the game
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	// get body's A type
	// we cast the bodyUserDataA void pointer to a pointer of the type GameObject to be able to access its type
	OBJECT_TYPE typeA = ((GameObject*)(bodyUserDataA))->GetGameObjectType();

	// a pointer from the physics object to the entity in the game
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	// get body's B type
	// we cast the bodyUserDataB void pointer to a pointer of the type GameObject to be able to access its type
	OBJECT_TYPE typeB = ((GameObject*)(bodyUserDataB))->GetGameObjectType();

	// if body A is of the type PLAYER
	if (typeA == PLAYER)
	{
		player = (Player*)(bodyUserDataA);
		game_object = (GameObject*)(bodyUserDataB);
	}
	// if body B is of the type PLAYER
	else if (typeB == PLAYER)
	{
		player = (Player*)(bodyUserDataB);
		game_object = (GameObject*)(bodyUserDataA);
	}

	// collision response
	if (player)
	{
		if (game_object)
		{
			// get the current ground player is at
			if (game_object->GetGameObjectType() == GROUND)
			{
				player->StartContact();
				current_ground_ = (Ground*)(game_object);

				if (current_ground_->GetGameObjectColour() == FINISH)
				{
					player->SetWin(true);
				}
			}
			// check if player is colliding with a pickup
			if (game_object->GetGameObjectType() == PICKUP)
			{
				// schedule pickup for removal
				dying_pickups_scheduled_for_removal_.insert((Pickup*)(game_object));
			}
			// check if player is of the same colour as the ground
			if (player->GetGameObjectColour() == game_object->GetGameObjectColour() && game_object->GetGameObjectType() == GROUND)
			{
				// reset jump
				player->RestartJump();
			}
		}
	}
}

void ContactListener::EndContact(b2Contact * contact)
{
	// Pointers for body A and body B
	Player* player = nullptr;
	GameObject* game_object = nullptr;

	// a pointer from the physics object to the entity in the game
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	// get body's A type
	// we cast the bodyUserDataA void pointer to a pointer of the type GameObject to be able to access its type
	OBJECT_TYPE typeA = ((GameObject*)(bodyUserDataA))->GetGameObjectType();

	// a pointer from the physics object to the entity in the game
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	// get body's B type
	// we cast the bodyUserDataB void pointer to a pointer of the type GameObject to be able to access its type
	OBJECT_TYPE typeB = ((GameObject*)(bodyUserDataB))->GetGameObjectType();

	// if body A is of the type PLAYER
	if (typeA == PLAYER)
	{
		// set player pointer to the player entity in the game
		player = static_cast<Player*>(bodyUserDataA);
		game_object = static_cast<GameObject*>(bodyUserDataB);
	}
	// if body B is of the type PLAYER
	else if (typeB == PLAYER)
	{
		player = static_cast<Player*>(bodyUserDataB);
		game_object = static_cast<GameObject*>(bodyUserDataA);
	}

	// collision response
	if (player)
	{
		if (game_object)
		{
			// get the current ground player is at
			if (game_object->GetGameObjectType() == GROUND)
			{
				player->EndContact();
				current_ground_ = (Ground*)(game_object);
			}
		}
	}
}