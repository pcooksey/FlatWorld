#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "world.h"
#include "agent.h"
#include "plant.h"
#include "ANN/CGenAlg.h"

#include <list>
#include <vector>

class Environment : public World
{
    public:
        Environment();
        virtual ~Environment();

        void init();

        void getStarted();

    protected:
    private:
        virtual void addObjects(const Object_list& objects);
        void initNewPopulation();

        int startTime;

        std::list<Agent*> agents;

        std::vector<SGenome> population;
        CGenAlg geneticAlg;
};

#endif // ENVIRONMENT_H
