#ifndef AGENT_H
#define AGENT_H

#include "object.h"


class Agent : public Object
{
    public:
        Agent();
        virtual ~Agent();
    protected:
    private:
        void look(const SDL_Surface* world);
};

#endif // AGENT_H
