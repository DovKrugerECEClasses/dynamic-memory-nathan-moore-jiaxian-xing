#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdio>
using namespace std;


class Postscript {
private:
    string file_Name;
public:
    Postscript(string file_Name) : file_Name(file_Name){
        ifstream file(file_Name);
        if(file){
            cout << "File Exists" <<endl;
            ofstream file;
            file.open(file_Name);
            file <<"";
            file.close();
        }
    }

    void line(int x1, int y1, int x2, int y2) {
        ofstream file;
        file.open(file_Name, fstream::app);
        file << x1 << " " << y1 << " moveto" << "\n";
        file << x2 << " " << y2 << " lineto" << "\n";
        file << "stroke" <<"\n";
        file.close();
    }

    void setColor(int r, int g, int b){
        double R = r/255.0;
        double G = g/255.0;
        double B = b/255.0;
        ofstream file;
        file.open(file_Name, fstream::app);
        file << R << " " << G << " " << B << " setrgbcolor" <<"\n";
        file.close();
    }

    void drawRect(double x, double y, double w, double h){
        ofstream file;
        file.open(file_Name, fstream::app);
        file << x << " " << y << " moveto" << "\n";
        file << x + w << " " << y << " lineto" << "\n";
        file << x + w << " " << y + h << " lineto" <<"\n";
        file  << x << " " << y + h << " lineto" <<"\n";
        file << x << " " << y << " lineto" <<"\n";
        file << "closepath" <<"\n";
        file << "stroke" << "\n";
        file.close();
    }

    void fillRect(double x, double y, double w, double h){
        ofstream file;
        file.open(file_Name, fstream::app);
        file << x << " " << y << " moveto" << "\n";
        file << x + w << " " << y << " lineto" << "\n";
        file << x + w << " " << y + h << " lineto" <<"\n";
        file  << x << " " << y + h << " lineto" <<"\n";
        file << x << " " << y << " lineto" <<"\n";
        file << "closepath" <<"\n";
        file << "fill" << "\n";
        file.close();
    }

    void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        ofstream file;
        file.open(file_Name, fstream::app);
        file << x1 << " " << y1 << " moveto" << "\n";
        file << x2 << " " << y2 << " lineto" << "\n";
        file << x3 << " " << y3 << " lineto" <<"\n";
        file  << x1 << " " << y1 << " lineto" <<"\n";
        file << "closepath" <<"\n";
        file << "stroke" << "\n";
        file.close();
    }

    void fillTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        ofstream file;
        file.open(file_Name, fstream::app);
        file << x1 << " " << y1 << " moveto" << "\n";
        file << x2 << " " << y2 << " lineto" << "\n";
        file << x3 << " " << y3 << " lineto" <<"\n";
        file  << x1 << " " << y1 << " lineto" <<"\n";
        file << "closepath" <<"\n";
        file << "fill" << "\n";
        file.close();
    }

    void drawCircle(double x, double y, double r){
        ofstream file;
        file.open(file_Name, fstream::app);
        file <<x<<" "<<y<<" "<<"moveto\n";
        file <<r<<" "<<"0"<<" "<<"360"<<" "<<"arc\n";
        file <<"stroke\n";
        file.close();
    }

    void fillCircle(double x, double y, double r){
        ofstream file;
        file.open(file_Name, fstream::app);
        file <<x<<" "<<y<<" "<<"moveto\n";
        file <<r<<" "<<"0"<<" "<<"360"<<" "<<"arc\n";
        file <<"fill\n";
        file.close();
    }
    
    void setFont(string a, int b){
        ofstream file;
        file.open(file_Name, fstream::app);
        file <<a<<" "<<"findfont\n";
        file <<b<<" "<<"scalefont\n";
        file <<"setfont\n";
        file.close();
    }
    
    void text(double a, double b, string c){
        ofstream file;
        file.open(file_Name, fstream::app);
        file <<a<<" "<<b<<" "<<"moveto\n";
        file <<c<<" "<<"show\n";
        file.close();
    }

    void grid(double x1, double xstep, double x2, double y1, double ystep, double y2){
        ofstream file;
        file.open(file_Name, fstream::app);
        for (int i =0; i <= ((y2-y1) / ystep); i++){
        file <<x1 + i*xstep<<" "<<y1<<" "<<"moveto\n";
        file <<y1<<" "<<y2<<" "<<"lineto\n";
        file <<"stroke\n";
        }
        for(int j =0; j <= ((x2-x1) / xstep); j++ ) {
        file <<x1<<" "<<y2 + j*ystep<<" "<<"moveto\n";
        file <<x1<<" "<<x2<<" "<<"lineto\n";
        file <<"stroke\n";
        }
        file.close();
    }
};

int main() {
    Postscript p("test.ps");
    p.line(0,0, 300,400);  // 0 0 moveto 300 400 lineto stroke
    int r = 255, g = 0, b = 0;
    p.setColor(r, g, b); // r, g, b should be from 0.0 to 1.0
    // should turn into 1 0 0 setrgbcolor\n

    p.drawRect(0, 0, 100, 100);   // x y moveto x+w y lineto x+w y+h lineto ... closepath stroke
    p.fillRect(0, 0, 200, 200);   // x y moveto x+w y lineto x+w y+h lineto ... closepath fill
    p.drawTriangle(0,0, 60,60, 120,0);
    p.fillTriangle(0,0, 120,120, 240,0);
    p.drawCircle(100,200,100); // x y 0 360 r arc stroke
    p.fillCircle(100,200,100);
    p.setFont("Helvetica", 32); //  "/Helvetica findfont 32 scalefont setfont"
    p.text(300,400, "testing testing 123"); // 300 400 moveto (testing testing 123)show
    p.grid(300, 50, 500, 400, 50, 700); // x = 300 to 500 stepping 50
	// y = 400 to 700 stepping 50

}



