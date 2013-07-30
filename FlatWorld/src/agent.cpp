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
    try
    {
        // Cast the obj to an agent
        Agent* agt = dynamic_cast<Agent*>(obj);
        // if @agt is not zero than it is an agetn
        if (agt != 0)
        {
            // For now just kill the agent (Testing purposes)
            agt->kill();
        }
    } catch (std::exception& e) {

    }
}
