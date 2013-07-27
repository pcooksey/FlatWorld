#include "..\include\world.h"

World::World()
 : objects()
{
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

bool World::start()
{
    bool quit = false;
    /// Keep track of the current frame
    int frame = 0;
    /// Whether or not to cap the frame rate
    bool cap = true;
    /// The frame rate regulator
    int fps;
    /// Object iterator
    std::list<Object*>::iterator obj;

    SDL_Event event;
    while(!quit)
    {
        fps = SDL_GetTicks();
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

        /// Show up here
        for(obj = objects.begin(); obj!=objects.end(); ++obj)
        {
            (*obj)->show(screen);
        }

        /// Update Screen
        if(SDL_Flip( screen ) == -1)
            return 1;

        /// Increment the frame counter
        frame++;
        int time = (SDL_GetTicks() - fps);
        /// If we want to cap the frame rate
        if( ( cap == true ) && ( time < 1000 / FRAMES_PER_SECOND ) )
        {
            /// Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - time );
        }
    }
}

void World::addObject(Object* temp)
{
    objects.push_back(temp);
}
