#pragma once

#include <psl1ght/types.h>

typedef struct {
	int x;
	int y;
} point;

typedef struct {
	int height;
	int width;
	uint32_t *ptr;
	// Internal stuff
	uint32_t offset;
} buffer;

void drawLine(buffer *buffer, point point1, point point2, uint32_t color, int thickness);
