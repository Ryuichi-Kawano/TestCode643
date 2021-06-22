//Enemy.cpp
#include "Enemy.h"
#include"Player.h"

using namespace Battle;

int 
Enemy::GetX()const {
	return x;
}
int 
Enemy::GetY()const{
	return y;
}
void 
Enemy::Attack() {
	player_->OnDamage();
}