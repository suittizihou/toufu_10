#include "ActorBase.h"
#include"Collision/HitInfo.h"
#include<algorithm>
#include"World/IWorld.h"
ActorBase::ActorBase()
	: ActorBase(nullptr, "none", Vector2::Zero, Vector2::Zero, 0, 0.0f, 0)
{
}

ActorBase::ActorBase(IWorld * world, const std::string & name, const Vector2& position, const Vector2& center, const int& _number, const float _speed, const int input_type, const Character chara)
	: world(world)
	, name(name)
	, status(Status::Active)
	, position(position)
	, center_pos(center)
	, number(_number)
	, speed(_speed)
	, input_type(input_type)
	, chara(chara)
{
}

ActorBase::ActorBase(const std::string & name)
	: ActorBase(nullptr, name, Vector2::Zero, Vector2::Zero, 0, 0.0f, 0)
{
}

ActorBase::~ActorBase()
{
}

void ActorBase::Initialize()
{
	OnInitialize();
	EachChildren([](ActorBase& actor) {
		actor.Initialize();
	});
}

void ActorBase::FirstUpdate(float deltaTime) {
	OnFirstUpdate(deltaTime);
	//TODO: 該当するstatusのみのアクターだけを抽出して更新する
	EachChildren([&deltaTime](ActorBase& actor) {
		bool isActive = actor.GetStatus() == Status::Active;
		bool isUpdateOnly = actor.GetStatus() == Status::UpdateOnly;

		if (isActive || isUpdateOnly)
			actor.FirstUpdate(deltaTime);
		});
}

void ActorBase::Update(float deltaTime)
{
	OnUpdate(deltaTime);
	//TODO: 該当するstatusのみのアクターだけを抽出して更新する
	EachChildren([&deltaTime](ActorBase& actor) {
		bool isActive = actor.GetStatus() == Status::Active;
		bool isUpdateOnly = actor.GetStatus() == Status::UpdateOnly;

		if (isActive || isUpdateOnly)
			actor.Update(deltaTime);
	});
}

void ActorBase::Draw(Renderer & renderer)
{
	OnDraw(renderer);

	EachChildren([&renderer](ActorBase& actor) {
		bool isActive = actor.GetStatus() == Status::Active;
		bool isDrawOnly = actor.GetStatus() == Status::DrawOnly;

		if (isActive || isDrawOnly)
			actor.Draw(renderer);
	});
}

void ActorBase::DrawShadow(Renderer & renderer)
{
	OnDrawShadow(renderer);
	EachChildren([&renderer](ActorBase& actor) {
		actor.DrawShadow(renderer);
	});
}

void ActorBase::Finalize()
{
	OnFinalize();

	EachChildren([](ActorBase& actor) {
		actor.Finalize();
	});
}

void ActorBase::HandleMessage(EventMessage message, void * param)
{
	OnMessage(message, param);
	EachChildren([&](ActorBase& child) {
		child.HandleMessage(message, param);
	});
}
void ActorBase::Collide(ActorBase & other)
{

	HitInfo hitInfo;


	if (IsCollide(other, hitInfo)) {
		hitInfo.collideActor = &other;
		OnCollide(hitInfo);
		hitInfo.collideActor = this;
		other.OnCollide(hitInfo);
	}


	//子の衝突判定を行う
	EachChildren([&](ActorBase& actor) {
		actor.Collide(other);
	});

}

void ActorBase::CollideChildren(ActorBase & other)
{
	EachChildren([&other](ActorBase& my) 
	{
		other.EachChildren([&](ActorBase& target) 
		{
			my.Collide(target);
		});
	});
}

void ActorBase::CollideSibling()
{
	for (auto&& i = children.begin(); i != children.end(); ++i) {
		std::for_each(std::next(i), children.end(),
			[&](const ActorPtr& actor) {(*i)->Collide(*actor); });
	}
}


void ActorBase::AddChild_Front(const ActorPtr & actor)
{
	children.emplace_front(actor);
	actor->Initialize();
}

void ActorBase::AddChild_Front(ActorGroup group, const ActorPtr & actor)
{
	world->AddActor_Front(group, actor);
}

void ActorBase::AddChild_Back(const ActorPtr & actor)
{
	children.emplace_back(actor);
	actor->Initialize();
}

void ActorBase::AddChild_Back(ActorGroup group, const ActorPtr & actor)
{
	world->AddActor_Back(group, actor);
}

void ActorBase::sort()
{
	children.sort([](ActorPtr a, ActorPtr b) { return a->GetVec2Position().y < b->GetVec2Position().y; });
}
void ActorBase::EachChildren(std::function<void(ActorBase&)> func)
{
	std::for_each(children.begin(), children.end(),
		[&](const ActorPtr& actor) { func(*actor); });
}

void ActorBase::EachChildren(std::function<void(const ActorBase&)> func) const
{
	std::for_each(children.begin(), children.end(),
		[&](const ActorPtr& actor) { func(*actor); });
}

void ActorBase::RemoveChildren(std::function<bool(ActorBase&actor)> func)
{
	children.remove_if(
		[&](const ActorPtr& actor) {return func(*actor); });
}

void ActorBase::RemoveChildren()
{
	RemoveChildren([](ActorBase& actor) {
		if (actor.GetStatus() == Status::Dead) {
			actor.Finalize();
			return true;
		}
		return false;
	});

	EachChildren([](ActorBase& actor) {
		actor.RemoveChildren();
	});
}

ActorPtr ActorBase::FindChildren(std::function<bool(const ActorBase&)> func)
{
	auto childIterator = std::find_if(children.begin(), children.end(),
		[&func](const ActorPtr& child) {
		return func(*child);
	});

	//見つかったら
	if (childIterator != children.end())
		return *childIterator;

	//子にもFindChildrenを実行させる
	for (ActorPtr& child : children) {
		ActorPtr actor = child->FindChildren(func);
		if (actor != nullptr)
			return actor;
	}

	return nullptr;
}

ActorPtr ActorBase::FindChildren(const std::string & name)
{
	return FindChildren([&](const ActorBase& actor) {
		return actor.GetName() == name;
	});
}

ActorGroup ActorBase::GetActorGroup() const
{
	return actor_group;
}

void ActorBase::ChangeStatus(Status status)
{
	this->status = status;
}

Status ActorBase::GetStatus() const
{
	return status;
}

std::string ActorBase::GetName() const
{
	return name;
}

int ActorBase::GetControllerType() const
{
	return input_type;
}

Character ActorBase::GetCharacter() const {
	return chara;
}

void ActorBase::ClearChildren()
{
	EachChildren([&](ActorBase& child) {
		child.ClearChildren();
	});
	children.clear();
}

std::list<ActorPtr>& ActorBase::GetChildren()
{
	return children;
}

int ActorBase::GetChildNum() const
{
	return static_cast<int>(std::distance(children.begin(), children.end()));
}

void ActorBase::OnInitialize()
{
}

void ActorBase::OnFirstUpdate(float deltaTime) {
	static_cast<void>(deltaTime);
}

void ActorBase::OnUpdate(float deltaTime)
{
	static_cast<void>(deltaTime);
}

void ActorBase::OnDraw(Renderer & renderer)
{
	static_cast<void>(renderer);
}

void ActorBase::OnDrawShadow(Renderer & renderer)
{
	static_cast<void>(renderer);
}

void ActorBase::OnFinalize()
{
}

void ActorBase::OnMessage(EventMessage message, void * param)
{
	static_cast<void>(message);
	static_cast<void>(param);
}


bool ActorBase::IsCollide(const ActorBase & other, HitInfo & hitInfo)
{
	static_cast<void>(other);
	static_cast<void>(hitInfo);
	return false;
}

void ActorBase::OnCollide(const HitInfo & hitInfo)
{
	static_cast<void>(hitInfo);
}

Vector2 ActorBase::GetVec2Position()
{
	return position;
}

Vector2 ActorBase::GetCenterPosition() {
	return center_pos;
}

int ActorBase::GetNumber()
{
	return number;
}
Vector2 ActorBase::GetMovement( ) const
{
	return movement;
}

float ActorBase::GetSpeed() {
	return speed;
}