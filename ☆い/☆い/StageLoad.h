#pragma once
#include "MyGame/MyApp.h"

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
			std::vector<Point> vpPos;
			std::vector<int> iColor;
		}sFragement;

		struct Star {
			bool state;
			int iNum;
			std::vector<int> viChange;
			std::vector<Point> vpPos;
		}sStar;

		struct Planet {
			int iNum;
			bool state;
			Rec rec;
		}sJupiter, sNeptune;

		struct SMeteo {
			bool state;
			int iNum;
			std::vector<Point> vpPos;
		}sMeteo, sAlien;

		struct SBlackhole {
			bool state;
			int iNum;
			std::vector<Point> vpPos;
			std::vector<float> vpSize;
			std::vector<int>   viMode;
		}sblackhole;
		int iStageNum;
		bool isLoad;
		bool LoadStage(int iStage);
		Obj() { Init(); }
		~Obj() { Finalize(); }
	private:
		RS_ptr res;
		void Init();
		void Finalize();
		void LoadFragments(std::ifstream &ifs);
		void LoadStar(std::ifstream &ifs);
		void LoadPlanet(std::ifstream &ifs, Planet &planet);
		void LoadMeteo(std::ifstream &ifs);
		void LoadAlien(std::ifstream &ifs);
		void LoadBlackHole(std::ifstream &ifs);
	public:
		void Update();
		void Render();
	}*OBJ_ptr;
}