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

        string nameToAdd = toUpperCase(nodeToAdd->getMovieInfo()->getName());

        if (nameToAdd < toUpperCase(this->nameHead->getMovieInfo()->getName()))
        {
            nodeToAdd->setNextName(this->nameHead);
            this->nameHead = nodeToAdd;
            return;
        }

        MovieNode *current = this->nameHead;
        MovieNode *next = this->nameHead->getNextName();

        cout << nameToAdd << endl;
        cout << toUpperCase(current->getMovieInfo()->getName()) << endl;
        while (next != nullptr && nameToAdd > toUpperCase(next->getMovieInfo()->getName()))
        {
            current = next;
            next = next->getNextName();
        }

        current->setNextName(nodeToAdd);
        nodeToAdd->setNextName(next);
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