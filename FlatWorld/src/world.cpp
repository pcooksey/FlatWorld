#include "..\include\world.h"

World::World()
 : success(false), objects()
{
    screen = NULL;
    success = init();
}

World::~World()
{
    /// Free the loaded image
    SDL_FreeSurface( screen );
    /// Quit SDL
    SDL_Quit();
}

bool World::init()
{
    /// Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;

    /// Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    /// If there was an error in setting up the screen
    if( screen == NULL )
        return false;

    /// Set the window caption
    SDL_WM_SetCaption( "Flat World", NULL );

    /// If everything initialized fine
    return true;
}

void World::getStart()
{
    start();
}

int World::start()
{
    bool quit = false;
    /// The frame rate regulator
    int delta = SDL_GetTicks(), time;
    /// Object iterator
    std::list<Object*>::iterator obj;

    SDL_Event event;
    while(!quit)
    {
        /// Check if user wants to quit
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        /// Move within the world here
        for(obj = objects.begin(); obj!=objects.end(); ++obj)
        {
            (*obj)->move(screen);
        }

        /// Clean the screen
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        /// Delta time for moving
        time = (SDL_GetTicks() - delta);
        /// Show up here
        for(obj = objects.begin(); obj!=objects.end(); ++obj)
        {
            (*obj)->show(screen, time);
        }
        delta = SDL_GetTicks();

        /// Update Screen
        if(SDL_Flip( screen ) == -1)
            return 1;
    }

    return 0;
}

void World::addObject(Object* temp)
{
    objects.push_back(temp);
}
