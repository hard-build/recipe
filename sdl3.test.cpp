#include "sdl3.hard.h"

#include <gtest/gtest.h>

#include <memory>

TEST(sdl3_recipe, creates_surface)
{
	EXPECT_EQ(SDL_GetVersion(), SDL_VERSION);

	std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> surface(
	        SDL_CreateSurface(8, 4, SDL_PIXELFORMAT_RGBA8888), SDL_DestroySurface);
	ASSERT_NE(surface, nullptr) << SDL_GetError();
	EXPECT_EQ(surface->w, 8);
	EXPECT_EQ(surface->h, 4);
	ASSERT_TRUE(SDL_FillSurfaceRect(surface.get(), nullptr, 0x123456ff)) << SDL_GetError();

	Uint8 red = 0, green = 0, blue = 0, alpha = 0;
	ASSERT_TRUE(SDL_ReadSurfacePixel(surface.get(), 7, 3, &red, &green, &blue, &alpha))
	        << SDL_GetError();
	EXPECT_EQ(red, 0x12);
	EXPECT_EQ(green, 0x34);
	EXPECT_EQ(blue, 0x56);
	EXPECT_EQ(alpha, 0xff);
}

class sdl3_headless_recipe : public testing::Test
{
protected:
	void SetUp() override
	{
		ASSERT_TRUE(SDL_SetHintWithPriority(SDL_HINT_VIDEO_DRIVER, "dummy", SDL_HINT_OVERRIDE));
		ASSERT_TRUE(SDL_SetHintWithPriority(SDL_HINT_AUDIO_DRIVER, "dummy", SDL_HINT_OVERRIDE));
		ASSERT_TRUE(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) << SDL_GetError();
	}

	void TearDown() override
	{
		SDL_Quit();
		SDL_ResetHint(SDL_HINT_VIDEO_DRIVER);
		SDL_ResetHint(SDL_HINT_AUDIO_DRIVER);
	}
};

TEST_F(sdl3_headless_recipe, creates_window)
{
	EXPECT_STREQ(SDL_GetCurrentVideoDriver(), "dummy");
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(
	        SDL_CreateWindow("recipe test", 32, 24, SDL_WINDOW_HIDDEN), SDL_DestroyWindow);
	ASSERT_NE(window, nullptr) << SDL_GetError();
	int width = 0, height = 0;
	ASSERT_TRUE(SDL_GetWindowSize(window.get(), &width, &height)) << SDL_GetError();
	EXPECT_EQ(width, 32);
	EXPECT_EQ(height, 24);
}

TEST_F(sdl3_headless_recipe, converts_audio)
{
	EXPECT_STREQ(SDL_GetCurrentAudioDriver(), "dummy");
	const SDL_AudioSpec input_spec{SDL_AUDIO_S16, 1, 8000};
	const SDL_AudioSpec output_spec{SDL_AUDIO_F32, 1, 8000};
	std::unique_ptr<SDL_AudioStream, decltype(&SDL_DestroyAudioStream)> stream(
	        SDL_CreateAudioStream(&input_spec, &output_spec), SDL_DestroyAudioStream);
	ASSERT_NE(stream, nullptr) << SDL_GetError();

	const Sint16 input[] = {-32768, 0, 16384};
	ASSERT_TRUE(SDL_PutAudioStreamData(stream.get(), input, sizeof(input))) << SDL_GetError();
	ASSERT_TRUE(SDL_FlushAudioStream(stream.get())) << SDL_GetError();
	float output[3] = {};
	ASSERT_EQ(SDL_GetAudioStreamData(stream.get(), output, sizeof(output)), sizeof(output))
	        << SDL_GetError();
	EXPECT_FLOAT_EQ(output[0], -1.0f);
	EXPECT_FLOAT_EQ(output[1], 0.0f);
	EXPECT_FLOAT_EQ(output[2], 0.5f);
}
