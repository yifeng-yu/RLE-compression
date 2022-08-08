#include "catch.hpp"
#include "RleData.h"
#include "RleFile.h"
#include "SrcMain.h"

// Helper function declarations (don't change these)
extern bool RunCompressionTest(const std::vector<int8_t>& test, const std::vector<int8_t>& expected);
extern bool RunDecompressionTest(const std::vector<int8_t>& test, const std::vector<int8_t>& expected);
extern bool CheckFileMD5(const std::string& fileName, const std::string& expected);
