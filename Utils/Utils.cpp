#include "Utils.h"

#include <algorithm>
#include <sstream>

/**
 * Utilities to help with repetitive tasks throughout the program.
 *
 * @author Duane Yoder, John Chittam
 */

/**
 * Converts and returns string in uppercase
 *
 * @precondition none
 * @postcondition none
 *
 * @param text the text to convert to upper case
 *
 * @return Uppercase version of the string
 */
const string toUpperCase(string text)
{
    transform(text.begin(), text.end(), text.begin(), ::toupper);

    return text;
}

/**
 * Converts passed in string to an int
 *
 * @precondition none
 * @postcondition none
 *
 * @throws Exception if text cannot be converted to an int
 *
 * @param text text to convert to an int
 * @param errorMessage message thrown if a problem occurs when converting text to an int
 *
 * @return text converted to an int
*/
int toInt(const string &text, const char *errorMessage)
{
    istringstream streamConversion(text);
    int value = 0;
    if (!(streamConversion >> value))
    {
        throw invalid_argument(errorMessage);
    }

    return value;

}

/**
 * Returns the Movie::Rating enum corresponding with the given string
 *
 * @precondition none
 * @postcondition none
 *
 * @param rating the string form of the Movie's rating
 * @return the Movie::Rating enum corresponding with the given string
 */
model::Movie::Rating returnRatingBasedOnString(string &rating)
{
    rating = toUpperCase(rating);

    if (rating == ENUM_TO_STR(G))
    {
        return model::Movie::Rating::G;
    }
    else if (rating == ENUM_TO_STR(PG))
    {
        return model::Movie::Rating::PG;
    }
    else if (rating == ENUM_TO_STR(PG13))
    {
        return model::Movie::Rating::PG13;
    }
    else if (rating == ENUM_TO_STR(R))
    {
        return model::Movie::Rating::R;
    }

    return model::Movie::Rating::NOT_RATED;
}
