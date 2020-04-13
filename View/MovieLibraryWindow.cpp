#include "MovieLibraryWindow.h"

#include "DeleteMovieWindow.h"
#include "AddMovieWindow.h"

#include <Fl/fl_draw.H>
#include <Fl/Fl_File_Chooser.H>

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT

#include <iostream>
#include <fstream>

#endif

namespace view
{
    /**
     * Defines the window where a user can load, save, add, and delete movies from a movie library
     *
     * @author Duane Yoder, John Chittam
     */

    /**
     * Constructs a movie library window creating and initializing all the widgets that will be displayed
     *
     * @precondition width > 0 AND height > 0
     * @postcondition none
     *
     * @param width The width of the window
     * @param height The height of the window
     * @param title The title to display for the window
     */
    MovieLibraryWindow::MovieLibraryWindow(int width, int height, const char *title) : Fl_Window(width, height, title)
    {
        begin();

        this->sortingOutputLabel = new Fl_Output(100, 25, 0, 0, "Sort order:");
        createAndDisplaySortingRadioButtons();

        this->librarySummaryOutputLabel = new Fl_Output(190, 110, 0, 0, "Movie library summary:");

        this->summaryOutputTextBuffer = new Fl_Text_Buffer();
        this->summaryOutputTextDisplay = new Fl_Text_Display(20, 120, 500, 200);
        this->summaryOutputTextDisplay->textfont(FL_COURIER);
        this->summaryOutputTextDisplay->buffer(summaryOutputTextBuffer);

        this->loadButton = new Fl_Button(120, 330, 70, 30, "Load");
        this->loadButton->callback(cbLoad, this);

        this->saveButton = new Fl_Button(200, 330, 70, 30, "Save");
        this->saveButton->callback(cbSave, this);

        this->addButton = new Fl_Button(280, 330, 70, 30, "Add");
        this->addButton->callback(cbAddMovie, this);

        this->deleteButton = new Fl_Button(360, 330, 70, 30, "Delete");
        this->deleteButton->callback(cbDeleteMovie, this);

        this->setSummaryText();

        end();
    }

    /**
     * Overriding drawing of FL_Window so can draw a boxes around the sorting type radio buttons
     * to make them appear in a group
     */
    void MovieLibraryWindow::draw()
    {
        Fl_Window::draw();
        fl_frame("AAAA", 20, 35, 500, 55);
    }


    void MovieLibraryWindow::createAndDisplaySortingRadioButtons()
    {
        const int X_RADIO_GROUP = 35;
        const int Y_RADIO_GROUP = 45;
        const int WIDTH_RADIO_GROUP = 400;
        const int HEIGHT_RADIO_GROUP = 100;

        this->sortingRadioGroup = new Fl_Group(X_RADIO_GROUP, Y_RADIO_GROUP, WIDTH_RADIO_GROUP, HEIGHT_RADIO_GROUP);

        this->sortingRadioGroup->begin();

        for (int i = 0; i < SORTING_GROUPS; i++)
        {
            for (int j = 0; j < SORTING_TYPES_PER_GROUP; j++)
            {
                string label = this->sortingGroup[i] + " " + this->sortingTypes[j];
                int offset = (i * SORTING_TYPES_PER_GROUP) + j;
                this->radioSortingLabels[offset] = new string(label);
                this->sortingRadioGroupButton[offset] = new Fl_Round_Button(X_RADIO_GROUP + i * 160,
                                                                            Y_RADIO_GROUP + j * 25, 12, 12,
                                                                            radioSortingLabels[offset]->c_str());
                this->sortingRadioGroupButton[offset]->type(FL_RADIO_BUTTON);
                this->sortingRadioGroupButton[offset]->callback(cbSortingMethodChanged, this);
            }
        }

        this->sortingRadioGroup->end();

        this->sortingRadioGroupButton[0]->set();
        this->sortOrderSelection = NAME_ASCENDING;
    }

    /**
     * Callback when a radio button for the way to sort the movies has changed
     *
     * @precondition widget != 0 AND data != 0
     * @postcondition MovieLibraryWindow::getSortOrder() == value of new sort order selected
     *
     * @param widget The widget that initiatied the callback
     * @param data Any data that was passed with the call back. In this instance, a pointer to the window.
     */
    void MovieLibraryWindow::cbSortingMethodChanged(Fl_Widget *widget, void *data)
    {
        auto *window = (MovieLibraryWindow *) data;
        window->sortingMethodChanged();
        window->setSummaryText();
    }

    /**
     * Callback that is an instance function of the window class to encapsulate function
     *
     * @precondition none
     * @postcondition getSortOrder() == value of new sort order selected
     */
    void MovieLibraryWindow::sortingMethodChanged()
    {
        this->setSortOrderBasedOnSelection();
    }

    /**
     * Callback when the Load button is invoked
     *
     * @precondition widget != 0 AND data != 0
     * @postcondition MovieLibraryWindow::getFilename() == file selected by the user
     *
     * @param widget The widget that initiated the callback
     * @param data Any data that was passed with the call back. In this instance, a pointer to the window.
     */
    void MovieLibraryWindow::cbLoad(Fl_Widget *widget, void *data)
    {
        auto *window = (MovieLibraryWindow *) data;
        window->promptUserForFilename(Fl_File_Chooser::SINGLE, "Movie file to load");

        ifstream movieFile(window->getFilename());
        string movieFileContent;
        movieFileContent.assign((istreambuf_iterator<char>(movieFile)), istreambuf_iterator<char>());

        window->library.importFromCSV(movieFileContent);
        window->setSummaryText();

    }

    /**
     * Callback when the Load button is invoked
     *
     * @precondition type == Fl_File_Chooser type of SINGLE, MULTI, CREATE, or DIRECTORY
     * @postcondition MovieLibraryWindow::getFilename() == file selected by the user
     *
     * @param type Fl_File_Chooser type of SINGLE, MULTI, CREATE, or DIRECTORY
     * @param title Title to display for the file chooser
     *
     * @return The filename the user selected
     */
    const string MovieLibraryWindow::promptUserForFilename(int type, const string &title)
    {
        Fl_File_Chooser chooser(".", "*", type, title.c_str());
        chooser.show();

        while (chooser.shown())
        {
            Fl::wait();
        }

        if (chooser.value() != 0)
        {
            this->selectedFilename = chooser.value();
        }
        else
        {
            this->selectedFilename = "";
        }

        return this->selectedFilename;
    }

    /**
     * Gets the filename the user selected when the file chooser was invoked
     *
     * @precondition none
     * @postcondition none
     *
     * @return The filename the user had selected when the file chooser was invoked
     */
    const string MovieLibraryWindow::getFilename() const
    {
        return this->selectedFilename;
    }

    /**
     * Callback when the Save button is invoked
     * @precondition widget != 0 AND data != 0
     * @postcondition MovieLibraryWindow::getFilename() == file selected by the user
     *
     * @param widget The widget that initiated the callback
     * @param data Any data that was passed with the call back. In this instance, a pointer to the window.
     */
    void MovieLibraryWindow::cbSave(Fl_Widget *widget, void *data)
    {
        auto *window = (MovieLibraryWindow *) data;
        window->promptUserForFilename(Fl_File_Chooser::CREATE, "Movie file to save to");
    }

    /**
     * Callback when the Add button is invoked
     *
     * @precondition widget != 0 AND data != 0
     * @postcondition none
     *
     * @param widget The widget that initiated the callback
     * @param data Any data that was passed with the call back. In this instance, a pointer to the window.
     */
    void MovieLibraryWindow::cbAddMovie(Fl_Widget *widget, void *data)
    {
        auto *window = (MovieLibraryWindow *) data;

        AddMovieWindow addMovie;
        addMovie.set_modal();
        addMovie.show();

        while (addMovie.shown())
        {
            Fl::wait();
        }

        if (addMovie.getWindowResult() == OKCancelWindow::WindowResult::OK)
        {
            try
            {
                Movie *pMovie = addMovie.getMovie();
                window->library.addMovie(pMovie);
            }
            catch (const invalid_argument &error)
            {
                fl_alert("%s", error.what());
            }


            window->setSummaryText();
        }
    }

    /**
     * Callback when the Delete button is invoked
     *
     * @precondition widget != 0 AND data != 0
     * @postcondition none
     *
     * @param widget The widget that initiated the callback
     * @param data Any data that was passed with the call back. In this instance, a pointer to the window.
     */
    void MovieLibraryWindow::cbDeleteMovie(Fl_Widget *widget, void *data)
    {
        auto *window = (MovieLibraryWindow *) data;

        DeleteMovieWindow deleteMovie;
        deleteMovie.set_modal();
        deleteMovie.show();

        while (deleteMovie.shown())
        {
            Fl::wait();
        }

        if (deleteMovie.getWindowResult() == OKCancelWindow::WindowResult::OK)
        {
            string movieToDelete = deleteMovie.getName();
            if (!window->library.deleteMovie(movieToDelete))
            {
                fl_alert("%s", ("\"" + movieToDelete + "\" does not exist in library").c_str());
            }
            window->setSummaryText();
        }
    }

    /**
     * Determines and sets the sort order based on the radio button the user has selected.
     *
     * @preconditon none
     * @postcondition getSortOrder() == sort order that user selected
     */
    void MovieLibraryWindow::setSortOrderBasedOnSelection()
    {
        for (int i = 0; i < TOTAL_SORTING_METHODS; i++)
        {
            if (this->sortingRadioGroupButton[i]->value())
            {
                this->sortOrderSelection = (SortOrder) i;
            }
        }
    }

    /**
     * Generates the summary output text
     *
     * @precondition none
     * @postcondition none
     */
    void MovieLibraryWindow::setSummaryText()
    {
        string output;

        if (this->getSortOrder() == NAME_ASCENDING)
        {
            output = this->library.generateSummaryByName(true);
        }
        else if (this->getSortOrder() == NAME_DESCENDING)
        {
            output = this->library.generateSummaryByName(false);
        }
        else if (this->getSortOrder() == LENGTH_ASCENDING)
        {
            output = this->library.generateSummaryByLength(true);
        }
        else if (this->getSortOrder() == LENGTH_DESCENDING)
        {
            output = this->library.generateSummaryByLength(false);
        }
        //TODO add other orders (based on radio buttons)
        this->summaryOutputTextBuffer->text(output.c_str());
    }

    /**
     * Gets the sort order the user has selected
     *
     * @precondition none
     * @postcondition none
     *
     * @return The sort order the user has selected
     */
    MovieLibraryWindow::SortOrder MovieLibraryWindow::getSortOrder() const
    {
        return this->sortOrderSelection;
    }

    /**
     * Destructor that cleans up all allocated resources for the window
     */
    MovieLibraryWindow::~MovieLibraryWindow()
    {
        for (int i = 0; i < TOTAL_SORTING_METHODS; i++)
        {
            delete this->radioSortingLabels[i];
            delete this->sortingRadioGroupButton[i];
        }

        delete this->sortingOutputLabel;

        delete this->librarySummaryOutputLabel;
        this->summaryOutputTextDisplay->buffer(0);
        delete this->summaryOutputTextBuffer;
        delete this->summaryOutputTextDisplay;

        delete this->loadButton;
        delete this->saveButton;
        delete this->addButton;
        delete this->deleteButton;
    }

}
