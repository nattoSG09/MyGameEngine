//�C���N���[�h
#include <Windows.h>
#include "Direct3D.h"
#include "Sprite.h"
#include "Dice.h"
#include "Camera.h"
#include "Fbx.h"
#include "Input.h"

//�萔�錾
const char* WIN_CLASS_NAME = "SampleGame";  //�E�B���h�E�N���X��
const char* WIN_TITLE_NAME = "����Ղ邰�`��";  //�E�B���h�E�N���X��

const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g(�v���O�����̃X�^�[�g�n�_)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);     //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j

	RegisterClassEx(&wc);  //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //�E�B���h�E�N���X��
		WIN_TITLE_NAME,     //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,                 //�E�B���h�E��
		winH,                 //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;
	//Direct3D������
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		MessageBox(nullptr, "Direct3D�̏������Ɏ��s���܂���", "�G���[", MB_OK);
		PostQuitMessage(0);
	}

	//�J������������
	Camera::Initialize(winW,winH);

	//DirectInput�̏�����
	Input::Initialize(hWnd);

	//Quad���쐬
	/*Quad* pQuad = new Quad;
	hr = pQuad->Initialize();*/

	//DIce��������
	Dice* pDice = new Dice;
	hr = pDice->Initialize();

	//Sprite��������
	Sprite* pSprite = new Sprite;
	hr = pSprite->Initialize(winW,winH);

	//fbx��������
	Fbx* pFbx = new Fbx;
	hr = pFbx->Load("Assets/Models/texture2Model.fbx");

	if (FAILED(hr)) {
		MessageBox(nullptr, "�����ꂩ�̃��f���̏������Ɏ��s���܂���", "�G���[", MB_OK);
		PostQuitMessage(0);
	}


	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)//�v���O���������s���Ă����
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			//Camara�̍X�V����
			Camera::Update();

			//Input�̍X�V����
			Input::Update();

			//�Q�[���̏���
			Direct3D::BeginDraw();

			//�[�x�o�b�t�@�N���A
			Direct3D::pContext_->ClearDepthStencilView(Direct3D::pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


			//���낢��o��
			static float angle = 0; angle += 0.01;
			
			//Dice��`��
			#if 0
			{
				Transform t;
				t.rotate_.x += angle;
				t.rotate_.y += angle;
				t.rotate_.z += angle;
				t.position_ = { -3,0,0 };
				pDice->Draw(t);
			}
			#endif

			//sprite��`��
			#if 0
			{
				Transform t;
				t.position_ = { 0,-0.7,0 };
				pSprite->Draw(t);
			}
			#endif
			
			//Oden.fbx��`��
			#if 1
			{
				Transform t;
				t.rotate_.y = angle;
				pFbx->Draw(t);
			}
			#endif

			if(Input::IsKey(DIK_ESCAPE) )
			{
				PostQuitMessage(0);  //�v���O�����I��
			}

			//�`�揈��
			Direct3D::EndDraw();
		}
	}

	//�������
	Direct3D::Release();
	
	SAFE_DELETE(pDice);
	SAFE_DELETE(pSprite);
	SAFE_DELETE(pFbx);
	Input::Release();

	return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//�E�B���h�E��������
	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}