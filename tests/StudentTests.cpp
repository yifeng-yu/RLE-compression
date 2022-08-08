#include "catch.hpp"
#include "RleData.h"
#include "RleFile.h"
#include "SrcMain.h"

// Helper function declarations (don't change these)
extern bool RunCompressionTest(const std::vector<int8_t>& test, const std::vector<int8_t>& expected);
extern bool RunDecompressionTest(const std::vector<int8_t>& test, const std::vector<int8_t>& expected);
extern bool CheckFileMD5(const std::string& fileName, const std::string& expected);

TEST_CASE("RLE Compression", "[student]")
{
    
    // 2. row = 10, col = 12  = 120, + 7
    SECTION("9. 128 a 128 a")
    {
        std::vector<int8_t> test = {
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a',

        };
        std::vector<int8_t> expected = {
            127,'a',1,'a',
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }
    
	SECTION("Basic positive run")
	{
		std::vector<int8_t> test = {
			'a','a','a','b','b','b','c','c','c',42,42,42,
			'a','a','a','b','b','b','c','c','c',42,42,42,
			'a','a','a','b','b','b','c','c','c',42,42,42,
			'a','a','a','b','b','b','c','c','c',42,42,42,
			'a','a','a','b','b','b','c','c','c',42,42,42,
			'a','a','a','b','b','b','c','c','c',42,42,42,
			'a','a','a','b','b','b','c','c','c',42,42,42,
			'a','a','a','b','b','b','c','c','c',42,42,42,
		};
		std::vector<int8_t> expected = {
			3,'a',3,'b',3,'c',3,42,
			3,'a',3,'b',3,'c',3,42,
			3,'a',3,'b',3,'c',3,42,
			3,'a',3,'b',3,'c',3,42,
			3,'a',3,'b',3,'c',3,42,
			3,'a',3,'b',3,'c',3,42,
			3,'a',3,'b',3,'c',3,42,
			3,'a',3,'b',3,'c',3,42,
		};

		bool result = RunCompressionTest(test, expected);
		REQUIRE(result);
	}


	// TODO: Add more test case sections!!



    SECTION("1. simple test case")
    {
        std::vector<int8_t> test = {
            'a','a','a','b','b','b','c',
        };
        std::vector<int8_t> expected = {
            3,'a',3,'b',1,'c',
        };

        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }
    SECTION("2. mix of positive and negative case")
    {
        std::vector<int8_t> test = {
            'a','b','c','a','b','c','a','a','a',
        };
        std::vector<int8_t> expected = {
            -6,'a','b','c','a','b','c',3,'a',
        };

        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    // 2. row = 10, col = 12  = 120, + 7
    SECTION("3. -127 followed by 2 same and 2 diff")
    {
        std::vector<int8_t> test = {
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',
            'h','h',
            'a','b',
        };
        std::vector<int8_t> expected = {
            -127,
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',
            2,'h',
            -2, 'a','b',
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    // 2. row = 10, col = 12  = 120, + 7
    SECTION("4. -127 followed by -2 and 2")
    {
        std::vector<int8_t> test = {
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',
            'h','i',
            'a','a',
        };
        std::vector<int8_t> expected = {
            -127,
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',
            -2,'h', 'i',
            2,'a',

        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

//   2. row = 10, col = 12  = 120, + 7
    SECTION("5. 127 followed by 1")
    {
        std::vector<int8_t> test = {
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a',
        };
        std::vector<int8_t> expected = {
            127,'a',1,'a'
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    // 2. row = 10, col = 12  = 120, + 7
    SECTION("5. 127 followed by -2 and 3a")
    {
        std::vector<int8_t> test = {
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a',
            'a','b',
            'a','a','a',
        };
        std::vector<int8_t> expected = {
            127,'a',-2,'a','b',3,'a',
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

     //2. row = 10, col = 12  = 120, + 7
    SECTION("6. 127")
    {
        std::vector<int8_t> test = {
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a',
        };
        std::vector<int8_t> expected = {
            127,'a',
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    // 2. row = 10, col = 12  = 120, + 7
    SECTION("7. -127")
    {
        std::vector<int8_t> test = {
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',
        };
        std::vector<int8_t> expected = {
            -127,
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',

        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    // 2. row = 10, col = 12  = 120, + 7
    SECTION("7. -127 127 2a -2 b c 2a")
    {
        std::vector<int8_t> test = {
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a',
            'a','a',
            'b','c',
            'a','a',
        };
        std::vector<int8_t> expected = {
            -127,
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',
            127,'a',
            2,'a',
            -2,'b','c',
            2,'a',

        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    // 2. row = 10, col = 12  = 120, + 7
    SECTION("8. 147 a 1b")
    {
        std::vector<int8_t> test = {
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'b',
        };
        std::vector<int8_t> expected = {
            127,'a',20,'a',1,'b',
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    // 2. row = 10, col = 12  = 120, + 7
    SECTION("9. 147  a -2 b c")
    {
        std::vector<int8_t> test = {
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'b','c',
        };
        std::vector<int8_t> expected = {
            127,'a',20,'a',-2,'b','c',
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    SECTION("10. -2 a b 3 c -4 d e f g ")
    {
        std::vector<int8_t> test = {
            'a','b','c','c','c','d','e','f','g',
        };
        std::vector<int8_t> expected = {
            -2,'a','b',3,'c',-4,'d','e','f','g',
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    SECTION("11. 3 a -6 b c d e f g ")
    {
        std::vector<int8_t> test = {
            'a','a','a','b','c','d','e','f','g',
        };
        std::vector<int8_t> expected = {
            3,'a',-6,'b','c','d','e','f','g',
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }

    SECTION("12. new test case")
    {
        std::vector<int8_t> test = {
            'a','a','a','b','c','d','e','f','g',
            'a','a','a','b','c','d','e','f','g',
            'a','a','a','b','c','d','e','f','g',
            'a','a','a','b','c','c','c','c',

        };
        std::vector<int8_t> expected = {
            3,'a',-6,'b','c','d','e','f','g',
            3,'a',-6,'b','c','d','e','f','g',
            3,'a',-6,'b','c','d','e','f','g',
            3,'a',1,'b',4,'c',
        };
        bool result = RunCompressionTest(test, expected);
        REQUIRE(result);
    }




}

TEST_CASE("RLE Decompression", "[student]")
{
	SECTION("Basic positive run")
	{
		std::vector<int8_t> test = {40,'x',};
		std::vector<int8_t> expected = {
			'x','x','x','x','x','x','x','x','x','x',
			'x','x','x','x','x','x','x','x','x','x',
			'x','x','x','x','x','x','x','x','x','x',
			'x','x','x','x','x','x','x','x','x','x',
		};

		bool result = RunDecompressionTest(test, expected);
		REQUIRE(result);
	}

	// TODO: Add more test case sections!!
    SECTION("1. Basic negative run")
    {
        std::vector<int8_t> test = { -5,'x','y','z','a','b',};
        std::vector<int8_t> expected = {
            'x','y','z','a','b',
        };

        bool result = RunDecompressionTest(test, expected);
        REQUIRE(result);
    }

    SECTION("2. long negative run ")
    {
        std::vector<int8_t> test = {
            -127,
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',

        };
        std::vector<int8_t> expected = {
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g','h','i','j',
            'a','b','c','d','e','f','g',
        };

        bool result = RunDecompressionTest(test, expected);
        REQUIRE(result);
    }

    SECTION("4. long positive run")
    {
        std::vector<int8_t> test = {127,'a',-2,'a','b',};
        std::vector<int8_t> expected = {
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','a','a',
            'a','a','a','a','a','a','a','a','b'
        };

        bool result = RunDecompressionTest(test, expected);
        REQUIRE(result);
    }

    
    

}

TEST_CASE("Command line arguments", "[student]")
{
	SECTION("instructions.txt.rl1")
	{
		const char* argv[] = {
			"tests/tests",
			"data/instructions.txt.rl1"
		};
		ProcessCommandArgs(2, argv);
		bool result = CheckFileMD5("data/instructions.txt", "5e042d2e4bf014e714dd7cfc4dc25aab");
		REQUIRE(result);
	}
}

TEST_CASE("File compression", "[student]")
{
	RleFile r;
	SECTION("rle.bmp")
	{
		r.CreateArchive("data/rle.bmp");
		bool result = CheckFileMD5("data/rle.bmp.rl1", "f2a9d8425d53c664e45d9eb1b53137b9");
		REQUIRE(result);
	}
	SECTION("pic.jpg")
	{
		r.CreateArchive("data/pic.jpg");
		bool result = CheckFileMD5("data/pic.jpg.rl1", "0bbf2a5109b30d79939d2061ea8c74aa");
		REQUIRE(result);
	}
	SECTION("Conquest.ogg")
	{
		r.CreateArchive("data/Conquest.ogg");
		bool result = CheckFileMD5("data/Conquest.ogg.rl1", "ec29ff368ec5100bfba22635ddc5ba5c");
		REQUIRE(result);
	}
}

TEST_CASE("File decompression", "[student]")
{
	RleFile r;
	SECTION("works.bmp.rl1")
	{
		r.ExtractArchive("data/works.bmp.rl1");
		bool result = CheckFileMD5("data/works.bmp", "8baad647acefae2f8c36ee111582a875");
		REQUIRE(result);
	}
	SECTION("xkcd.bmp.rl1")
	{
		r.ExtractArchive("data/xkcd.bmp.rl1");
		bool result = CheckFileMD5("data/xkcd.bmp", "a4d7efa89d47a94a76f8050dd8d60cd0");
		REQUIRE(result);
	}
	SECTION("logo.png.rl1")
	{
		r.ExtractArchive("data/logo.png.rl1");
		bool result = CheckFileMD5("data/logo.png", "95403309460632f60efa647ef59b78fc");
		REQUIRE(result);
	}
}

