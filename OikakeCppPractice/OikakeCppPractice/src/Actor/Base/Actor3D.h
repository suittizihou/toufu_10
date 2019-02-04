#pragma once
#include"Actor/Base/ActorBase.h"
#include"Math/Vector3/Vector3.h"
#include"Math/Matrix4/Matrix4.h"
#include"Collision/ShapePtr.h"
#include<vector>

class Actor3D : public ActorBase {
public:
	Actor3D();
	Actor3D(IWorld* world, const std::string& name, const Vector3& position, const ShapePtr& body);
	Actor3D(IWorld* world, const std::string& name, const Vector3& position, const std::vector<ShapePtr>& bodies);
	virtual ~Actor3D();
public:
	void SetBodyActive(bool isActive, int index = 0);
	Matrix4 GetMatrix() const;
	std::vector<ShapePtr> GetBodies() const;
	void DrawBodies();
protected:
	virtual void OnInitialize();
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(Renderer& renderer);
	virtual void OnDrawShadow(Renderer& renderer);
	virtual void OnDrawAlpha(Renderer& renderer);
	virtual void OnFinalize();
	virtual void OnMessage(EventMessage message, void* param);
	virtual void OnCollision(const HitInfo& hitInfo);
private:
	virtual bool IsCollide(const ActorBase& other, HitInfo& hitInfo);
public:
	Vector3	position;
	Matrix4	matrix;
protected:
	//!•¡”‚Ì“–‚½‚è”»’è‚ğ‚Â”z—ñ@‰Šú’l‚Í0 empty
	std::vector<ShapePtr> bodies;
};