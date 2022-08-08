#include "SrcMain.h"
#include <string>
#include "RleFile.h"

void ProcessCommandArgs(int argc, const char* argv[])
{
	// TODO: Process argc and argv, and use to compress/decompress files
    // In this case, argv[1] contains the name of a file. If this file name ends with “.rl1” then you should take the file and call ExtractArchive on it. For files that do not end in “.rl1” call CreateArchive.
    if (argc == 2){
        std::string filename = argv[1];
        std::string ext = filename.substr(filename.length()-4, filename.length());
        if(ext == ".rl1"){
            RleFile().ExtractArchive(filename);
        }
        else {
            RleFile().CreateArchive(filename);
        }
    }
    
}

