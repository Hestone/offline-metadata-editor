#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "taglib-install/include/taglib/fileref.h"
#include "taglib-install/include/taglib/tag.h"
#include "taglib-install/include/taglib/attachedpictureframe.h"
#include "taglib-install/include/taglib/mpegfile.h"
#include "taglib-install/include/taglib/id3v2tag.h"
#include "nfd/src/include/nfd.h"

void displayMainMenu()
{
    std::cout << "1. Edit song title" << std::endl;
    std::cout << "2. Edit artist name" << std::endl;
    std::cout << "3. Edit album name" << std::endl;
    std::cout << "4. Change song cover" << std::endl;
    std::cout << "5. Close" << std::endl;
    std::cout << "Type any number from \"1\" to \"5\"" << std::endl;
}

void editNameClasses(int option, char * filename)
{
    TagLib::FileRef songfile(filename, true, TagLib::AudioProperties::Average);
    std::cout << "Edit (" << option << "): ";
    std::string name;
    std::getline(std::cin, name);
    if (option == 1)
    {
        songfile.tag()->setTitle(name);
    } else if (option == 2)
    {
        songfile.tag()->setArtist(name);
    } else
    {
        songfile.tag()->setAlbum(name);
    }
    if (songfile.save())
    {
        std::cout << "Option (" << option << ") successfully changed" << std::endl;
    };
}

void editSongCover(char * filename)
{
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

        std::string audioFilePath = filename;
        TagLib::MPEG::File songFile(audioFilePath.c_str());
        if (!songFile.isValid())
        {
            std::cerr << "Invalid audio file." << std::endl;
            return;
        }

        std::ifstream file(outPath, std::ios::binary | std::ios::ate);
        if (!file.is_open())
        {
            std::cerr << "Could not open image file" << std::endl;
            return;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<char> buffer(size);
        if (!file.read(buffer.data(), size))
        {
            std::cerr << "Failed to read image data." << std::endl;
            return;
        }

        TagLib::ByteVector picture(buffer.data(), size);

        TagLib::ID3v2::Tag* tag = songFile.ID3v2Tag(true);

        tag->removeFrames("APIC");

        TagLib::ID3v2::AttachedPictureFrame * frame = new TagLib::ID3v2::AttachedPictureFrame();
        frame->setMimeType("image/jpeg");
        frame->setType(TagLib::ID3v2::AttachedPictureFrame::FrontCover);
        frame->setDescription("Front Cover");
        frame->setPicture(picture);

        tag->addFrame(frame);
        if (songFile.save())
        {
            std::cout << "Cover art successfully updated" << std::endl;
            return;
        } else
        {
            std::cerr << "Failed to save the file." << std::endl;
        }

        NFD_FreePathU8(outPath);
    } else if (result == NFD_CANCEL)
    {
        puts("User pressed cancel.");
    } else
    {
        printf("Error: %s\n", NFD_GetError());
    }
}

void run(char * filename) 
{
    int option = -1;
    do
    {
        displayMainMenu();
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (1 <= option && option <= 3)
        {
            editNameClasses(option, filename);
        } else if (option == 4)
        {
            editSongCover(filename);
        } else if (option != 5)
        {
            std::cout << "Unknown option" << std::endl;
        }
    } while (option != 5);
}

int main(int argc, char * argv[1])
{
    if (argc != 2)
    {
        std::cerr << "error: require filename" << std::endl;
        return -1;
    }

    NFD_Init();
    run(argv[1]);
    NFD_Quit();

    return 0;
}
