#include <iostream>
#include <Utils.h>
#include "MoviePlaitedList.h"

namespace model
{
    /**
     * The plaited list containing movies. There are strands to link movies by
     * name, length, and rating.
     *
     * @author John Chittam
     */

    /**
     * Constructs a new MoviePlaitedList
     *
     * @precondition none
     * @postcondition getNameHead()==nullptr AND getLengthHead()==nullptr AND getRatingHead()==nullptr
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
     * Adds the given Movie to the plaited list in the proper position for
     * all strands
     *
     * @precondition none
     * @postcondition Movie added to plaited list if there are no errors
     *
     * @param pMovie the Movie to add
     */
    void MoviePlaitedList::insertMovie(Movie *pMovie)
    {
        auto *node = new MovieNode(pMovie);
        this->insertByName(node);
        this->insertByLength(node);
        this->insertByRating(node);
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
            throw invalid_argument("Movie \"" + nodeToAdd->getMovieInfo()->getName() + "\" already exists.");
        }

        current->setNextName(nodeToAdd);
        nodeToAdd->setNextName(next);
    }

    void MoviePlaitedList::insertByLength(MovieNode *nodeToAdd)
    {
        int lengthToAdd = nodeToAdd->getMovieInfo()->getLength();
        if (this->lengthHead == nullptr || lengthHead->getMovieInfo()->getLength() > lengthToAdd)
        {
            nodeToAdd->setNextLength(this->lengthHead);
            this->lengthHead = nodeToAdd;
            return;
        }

        MovieNode *current = this->lengthHead;
        while (current->getNextLength() != nullptr && current->getNextLength()->getMovieInfo()->getLength() < lengthToAdd)
        {
            current = current->getNextLength();
        }

        string nameToAdd = toUpperCase(nodeToAdd->getMovieInfo()->getName());
        MovieNode *next = current->getNextLength();
        if (next != nullptr && lengthToAdd == next->getMovieInfo()->getLength())
        {
            while (next != nullptr && next->getMovieInfo()->getLength() == lengthToAdd && toUpperCase(next->getMovieInfo()->getName()) < nameToAdd)
            {
                next = next->getNextLength();
                current = current->getNextLength();
            }
        }

        nodeToAdd->setNextLength(current->getNextLength());
        current->setNextLength(nodeToAdd);
    }

    void MoviePlaitedList::insertByRating(MovieNode *nodeToAdd)
    {
        int ratingToAdd = nodeToAdd->getMovieInfo()->getRating();
        if (this->ratingHead == nullptr || ratingHead->getMovieInfo()->getRating() > ratingToAdd)
        {
            nodeToAdd->setNextRating(this->ratingHead);
            this->ratingHead = nodeToAdd;
            return;
        }

        MovieNode *current = this->ratingHead;
        while (current->getNextRating() != nullptr && current->getNextRating()->getMovieInfo()->getRating() < ratingToAdd)
        {
            current = current->getNextRating();
        }

        string nameToAdd = toUpperCase(nodeToAdd->getMovieInfo()->getName());
        MovieNode *next = current->getNextRating();
        if (next != nullptr && ratingToAdd == next->getMovieInfo()->getRating())
        {
            while (next != nullptr && next->getMovieInfo()->getRating() == ratingToAdd && toUpperCase(next->getMovieInfo()->getName()) < nameToAdd)
            {
                next = next->getNextRating();
                current = current->getNextRating();
            }
        }

        nodeToAdd->setNextRating(current->getNextRating());
        current->setNextRating(nodeToAdd);
    }

    /**
     * Removes the movie with the given name from all strands of the plaited
     * list and deletes the associated MovieNode pointer
     *
     * @precondition none
     * @postcondition Movie removed if it exists
     *
     * @param movieName the name of the Movie
     *
     * @return true if the movie existed and was removed, false if it did not exist
     */
    bool MoviePlaitedList::deleteMovie(const string &movieName)
    {
        MovieNode *current = this->nameHead;
        string uppercaseMovieName = toUpperCase(movieName);

        if (current == nullptr)
        {
            return false;
        }

        MovieNode *next = this->nameHead->getNextName();

        if (next == nullptr && toUpperCase(current->getMovieInfo()->getName()) != uppercaseMovieName)
        {
            return false;
        }

        if (toUpperCase(current->getMovieInfo()->getName()) == uppercaseMovieName)
        {
            this->nameHead = next;
            this->deleteFromLength(current);
            this->deleteFromRating(current);
            delete current;
            return true;
        }

        while (toUpperCase(next->getMovieInfo()->getName()) != uppercaseMovieName)
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
            this->deleteFromRating(next);
            delete next;
            return true;
        }

        current->setNextName(next->getNextName());
        this->deleteFromLength(next);
        this->deleteFromRating(next);
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

    void MoviePlaitedList::deleteFromRating(MovieNode *nodeToDelete)
    {
        if (this->ratingHead == nodeToDelete)
        {
            this->ratingHead = nodeToDelete->getNextRating();
            return;
        }

        MovieNode *current = this->ratingHead;
        MovieNode *next = this->ratingHead->getNextRating();

        while (next != nullptr)
        {
            if (next == nodeToDelete)
            {
                current->setNextRating(next->getNextRating());
                return;
            }

            current = current->getNextRating();
            next = next->getNextRating();
        }
    }

    /**
     * MoviePlaitedList destructor
     */
    MoviePlaitedList::~MoviePlaitedList()
    {
        MovieNode *current = this->nameHead;
        while (current != nullptr)
        {
            MovieNode *next = current->getNextName();
            delete current;
            current = next;
        }

    }

}