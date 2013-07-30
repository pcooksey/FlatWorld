#ifndef OBJECT_H
#define OBJECT_H
#include "SDL\SDL.h"
#include "object.h"
#include <string>
#include <ctime>
#include <limits>

namespace ObjectBody {
    /// The attributes of the object
    enum Type {ALIVE, DIED, INANIMATE};
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
SDL_Surface *load_image( std::string filename );

class Object
{
    public:
        Object(const int &x, const int &y);
        virtual ~Object();

        float Getx() const { return x; }
        float Gety() const { return y; }
        float GetxVel() const { return xVel; }
        float GetyVel() const { return yVel; }

        /** Height and width of the body */
        int Object_WIDTH() { return body->w; }
        int Object_HEIGHT() { return body->h; }

        /** Setting the velocities will change
            the position of the object in @show */
        void SetxVel(float val) { xVel = val; }
        void SetyVel(float val) { yVel = val; }

        /** Object will move after @look */
        void move(const SDL_Surface* world, const Uint32& deltaTicks);

        /** Collision happens when the world
        *  detects that the object has hit another object */
        virtual void collision(Object* obj) = 0;

        /** Shows the object in the world
            and moves it based on the velocities */
        void show(SDL_Surface* world) const;

        /** World can check if you are alive or inanimate
            so that is knows if the object needs to be deleted */
        bool alive() const { return type==ObjectBody::DIED ? false : true; }

        bool kill();

    protected:
        /** Object should observe @world
            and set @xVel, @yVel */
        virtual void look(const SDL_Surface* world) = 0;

        /** Create the body of your object */
        void setBody(SDL_Surface* body);

        /** Body type is by default real */
        ObjectBody::Type type;

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
