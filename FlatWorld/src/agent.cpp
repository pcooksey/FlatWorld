#include "..\include\agent.h"

Agent::Agent()
{
    //ctor
}

Agent::~Agent()
{
    //dtor
}

void Agent::look(const SDL_Surface* world)
{
    this->SetxVel(4);
    this->SetyVel(4);
}
