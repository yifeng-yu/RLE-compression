#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "RleData.h"
#include "RleFile.h"
#include "catch_reporter_github.hpp"
#include "md5.h"
#include <fstream>
#include <string>
#include <cstdlib>

// Helper functions
bool BuffersAreSame(const std::vector<int8_t>& expected, const std::vector<int8_t>& actual)
{
	if (actual.size() != expected.size())
	{
		FAIL("Expected size is " << expected.size() << " but actual size is " << actual.size());
		return false;
	}
	
	bool retVal = true;
	
	for (size_t i = 0; i < expected.size(); i++)
	{
		if (expected[i] != actual[i])
		{
			retVal = false;
			FAIL("Expected " << static_cast<int>(expected[i])
				 << " at index " << i << " but saw" <<
				 static_cast<int>(actual[i]));
			break;
		}
	}
	
	return retVal;
}

bool RunCompressionTest(const std::vector<int8_t>& test, const std::vector<int8_t>& expected)
{
	RleData r;
	r.Compress(test);
	return BuffersAreSame(expected, r.mData);
}

bool RunDecompressionTest(const std::vector<int8_t>& test, const std::vector<int8_t>& expected)
{
	RleData r;
	r.Decompress(test, expected.size());
	return BuffersAreSame(expected, r.mData);
}

bool CheckFileMD5(const std::string& fileName, const std::string& expected)
{
	MD5 md5;
	std::string hash = md5.digestFile(fileName.c_str());
	return hash == expected;
}

bool CheckTextFilesSame(const std::string& fileNameA, 
	const std::string& fileNameB)
{
	// This is super unfortunate that I'm using std::system, but...
	std::string command;
#ifdef _MSC_VER
	command = "FC /W /LB5 " + fileNameA + " " + fileNameB;
#elif __APPLE__
	command = "diff -sBbu " + fileNameA + " " + fileNameB + " > diff.txt";
#else
	command = "diff -sBbu " + fileNameA + " " + fileNameB + " > diff.txt";
#endif
	int retVal = std::system(command.c_str());
#if !defined(_MSC_VER)
   // Add up to 50 lines of diff output, so we know the difference
   std::system("head -50 diff.txt");
#endif
	return retVal == 0;
}
