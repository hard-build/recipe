#include "tinyxml2.hard.h"

#include <gtest/gtest.h>

TEST(tinyxml2_recipe, parses_xml)
{
	tinyxml2::XMLDocument document;
	ASSERT_EQ(document.Parse("<result answer=\"42\"/>"), tinyxml2::XML_SUCCESS);

	const tinyxml2::XMLElement* result = document.FirstChildElement("result");
	ASSERT_NE(result, nullptr);

	int answer = 0;
	EXPECT_EQ(result->QueryIntAttribute("answer", &answer), tinyxml2::XML_SUCCESS);
	EXPECT_EQ(answer, 42);
}
