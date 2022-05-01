#include <iostream>
#include <math.h>
#include "Application.h"

int main(int argc, char* args[])
{
    Application app;

    app.Setup(1200, 320, 10);

    while(app.IsRunning()) 
    {
        app.Input();
        app.Update();
        app.Render();
    }

    app.Destroy();

    return 0;
}

