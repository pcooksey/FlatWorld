#ifndef WORLD_H
#define WORLD_H

#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"
#include "object.h"
#include <string>
#include <list>

namespace Screen {
    /// The attributes of the screen
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SCREEN_BPP = 32;
}

using namespace Screen;

class World
{
    public:
        World();
        virtual ~World();
        bool successful() const { return success; };
        void addObject(Object* temp);
        void getStart();

    protected:
    private:
        bool init();
        int start();
        static int starter(void *data);
        void collisionDetection(int time);

        void setRunning(bool run);
        bool getRunning();

        /// Is true when the init was successful
        bool success;
        /// Is true when start is running
        bool running;
        ///The protective semaphore for running
        SDL_sem *runLock;
        SDL_Surface* screen;
        std::list<Object*> objects;
};

#endif // WORLD_H
