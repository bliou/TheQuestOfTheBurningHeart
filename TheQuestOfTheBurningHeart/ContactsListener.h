#pragma once
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include <anax/anax.hpp>

class GameScreen;

class ContactsListener: public b2ContactListener
{
public:
	ContactsListener(GameScreen& gameInstance);
	~ContactsListener();

	// Called when two fixtures begin to touch
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	bool canCollide(uint16 filterBits);

protected:
	GameScreen & m_gameInstance;
};

