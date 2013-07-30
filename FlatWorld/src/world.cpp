#include "..\include\world.h"

World::World()
 : success(false), objects()
{
    screen = NULL;
    success = init();
}

World::~World()
{
    for(std::list<Object*>::iterator it=objects.begin(); it!=objects.end(); ++it)
    {
        delete (*it);
    }

    SDL_DestroySemaphore( runLock ); //Destroy semaphore
    SDL_Quit(); //Quit SDL
}

bool World::init()
{
    // Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;

    // Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    // If there was an error in setting up the screen
    if( screen == NULL )
        return false;

    // Create the semaphore
    runLock = SDL_CreateSemaphore( 1 );

    // Set the window caption
    SDL_WM_SetCaption( "Flat World", NULL );

    // If everything initialized fine
    return true;
}

void World::getStarted()
{
    bool quit = false;
    running = true;
    SDL_Thread *thread = SDL_CreateThread( starter, this );
    SDL_Event event;
    while(!quit)
    {
        // Check if user wants to quit
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
                setRunning(false); // Stop the thread
                SDL_WaitThread( thread, NULL ); //Waits for thread to end
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
    // The frame rate regulator
    int delta = SDL_GetTicks(), time;
    // Object iterator
    std::list<Object*>::iterator obj;

    while(getRunning())
    {
        // Time (dt) between frames
        time = (SDL_GetTicks() - delta);

        // Check for future collisions here
        collisionDetection(time);

        // Move the objects in the world
        for(obj = objects.begin(); obj!=objects.end(); ++obj)
        {
            (*obj)->move(screen,time);
        }
        // Start clock over again
        delta = SDL_GetTicks();

        // Clean the screen
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );

        // Print the objects onto the world
        for(obj = objects.begin(); obj!=objects.end(); ++obj)
        {
            (*obj)->show(screen);
        }

        // Update Screen
        if(SDL_Flip( screen ) == -1)
            return 1;
    }

    return 0;
}

void World::setRunning(bool run)
{
    SDL_SemWait( runLock ); //Lock
    running = run;
    SDL_SemPost( runLock ); //unlock
}

bool World::getRunning()
{
    SDL_SemWait( runLock ); //Lock
    bool run = running;
    SDL_SemPost( runLock ); //unlock
    return run;
}

void World::addObject(Object* temp)
{
    objects.push_back(temp);
}

void World::collisionDetection(int time)
{
    // Object iterator
    std::list<Object*>::iterator obj, check;
    int objx, objy, checkx, checky;
    for(obj = objects.begin(); obj!=objects.end(); ++obj)
    {
        objx = (*obj)->Getx() + (*obj)->GetxVel() * (time / 100.f);
        objy = (*obj)->Gety() + (*obj)->GetyVel() * (time / 100.f);
        for(check = objects.end(); check!=obj; --check)
        {
            checkx = (*check)->Getx() + (*check)->GetxVel() * (time / 100.f);
            checky = (*check)->Gety() + (*check)->GetyVel() * (time / 100.f);

            if( objy + ObjectBody::Object_HEIGHT <= checky
                || objy >= checky + ObjectBody::Object_HEIGHT
                || objx + ObjectBody::Object_WIDTH <= checkx
                || objx >= checkx + ObjectBody::Object_WIDTH )
            {} else {
                /*
                int xVel = (*obj)->GetxVel();
                int yVel = (*obj)->GetyVel();
                (*obj)->SetxVel((*check)->GetxVel());
                (*obj)->SetyVel((*check)->GetyVel());
                (*check)->SetxVel(xVel);
                (*check)->SetyVel(yVel);
                */
                (*obj)->SetxVel(0);
                (*obj)->SetyVel(0);
                (*check)->SetxVel(0);
                (*check)->SetyVel(0);
            }
        }
    }
}
