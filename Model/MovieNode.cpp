#include "MovieNode.h"

namespace model
{
    /**
     * TODO class info
     * @param movieInfo
     */
    MovieNode::MovieNode(Movie *movieInfo)
    {
        this->movieInfo = movieInfo;
    }

    /**
    * TODO public function
    * @return
    */
    Movie * MovieNode::getMovieInfo()
    {
        this->movieInfo;
    }

    /**
    * TODO public function
    * @return
    */
    MovieNode * MovieNode::getNextName()
    {
        return this->nextName;
    }

    /**
    * TODO public function
    * @return
    */
    MovieNode * MovieNode::getNextLength()
    {
        return this->nextLength;
    }

    /**
    * TODO public function
    * @return
    */
    MovieNode * MovieNode::getNextRating()
    {
        return this->nextRating;
    }

    /**
    * TODO public function
    * @param nextName
    */
    void MovieNode::setNextName(MovieNode *nextName)
    {
        this->nextName = nextName;
    }

    /**
    * TODO public function
    * @param nextLength
    */
    void MovieNode::setNextLength(MovieNode *nextLength)
    {
        this->nextLength = nextLength;
    }

    /**
    * TODO public function
    * @param nextRating
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