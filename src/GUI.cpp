#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include <FL/Fl_Scroll.H>
#include <FL/Fl_Pack.H>

#include <FL/Fl_Input.H>

#include "Date.hpp"
#include "Person.hpp"
#include "Family_Tree_Controller.hpp"

#include "Widget_Sizes.hpp"

void bttn_click(Fl_Widget* widget, void* data)
{
    Fl_Pack* pack = static_cast<Fl_Pack *>(data);
    Fl_Scroll* scroll = static_cast<Fl_Scroll*>(pack->parent());

    pack->begin();
    Fl_Box* box = new Fl_Box(0, 0, PERSON_BOX_WIDTH, PERSON_BOX_HEIGHT, "Person");
    box->box(FL_UP_BOX);
    // box_y_pos += (PERSON_BOX_HEIGHT + 10);
    pack->end();
    scroll->init_sizes();
    scroll->redraw();

    scroll->scroll_to(scroll->xposition(), scroll->yposition() + PERSON_BOX_HEIGHT + 10);
}

int main(int argc, char** argv)
{

    Family_Tree_Controller ftc = Family_Tree_Controller();

    // initialise gui
    Fl_Window *window = new Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT);

    Fl_Button* bttn = new Fl_Button(10, 600, 100, 200, "Add Box");

    Fl_Scroll* scroll = new Fl_Scroll(10, 20, SCROLL_REGION_WIDTH, SCROLL_REGION_HEIGHT);
        scroll->box(FL_UP_BOX);
        Fl_Pack* pack = new Fl_Pack(10, 20, SCROLL_REGION_WIDTH, SCROLL_REGION_HEIGHT);
        pack->type(Fl_Pack::VERTICAL);
        pack->spacing(10);
        pack->end();
    scroll->end();

    bttn->callback(bttn_click, pack);


    window->end();
    window->show(argc, argv);
    return Fl::run();


}