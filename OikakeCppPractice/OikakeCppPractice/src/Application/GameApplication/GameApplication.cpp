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
	//���O���o���Ȃ�
	SetOutApplicationLogValidFlag(FALSE);
#endif


	CSVLoader loader("setting.csv");

	//�E�B���h�E�̑傫����ݒ�
	SetGraphMode(loader.GetDataInt(1,0), loader.GetDataInt(1, 1), 32);
	//�E�B���h�E���[�h�ɕύX
	ChangeWindowMode((loader.GetDataString(1,2) == "TRUE") ? TRUE : FALSE);
	//�E�B���h�E�̖��O��ݒ�
	SetMainWindowText(loader.GetDataString(1,3).c_str());
	//�}�E�X��\�����邩�ݒ�
	isMouseShow = (loader.GetDataString(1, 4) == "TRUE") ? TRUE : FALSE;
	//�t���V�[���A���`�G�C���A�X��ݒ�
	SetFullSceneAntiAliasingMode(4, 2);
	//�Q�[���A�C�R����ݒ�
	//SetWindowIconID(ID_ICON);

	Window::width = loader.GetDataInt(1,0);
	Window::height = loader.GetDataInt(1, 1);

}


GameApplication::~GameApplication()
{
}

int GameApplication::Run()
{
	//DXLIB������
	if (DxLibInit() == false) {
		return -1;
	}
	//�}�E�X��\�����邩�ݒ�
	SetMouseDispFlag(isMouseShow);


	Initialize();

	//�Q�[�����[�v
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

	//DXLIB�I��
	DxLibEnd();

	return 0;
}

void GameApplication::ShutDown()
{
	isShutDown = true;
}

bool GameApplication::DxLibInit() {


	//DxLib�̏�����
	if (DxLib_Init() == -1) {
		return false;
	}

	//����ʂɕ`��ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);
	//Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	SetWriteZBuffer3D(TRUE);

	return true;
}


void GameApplication::DxLibEnd() {
	//DxLib�̏I��
	DxLib_End();
}


bool GameApplication::IsShutDown() {
	return ProcessMessage() == 0  && isShutDown == false;
}