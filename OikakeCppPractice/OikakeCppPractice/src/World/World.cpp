#include "World.h"
#include "Actor/Base/ActorGroup.h"
#include"Actor/Base/EventMessage.h"

World::World()
	: actorManager()
	, listener([](EventMessage, void*) {})
{
}

World::~World() {
}

void World::Initialize() {
	Clear();
	actorManager.Initialize();
}

void World::FirstUpdate(float deltaTime) {
	actorManager.FirstUpdate(deltaTime);
}

void World::Update(float deltaTime)
{
	actorManager.Update(deltaTime);
}

void World::Draw(Renderer& renderer) {
	actorManager.Draw(renderer);
}

void World::Finalize() {
	actorManager.Finalize();
	Clear();
}

void World::Clear()
{
	actorManager.Clear();
}

void World::AddActor_Front(ActorGroup group, const ActorPtr & actor)
{
	actorManager.AddActor_Front(group, actor);
}

void World::AddActor_Back(ActorGroup group, const ActorPtr & actor)
{
	actorManager.AddActor_Back(group, actor);
}

ActorPtr World::FindActor(const std::string& name) {
	return actorManager.FindActor(name);
}

ActorPtr World::FindActor(ActorGroup group, const std::string& name) {
	return actorManager.FindActor(group, name);
}

ActorPtr World::GetRoot(ActorGroup group) {
	return actorManager.GetRoot(group);
}


void World::SendEventMessage(EventMessage message, void * param) {
	listener(message, param);
	actorManager.HandleMessage(message, param);
}

SceneShareValue & World::GetSceneShareValue()
{
	return sceneShareValue;
}


void World::AddEventMessageListener(std::function<void(EventMessage, void*)> listener) {
	this->listener = listener;
}

