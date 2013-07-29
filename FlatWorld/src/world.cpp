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
    bool quit = false;
    SDL_Thread *thread = SDL_CreateThread( starter, this );
    SDL_Event event;
    while(!quit)
    {
        /// Check if user wants to quit
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
                /// Stop the thread
                SDL_KillThread( thread );
            }
        }
    }
}

int World::starter(void *data)
{
    return ((World*)data)->start();
}

int World::start()
{
    /// The frame rate regulator
    int delta = SDL_GetTicks(), time;
    /// Object iterator
    std::list<Object*>::iterator obj;

    while(true)
    {
        ///Check for future collisions here

        /// Time (dt) between frames
        time = (SDL_GetTicks() - delta);
        /// Move the objects in the world
        for(obj = objects.begin(); obj!=objects.end(); ++obj)
        {
            (*obj)->move(screen,time);
        }
        ///Start clock over again
        delta = SDL_GetTicks();

        /// Clean the screen
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );

        /// Print the objects onto the world
        for(obj = objects.begin(); obj!=objects.end(); ++obj)
        {
            (*obj)->show(screen);
        }

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
