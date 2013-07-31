#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "world.h"
#include "agent.h"
#include "plant.h"

class Environment : public World
{
    public:
        Environment();
        virtual ~Environment();

    protected:
    private:
};

#endif // ENVIRONMENT_H
