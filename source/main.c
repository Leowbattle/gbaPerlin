#include <stdint.h>

#define STB_PERLIN_IMPLEMENTATION
#include <stb_perlin.h>

#define IORAM ((uint8_t*)0x04000000)
#define VRAM ((uint16_t*)0x06000000)

#define WIDTH 240
#define HEIGHT 160

typedef uint32_t Colour;

inline Colour rgb(uint32_t red, uint32_t green, uint32_t blue) {
	return red | (green<<5) | (blue<<10);
}

inline void plotRGB(int x, int y, Colour colour) {
	VRAM[y * WIDTH + x] = colour;
}

Colour getColourFromValue(float value) {
	int val = value * 256;
	return rgb(val, val, val);
}

int main() {
	IORAM[0] = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	IORAM[1] = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			float value = stb_perlin_noise3((float)x / 45, (float)y / 45, 0, WIDTH, HEIGHT, 1);
			plotRGB(x, y, getColourFromValue(value));
		}
	}

	while (1);

	return 0;
}