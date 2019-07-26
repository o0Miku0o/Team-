#include "MyGame/MyApp.h"
#include "Title.h"
#include "GameInit.h"

//#include "Result.h"
//#include "StageManager.h"
//#include "TimeAttack.h"
//#include "MiniGame.h"

//�O���[�o���̈�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//

//�����������[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
void Init()
{
	/*�����ōŏ��̃^�X�N��ǉ�*/
	/*TB::Add<StageManager::Obj>();
	TB::Add<Result::Obj>()->SetParam(1, std::array<byte, 3>({ 2, 3, 1 }));/*/
	TB::Add<GameInit::Obj>();/**/
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
