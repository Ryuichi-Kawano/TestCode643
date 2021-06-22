#include "Debug.h"
#include<DxLib.h>



void 
Debug::Output(const char* str) {
	test++;
	OutputDebugString(L"Debug Output...\n");
}