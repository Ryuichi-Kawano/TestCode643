#include<iostream>
#include<sstream>
#include<cmath>
using namespace std;

class Test {
public:
	void Out() {
		cout << "Test out " << endl;
	}
	static void StaticOut() {
		cout << "Static out " << endl;
	}
};
constexpr int SLIME_NO = 0;
constexpr int SKELTON_NO = 1;
constexpr int WAREWOLF_NO = 2;
constexpr int MAGICIAN_NO = 3;
constexpr int DRAGON_NO = 4;
int main() {
	//Test::StaticOut();
	int value = rand() % 5;
	switch (value) {
	case SLIME_NO:
		cout << "スライム" << endl;
		break;
	case SKELTON_NO:
		cout << "スケルトン" << endl;
		break;
	case WAREWOLF_NO:
		cout << "狼男" << endl;
		break;
	case MAGICIAN_NO:
		cout << "魔法使い" << endl;
		break;
	case DRAGON_NO:
		cout << "ドラゴン" << endl;
		break;
	}
	//int a = 100, b = 200;

	//printf("%d,%d\n", a, b);
	//char outStr[32];
	//sprintf_s(outStr,sizeof(outStr), "%d,%d\n", a, b);
	ostringstream oss;
	/*oss << a << "," << b << endl;
	
	printf("%s", oss.str().c_str());*/

	return 0;
}