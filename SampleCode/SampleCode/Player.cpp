//Player.cpp
#include "Player.h"
#include"Enemy.h"

namespace Battle {
	int
		Player::GetX()const {
		return x;
	}
	int
		Player::GetY()const {
		return y;
	}
	void
		Player::Attack() {
		enemy_->OnDamage();
	}
}