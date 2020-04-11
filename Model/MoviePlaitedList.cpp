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
            newPrevName = newPrev->getMovieInfo()->getName();
            string newNextName = newNext->getMovieInfo()->getName();

            if (newMovieName == newNextName || newMovieName == newPrevName)
            {
                throw invalid_argument("A movie with name " + newMovieName + " already exists");
            }

            if (newMovieName.compare(newPrevName) < 0 && newMovieName.compare(newNextName) < 0)
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

    void MoviePlaitedList::insertByLength(MovieNode *nodeToAdd)
    {
        //TODO insert where length goes
    }

    void MoviePlaitedList::insertByRating(MovieNode *nodeToAdd)
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
    string MoviePlaitedList::generateSummaryByNameAscending()
    {
        string output;
        MovieNode *currMovieNode = this->nameHead;
        this->addToSummaryByNameAscending(currMovieNode, output);

        return output;
    }

    void MoviePlaitedList::addToSummaryByNameAscending(MovieNode *node, string &output)
    {
        if (node == nullptr)
        {
            return;
        }

        Movie *movie = node->getMovieInfo();
        const string &name = movie->getName();
        const string &studio = movie->getStudio();
        const string &year = to_string(movie->getYear());
        const string &rating = movie->getRatingString();
        const string &length = to_string(movie->getLength());
        output += name + " " + studio + " " + year + " " + rating + " " + length + "\n";

        this->addToSummaryByNameAscending(node->getNextName(), output);
    }

    /**
     * MoviePlaitedList destructor
     */
    MoviePlaitedList::~MoviePlaitedList()
    {
        //TODO go through one strand only (like name strand) and delete movie node
    }

}