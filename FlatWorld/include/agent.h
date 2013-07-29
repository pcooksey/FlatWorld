#ifndef AGENT_H
#define AGENT_H

#include "object.h"
#include "ANN/NeuralNet.h"

#include <iostream>
#include <vector>


static int ints[] = {2,3,2};
static std::vector<unsigned> topology (ints, ints + sizeof(ints) / sizeof(int) );

class Agent : public Object
{
    public:
        Agent(int x, int y);
        virtual ~Agent();
    protected:
    private:
        void look(const SDL_Surface* world);

        std::vector<double> inputValues;
        std::vector<double> targetValues;
        std::vector<double> resultValues;

        NeuralNet network;
};

#endif // AGENT_H
