#include "..\include\object.h"

Object::Object()
{
    x = 0;
    y = 0;
    xVel = 0;
    yVel = 0;
    body = load_image("square.bmp");
}

Object::~Object()
{
    SDL_FreeSurface(body);
}

void Object::move(const SDL_Surface* world)
{
    xVel = 2;
    yVel = 2;
}

void Object::show(SDL_Surface* world)
{
    /// Move the object based on x velocity
    x += xVel;
    /// If the object went too far to the left or right
    if( ( x < 0 ) || ( x + Object_WIDTH > world->w ) )
        x -= xVel;

    /// Move the object based on y velocity
    y += yVel;

    /// If the object went too far up or down
    if( ( y < 0 ) || ( y + Object_HEIGHT > world->h ) )
        y -= yVel;

    /// Show the Object
    apply_surface( x, y, body, world );
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

