#include <iostream>
#include <cmath>
#include "Color.hh"
using namespace std;

class Bitmap{
private:
	int width, height;
	char* Matrix;
public:
	Bitmap(int across, int high) : height(high), width(across), Matrix(new char[height*width]){
		for (int i = 0; i < width * height; i++)
			Matrix[i] = '?';
	}
	void line(int x0, int y0, int x1, int y1, Color c){
		int dx = x1 - x0;
		int dy = y1 - y0;
		double error = 0.0;
		double deltaerr = double(dy) / double(dx);
		int y = y0;
		for (int x = x0; x <= x1; ++x){
			Matrix[y*width + x] = c.getColor();
			error += deltaerr;
			if (abs(error) >= 0.5){
				y += 1;
				error -= 1.0;
			}
		}
	}
	void horizLine(int x0, int x1, int y, Color c){
		for(int i = x0; i <x1; i++)
			Matrix[y*width + i] = c.getColor();
	}
	void vertLine(int x, int y0, int y1, Color c){
		for(int i = y0; i <y1; i++)
			Matrix[width*i + x] = c.getColor();
	}
	void fillRect(int x, int y, int w, int h, Color c){
		for(int i = 0; i < h; i++)
			horizLine(x, x+w, y+i, c);
	}
	void drawRect(int x, int y, int w, int h, Color c){
		horizLine(x, x+w, y, c);
		horizLine(x, x+w, y+h, c);
		vertLine(x, y, y+h, c);
		vertLine(x+w, y, y+h, c);
	}
	void ellipse(int x, int y, int w, int h, Color c){
		Matrix[0] = c.getColor();
	}

	friend ostream& operator <<(ostream& s, const Bitmap& xxx){
        for(int i=0; i<xxx.height; i++){
            for(int j=0; j<xxx.width; j++){
                s << xxx.Matrix[i*xxx.width+j] << " ";
            }
            s << '\n';
        }
        return s;
    }

	~Bitmap(){
		delete [] Matrix;
	}

};


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
	cout << b<<"over";


}