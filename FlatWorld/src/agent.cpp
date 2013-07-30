#include "..\include\agent.h"

Agent::Agent(int x, int y)
    :Object(x,y), network(topology)
{
    fitness = 0;
}

Agent::~Agent()
{
    //dtor
}

void Agent::look(const SDL_Surface* world)
{
    // Simple try to teach a ANN to go only forward
    inputValues.clear();
    inputValues.push_back(GetxVel()*8);
    inputValues.push_back(GetyVel()*8);

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

void Agent::collision(Object* obj)
{
    // TODO: Idea is to only kill the object if the velocity is towards it
    // However, this might need to be implement in the world as determining
    // which object actually collide with the object
    try
    {
        // Cast the obj to a plant to eat
        Plant* plt = dynamic_cast<Plant*>(obj);
        // if @plt is a zero than the casting failed so skip
        if (plt != 0)
        {
            // Kill the plan for fitness improvement
            if(plt->kill())
            {
                fitness++;
            }
        }
    } catch (std::exception& e) {

    }
}
