#include "StageSelectIcon.h"
#include "StageManager.h"
#include "Cursor.h"
#include "StageLoad.h"
#include "Hukidasi.h"

namespace StageSelectIcon
{
	/*���\�[�X�̏���������*/
	void RS::Init()
	{
	}
	/*���\�[�X�̏I������*/
	void RS::Finalize()
	{
	}
	/*�^�X�N�̏���������*/
	void Obj::Init()
	{
		/*�^�X�N���ݒ�*/
		SetName(caTaskName);

		/*���\�[�X����*/

		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/
		type = ET;
		rIcon.Scaling(16.f * 10.f, 16.f * 10.f);
	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{

	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		const auto pad = JoyPad::GetState(0);

		IconAnimation[type](&i, &iAddOffSet, &iOffSetX, &iOffSetY);

	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (auto res = RB::Find<StageManager::RS>(StageManager::caResName))
		{
			Frec src(16.f * (iOffSetX + iAddOffSet), iOffSetY * 16.f, 16.f, 16.f);
			rIcon.Draw(&res->iStageImg, &src);
		}
	}
	void AnimEarth(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 37;
		*iOffSetY = 1;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
	void AnimMeteo(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 41;
		*iOffSetY = 1;
		if (*iAnimCount >= 13)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
	void AnimGalaxy(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 45;
		*iOffSetY = 1;
		if (*iAnimCount >= 15)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 2) % 8;
		}
		++*iAnimCount;
	}
	void AnimUranus(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 33;
		*iOffSetY = 1;
		if (*iAnimCount >= 15)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
	void AnimBlackHole(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 53;
		*iOffSetY = 1;
		if (*iAnimCount >= 15)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 2) % 8;
		}
		++*iAnimCount;
	}
	void AnimTimeAttack(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 85;
		*iOffSetY = 1;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
	void AnimFragment(int * const iAnimCount, int * const iAddOffSet, int * const iOffSetX, int * const iOffSetY)
	{
		*iOffSetX = 89;
		*iOffSetY = 1;
		if (*iAnimCount >= 16)
		{
			*iAnimCount = 0;
			*iAddOffSet = (*iAddOffSet + 1) % 4;
		}
		++*iAnimCount;
	}
}
