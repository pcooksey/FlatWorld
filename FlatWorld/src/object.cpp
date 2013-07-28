#include "..\include\object.h"

Object::Object()
{
    x = 0;
    y = 0;
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
    look(world);
    /// Move the object based on x velocity
    x += xVel * (deltaTicks / 100.f);
    /// If the object went too far to the left or right
    if( ( x < 0 ) || ( x + Object_WIDTH > world->w ) )
        x -= xVel * (deltaTicks / 100.f);

    /// Move the object based on y velocity
    y += yVel * (deltaTicks / 100.f);

    /// If the object went too far up or down
    if( ( y < 0 ) || ( y + Object_HEIGHT > world->h ) )
        y -= yVel* (deltaTicks / 100.f);
}

SDL_Surface* Object::setBody()
{
    return load_image("square.bmp");
}

void Object::show(SDL_Surface* world)
{
    /// Show the Object
    apply_surface( (int)x, (int)y, body, world );
}

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

