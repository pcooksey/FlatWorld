#ifndef WORLD_H
#define WORLD_H

#include "SDL/SDL.h"
#include "object.h"
#include <string>
#include <list>

/// The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

/// The frames per second
const int FRAMES_PER_SECOND = 30;

class World
{
    public:
        World();
        virtual ~World();
        bool start();
        bool successful() { return success; };
        void addObject(Object* temp);

    protected:
    private:
        bool init();

        bool success = false;
        SDL_Surface* screen = NULL;
        std::list<Object*> objects;
};

#endif // WORLD_H
