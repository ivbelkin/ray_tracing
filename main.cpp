#include "Application.h"

#include "tests.h"

int main(int argc, char **argv)
{
    Application app(argc, argv);

    app.exec();

    return 0;
}