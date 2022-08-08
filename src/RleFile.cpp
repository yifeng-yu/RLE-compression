#include "RleFile.h"
#include "RleData.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <fstream>

void RleFile::CreateArchive(const std::string& source)
{
	// TODO
    std::ifstream::pos_type size;
    char* memblock = nullptr;
    // Open the file for input, in binary mode, and start ATE (at the end)
    std::ifstream file (source, std::ios::in|std::ios::binary|std::ios::ate);
    std::vector<int8_t> input;
    if (file.is_open()){
        size = file.tellg(); // Save the size of the file
        memblock = new char[static_cast<unsigned int>(size)];
        file.seekg(0, std::ios::beg); // Seek back to start of file
        file.read(memblock, size);
        file.close();
        // File data is now in memblock array
        // (Do something with it here...)

        mHeader.mFileSize = static_cast<int>(size);
        mHeader.mFileNameLength = static_cast<unsigned char> (source.length());
        mHeader.mFileName = source;
        
        input.reserve(size);
        for(int i = 0; i < size; i++){
            input.push_back(memblock[i]);
        }
        mRleData.Compress(input);
        // Make sure to clean up!
        delete[] memblock;
    }

    std::ofstream arc(source + ".rl1", std::ios::out|std::ios::binary|std::ios::trunc);
    if (arc.is_open())
    {
    // Use arc.write function to write data here
        arc.write(mHeader.mSig, 4);
        arc.write(reinterpret_cast<char*>(&mHeader.mFileSize), 4);
        arc.write(reinterpret_cast<char*>(&mHeader.mFileNameLength), 1);
        arc.write(mHeader.mFileName.c_str(), static_cast<int>(mHeader.mFileNameLength));

        for(size_t i = 0; i < mRleData.mData.size(); i++){
            arc.write(reinterpret_cast<char*>(&mRleData.mData[i]), 1);
        }
        arc.close();
    }

}

void RleFile::ExtractArchive(const std::string& source)
{
	// TODO

    std::ifstream::pos_type size;
    char* memblock = nullptr;

    std::ifstream file(source, std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char[static_cast<int>(size)];
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);
        file.close();

        mHeader.mFileSize = *(reinterpret_cast<int*>(&memblock[4]));
        mHeader.mFileNameLength = *(reinterpret_cast<unsigned char*>(&memblock[8]));
        for (size_t i = 0; i < mHeader.mFileNameLength; i++)
        {
            mHeader.mFileName += memblock[9 + i];
        }
        std::vector<int8_t> input;
        
        for (size_t i = mHeader.mFileNameLength + 9; i < size; i++)
        {
           input.push_back(memblock[i]);
        }
        mRleData.Decompress(input, mHeader.mFileSize);
        delete[] memblock;

        std::ofstream arc(mHeader.mFileName, std::ios::out | std::ios::binary | std::ios::trunc);
        if (arc.is_open())
        {
//            arc.write(reinterpret_cast<char*>(&mHeader.mFileSize), 4);
//            arc.write(reinterpret_cast<char*>(&mHeader.mFileNameLength), 1);
//            arc.write(mHeader.mFileName.c_str(), static_cast<int>(mHeader.mFileNameLength));
            for(size_t i = 0; i < mRleData.mData.size(); i++){
                arc.write(reinterpret_cast<char*>(&mRleData.mData[i]), 1);
            }
            arc.close();
        }


    }


}
