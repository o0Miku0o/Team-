#pragma once
#include "MyGame/TaskBase.h"

using namespace std;

namespace BlackHoleGenerator
{
	const char caTaskName[] = { "ブラックホール生成タスク" };
	const char caResName[] = { "ブラックホール生成リソース" };

	/*リソース*/
	class RS : public ResourceBase
	{
	public:
		/*ここに共通変数を追加*/
		/*以下変更不要*/
		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;

	/*タスクオブジェクト*/
	typedef class Obj : public TaskBase
	{
	public:
		/*ここにタスクごとの変数を追加*/
		enum SizeMode
		{
			Normal,	//普通
			Bigger, //どんどん大きくする
			Move	//移動する
		}sizeMode;

		//pPosが位置、pSizeで大きさ、modeで種類(Normal,Bigger,Move)、EndPosは移動の場合だけ終点を指定
		void Bridge(const int iNum, const Point *pPos, const float *pSize, const int* mode, const Point *pMovePos = 0);
		void Bridge(const int iNum, const vector<Point> pPos, const vector<float> pSize, const vector<int> mode, const vector<Point>* pMovePos = 0);
		/*以下変更不要*/
		Obj() { Init(); }
		~Obj() { Finalize(); }
	private:
		/*リソースを参照*/
		RS_ptr res;
		void Init();
		void Finalize();
	public:
		void Update();
		void Render();
	}*Obj_ptr;
}