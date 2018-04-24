#include "SingleThreadedApplication.h"
#include "Multithreading.h"


int main()
{
    //SingleThreadedApplication app2;
	Multithreading app;

    while (true)
    {
        app.Tick();
    }

    return 0;
}


