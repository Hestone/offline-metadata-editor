// #include <QApplication>
// #include "mainwindow.h"

#include <iostream>

void displayMainMenu() {
    while(true)
    {
        std::cout << "1. Edit" << std::endl;
        std::cout << "2. Close" << std::endl;
        std::cout << "Type \"1\" or \"2\"" << std::endl;
        int option = -1;
        std::cin >> option;
        switch(option)
        {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;            
            case 4:

                break;
            default:
                std::cout << "Unknown option" << std::endl;
        }
    }
}

void run() {
    // Open file

    // Main menu
   displayMainMenu();

    // Close file

}

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);

    // MainWindow w;
    // w.show();

    run();

    // return a.exec();
    return 0;
}
