#include "MyGame/MyApp.h"
#include "Title.h"
#include "GameInit.h"

#include "StageManager.h"
#include "TimeAttack.h"
#include "MiniGame.h"
//�O���[�o���̈�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//

//�����������[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
void Init()
{
	/*�����ōŏ��̃^�X�N��ǉ�*/
	TB::Add<GameInit::Obj>();
	/*TB::Add<StageManager::Obj>();
	TB::Add<MiniGame::Obj>();*/
}

//�I�������[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
void Finalize()
{
	TB::SysFinalize();
}

//�X�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
bool Update()
{
	return TB::SysUpdate();
}

//�`�揈���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
void Render()
{
	TB::SysRender();
}
