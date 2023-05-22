#ifndef _CARD_RENDER_INFO_H_
#define _CARD_RENDER_INFO_H_

#include "CardValue.h"
#include "Point.h"

struct CardRenderInfo {
	Point coords = Point(0,0);
	bool matched;
	bool rotate;
	CardValue value;

	CardRenderInfo(bool matched, bool rotate, CardValue value) {
		this->matched = matched;
		this->rotate = rotate; 
		this->value = value;
	}

	void assignPoint(Point coords) {
		this->coords = coords;
	}
};
#endif