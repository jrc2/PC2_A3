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
        this->longestName = 0;
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
        //TODO call insert by rating, insert by length
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
            return; //TODO return or throw something so error can be shown
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

        while (next != nullptr && lengthToAdd > next->getMovieInfo()->getLength())
        {
            current = next;
            next = next->getNextLength();
        }

        if ((next != nullptr && next->getMovieInfo()->getLength() == lengthToAdd) ||
                current->getMovieInfo()->getLength() == lengthToAdd)
        {
            return; //TODO return or throw something so error can be shown
        }

        current->setNextLength(nodeToAdd);
        nodeToAdd->setNextLength(next);
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
    string MoviePlaitedList::generateSummaryByName(bool ascending)
    {
        string output;
        MovieNode *currMovieNode = this->nameHead;
        this->addToSummaryByName(currMovieNode, output, ascending);

        return output;
    }

    void MoviePlaitedList::addToSummaryByName(MovieNode *node, string &output, bool ascending)
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

        if (ascending)
        {
            output += name + " " + studio + " " + year + " " + rating + " " + length + "\n";
        }

        this->addToSummaryByName(node->getNextName(), output, ascending);

        if (!ascending)
        {
            output += name + " " + studio + " " + year + " " + rating + " " + length + "\n";
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