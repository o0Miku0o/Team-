#pragma once
#include "MyGame/MyApp.h"
#include "Alien.h"

using namespace std;

namespace StageLoad
{
	/*���\�[�X�N���X*/
	class RS : public ResourceBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/

		RS() { Init(); }
		~RS() { Finalize(); }
	private:
		void Init();
		void Finalize();
	};
	typedef RS *RS_ptr;
	/*�^�X�N�I�u�W�F�N�g�N���X*/
	typedef class Obj : public TaskBase
	{
	public:
		/*�K�v�ȃ����o�͂����ɒǉ�*/
		struct Fragment {
			bool state;
			int iNum;
			vector<Point> vpPos;
			vector<int> iColor;
		}sFragement;

		struct Star {
			bool state;
			int iNum;
			vector<int> viChange;
			vector<Point> vpPos;
		}sStar;

		struct Planet {
			int iNum;
			bool state;
			Rec rec;
		}sJupiter, sNeptune;

		struct SMeteo {
			bool state;
			int iNum;
			vector<Point> vpPos;
		}sMeteo, sAlien;

		struct SBlackhole {
			bool state;
			int iNum;
			vector<Point> vpPos;
			vector<float> vpSize;
			vector<int>   viMode;
		}sblackhole;

		//struct SAlien {
		//	bool state;
		//	int iNum;
		//	vector<Point> vpPos;
		//	vector<Alien::Move> vaMove;
		//	vector<Alien::Hit> vaBMHit, vaFGHit;
		//	vector<Alien::Anim> vaAnim;			
		//}sAlien;

		int iStageNum;
		bool isLoad;
		bool LoadStage(int iStage);
		Obj() { Init(); }
		~Obj() { Finalize(); }
	private:
		RS_ptr res;
		void Init();
		void Finalize();
		void LoadFragments(ifstream &ifs);
		void LoadStar(ifstream &ifs);
		void LoadPlanet(ifstream &ifs, Planet &planet);
		void LoadMeteo(ifstream &ifs);
		void LoadAlien(ifstream &ifs);
		void LoadBlackHole(ifstream &ifs);
	public:
		void Update();
		void Render();
	}*OBJ_ptr;
}