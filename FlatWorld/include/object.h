#ifndef OBJECT_H
#define OBJECT_H
#include "SDL\SDL.h"
#include <string>
#include <ctime>
#include <limits>

/// The attributes of the object
const int Object_WIDTH = 20;
const int Object_HEIGHT = 20;

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
SDL_Surface *load_image( std::string filename );

class Object
{
    public:
        Object();
        virtual ~Object();

        int Getx() { return x; }
        int Gety() { return y; }

        /** Object should observe @world
            and set @xVel, @yVel */
        virtual void move(const SDL_Surface* world);

        /** Shows the object in the world
            and moves it based on the velocities */
        void show(SDL_Surface* world);

    protected:
        /** Setting the velocities will change
            the position of the object in @show */
        void SetxVel(int val) { xVel = val; }
        void SetyVel(int val) { yVel = val; }

    private:
        /** Velocities of the object
            Change through the setters */
        int xVel, yVel;

        /** Position of the object
            !Can't change manually */
        int x, y;

        SDL_Surface* body = NULL;
};

#endif // OBJECT_H
