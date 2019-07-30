#include "MyGame/MyApp.h"
#include "Title.h"
#include "GameInit.h"

#include "Result.h"
#include "StageManager.h"

#include "JecLogo.h"

//�O���[�o���̈�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//

//�����������[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
void Init()
{
	/*�����ōŏ��̃^�X�N��ǉ�*/
	/**TB::Add<StageManager::Obj>();
	TB::Add<Result::Obj>()->SetParam(1, std::array<byte, 3>({ 3, 3, 3 }));/*/
	TB::Add<JecLogo::Obj>();/*TB::Add<GameInit::Obj>();*//**/
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
