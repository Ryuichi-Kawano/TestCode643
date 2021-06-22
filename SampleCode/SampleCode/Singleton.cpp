#include "Singleton.h"
#include<DxLib.h>


void 
Singleton::OutCounter() {
	char str[32];
	sprintf_s(str, 32, "counter=%d\n", counter);
	OutputDebugStringA(str);
	++counter;
}