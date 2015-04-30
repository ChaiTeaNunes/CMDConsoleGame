#pragma once

#include <stdio.h>

// inline allows this function to be safely defined in a header file
inline void drawProgressBar(int barWidth, int progress, char fg, char bg) {
	for (int i = 0; i < barWidth; i++) {
		putchar((i < progress) ? fg : bg);
	}
}