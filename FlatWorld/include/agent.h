#ifndef AGENT_H
#define AGENT_H

#include "object.h"
#include "ANN/NeuralNet.h"

#include <iostream>
#include <vector>
#include <exception>


static int ints[] = {2,3,2};
static std::vector<unsigned> topology (ints, ints + sizeof(ints) / sizeof(int) );

class Agent : public Object
{
    public:
        Agent(int x, int y);
        virtual ~Agent();
        double getFitness() { return fitness; }
        const NeuralNet& getNetwork() { return network; }

    protected:
    private:
        virtual void look(const SDL_Surface* world);
        virtual void collision(Object* obj);

        std::vector<double> inputValues;
        std::vector<double> targetValues;
        std::vector<double> resultValues;

        double fitness;
        NeuralNet network;
};

#endif // AGENT_H
