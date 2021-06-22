//#pragma onceは、
//「この翻訳単位では1回しか読み込まれませんよ」
//という意味になります。
#pragma once

class Debug
{
public:
	static void Output(const char* str);
};

static int test;//メモリ4バイトを確保して、testというシンボルにしてる
