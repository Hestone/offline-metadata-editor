# offline-metadata-editor
A C++ GUI app that edits music metadata

to compile:
g++ main.cpp nfd/src/nfd_cocoa.m   -I./taglib-install/include   -I./nfd/src/include   -L./taglib-install/lib   -ltag -lz   -framework AppKit   -framework UniformTypeIdentifiers   -o musiceditor