#include "GameApplication.h"

#include<DxLib.h>
#include"Application/LoadData/LoadData.h"
#include"Utility/CSVLoader/CSVLoader.h"
#include"Application/Window/Window.h"
bool GameApplication::isShutDown = false;

GameApplication::GameApplication()
	: fps()
{
#ifndef _DEBUG
	//ログを出さない
	SetOutApplicationLogValidFlag(FALSE);
#endif


	CSVLoader loader("setting.csv");

	//ウィンドウの大きさを設定
	SetGraphMode(loader.GetDataInt(1,0), loader.GetDataInt(1, 1), 32);
	//ウィンドウモードに変更
	ChangeWindowMode((loader.GetDataString(1,2) == "TRUE") ? TRUE : FALSE);
	//ウィンドウの名前を設定
	SetMainWindowText(loader.GetDataString(1,3).c_str());
	//マウスを表示するか設定
	isMouseShow = (loader.GetDataString(1, 4) == "TRUE") ? TRUE : FALSE;
	//フルシーンアンチエイリアスを設定
	SetFullSceneAntiAliasingMode(4, 2);
	//ゲームアイコンを設定
	//SetWindowIconID(ID_ICON);

	Window::width = loader.GetDataInt(1,0);
	Window::height = loader.GetDataInt(1, 1);

}


GameApplication::~GameApplication()
{
}

int GameApplication::Run()
{
	//DXLIB初期化
	if (DxLibInit() == false) {
		return -1;
	}
	//マウスを表示するか設定
	SetMouseDispFlag(isMouseShow);


	Initialize();

	//ゲームループ
	while (IsShutDown() && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		fps.Update();
		FirstUpdate(fps.GetdeltaTime());
		Update(fps.GetdeltaTime());

		ClearDrawScreen();

		Draw();
#ifdef _DEBUG
		fps.Draw();
#endif

		Reset();

		ScreenFlip();

		fps.Wait();
	}


	Finalize();

	//DXLIB終了
	DxLibEnd();

	return 0;
}

void GameApplication::ShutDown()
{
	isShutDown = true;
}

bool GameApplication::DxLibInit() {


	//DxLibの初期化
	if (DxLib_Init() == -1) {
		return false;
	}

	//裏画面に描画設定
	SetDrawScreen(DX_SCREEN_BACK);

	//Zバッファを有効にする
	SetUseZBuffer3D(TRUE);
	//Zバッファへの書き込みを有効にする。
	SetWriteZBuffer3D(TRUE);

	return true;
}


void GameApplication::DxLibEnd() {
	//DxLibの終了
	DxLib_End();
}


bool GameApplication::IsShutDown() {
	return ProcessMessage() == 0  && isShutDown == false;
}