#include "MyGame/MyApp.h"
#include "resource.h"
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
		//�`�揈��
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		//�`��J�n
		hDC = BeginPaint(hWnd_, &ps);
		//�I�t�X�N���[�����I���X�N���[���ɕ`��
		Rec::DrawBackToFront(hDC);
		//�`��I��
		EndPaint(hWnd_, &ps);
		break;
	}
	case MM_WOM_DONE:
	{
		WSound::LoopProc(wParam_, lParam_);
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
		/**/1920/*/x/**/,
		// �E�B���h�E�̍���
		/**/1080/*/y/**/,
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
bool WaitProcess(long * const setsec_, const long waitsec_)
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
	/**/
	while (ShowCursor(false) != -1);
	/**/
	KB kb;
	//�}�E�X�̏�����
	MS ms(g_hWnd);
	//��`�N���X��������
	Rec::Init(g_hWnd);
	/*JoyPad�̏�����*/
	JoyPad::Init(3000);
	/*JoyPad�P*/
	JoyPad joy1;
	/*JoyPad�Q*/
	JoyPad joy2;
	//�����̏�����
	srand(/**/(unsigned int)time(nullptr)/*/0/**/);
	//�Q�[���̏���������
	Init();
	//�A�v���P�[�V�����܂��̓f�o�C�X�h���C�o��
	//�ŏ��^�C�}����\���A�~���b�P�ʂŎw��
	timeBeginPeriod(1);
	//�����O�̌��ݎ��Ԃ��擾����
	long tmptime1 = timeGetTime();
	long tmptime2 = timeGetTime();
	constexpr long cedFps = FP(1000.0 / 60.0);

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
		else if (WaitProcess(&tmptime1, cedFps))
		{
			//�L�[�{�[�h���͂��擾
			KB::GetKeyState();
			//�}�E�X���͂��擾
			MS::GetMouseState();
			//JoyPad�̏����擾
			JoyPad::GetStateAll();
			//�Q�[���̍X�V����
			if (Update()) PostQuitMessage(0);

			//�`��O�ɃI�t�X�N���[���������h��Ԃ��i���Z�b�g�H�j
			Rec::ResetOff(BLACKNESS);
			//�Q�[���̕`�揈��
			Render();

#ifdef _DEBUG
			std::string tex = "FPS[" + std::to_string(int(1000. / FToD(SubFP(FP(timeGetTime()), FP(tmptime2))))) + "]";
			Font f;
			f.FontCreate("���C���I");
			f.Draw(&Point(200.f, 0.f), tex.c_str());
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
	//�E�B���h�E�n���h����j��
	DeleteObject(g_hWnd);
	//�I��
	return msg.wParam;
}