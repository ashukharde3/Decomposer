/*! main.cc
 * 
 * This file includes the definition for the main function which is
 * standard entry point for the application.
 */
#include <cstdlib>
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::cin;

#include "declaration.h"
#include "user_interface.h"


/*
 * @breif The entry point for the application.
 */
int main(void) {

    UserInterface ui = UserInterface::instance();
    ui.run();
    return EXIT_SUCCESS;
}
