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
     * TODO
     * @param pMovie
     */
    void MoviePlaitedList::insertMovie(Movie *pMovie)
    {
        auto *node = new MovieNode(pMovie);
        this->insertByName(node);
        //TODO call insert by rating, insert by length
    }

    void MoviePlaitedList::insertByName(MovieNode *nodeToAdd)
    {
        if (this->nameHead == nullptr)
        {
            this->nameHead = nodeToAdd;
            return;
        }
        Movie *newMovie = nodeToAdd->getMovieInfo();
        const string& newMovieName = newMovie->getName();
        MovieNode *newPrev = this->nameHead;
        MovieNode *newNext = this->nameHead->getNextName();
        string newPrevName = newPrev->getMovieInfo()->getName();

        if (newMovieName == newPrevName)
        {
            throw invalid_argument("A movie with name " + newMovieName + " already exists"); //TODO make sure this works
        }

        while (newNext != nullptr)
        {
            string newNextName = newNext->getMovieInfo()->getName();

            if (newMovieName == newNextName || newMovieName == newPrevName)
            {
                throw invalid_argument("A movie with name " + newMovieName + " already exists");
            }

            if (newMovieName > newPrevName && newMovieName < newNextName)
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

    //TODO doc
    bool MoviePlaitedList::deleteMovie(const string &movieName)
    {
        MovieNode *current = this->nameHead;
        MovieNode *next = this->nameHead->getNextName();

        if (current->getMovieInfo()->getName() == movieName)
        {
            this->nameHead = next;
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
            delete next;
            return true;
        }

        current->setNextName(next->getNextName());
        delete next;
        return true;
    }

    //TODO doc
    string MoviePlaitedList::generateSummaryByName() const
    {
        string output;
        MovieNode *currMovieNode = this->nameHead;
        while (currMovieNode != nullptr)
        {
            Movie *movie = currMovieNode->getMovieInfo();
            const string &name = movie->getName();
            const string &studio = movie->getStudio();
            const string &year = to_string(movie->getYear());
            const string &rating = movie->getRatingString();
            const string &length = to_string(movie->getLength());
            output += name + " " + studio + " " + year + " " + rating + " " + length + "\n";
            currMovieNode = currMovieNode->getNextName(); //TODO make recursive
        }

        return output;
    }

    /**
     * MoviePlaitedList destructor
     */
    MoviePlaitedList::~MoviePlaitedList()
    {
        //TODO go through one strand only (like name strand) and delete movie node
    }

}