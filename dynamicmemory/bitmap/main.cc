#include <iostream>
#include "Color.hh"
using namespace std;

int main() {
	Bitmap b(30,20); // 30 pixels across, 20 pixels high, each pixel RGBA
	// top left pixel = (0,0)
	Color RED(255,0,0); // all red, no green, no blue (fully opaque)
	Color BLUE(0,255,0);
	Color GREEN(0,0,255);
	Color WHITE(255,255,255);
	Color BLACK(0,0,0);
	
	
	b.line(0,0,   19,19, RED);
	b.line(0,5,   29,10, BLUE); //Bresenham algorithm
	//https://en.wikipedia.org/wiki/Bresenham's_line_algorithm

	// https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
	//TODO: b.line(0,100, 100,50, BLUE); //Wu algorithm
	b.horizLine(0, 20, 19, GREEN); // from x=0 to x=20 at y=19
	b.vertLine(5, 0,19, GREEN); // from y = 0 to y=19 at x = 5
	b.fillRect(10,10, 4, 3,BLACK); // x = 10, y =10 w=4, h=3
	b.drawRect(10,10, 4, 3,WHITE); // x = 10, y =10 w=4, h=3
  b.ellipse(15,0, 8, 5, RED);    // ellipse centered at (15,0) w= 8, h=5
	cout << b;
	/*
R
 R
  R
   R
    R
BBB
   BBBBB
        BBBBBB
	*/
}

class Bitmap{
private:
	double width, height;
	double* Matrix;
pubilc:
	Bitmap(int across, int high) : height(high), width(across), Matrix(new Array(height*width)){}
	~Bitmap(){
		delete [] Matrix;
	}
	void line(int x0, int y0, int x1, int y1, Color rgba){

	}
	horizLine(int x0, int x1, int y, Color rgba){
		for(int i = x0; i <x2; i++)
			b[y*width + i] = rgba.getColor();
	}
	vertLine(int x, int y0, int y1, Color rgba){
		for(int i = y0; i <y2; i++)
			b[y*i + x] = rgba.getColor();
	}
	fillRect(int x, int y, int w, int h, Color rgba){
		for(int i = 0 , i < h; i++)
			horizLine(int x, int x+w, int y+i, Color rgba);
	}
	drawRect(int x, int y, int w, int h, Color rgba){
		horizLine(int x, int x+w, int y, Color rgba);
		horizLine(int x, int x+w, int y+h, Color rgba);
		vertLine(int x, int y, int y+h, Color rgba);
		vertLine(int x+w, int y, int y+h, Color rgba);
	}
	ellipse(int x, int y, int w, int h, Color rgba){

	}

	friend ostream& operator <<(ostream& s, const Bitmap& b){
        for(int i=0; i<b.height; i++){
            for(int j=0; j<b.width; j++){
                s << b.Matrix[i*b.width+j] << " ";
            }
            s << '\n';
        }
        return s;
    }
	
};

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

	
