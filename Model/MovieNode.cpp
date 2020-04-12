#include <stdexcept>
#include "MovieNode.h"

namespace model
{
    /**
     * Contains info about a movie, plus a pointer to the next
     * movie based on name, length, and rating.
     *
     * @author John Chittam
     */

    /**
     * Constructs a new MovieNode
     *
     * @precondition movieInfo!=nullptr
     * @postcondition getMovieInfo()==movieInfo, getNextName()==nullptr, getNextLength()==nullptr,
     *                getNextRating()==nullptr
     *
     * @param movieInfo pointer to Movie
     */
    MovieNode::MovieNode(Movie *movieInfo)
    {
        if (movieInfo == nullptr)
        {
            throw invalid_argument("movieInfo cannot be null");
        }

        this->movieInfo = movieInfo;
        this->nextName = nullptr;
        this->nextLength = nullptr;
        this->nextRating = nullptr;
    }

    /**
     * Gets movie info
     *
     * @precondition none
     * @postcondition none
     *
     * @return this->movieInfo
     */
    Movie *MovieNode::getMovieInfo()
    {
        return this->movieInfo;
    }

    /**
     * Gets next Movie by name
     *
     * @precondition none
     * @postcondition none
     *
     * @return next Movie by name
     */
    MovieNode *MovieNode::getNextName()
    {
        return this->nextName;
    }

    /**
     * Gets next Movie by length
     *
     * @precondition none
     * @postcondition none
     *
     * @return next Movie by length
     */
    MovieNode *MovieNode::getNextLength()
    {
        return this->nextLength;
    }

    /**
     * Gets next Movie by rating
     *
     * @precondition none
     * @postcondition none
     *
     * @return next Movie by rating
     */
    MovieNode *MovieNode::getNextRating()
    {
        return this->nextRating;
    }

    /**
     * Sets next Movie by name
     *
     * @precondition none
     * @postcondition none
     *
     * @param nextName next Movie by name
     */
    void MovieNode::setNextName(MovieNode *nextName)
    {
        this->nextName = nextName;
    }

    /**
     * Sets next Movie by length
     *
     * @precondition none
     * @postcondition none
     *
     * @param nextLength next Movie by length
     */
    void MovieNode::setNextLength(MovieNode *nextLength)
    {
        this->nextLength = nextLength;
    }

    /**
     * Sets next Movie by rating
     *
     * @precondition none
     * @postcondition none
     *
     * @param nextRating next Movie by rating
     */
    void MovieNode::setNextRating(MovieNode *nextRating)
    {
        this->nextRating = nextRating;
    }

    /**
     * MovieNode destructor
     */
    MovieNode::~MovieNode()
    {
        delete this->movieInfo;
    }
}