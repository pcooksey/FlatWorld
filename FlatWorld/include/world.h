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
        /** Controls the event loop of the world */
        void getStarted();

    protected:
    private:
        bool init();
        /** Controls the screen in another thread */
        int start();
        /** Starts the thread that controls the screen */
        static int starter(void *data);
        void collisionDetection(int time);

        void setRunning(bool run);
        bool getRunning();

        bool success; // Is true when the init was successful
        bool running; // When false it signals for the @start thread to end
        SDL_sem *runLock; //The protective semaphore for @running

        SDL_Surface* screen;
        std::list<Object*> objects;
};

#endif // WORLD_H
