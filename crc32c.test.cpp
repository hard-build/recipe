#include "crc32c.hard.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

TEST(crc32c_recipe, computes_checksum)
{
	const std::string input(32, '\0');

	EXPECT_EQ(
		crc32c::Crc32c(input),
		static_cast<std::uint32_t>(0x8a9136aa));
}
