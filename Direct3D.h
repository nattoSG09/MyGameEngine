#pragma once

//�C���N���[�h
#include <d3d11.h>
#include <cassert>
#include <string>

//using�錾
using std::string;

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//�u��
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Direct3D
{
	extern ID3D11Device* pDevice_;			//�f�o�C�X
	extern 	ID3D11DeviceContext* pContext_;	//�f�o�C�X�R���e�L�X�g

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader(string _hlslFileName);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

	//�C���v�b�g���C�A�E�g�f�[�^���Z�b�g
	HRESULT D3DCreateInputLayout(string _hlslFileName, ID3DBlob* pCompileVS);
};