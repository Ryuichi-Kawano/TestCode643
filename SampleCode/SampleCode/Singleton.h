#pragma once
/// <summary>
/// シングルトンクラス
/// </summary>
/// シングルトンとは、アプリケーション中に
/// 実体が一つしかないことを保証するクラス
class Singleton
{
public:
	//staticで宣言された関数は、クラスが
	//オブジェクト化してなくても呼び出せる
	//返すのは「参照」であることに注意
	static Singleton& Instance() {
		//staticはローカル変数として
		//宣言しても「ひとつしかない」保証
		static Singleton instance;
		return instance;
	}

	void OutCounter();
private:
	int counter = 0;
	Singleton() {};//コンストラクタをprivateにする
	//コピー禁止
	//コピーコンストラクタ(引数に自分自身の型をもつ)
	Singleton(const Singleton&)=delete;
	//代入禁止
	void operator=(const Singleton&)=delete;
};

