// #include <QApplication>
// #include "mainwindow.h"

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "taglib-install/include/taglib/fileref.h"
#include "taglib-install/include/taglib/tag.h"
#include "nfd/src/include/nfd.h"

void displayMainMenu()
{
    std::cout << "1. Edit song title" << std::endl;
    std::cout << "2. Edit artist name" << std::endl;
    std::cout << "3. Change song cover" << std::endl;
    std::cout << "4. Close" << std::endl;
    std::cout << "Type any number from \"1\" to \"4\"" << std::endl;
}

void editSongTitle(char * filename)
{
    TagLib::FileRef songfile(filename, true, TagLib::AudioProperties::Average);
    std::cout << "Type new song title: ";
    std::string song_name;
    std::getline(std::cin, song_name);
    songfile.tag()->setTitle(song_name);
    if (songfile.save())
    {
        std::cout << "Song title changed" << std::endl;
    };
}

void editArtistName(char * filename)
{
    TagLib::FileRef songfile(filename, true, TagLib::AudioProperties::Average);
    std::cout << "Type new artist title: ";
    std::string artist_name;
    std::getline(std::cin, artist_name);
    songfile.tag()->setArtist(artist_name);
    if (songfile.save())
    {
        std::cout << "Artist name changed" << std::endl;
    };
}

void editSongCover(char * filename)
{
    TagLib::FileRef songfile(filename, true, TagLib::AudioProperties::Average);

    NFD_Init();

    nfdchar_t *outPath = nullptr;

    nfdu8filteritem_t filters[1] = {
        { "Image Files", "png, jpg, jpeg" }
    };
    
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);

    if (result == NFD_OKAY)
    {
        puts("Success!");
        puts(outPath);
        NFD_FreePathU8(outPath);
    }
    else if (result == NFD_CANCEL)
    {
        puts("User pressed cancel.");
    }
    else
    {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();
}

void run(char * filename) 
{
    // Open file
    std::ifstream ReadFile(filename);

    int option = -1;
    do
    {
        displayMainMenu();
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(option)
        {
            case 1:
                editSongTitle(filename);
                break;
            case 2:
                editArtistName(filename);
                break;
            case 3:
                editSongCover(filename);
                break;            
            case 4:
                break;
            default:
                std::cout << "Unknown option" << std::endl;
        }
    } while (option != 4);

    // Close file
    ReadFile.close();
}

int main(int argc, char * argv[1])
{
    // QApplication a(argc, argv);

    // MainWindow w;
    // w.show();

    if (argc != 2)
    {
        std::cerr << "error: require filename" << std::endl;
        return -1;
    }

    run(argv[1]);

    // return a.exec();
    return 0;
}
