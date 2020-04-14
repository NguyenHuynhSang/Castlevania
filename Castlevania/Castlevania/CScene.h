#pragma once
class CScene
{
public:

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void OnActivate() {};
    virtual void OnDeactivate() {};

    // The below functions can be overridden as necessary in our scenes.
    virtual void ProcessInput() {};
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime) {};
    virtual void Render() {};
};

