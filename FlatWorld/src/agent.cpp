#include "..\include\agent.h"

Agent::Agent()
{
    this->SetxVel(8);
    this->SetyVel(8);
}

Agent::~Agent()
{
    //dtor
}

void Agent::look(const SDL_Surface* world)
{

}
