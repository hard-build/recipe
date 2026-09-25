#include "libpng.hard.h"

#include <gtest/gtest.h>

#include <array>
#include <vector>

TEST(libpng_recipe, round_trips_rgba_pixels_in_memory)
{
	const std::array<png_byte, 16> pixels = {
	        255, 0, 0, 255, 0, 255, 0, 128, 0, 0, 255, 64, 255, 255, 255, 0};
	png_image input{};
	input.version = PNG_IMAGE_VERSION;
	input.width = 2;
	input.height = 2;
	input.format = PNG_FORMAT_RGBA;

	png_alloc_size_t size = 0;
	ASSERT_TRUE(png_image_write_to_memory(
	        &input, nullptr, &size, 0, pixels.data(), 0, nullptr))
	        << input.message;
	std::vector<png_byte> encoded(size);
	ASSERT_TRUE(png_image_write_to_memory(
	        &input, encoded.data(), &size, 0, pixels.data(), 0, nullptr))
	        << input.message;
	encoded.resize(size);
	ASSERT_GE(encoded.size(), 8u);
	EXPECT_EQ(png_sig_cmp(encoded.data(), 0, 8), 0);

	png_image output{};
	output.version = PNG_IMAGE_VERSION;
	ASSERT_TRUE(png_image_begin_read_from_memory(
	        &output, encoded.data(), encoded.size()))
	        << output.message;
	EXPECT_EQ(output.width, input.width);
	EXPECT_EQ(output.height, input.height);
	output.format = PNG_FORMAT_RGBA;
	std::vector<png_byte> decoded(PNG_IMAGE_SIZE(output));
	const bool read = png_image_finish_read(
	        &output, nullptr, decoded.data(), 0, nullptr);
	EXPECT_TRUE(read) << output.message;
	png_image_free(&output);
	EXPECT_EQ(decoded, std::vector<png_byte>(pixels.begin(), pixels.end()));
}
