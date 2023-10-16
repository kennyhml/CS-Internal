#pragma once

struct Model;
struct Vector3;
struct Ray;
struct Trace;
struct HandleEntity;
struct Matrix3x4;
struct CUnknown;

enum SolidType
{
	SOLID_NONE = 0,	// no solid model
	SOLID_BSP = 1,	// a BSP tree
	SOLID_BBOX = 2,	// an AABB
	SOLID_OBB = 3,	// an OBB (not implemented yet)
	SOLID_OBB_YAW = 4,	// an OBB, constrained so that it can only yaw
	SOLID_CUSTOM = 5,	// Always call into the entity for tests
	SOLID_VPHYSICS = 6,	// solid vphysics object, get vcollide from the model and collide with that
	SOLID_LAST,
};

struct Collideable
{
	virtual HandleEntity* GetEntityHandle() = 0;

	virtual const Vector3& OBBMins() const = 0;
	virtual const Vector3& OBBMaxs() const = 0;

	virtual void WorldSpaceTriggerBounds(Vector3* mins, Vector3* maxs) const = 0;

	virtual bool TestCollision(const Ray& ray, unsigned int mask, Trace& tr) = 0;

	virtual bool TestHitboxes(const Ray& ray, unsigned int mask, Trace& tr) = 0;

	virtual int GetCollisionModelIndex() = 0;

	virtual const Model* GetCollisionModel() = 0;

	virtual const Vector3& GetCollisionOrigin() const = 0;
	virtual const Vector3& GetCollisionAngles() const = 0;
	virtual const Matrix3x4& CollisionToWorldTransform() const = 0;

	virtual SolidType GetSolid() const = 0;
	virtual int GetSolidFlags() const = 0;

	virtual CUnknown* GetIClientUnknown() = 0;

	virtual int GetCollisionGroup() const = 0;

	virtual void WorldSpaceSurroundingBounds(Vector3* mins, Vector3* maxs) = 0;

	virtual unsigned int GetRequiredTriggerFlags() const = 0;

	// returns NULL unless this collideable has specified FSOLID_ROOT_PARENT_ALIGNED
	virtual const Matrix3x4* GetRootParentToWorldTransform() const = 0;
	virtual void* GetVPhysicsObject() const = 0;
};