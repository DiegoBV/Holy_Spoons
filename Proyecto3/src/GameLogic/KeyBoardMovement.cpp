#include "KeyBoardMovement.h"
#include "PhysicsComponent.h"
#include "FPSCamera.h"
#include <LogSystem.h>

KeyBoardMovement::KeyBoardMovement(nap_json const & cfg, GameObject* owner) :Component(cfg, owner)
{
}

void KeyBoardMovement::updateVelocity(nap_vector3 orientation)
{
	nap_vector3 dir = owner_->getOrientation().toNapVec3(orientation);
	dir.y_ = 0;
	dir = dir.normalize();
	velocity = velocity + dir * vel_;
}

void KeyBoardMovement::setUp()
{
	if (isInited()) return;
	setInited();

	// always these keycodes, if you want to use others in the .json
	// you must do a factory of them
	forward_ = SDLK_w;
	left_ = SDLK_a;
	backward_ = SDLK_s;
	right_ = SDLK_d;
	run_ = SDLK_LSHIFT;
	jump_ = SDLK_SPACE;

	// velocity sets
	if (!cfg_["walkVel"].is_null())
		walkVel_ = cfg_["walkVel"];
	else vel_ = 2;
	if (!cfg_["runVel"].is_null())
		runVel_ = cfg_["runVel"];
	else runVel_ = 4;
	if (!cfg_["jumpForce"].is_null())
		jumpForce_ = cfg_["jumpForce"];
	else jumpForce_ = 4;
	vel_ = walkVel_;

	physBody = static_cast<PhysicsComponent*>(owner_->getComponent("basic_phy"))->getDynamicBody();
	velocity = nap_vector3(0, 0, 0);
}


bool KeyBoardMovement::handleEvents(GameObject * o, const SDL_Event & evt)
{
	bool handled = false;

	if (evt.type == SDL_KEYDOWN) {
		SDL_Keycode pressedKey = evt.key.keysym.sym;

		if (pressedKey == forward_) {
			Zaxis.push_front(forward_);
			handled = true;
		}
		else if (pressedKey == left_) {
			Xaxis.push_front(left_);
			handled = true;
		}
		else if (pressedKey == backward_) {
			Zaxis.push_front(backward_);
			handled = true;
		}
		else if (pressedKey == right_) {
			Xaxis.push_front(right_);
			handled = true;
		}
		else if (pressedKey == run_) {
			vel_ = runVel_;
			handled = true;
		}
		else if (pressedKey == jump_ && !jumped) {
			jumped = true;
			nap_vector3 v = { 0, jumpForce_, 0 };
			physBody->addForce(v.px());
			handled = true;
		}
	}

	else if (evt.type == SDL_KEYUP) {
		SDL_Keycode pressedKey = evt.key.keysym.sym;

		if (pressedKey == forward_) {
			Zaxis.remove(forward_);
			handled = true;
		}
		else if (pressedKey == left_) {
			Xaxis.remove(left_);
			handled = true;
		}
		else if (pressedKey == backward_) {
			Zaxis.remove(backward_);
			handled = true;
		}
		else if (pressedKey == right_) {
			Xaxis.remove(right_);
			handled = true;
		}
		else if (pressedKey == run_) {
			vel_ = walkVel_;
			handled = true;
		}
	}

	return handled;
}

void KeyBoardMovement::update(GameObject* o, double time) {
	velocity = nap_vector3(0, 0, 0);

	if (!Zaxis.empty()) {
		if (Zaxis.front() == forward_)  updateVelocity(nap_vector3(0, 0, -1));
		if (Zaxis.front() == backward_) updateVelocity(nap_vector3(0, 0, 1));
	}
	if (!Xaxis.empty()) {
		if (Xaxis.front() == left_) updateVelocity(nap_vector3(-1, 0, -0));
		else if (Xaxis.front() == right_) updateVelocity(nap_vector3(1, 0, 0));
	}

	physBody->setLinearVelocity(velocity.px()*time);
}

KeyBoardMovement::~KeyBoardMovement()
{
}
