#include "MovieLibraryWindow.h"
using namespace view;

int main(int argc, char ** argv)
{
    MovieLibraryWindow mainWindow(540, 375, "John Chittam's Movie Database");
    mainWindow.show();

    int exitCode = Fl::run();
    return exitCode;
}
