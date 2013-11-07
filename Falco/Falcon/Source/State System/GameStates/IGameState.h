#ifndef IGAMESTATE_H
#define IGAMESTATE_H

class IGameState
{

public:

	virtual ~IGameState(void) = 0 
	{ }

	// Called to load resources
	virtual void Enter() = 0;

	// Called to unload resources
	virtual void Exit() = 0;

	// Handle Input
	virtual bool Input() = 0;		

	// Update game entities
	virtual void Update(float _fElapsedTime) = 0;		

	//Putting this here for now...might not need. Depends on how we decide to render
	// Render game entities
	virtual void Render() = 0;
};



#endif