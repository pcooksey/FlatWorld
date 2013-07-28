#include "..\include\agent.h"

Agent::Agent()
    :network(topology)
{
    frame = 0;
}

Agent::~Agent()
{
    //dtor
}

void Agent::look(const SDL_Surface* world)
{
    // Simple try to teach a ANN to go only forward
    inputValues.clear();
    inputValues.push_back(GetxVel());
    inputValues.push_back(GetyVel());

    network.feedForward(inputValues);

    targetValues.clear();
    targetValues.push_back(GetxVel()>=0?1:-1);
    targetValues.push_back(0);

    network.getResults(resultValues);
    SetxVel(resultValues[0]*5);
    SetyVel(resultValues[1]*5);

    network.backProp(targetValues);

    std::cout << frame<< " Average error: "<< network.getRecentAverageError() <<std::endl;
    frame++;
}
