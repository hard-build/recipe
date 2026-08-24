#include "yaml-cpp.hard.h"

#include <gtest/gtest.h>

TEST(yaml_cpp_recipe, parses_yaml)
{
	const YAML::Node document = YAML::Load("answer: 42\nname: hard\n");

	ASSERT_TRUE(document.IsMap());
	EXPECT_EQ(document["answer"].as<int>(), 42);
	EXPECT_EQ(document["name"].as<std::string>(), "hard");
}
