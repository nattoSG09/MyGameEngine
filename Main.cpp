//インクルード
#include <Windows.h>
#include "Direct3D.h"
#include "Sprite.h"
#include "Dice.h"
#include "Camera.h"
#include "Light.h"
#include "Fbx.h"
#include "Input.h"

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const char* WIN_TITLE_NAME = "さんぷるげ〜む";  //ウィンドウクラス名

const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント(プログラムのスタート地点)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);     //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）

	RegisterClassEx(&wc);  //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		WIN_TITLE_NAME,     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                 //ウィンドウ幅
		winH,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;
	//Direct3D初期化
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		MessageBox(nullptr, "Direct3Dの初期化に失敗しました", "エラー", MB_OK);
		PostQuitMessage(0);
	}

	//カメラを初期化
	Camera::Initialize(winW,winH);

	//Inputの初期化
	Input::Initialize(hWnd);

	//ライトの初期化
	Light::Initialize();

	//Quadを作成
	/*Quad* pQuad = new Quad;
	hr = pQuad->Initialize();*/

	//DIceを初期化
	Dice* pDice = new Dice;
	hr = pDice->Initialize();

	//Spriteを初期化
	Sprite* pSprite = new Sprite;
	hr = pSprite->Initialize(winW,winH);

	//fbxを初期化
	Fbx* pFbx = new Fbx;
	hr = pFbx->Load("Assets/Ball2.fbx");

	Fbx* pFbx2 = new Fbx;
	hr = pFbx2->Load("Assets/Ball2.fbx");

	if (FAILED(hr)) {
		MessageBox(nullptr, "いずれかのモデルの初期化に失敗しました", "エラー", MB_OK);
		PostQuitMessage(0);
	}


	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)//プログラムが実行している間
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			//Direct3d更新処理
			{
				//Camaraの更新処理
				Camera::Update();

				//Inputの更新処理
				Input::Update();

				//ライトの更新処理
				Light::Update();
			}

			//ゲームの処理
			Direct3D::BeginDraw();

			//深度バッファクリア
			Direct3D::pContext_->ClearDepthStencilView(Direct3D::pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

			//いろいろ出力
			static float angle = 0; angle += 0.01;
			
			//Diceを描画
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

			//spriteを描画
			#if 0
			{
				Transform t;
				t.position_ = { 0,-0.7,0 };
				pSprite->Draw(t);
			}
			#endif
			
			//Oden.fbxを描画
			#if 1
			{
				//ライトの処理
				{
					static float x = 0;
					if (Input::IsKey(DIK_A))x -= 0.001f;
					if (Input::IsKey(DIK_D))x += 0.001f;
					static float y = 0;
					if (Input::IsKey(DIK_W))y += 0.001f;
					if (Input::IsKey(DIK_S))y -= 0.001f;
					static float z = 0;
					if (Input::IsKey(DIK_Q))z += 0.001f;
					if (Input::IsKey(DIK_E))z -= 0.001f;
					//Light::SetPosition(XMFLOAT4(x, y, z, 0));//動かせるライト
					Light::SetPosition(XMFLOAT4(-0.3f, 0.6f, -0.6f, 0));//ボール用ライト
					Light::SetIntensity(2);
				}

				//描画
				static Transform t;
				t.position_.x = 3.0f;
				pFbx->Draw(t);

				static Transform t2;
				t2.position_.x = -3.0f;
				pFbx->Draw(t2);

			}
			#endif

			//入力処理確認
			if (Input::IsKeyDown(DIK_ESCAPE))
			{
				static int cnt = 0;
				cnt++;
				if(cnt >= 3)
					PostQuitMessage(0);
			}

			//描画処理
			Direct3D::EndDraw();
		}
	}

	//解放処理
	Direct3D::Release();
	
	SAFE_DELETE(pDice);
	SAFE_DELETE(pSprite);
	SAFE_DELETE(pFbx);
	SAFE_DELETE(pFbx2);
	Input::Release();

	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//ウィンドウが閉じたら
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}