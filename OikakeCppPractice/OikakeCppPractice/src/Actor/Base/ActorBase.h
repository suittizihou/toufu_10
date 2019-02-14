#pragma once

class Renderer;
class HitInfo;
#include "ActorPtr.h"
#include "Status.h"
#include"EventMessage.h"
#include"ActorGroup.h"
#include"World/IWorld.h"
#include<string>
#include<functional>
#include<list>
#include"Math/Vector2/Vector2.h"
#include"Scenes/CharacterSelect/CharacterManager.h"

class ActorBase {
public:
	ActorBase();
	ActorBase(IWorld* world, const std::string& name, const Vector2& position, const Vector2& center_pos, const int& _number, const float _speed, const int input_type, const Character chara = Character::None);
	explicit ActorBase(const std::string& name);
	virtual ~ActorBase();
public:

	void Initialize();
	void FirstUpdate(float deltaTime);
	void Update(float deltaTime);
	void Draw(Renderer& renderer);
	void DrawShadow(Renderer& renderer);
	void Finalize();
	void HandleMessage(EventMessage message, void* param);

	void Collide(ActorBase& other);
	void CollideChildren(ActorBase& other);
	void CollideSibling();


	void AddChild_Front(const ActorPtr& actor);
	void AddChild_Front(ActorGroup group, const ActorPtr& actor);
	void AddChild_Back(const ActorPtr& actor);
	void AddChild_Back(ActorGroup group, const ActorPtr& actor);
	void EachChildren(std::function<void(ActorBase&)> func);
	void EachChildren(std::function<void(const ActorBase&)> func) const;
	void RemoveChildren(std::function<bool(ActorBase& actor)> func);
	void RemoveChildren();
	ActorPtr FindChildren(std::function<bool(const ActorBase&)> func);
	ActorPtr FindChildren(const std::string& name);
	ActorGroup GetActorGroup() const;
	Status GetStatus() const;
	Character GetCharacter() const;
	std::string GetName() const;
	std::list<ActorPtr>& GetChildren();
	void ClearChildren();
	void ChangeStatus(Status status);
	Vector2 GetTarget_Pos();
	Vector2 GetVec2Position();
	Vector2 GetCenterPosition();
	Vector2 GetMovement() const;
	Vector2 GetSponedPosition() const;
	int GetControllerType() const;
	int GetChildNum() const;
	int GetNumber();
	float GetSpeed();
	bool GetKinnikuMove();

	void sort();
protected:
	virtual void OnInitialize();
	virtual void OnFirstUpdate(float deltaTime);
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(Renderer& renderer);
	virtual void OnDrawShadow(Renderer& renderer);
	virtual void OnFinalize();
	virtual void OnMessage(EventMessage message, void* param);
	virtual bool IsCollide(const ActorBase& other, HitInfo& hitInfo);
	virtual void OnCollide(const HitInfo& hitInfo);

protected:
	IWorld* world;
	std::string name;
	ActorGroup actor_group{};
	int input_type;
	Character chara;
	Status	status;
	Vector2 target_pos;
	Vector2 position;
	Vector2 center_pos;
	Vector2 movement = Vector2::Zero;
	Vector2 sponed_pos{};
	float speed{};
	int number = 0;
	bool kinniku_move{ false };		// ãÿì˜ì§ïÖÇ…âüÇ≥ÇÍÇΩÇ∆Ç´trueÇ…Ç»ÇÈÇ‡ÇÃ

private:
	std::list<ActorPtr> children;
private:
	//ÉRÉsÅ[ã÷é~
	ActorBase(const ActorBase& other) = delete;
	ActorBase& operator = (const ActorBase& other) = delete;
};