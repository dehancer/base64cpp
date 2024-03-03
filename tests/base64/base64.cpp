//
// Created by denn nevera on 2019-08-14.
//

#include "gtest/gtest.h"
#include "base64cpp.hpp"

GTEST_TEST(Base64, Base64Test) {

    std::string str = "1234567890-=asdfghjkl;'zxcvbnm,./1234567890-=asdfghjkl;'zxcvbnm,./1234567890-=asdfghjkl;'zxcvbnm,./1234567890-=asdfghjkl;'zxcvbnm,./1234567890-=asdfghjkl;'zxcvbnm,./1234567890-=asdfghjkl;'zxcvbnm,./";
    std::string base64;

    base64::encode(str, base64, 24);

    std::cout << ">" << base64 << std::endl;

    std::string from_base64;

    base64::decode(base64, from_base64);

    std::cout << "<" << from_base64 << std::endl;

    EXPECT_TRUE(from_base64 == str);

}
