#include "SceneNull.h"
#include "Scene.h"

void SceneNull::LoadAssets() {
}

void SceneNull::Initialize() {
}

void SceneNull::FirstUpdate(float deltaTime)
{
	static_cast<void>(deltaTime);
}

void SceneNull::Update(float deltaTime) {
	static_cast<void>(deltaTime);
}

void SceneNull::Draw() const {
}

bool SceneNull::IsEnd() const {
	return false;
}

Scene SceneNull::Next() const {
	return Scene::None;
}

void SceneNull::Finalize() {
}