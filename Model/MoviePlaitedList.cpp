#include "MoviePlaitedList.h"

namespace model
{
    /**
     * TODO
     * @param pMovie
     */
    void MoviePlaitedList::insertMovie(model::Movie *pMovie)
    {
        //create movie node
        MovieNode *node = new MovieNode(pMovie);
        //call insert by name, insert by rating, insert by length
    }

    void MoviePlaitedList::insertByName(MovieNode *node)
    {
        //TODO insert where name goes
    }

    void MoviePlaitedList::insertByLength(MovieNode *node)
    {
        //TODO insert where length goes
    }

    void MoviePlaitedList::insertByRating(MovieNode *node)
    {
        //TODO insert where rating goes
    }

    /**
     * MoviePlaitedList destructor
     */
    MoviePlaitedList::~MoviePlaitedList()
    {
        //TODO go through one strand only (like name strand) and delete movie node
    }
}