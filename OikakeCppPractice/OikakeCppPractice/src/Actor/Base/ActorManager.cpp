#include "ActorManager.h"

#include "ActorBase.h"
#include "ActorGroup.h"

ActorManager::ActorManager()
	: root("Root")
{
}

void ActorManager::Initialize() {
	Clear();
	RegisterGroup();
	root.Initialize();
}

void ActorManager::FirstUpdate(float deltaTime) {
	root.FirstUpdate(deltaTime);
	//root.RemoveChildren();
}

void ActorManager::Update(float deltaTime) {
	root.Update(deltaTime);
	Collide();
	root.RemoveChildren();
}

void ActorManager::Draw(Renderer& renderer) {
	root.Draw(renderer);
}


void ActorManager::Finalize() {
	root.Finalize();
	Clear();

}

void ActorManager::AddActor_Front(ActorGroup group, const ActorPtr & actor)
{
	actors[group]->AddChild_Front(actor);
}

void ActorManager::AddActor_Back(ActorGroup group, const ActorPtr & actor)
{
	actors[group]->AddChild_Back(actor);
}


void ActorManager::AddGroup(ActorGroup group, const std::string& name, const ActorPtr& actor ) {
	ActorPtr target = actor == nullptr ? std::make_shared<ActorBase>(name) : actor;

	actors[group] = target;
	root.AddChild_Back(actors[group]);
}

void ActorManager::HandleMessage(EventMessage message, void * param)
{
	root.HandleMessage(message, param);
}

ActorPtr ActorManager::FindActor(const std::string& name) {
	return root.FindChildren(name);
}

ActorPtr ActorManager::FindActor(ActorGroup group, const std::string& name) {
	if (actors[group]->GetName() == name)
		return actors[group];
	return actors[group]->FindChildren(name);
}

ActorPtr ActorManager::GetRoot(ActorGroup group)
{
	return actors[group];
}

void ActorManager::Clear()
{
	root.ClearChildren();
	for (auto& actor : actors) {
		actor.second->ClearChildren();
	}
	actors.clear();
}

void ActorManager::RegisterGroup() {
	AddGroup(ActorGroup::BackGround, "BackGrountRoot");
	AddGroup(ActorGroup::NormalToufu, "NormalToufuRoot");
	AddGroup(ActorGroup::MetalToufu, "MetalToufuRoot");
	AddGroup(ActorGroup::Player, "PlayerRoot");
	AddGroup(ActorGroup::Player2, "PlayerRoot");
	AddGroup(ActorGroup::UI, "UIRoot");
}

void ActorManager::Collide() {
	actors[ActorGroup::Player]->CollideChildren(*actors[ActorGroup::NormalToufu]);
	actors[ActorGroup::Player2]->CollideChildren(*actors[ActorGroup::NormalToufu]);
	actors[ActorGroup::NormalToufu]->CollideChildren(*actors[ActorGroup::NormalToufu]);
	actors[ActorGroup::MetalToufu]->CollideChildren(*actors[ActorGroup::NormalToufu]);
}