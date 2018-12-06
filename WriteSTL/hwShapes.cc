/*
	Author:jx
    cite: view the code of Christian Jensen(https://github.com/DovKrugerECEClasses/dynamic-memory-rostyslav-christian/blob/master/STLgen.cpp)
*/
/*
	Cube
	Cylinder
	Sphere (optional)

https://en.wikipedia.org/wiki/STL_(file_format)
An ASCII STL file begins with the line:
solid name
The file continues with any number of triangles, each represented as follows:(	all facets are simple triangles.)
facet normal ni nj nk
    outer loop
        vertex v1x v1y v1z
        vertex v2x v2y v2z
        vertex v3x v3y v3z
    endloop
endfacet
(where each n or v is a floating-point number in sign-mantissa-"e"-sign-exponent format,
e.g., "2.648000e-002". )
The file concludes with：
endsolid name
 */
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<fstream>
using namespace std;

const double PI = 3.14159265358979;

class point{
public:
	double x,y,z;
public:
	point(double x,double y, double z):x(x),y(y),z(z){}
};

class Facet{
private:
	point a, b, c;
public:
	Facet(const point& a,const point& b,const point& c):a(a),b(b),c(c){}// get a triangle facet

	friend string operator +(const string& o,const Facet& f) {
		double ni, nj, nk;
		ni =1;
		nj =1;
		nk =1;
		string s = o + "facet normal " + to_string(ni) +' '+ to_string(nj)+' ' + to_string(nk) + "\n"
				   + "\touter loop" + "\n"
				   + "\t\tvertex " + to_string(f.a.x)+' ' + to_string(f.a.y)+' ' + to_string(f.a.z) + "\n"
				   + "\t\tvertex " + to_string(f.b.x)+' ' + to_string(f.b.y)+' ' + to_string(f.b.z) + "\n"
				   + "\t\tvertex " + to_string(f.c.x)+' ' + to_string(f.c.y)+' ' + to_string(f.c.z) + "\n"
				   + "\t endloop" + "\n"
				   + "endfacet" + "\n";
		return s;
	}
};

class Shape{
public:
	double x0,y0,z0;
public:
	Shape(): x0(0), y0(0), z0(0){};
	virtual double volume() const = 0;
};

class Cube: public Shape{
private:
	double cubeRadius, cubeHeight, n;

public:
	string s;
	Cube(double l): Shape(), cubeRadius(sqrt(2*l*l)/2), cubeHeight(l),  n(4){};
//	getCube(){//bottom + top + front + back + left + right;
//        e = s/2.0;//e is half lenght of the edges of cube
//        point a(x0+e,y0+e,z0-e);point b(x0-e,y0+e,z0-e) ;point c(x0-e,y0-e,z0-e); Facet f(point a,point b,point c);
//        Facet(a,b,c);
//	}

	void get() {//bottom + top + side;
		double q = 2*PI/n;

		for(int i = 0;i < n; i++){
			point a(x0,y0,z0-cubeHeight/2.0)  ;
			point b(x0+cubeRadius*cos(q*i),y0+cubeRadius*sin(q*i),z0-cubeHeight/2.0);
			point c(x0+cubeRadius*cos(q*(i+1)),y0+cubeRadius*sin(q*(i+1)),z0-cubeHeight/2.0);
			Facet f1( a, b, c);
			s = s + f1;
		}

		for(int i = 0;i < n; i++){
			point a(x0,y0,z0+cubeHeight/2.0)  ;
			point b(x0+cubeRadius*cos(q*i),y0+cubeRadius*sin(q*i),z0+cubeHeight/2.0);
			point c(x0+cubeRadius*cos(q*(i+1)),y0+cubeRadius*sin(q*(i+1)),z0+cubeHeight/2.0);
			Facet f1( a, b, c);
			s = s + f1;
		}

		for(int i = 0;i < n; i++){
			point a(x0+cubeRadius*cos(q*i),y0+cubeRadius*sin(q*i),z0-cubeHeight/2.0);
			point b(x0+cubeRadius*cos(q*(i+1)),y0+cubeRadius*sin(q*(i+1)),z0-cubeHeight/2.0);
			point c(x0+cubeRadius*cos(q*i),y0+cubeRadius*sin(q*i),z0+cubeHeight/2.0);
			Facet f1( a, b, c);
			s = s + f1;
			point d(x0+cubeRadius*cos(q*i),y0+cubeRadius*sin(q*i),z0+cubeHeight/2.0);
			point e(x0+cubeRadius*cos(q*(i+1)),y0+cubeRadius*sin(q*(i+1)),z0+cubeHeight/2.0);
			point f(x0+cubeRadius*cos(q*i),y0+cubeRadius*sin(q*i),z0-cubeHeight/2.0);
			Facet f2( d, e, f);
			s = s + f2;
		}
	}

	void translate(double dx, double dy, double dz){
		x0 += dx;
		y0 += dy;
		z0 += dz;
	}

	double volume(){
		return cubeHeight*cubeHeight*cubeHeight;
	}

	void write(const string& file_Name){
		ifstream file(file_Name);
//        ofstream file;
		file.open(file_Name, fstream::app);
		get();
		file << s;
		file.close();
	}
};

class Cylinder: public Shape {
private:
	double radius, height,n;// n sides(n = 10);
public:
	string s;
	Cylinder(double r,double h):Shape(), radius(r), height(h), n(10){};

	string get() {//bottom + top + side;
		double q = 2 * PI / n;

		for (int i = 0; i < n; i++) {
			point a(x0, y0, z0 - height / 2.0);
			point b(x0 + radius * cos(q * i), y0 + radius * sin(q * i), z0 - height / 2.0);
			point c(x0 + radius * cos(q * (i + 1)), y0 + radius * sin(q * (i + 1)), z0 - height / 2.0);
			Facet f1( a, b, c);
			s = s + f1;
		}

		for (int i = 0; i < n; i++) {
			point a(x0, y0, z0 + height / 2.0);
			point b(x0 + radius * cos(q * i), y0 + radius * sin(q * i), z0 + height / 2.0);
			point c(x0 + radius * cos(q * (i + 1)), y0 + radius * sin(q * (i + 1)), z0 + height / 2.0);
			Facet f1( a, b, c);
			s = s + f1;
		}

		for (int i = 0; i < n; i++) {
			point a(x0 + radius * cos(q * i), y0 + radius * sin(q * i), z0 - height / 2.0);
			point b(x0 + radius * cos(q * (i + 1)), y0 + radius * sin(q * (i + 1)), z0 - height / 2.0);
			point c(x0 + radius * cos(q * i), y0 + radius * sin(q * i), z0 + height / 2.0);
			Facet f1( a, b, c);
			s = s + f1;
			point d(x0 + radius * cos(q * i), y0 + radius * sin(q * i), z0 + height / 2.0);
			point e(x0 + radius * cos(q * (i + 1)), y0 + radius * sin(q * (i + 1)), z0 + height / 2.0);;
			point f(x0 + radius * cos(q * i), y0 + radius * sin(q * i), z0 - height / 2.0);
			Facet f2( d, e, f);
			s = s + f2;
		}
	}

	double volume(){
		return PI * radius * radius * height;
	}

};

class Design {
private:
	string s;
public:
//    Design(){};//build auto

	void add(const Cube& x){
		s += x.s;//how to get all my shapes into the same file
	}
	void add(const Cylinder& x){
		s += x.s;//how to get all my shapes into the same file
	}

	void write(string file_Name){
		ifstream file(file_Name);
//        ofstream file;
		file.open(file_Name, fstream::app);
		file << s;
		file.close();
	}
};

int main() {
	Design d;
	double s = 10;
	Cube c(s);
	c.translate(5,5,5);
	// rotate??
	cout << c.volume() << '\n';
	c.write("out.stl"); // how to get all my shapes into the same file
	d.add(c);
	double r = 10, height  = 20;
	Cylinder cyl(r, height);
//    cout << cyl.volume() << '\n';
	d.add(cyl);
	d.write("test.stl");
}
