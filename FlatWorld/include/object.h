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

        float Getx() { return x; }
        float Gety() { return y; }

        /** Object will move after @look */
        void move(const SDL_Surface* world, const Uint32& deltaTicks);

        /** Shows the object in the world
            and moves it based on the velocities */
        void show(SDL_Surface* world);

    protected:
        /** Setting the velocities will change
            the position of the object in @show */
        void SetxVel(float val) { xVel = val; }
        void SetyVel(float val) { yVel = val; }

        /** Object should observe @world
            and set @xVel, @yVel */
        virtual void look(const SDL_Surface* world) = 0;

        /** Create the body of your object */
        virtual SDL_Surface* setBody();

    private:
        /** Velocities of the object
            Change through the setters */
        float xVel, yVel;

        /** Position of the object
            !Can't change manually */
        float x, y;

        /** Will determine forces acting on the body */
        float sizeOfBody;

        /** Body is by default a square but can be changed */
        SDL_Surface* body;
};

#endif // OBJECT_H
