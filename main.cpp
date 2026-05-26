// #include <QApplication>
// #include "mainwindow.h"

#include <iostream>

void displayMainMenu() {
    int option = -1;
    do
    {
        std::cout << "1. Edit song title" << std::endl;
        std::cout << "2. Edit artist name" << std::endl;
        std::cout << "3. Change song cover" << std::endl;
        std::cout << "4. Close" << std::endl;
        std::cout << "Type \"1\" or \"2\"" << std::endl;
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
    } while (option != 4);
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
