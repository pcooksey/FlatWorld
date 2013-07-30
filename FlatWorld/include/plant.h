#ifndef PLANT_H
#define PLANT_H

#include "Object.h"


class Plant : public Object
{
    public:
        Plant(int x, int y);
        virtual ~Plant();
    protected:
    private:
        virtual void look(const SDL_Surface* world);
        virtual void collision(Object* obj);
};

#endif // PLANT_H
