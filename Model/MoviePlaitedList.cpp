#include <iostream>
#include <Utils.h>
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
     * Gets nameHead
     *
     * @precondition none
     * @postcondition none
     *
     * @return nameHead
     */
    MovieNode *MoviePlaitedList::getNameHead()
    {
        return this->nameHead;
    }

    /**
     * Gets lengthHead
     *
     * @precondition none
     * @postcondition none
     *
     * @return lengthHead
     */
    MovieNode *MoviePlaitedList::getLengthHead()
    {
        return this->lengthHead;
    }

    /**
     * Gets ratingHead
     *
     * @precondition none
     * @postcondition none
     *
     * @return ratingHead
     */
    MovieNode *MoviePlaitedList::getRatingHead()
    {
        return this->ratingHead;
    }

    /**
     * TODO
     * @param pMovie
     */
    void MoviePlaitedList::insertMovie(Movie *pMovie)
    {
        auto *node = new MovieNode(pMovie);
        this->insertByName(node);
        this->insertByLength(node);
        //TODO call insert by rating
    }

    void MoviePlaitedList::insertByName(MovieNode *nodeToAdd)
    {
        if (this->nameHead == nullptr)
        {
            this->nameHead = nodeToAdd;
            return;
        }

        string nameToAdd = toUpperCase(nodeToAdd->getMovieInfo()->getName());

        if (nameToAdd < toUpperCase(this->nameHead->getMovieInfo()->getName()))
        {
            nodeToAdd->setNextName(this->nameHead);
            this->nameHead = nodeToAdd;
            return;
        }

        MovieNode *current = this->nameHead;
        MovieNode *next = this->nameHead->getNextName();

        while (next != nullptr && nameToAdd > toUpperCase(next->getMovieInfo()->getName()))
        {
            current = next;
            next = next->getNextName();
        }

        if ((next != nullptr && toUpperCase(next->getMovieInfo()->getName()) == nameToAdd) ||
                toUpperCase(current->getMovieInfo()->getName()) == nameToAdd)
        {
            throw invalid_argument("\"" + nameToAdd + "\" already exists");
        }

        current->setNextName(nodeToAdd);
        nodeToAdd->setNextName(next);
    }

    void MoviePlaitedList::insertByLength(MovieNode *nodeToAdd)
    {
        if (this->lengthHead == nullptr)
        {
            this->lengthHead = nodeToAdd;
            return;
        }

        int lengthToAdd = nodeToAdd->getMovieInfo()->getLength();

        if (lengthToAdd < this->lengthHead->getMovieInfo()->getLength())
        {
            nodeToAdd->setNextLength(this->lengthHead);
            this->lengthHead = nodeToAdd;
            return;
        }

        MovieNode *current = this->lengthHead;
        MovieNode *next = this->lengthHead->getNextLength();
        string nameToAdd = toUpperCase(nodeToAdd->getMovieInfo()->getName());

        if (next == nullptr && lengthToAdd == current->getMovieInfo()->getLength())
        {
            if (toUpperCase(current->getMovieInfo()->getName()) > nameToAdd)
            {
                nodeToAdd->setNextLength(current);
                this->lengthHead = nodeToAdd;
                return;
            }
        }

        while (next != nullptr && lengthToAdd > next->getMovieInfo()->getLength())
        {
            current = next;
            next = next->getNextLength();
        }

        if (next != nullptr && next->getMovieInfo()->getLength() == lengthToAdd)
        {
            while (next != nullptr && toUpperCase(next->getMovieInfo()->getName()) < nameToAdd)
            {
                current = next;
                next = next->getNextName();
            }
        }

        nodeToAdd->setNextLength(current->getNextLength());
        current->setNextLength(nodeToAdd);

    }

    void MoviePlaitedList::insertByRating(MovieNode *nodeToAdd)
    {
        //TODO insert where rating goes
    }

    //TODO doc
    bool MoviePlaitedList::deleteMovie(const string &movieName) //TODO delete from length and rating strands, handle delete when only one element and it doesnt match
    {
        MovieNode *current = this->nameHead;

        if (current == nullptr)
        {
            return false;
        }

        MovieNode *next = this->nameHead->getNextName();

        if (current->getMovieInfo()->getName() == movieName)
        {
            this->nameHead = next;
            this->deleteFromLength(current);
            delete current;
            return true;
        }

        while (next->getMovieInfo()->getName() != movieName)
        {
            current = current->getNextName();
            next = next->getNextName();
            if (next == nullptr) {
                return false;
            }
        }

        if (next->getNextName() == nullptr)
        {
            current->setNextName(nullptr);
            this->deleteFromLength(next);
            delete next;
            return true;
        }

        current->setNextName(next->getNextName());
        this->deleteFromLength(next);
        delete next;
        return true;
    }

    void MoviePlaitedList::deleteFromLength(MovieNode *nodeToDelete)
    {
        if (this->lengthHead == nodeToDelete)
        {
            this->lengthHead = nodeToDelete->getNextLength();
            return;
        }

        MovieNode *current = this->lengthHead;
        MovieNode *next = this->lengthHead->getNextLength();

        while (next != nullptr)
        {
            if (next == nodeToDelete)
            {
                current->setNextLength(next->getNextLength());
                return;
            }

            current = current->getNextLength();
            next = next->getNextLength();
        }
    }

    /**
     * MoviePlaitedList destructor
     */
    MoviePlaitedList::~MoviePlaitedList()
    {
        //TODO check this
        MovieNode *current = this->nameHead;
        while (current != nullptr)
        {
            MovieNode *next = current->getNextName();
            delete current;
            current = next;
        }
    }

}