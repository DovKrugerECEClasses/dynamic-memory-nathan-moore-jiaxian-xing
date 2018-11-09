#pragma once

class Color {
private:
  uint32_t rgba;
public:
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 1) {
		rgba = (r<<24) + (g<<16) + (b<<8) + alpha;
	}

	char getColor(){
		if(rgba = 4278190081)return'R';
		if(rgba = 65281)return'G';
		if(rgba = 16711681)return'B';
		if(rgba = 4294967041)return'W';
		if(rgba = 1)return'B';
	}

};
