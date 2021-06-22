#pragma once
namespace Battle {
	class Player;//プロトタイプ宣言もBattle名前空間に含めてしまう
}
class Scene
{
public:
	Scene();
private:
	Battle::Player* player_;
};

