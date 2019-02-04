#include "SceneManager.h"
#include "SceneNull.h"
#include "Scene.h"
#include "Math/Math.h"
#include "Application/FPS/FPS.h"


SceneManager::SceneManager()
	: currentScene(std::make_shared<SceneNull>())
	, fadeManager() {
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize() {
	Finalize();
	scenes.clear();
}

void SceneManager::Update(float deltaTime) {

	UpdateSceneChange();
	//!フェードイン終了後シーンのアップデート
	if (fadeManager.GetFadeType() == FadeType::FadeOutWait) {
		currentScene->FirstUpdate(deltaTime);
		currentScene->Update(deltaTime);
	}
	fadeManager.Update(deltaTime);
}

void SceneManager::Draw() const {
	currentScene->Draw();
	fadeManager.Draw();
}

void SceneManager::Finalize() {
	currentScene->Finalize();
	currentScene = std::make_shared<SceneNull>();
}

void SceneManager::Add(Scene name, const IScenePtr & scene) {
	scenes[name] = scene;
}

void SceneManager::Change(Scene name) {
	Finalize();
	currentScene = scenes[name];
	currentScene->LoadAssets();
	currentScene->Initialize();
	fadeManager.FadeIn();
}

void SceneManager::UpdateSceneChange()
{
	// シーン終了していてフェードが始まっていない場合フェード開始
	if (currentScene->IsEnd() && fadeManager.GetFadeType() == FadeType::FadeOutWait) {
		fadeManager.FadeOut();
	}
	// シーンとフェードが終わっていたらシーン変更
	if (currentScene->IsEnd() && fadeManager.GetFadeType() == FadeType::FadeInWait) {
		Change(currentScene->Next());
	}
}
