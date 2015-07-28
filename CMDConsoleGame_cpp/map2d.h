#pragma once

#include "vector2.h"
#include "platform_conio.h"

struct Pixel {
	char icon, fcolor, bcolor;
	Pixel() : icon('.'), fcolor(7), bcolor(0) {}
	Pixel(char c) : icon(c), fcolor(7), bcolor(0) {}
};

class Map2D {
	Vector2 size;
	Pixel * pixels;
public:
	Map2D() : pixels(nullptr) {}
	void SetSize(Vector2 size) {
		this->size = size;
		if (pixels) delete[] pixels;
		int total = size.x * size.y;
		pixels = new Pixel[total];
	}
	void SetData(const char * map) {
		int total = size.x * size.y;
		for (int i = 0; i < total; i++) {
			pixels[i].icon = map[i];
		}
	}
	void Draw() {
		for (int row = 0; row < size.y; row++) {
			for (int col = 0; col < size.x; col++) {
				int index = row * size.x + col;
				Pixel * p = &pixels[index];
				char icon = p->icon;
				char something = 'j';
				platform_setColor(p->fcolor, p->bcolor);
				platform_move(row, col);
				putchar(icon);
			}
		}
	}
};