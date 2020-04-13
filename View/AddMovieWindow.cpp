#include "AddMovieWindow.h"

#include "Utils.h"

#include <Fl/fl_ask.H>
#include <sstream>

using namespace std;

namespace view
{
    /**
     * Defines the window where the user can enter the movie information.
     *
     * @author Duane Yoder, small adaptations by John Chittam
     */

    /**
     * Constructs an add movie window creating and initializing all the widgets that will be displayed
     *
     * @precondition none
     * @postcondition none
     */
    AddMovieWindow::AddMovieWindow() : OKCancelWindow(330, 215, "Movie to add")
    {
        const int X_INPUT_LOCATION = 110;

        this->pMovie = 0;

        begin();

        this->nameInput = new Fl_Input(X_INPUT_LOCATION, 15, 200, 25, "Name:");
        this->studioInput = new Fl_Input(X_INPUT_LOCATION, 45, 200, 25, "Studio:");
        this->yearInput = new Fl_Input(X_INPUT_LOCATION, 75, 60, 25, "Year:");
        this->ratingInput = new Fl_Input(X_INPUT_LOCATION, 105, 60, 25, "Rating:");
        this->lengthInput = new Fl_Input(X_INPUT_LOCATION, 135, 60, 25, "Length:");

        this->setOKLocation(90, 170);
        this->setCancelLocation(170, 170);

        end();
    }

    /**
     * The instance handler when OK is invoked
     *
     * @precondition none
     * @postcondition getMovieInfo() == movie object created from data user entered
     */
    void AddMovieWindow::okHandler()
    {
        string name = this->nameInput->value();
        string studio = this->studioInput->value();

        Movie::Rating rating = this->determineAndSetRatingBasedOnUserInput();

        try
        {
            int year = this->determineAndSetYearBasedOnUserInput();
            int length = this->determineAndSetLengthBasedOnUserInput();
            this->pMovie = new Movie(name, studio, year, rating, length);
            this->hide();
        }
        catch (const invalid_argument &error)
        {
            fl_alert("%s", error.what());
        }


    }

    Movie::Rating AddMovieWindow::determineAndSetRatingBasedOnUserInput()
    {
        string ratingEntered = this->ratingInput->value();

        return returnRatingBasedOnString(ratingEntered);
    }

    int AddMovieWindow::determineAndSetYearBasedOnUserInput()
    {
        string yearStr = this->yearInput->value();
        int year = toInt(yearStr, "Error converting year to an integer.");
        return year;
    }


    int AddMovieWindow::determineAndSetLengthBasedOnUserInput()
    {
        string lengthStr = this->lengthInput->value();
        int length = toInt(lengthStr, "Error converting length to an integer.");
        return length;
    }

    /**
     * The instance handler when cancel is invoked
     *
     * @precondition none
     * @postcondition getMovieInfo() == 0
     */
    void AddMovieWindow::cancelHandler()
    {
        if (this->pMovie)
        {
            delete pMovie;
        }

        this->pMovie = 0;
        this->hide();
    }

    /**
     * Gets the new movie object based on what user entered
     *
     * @precondition none
     * @postcondition none
     *
     * @return The movie object
     */
    Movie *AddMovieWindow::getMovie() const
    {
        return this->pMovie;
    }

    /**
     * Destructor that cleans up all allocated resources for the window
     */
    AddMovieWindow::~AddMovieWindow()
    {
        delete this->nameInput;
        delete this->studioInput;
        delete this->yearInput;
        delete this->ratingInput;
        delete this->lengthInput;
    }

}
