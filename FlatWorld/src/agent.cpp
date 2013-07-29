#include "..\include\agent.h"

Agent::Agent(int x, int y)
    :Object(x,y), network(topology)
{

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
    std::cout<<"Input: "<<inputValues[0]<<" : "<<inputValues[1]<<std::endl;

    /*
    targetValues.clear();
    targetValues.push_back(inputValues[0]>0?1:-1);
    targetValues.push_back(0);
    std::cout<<"Target: "<<targetValues[0]<<" : "<<targetValues[1]<<std::endl;
    */

    network.getResults(resultValues);
    SetxVel(resultValues[0]*8);
    SetyVel(resultValues[1]*8);
    std::cout<<"Result: "<<resultValues[0]<<" : "<<resultValues[1]<<std::endl;

    //network.backProp(targetValues);

    //std::cout <<" Average error: "<< network.getRecentAverageError() <<std::endl<<std::endl;
}
