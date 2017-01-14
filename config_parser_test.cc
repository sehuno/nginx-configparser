#include "gtest/gtest.h"
#include "config_parser.h"

TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
}

TEST(NginxConfigParserTest, ToStringTest) {
	NginxConfigStatement statement;
	statement.tokens_.push_back("listen");
	statement.tokens_.push_back("80");
	EXPECT_EQ(statement.ToString(0), "listen 80;\n");
}

class NginxConfigStringTest : public ::testing::Test {
protected:
	bool ParseString(const std::string config_string) {
		std::stringstream config_stream(config_string);
		return parser.Parse(&config_stream, &out_config);
	}
	NginxConfigParser parser;
	NginxConfig out_config;
};

TEST_F(NginxConfigStringTest, EmptyConfigTest) {
	EXPECT_FALSE(ParseString(""));
}

TEST_F(NginxConfigStringTest, EmptyInsideTest) {
	EXPECT_FALSE(ParseString("server { }"));
}

TEST_F(NginxConfigStringTest, MissingSemiColonTest) {
	EXPECT_FALSE(ParseString("server { listen 80 }"));
}

TEST_F(NginxConfigStringTest, UnbalancedCurlyBraces) {
	EXPECT_FALSE(ParseString("server { "));
	EXPECT_FALSE(ParseString("server { listen 80;"));
}