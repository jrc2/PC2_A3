#include <iostream>
#include "MoviePlaitedList.h"

namespace model
{
    /**
     * TODO
     */
    MoviePlaitedList::MoviePlaitedList()
    {
        this->nameHead = nullptr;
        this->lengthHead = nullptr;
        this->ratingHead = nullptr;
    }

    /**
     * TODO
     * @param pMovie
     */
    void MoviePlaitedList::insertMovie(Movie *pMovie)
    {
        //create movie node
        MovieNode *node = new MovieNode(pMovie);
        this->insertByName(node);
        //call insert by rating, insert by length
    }

    void MoviePlaitedList::insertByName(MovieNode *nodeToAdd)
    {
        if (this->nameHead == nullptr)
        {
            this->nameHead = nodeToAdd;
            return;
        }
        string newMovieName = nodeToAdd->getMovieInfo()->getName();
        MovieNode *newPrev = this->nameHead;
        MovieNode *newNext = this->nameHead->getNextName();
        while (newNext != nullptr)
        {
            if (newMovieName > newPrev->getMovieInfo()->getName() && newMovieName < newNext->getMovieInfo()->getName())
            {
                newPrev->setNextName(nodeToAdd);
                nodeToAdd->setNextName(newNext);
                return;
            }

            newPrev = newNext;
            newNext = newNext->getNextName();
        }

        newPrev->setNextName(nodeToAdd);
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