#ifndef __PHYSMGR_H__
#define __PHYSMGR_H__

class PhysicsManager {
public:
	PhysicsManager();
	~PhysicsManager();

	void StartUp();
	void Shutdown();

	void Update(float t, float dt);

private:
	void UpdatePlayer(float t, float dt);
};

#endif