#include "base64cpp.hpp"
#include "gtest/gtest.h"

GTEST_TEST(Base64, Base64Test) {
	std::string str =
	    "1234567890-=asdfghjkl;'zxcvbnm,./1234567890-=asdfghjkl;'zxcvbnm,./"
			"1234567890-=asdfghjkl;'zxcvbnm,./1234567890-=asdfghjkl;'zxcvbnm,./"
			"1234567890-=asdfghjkl;'zxcvbnm,./1234567890-=asdfghjkl;'zxcvbnm,./";
	std::string base64;

	base64::encode(str, base64, 24);

	std::string from_base64;

	base64::decode(base64, from_base64);

	EXPECT_TRUE(from_base64 == str);
}
