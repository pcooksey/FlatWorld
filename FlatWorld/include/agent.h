#ifndef AGENT_H
#define AGENT_H

#include "object.h"
#include "ANN/NeuralNet.h"

#include <iostream>
#include <vector>


static int ints[] = {2,2};
static std::vector<unsigned> topology (ints, ints + sizeof(ints) / sizeof(int) );

class Agent : public Object
{
    public:
        Agent();
        virtual ~Agent();
    protected:
    private:
        void look(const SDL_Surface* world);

        std::vector<double> inputValues;
        std::vector<double> targetValues;
        std::vector<double> resultValues;
        float prevXvel;
        float prevYvel;
        unsigned frame;
        NeuralNet network;
};

#endif // AGENT_H
