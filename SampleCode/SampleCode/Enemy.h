#pragma once
namespace Battle {
	class Player;//��{�I�ɂ̓v���g�^�C�v�錾����
	class Enemy
	{
		int x, y;
		int life_;
		//Player player_;//���͎̂��Ă܂���(�T�C�Y���킩��Ȃ��̂�)
		Player* player_;//�|�C���^�Ȃ�T�C�Y���������Ă�̂Ŏ��Ă�
	public:
		int GetX()const;
		int GetY()const;
		void Attack();
		void OnDamage() {
			life_--;
		}
	};
}//namespace Battle

