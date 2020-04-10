#include "MovieNode.h"

/**
 * TODO class info
 * @param movieInfo
 * @param nextName
 * @param nextLength
 * @param nextRating
 */
MovieNode::MovieNode(Movie *movieInfo, string *nextName, int nextLength, int nextRating)
{
    this->movieInfo = movieInfo;
    this->nextName = nextName;
    this->nextLength = nextLength;
    this->nextRating = nextRating;
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
string * MovieNode::getNextName()
{
    return this->nextName;
}

/**
 * TODO public function
 * @return
 */
int MovieNode::getNextLength()
{
    return this->nextLength;
}

/**
 * TODO public function
 * @return
 */
int MovieNode::getNextRating()
{
    return this->nextRating;
}

/**
 * TODO public function
 * @param nextName
 */
void MovieNode::setNextName(string *nextName)
{
    this->nextName = nextName;
}

/**
 * TODO public function
 * @param nextLength
 */
void MovieNode::setNextLength(int nextLength)
{
    this->nextLength = nextLength;
}

/**
 * TODO public function
 * @param nextRating
 */
void MovieNode::setNextRating(int nextRating)
{
    this->nextRating = nextRating;
}
