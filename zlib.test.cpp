#include "zlib.hard.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

TEST(zlib_recipe, compresses_and_decompresses_data)
{
	const std::string input = "The quick brown fox jumps over the lazy dog.";
	const uLong input_size = static_cast<uLong>(input.size());

	uLongf compressed_size = compressBound(input_size);
	std::vector<Bytef> compressed(compressed_size);
	ASSERT_EQ(
		compress2(
			compressed.data(),
			&compressed_size,
			reinterpret_cast<const Bytef*>(input.data()),
			input_size,
			Z_BEST_COMPRESSION),
		Z_OK);
	compressed.resize(compressed_size);

	uLongf output_size = input_size;
	std::vector<Bytef> output(output_size);
	ASSERT_EQ(
		uncompress(
			output.data(),
			&output_size,
			compressed.data(),
			static_cast<uLong>(compressed.size())),
		Z_OK);

	EXPECT_EQ(output_size, input_size);
	EXPECT_EQ(
		std::string(reinterpret_cast<const char*>(output.data()), output_size),
		input);
}
