#include "..\include\object.h"

Object::Object(int x, int y)
{
    this->x = x;
    this->y = y;
    xVel = 0;
    yVel = 0;
    body = setBody();
}

Object::~Object()
{
    SDL_FreeSurface(body);
}

void Object::move(const SDL_Surface* world, const Uint32& deltaTicks)
{
    if (x < 0 && xVel < 0)
    {
        xVel = -xVel;
    }
    if (y + ObjectBody::Object_HEIGHT > world->h && yVel > 0)
    {
        yVel = -yVel;
    }
    if (x + ObjectBody::Object_WIDTH > world->w && xVel > 0)
    {
        xVel = -xVel;
    }
    if (y < 0 && yVel < 0)
    {
        yVel = -yVel;
    }

    // Move the object based on x velocity
    x += xVel * (deltaTicks / 100.f);

    // Move the object based on y velocity
    y += yVel * (deltaTicks / 100.f);

    // Must look after position gets changed because of collision
    // detection might change the velocity of the object
    look(world);
}

SDL_Surface* Object::setBody()
{
    return load_image("square.bmp");
}

void Object::show(SDL_Surface* world) const
{
    // Show the Object on the world
    apply_surface( (int)x, (int)y, body, world );
}


/**
    Static functions used by Object class
*/

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = SDL_LoadBMP( filename.c_str() );
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    return optimizedImage;
}

