#ifndef WORLD_H
#define WORLD_H

#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"
#include "object.h"
#include <string>
#include <list>

/// The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

class World
{
    public:
        World();
        virtual ~World();
        bool successful() { return success; };
        void addObject(Object* temp);
        void getStart();

    protected:
    private:
        bool init();
        int start();
        static int starter(void *data);

        bool success;
        SDL_Surface* screen;
        std::list<Object*> objects;
};

#endif // WORLD_H
