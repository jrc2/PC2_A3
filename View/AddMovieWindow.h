#ifndef ADDMOVIEWINDOW_H
#define ADDMOVIEWINDOW_H

#include "OKCancelWindow.h"
#include "Movie.h"

using namespace model;

#include <Fl/Fl_Input.H>

namespace view
{

    class AddMovieWindow : public OKCancelWindow
    {
    private:
        Fl_Input *nameInput;
        Fl_Input *studioInput;
        Fl_Input *yearInput;
        Fl_Input *ratingInput;
        Fl_Input *lengthInput;

        Movie *pMovie;

        Movie::Rating determineAndSetRatingBasedOnUserInput();

        int determineAndSetYearBasedOnUserInput();

        int determineAndSetLengthBasedOnUserInput();

    public:
        AddMovieWindow();

        virtual ~AddMovieWindow();

        void okHandler();

        void cancelHandler();

        Movie *getMovie() const;
    };

}

#endif // ADDMOVIEWINDOW_H
