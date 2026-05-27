# Offline Metadata Editor
A lightweight C++ application for editing music file metadata locally.

## Features
* Edit song title, artist, and album metadata,
* Embed album cover art into MP3 files (ID3v2 support),
* Native file picker integration using NFD
* Simple terminal-based menu interface
* Built using TagLib for audio metadata manipulation

## Build Instructions
```
g++ main.cpp nfd/src/nfd_cocoa.m \ 
    -I./taglib-install/include \
    -I./nfd/src/include \
    -L./taglib-install/lib \
    -ltag -lz \
    -framework AppKit \
    -framework UniformTypeIdentifiers \
    -o app
```

## Current Work in Progress
* Album cover support refinement (JPEG/PNG handling improvements)
* Input validation for menu system
* Audio file type validation
* File picker integration for audio file selection instead of manual path entry
* Improved error handling and stability

## Planned Features
* Genre editing support
* Album-level batch editing interface
    ```
    User chooses an album -> Program prints all songs in the album -> Dynamic list of songs is printed -> individually change each song's metadata
    ```
* Duplicate detection for song metadata
    * Prevent duplicate song names within the same album
    * Allow duplicates across unreleated selections with warning logic.
    ```
    If a song's name matches another song's name, program must assert and disallow changes.
    If users select an album with duplicated names, program must detect duplicates and immediately forces users to change song name.
    If users select a song individually with the same song name as an unselected song, proceed anyway but warn that the same name is present.
    ```

## Notes
This project is under active development and focuses on building a cross-platform offline tool for managing music metadata efficiently.