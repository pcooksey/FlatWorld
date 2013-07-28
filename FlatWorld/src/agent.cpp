#include "..\include\agent.h"

Agent::Agent()
    :network(topology)
{
    prevXvel = 0;
    prevYvel = 0;
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
    inputValues.push_back(GetxVel()/5);
    inputValues.push_back(GetyVel()/5);

    network.feedForward(inputValues);

    if( frame==0 || (GetxVel()!=prevXvel || GetyVel()!=prevYvel))
    {
        std::cout<<"Input: "<<GetxVel()<<" : "<<GetyVel()<<std::endl;
        targetValues.clear();
        targetValues.push_back(GetxVel()>=0?1:-1);
        targetValues.push_back(0);
        std::cout<<"Target: "<<targetValues[0]<<" : "<<targetValues[1]<<std::endl;

        network.getResults(resultValues);
        SetxVel(resultValues[0]*5);
        SetyVel(resultValues[1]*5);
        std::cout<<"Result: "<<resultValues[0]<<" : "<<resultValues[1]<<std::endl;
        prevXvel = resultValues[0]*5;
        prevYvel = resultValues[1]*5;

        network.backProp(targetValues);

        std::cout << frame<< " Average error: "<< network.getRecentAverageError() <<std::endl<<std::endl;
    }
    frame++;
}
