#include "Game.h"
#include "Title.h"

namespace Game
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
		SetName("�����^�X�N");
		/*���\�[�X����*/
		RB::Add<RS>("�������\�[�X");
		/*�^�X�N�̐���*/

		/*�f�[�^�̏�����*/

	}
	/*�^�X�N�̏I������*/
	void Obj::Finalize()
	{
		RB::Remove("�������\�[�X");
	}
	/*�^�X�N�̍X�V����*/
	void Obj::Update()
	{
		const auto kb = KB::GetState();
		/*if (kb->Now('T') == 1)
		{
			RemoveAll();
			Add<Title::Obj>();
		}*/
		const auto pad = JoyPad::GetState(0);
		if (pad->NowBut(J_BUT_1))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
		if (pad->NowBut(J_BUT_2))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
		if (pad->NowBut(J_BUT_3))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
		if (pad->NowBut(J_BUT_4))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
		if (pad->NowBut(J_BUT_5))
		{
			RemoveAll();
			Add<Title::Obj>();
		}
	}
	/*�^�X�N�̕`�揈��*/
	void Obj::Render()
	{
		if (res = RB::Find<RS>("�������\�[�X"))
		{

		}
	}
}
