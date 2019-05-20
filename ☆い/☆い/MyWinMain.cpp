#include "MyGame/MyApp.h"
#include "resource.h"
#ifdef _DEBUG
#include "StageManager.h"
#include "MyGame/TaskBase.h"
#endif // _DEBUG

//�����������[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
void Init();
//�I�������[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
void Finalize();
//�X�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
bool Update();
//�`�揈���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//
void Render();

//�O���[�o���̈�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[//

//�E�B���h�E�̃n���h��
static HWND g_hWnd;

//�E�B���h�E�v���V�[�W���֐�
//(�E�B���h�E�Y����̃��b�Z�[�W�ɉ����ď���������)
LRESULT CALLBACK WinProc(HWND hWnd_, UINT message_, WPARAM wParam_, LPARAM lParam_)
{
	switch (message_)
	{
	case WM_CREATE:
	{
		if (FindWindow(WINNAME, WINCLASS))
		{
			MessageBox(nullptr, "���̃A�v���P�[�V�����͋N���ς݂ł��B", WINNAME, MB_ICONWARNING);
			PostQuitMessage(1);
		}
		break;
	}
		//�`�揈��
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		//�`��J�n
		hDC = BeginPaint(hWnd_, &ps);
		//�I�t�X�N���[�����I���X�N���[���ɕ`��
		Rec::DrawBackToFront(hDC);

		if (auto kb = KB::GetState())
		{
			if (kb->On(VK_CONTROL) && kb->Down('Z'))
			{
				SaveBitMap(hDC, &Rec::Win, "./data/image/other/Stage/ScreenShot.bmp");
			}
		}

		//�`��I��
		EndPaint(hWnd_, &ps);
		break;
	}
	case MM_WOM_DONE:
	{
		WSound::LoopProc(wParam_, lParam_);
		/*MM_WOM_DONE�ɂ�閳�����[�v�̉������@���킩��Ȃ��������߁A*/
		/*�_�~�[�̃��b�Z�[�W�𑗐M���܂��B*/
		SendMessage(g_hWnd, WM_USER, 0, 0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam_)
		{
		case VK_ESCAPE:
			//WM_QUIT���b�Z�[�W�𔭍s
			PostQuitMessage(0);
			break;
		}
		break;
	}
	case WM_CLOSE:
	case WM_DESTROY:
	{
		//WM_QUIT���b�Z�[�W�𔭍s
		PostQuitMessage(0);
		break;
	}
	//��L�ȊO�̃��b�Z�[�W��Windows�ɔC����
	default:
	{
		return DefWindowProc(hWnd_, message_, wParam_, lParam_);
	}
	}
	return 0;
}

//�A�v���P�[�V�����̏�����
bool ApplicationInitialize(HINSTANCE hThisInst_, int nWinMode_)
{
	WNDCLASSEX winclass;
	//�E�B���h�E�N���X���`����
	// ���̃C���X�^���X�ւ̃n���h��
	winclass.hInstance = hThisInst_;
	// �E�B���h�E�N���X��
	winclass.lpszClassName = WINCLASS;
	// �E�B���h�E�֐�
	winclass.lpfnWndProc = WinProc;
	// �E�B���h�E�X�^�C���i�f�t�H���g�j
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	// WNDCLASSEX�\���̂̃T�C�Y��ݒ�
	winclass.cbSize = sizeof(WNDCLASSEX);
	// ���[�W�A�C�R��
	winclass.hIcon = LoadIcon(hThisInst_, MAKEINTRESOURCE(IDI_ICON1));
	// �X���[���A�C�R��
	winclass.hIconSm = LoadIcon(hThisInst_, MAKEINTRESOURCE(IDI_ICON1));
	// �J�[�\���X�^�C��
	winclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// ���j���[�i�Ȃ��ɐݒ�j
	winclass.lpszMenuName = nullptr;
	// �G�N�X�g��
	winclass.cbClsExtra = 0;
	// �K�v�ȏ��
	winclass.cbWndExtra = 0;
	// �E�B���h�E�̔w�i
	winclass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	//�E�B���h�E�N���X��o�^����
	if (!RegisterClassEx(&winclass))
		return 0;
	//�E�B���h�E�𐶐�
	g_hWnd = CreateWindow(
		// �E�B���h�E�N���X�̖��O
		WINCLASS,
		// �E�B���h�E�^�C�g��
		WINNAME,
		// �E�B���h�E�X�^�C��
		/**/WS_VISIBLE | WS_POPUP/*/WS_SYSMENU/**/,
		// �E�B���h�E�̍��p�w���W
		0,
		// �E�B���h�E�̍��p�x���W
		0,
		// �E�B���h�E�̕�
		1920,
		// �E�B���h�E�̍���
		1080,
		// �e�E�B���h�E
		NULL,
		// ���j���[
		NULL,
		// ���̃v���O�����̃C���X�^���X�̃n���h��
		hThisInst_,
		// �ǉ�����
		NULL
	);
	// �E�B���h�E��\������
	ShowWindow(g_hWnd, nWinMode_);
	UpdateWindow(g_hWnd);
	return 0;
}

//�w�莞�ԏ�����҂֐�
//(�R���s���[�^�̏������x�̈Ⴂ�ŏ����������Ȃ肷���Ȃ��悤�ɂ���)
bool WaitProcess(unsigned long * const setsec_, const unsigned long waitsec_)
{
	if (SubFP(FP(timeGetTime()), waitsec_) >= FP(*setsec_))
	{
		*setsec_ = timeGetTime();
		return 1;
	}
	return 0;
}

//�E�B���h�E�Y�̃��C���֐�
//(�A�v���P�[�V�����̃G���g���[�|�C���g)
int WINAPI WinMain(HINSTANCE hThisInst_, HINSTANCE hPrevInst_, LPSTR lpszArgs_, int nWinMode_)
{
	MSG msg;
	//�\������E�B���h�E�̒�`�A�o�^�A�\��
	if (ApplicationInitialize(hThisInst_, nWinMode_))
		return 0;
	/*�L�[�{�[�h*/
	KB kb;
	/*�}�E�X*/
	MS ms(g_hWnd);
	/*�}�E�X�̕\��/��\��*/
	MS::Visible(false);
	/*��`�N���X��������*/
	Rec::Init(g_hWnd);
	/*JoyPad�̏�����*/
	JoyPad::Init(3000);
	/*JoyPad�P*/
	JoyPad joy1;
	/*JoyPad�Q*/
	JoyPad joy2;
	/*�����̏�����*/
	srand(/**/(unsigned int)time(nullptr)/*/0/**/);
	//�A�v���P�[�V�����܂��̓f�o�C�X�h���C�o��
	//�ŏ��^�C�}����\���A�~���b�P�ʂŎw��
	timeBeginPeriod(1);
	//�����O�̌��ݎ��Ԃ��擾����
	unsigned long tmptime1 = timeGetTime();
	unsigned long tmptime2 = timeGetTime();
	constexpr unsigned long celFPS = FP(1000.0 / 60.0);

	byte bArr[40] = {};
	byte bFPS = 0;
	byte bCount = 0;
#ifdef _DEBUG
	fix fZoom = 1.f;
#endif

	//�Q�[���̏���������
	Init();
	//���C�����b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//���b�Z�[�W��WM_QUIT�Ȃ烋�[�v�𔲂���
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (WaitProcess(&tmptime1, celFPS))
		{
			//�L�[�{�[�h���͂��擾
			KB::GetKeyState();
			//�}�E�X���͂��擾
			MS::GetMouseState();
			//JoyPad�̏����擾
			JoyPad::GetStateAll();

			//�Q�[���̍X�V����
			if (Update()) PostQuitMessage(0);
			//
			Particle::UpdateAll();
			//
			Animation::UpdateAll();

#ifdef _DEBUG
			fix fX = 0.f, fY = 0.f;
			if (kb.On('I'))
			{
				fY -= 10.f;
			}
			if (kb.On('K'))
			{
				fY += 10.f;
			}
			if (kb.On('J'))
			{
				fX -= 10.f;
			}
			if (kb.On('L'))
			{
				fX += 10.f;
			}
			if (kb.On('Y'))
			{
				fZoom = Min(fZoom + 0.2f, 2.f);
			}
			if (kb.On('U'))
			{
				fZoom = Max(fZoom - 0.2f, 1.f);
			}
			if (kb.Down(VK_BACK)) {
				if (auto sm = TaskBase::Find<StageManager::Obj>("�X�e�[�W�����^�X�N"))
				{
					sm->bIsDebug = !sm->bIsDebug;
				}
			}
			Rec::MoveCamera(&Vector2(fX, fY));
			Rec::Zoom(fZoom);
#endif

			//�`��O�ɃI�t�X�N���[���������h��Ԃ��i���Z�b�g�H�j
			Rec::ResetOff(BLACKNESS);
			//�Q�[���̕`�揈��
			Render();
			//
			Particle::DrawAll();

			if (bCount >= sizeof(bArr) / sizeof(bArr[0]))
			{
				bCount = 0;
				unsigned short usTotal = 0;
				for (auto &ba : bArr)
				{
					usTotal += ba;
				}
				bFPS = byte(usTotal / (sizeof(bArr) / sizeof(bArr[0])));
			}
			Font f;
			f.FontCreate("���C���I");
			Point pP(Rec::GetCameraPosX() - Rec::Win.r * 0.5f, Rec::GetCameraPosY() + Rec::Win.b * 0.5f - 20.f);
			f.Draw(&pP, std::to_string(bFPS).c_str());

			bArr[bCount] = byte(1000.0 / FToD(SubFP(FP(timeGetTime()), FP(tmptime2))));
			++bCount;
#ifdef _DEBUG
#endif
			tmptime2 = timeGetTime();
		}
		//�̈斳����
		InvalidateRect(g_hWnd, nullptr, false);
		//�E�B���h�E�̍X�V�𔽉f������
		UpdateWindow(g_hWnd);
	}
	//�I������
	Finalize();
	//�A�v���P�[�V�����܂��̓f�o�C�X�h���C�o��
	//�ŏ��^�C�}����\�����ɖ߂�
	timeEndPeriod(1);
	//��`�N���X�̃o�b�t�@��j��
	Rec::Release();
	//
	Rep::Clear();
	//�E�B���h�E�n���h����j��
	DeleteObject(g_hWnd);
	//�I��
	return msg.wParam;
}