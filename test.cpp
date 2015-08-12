#include <iostream>
#include <string>
#include <unistd.h>
#include <term.h>
#include <cstdlib>
#include <bitmap_image.hpp>
#include <math.h>
using namespace std;

class location{
public:
int x;
int y;
};

	// Clear Screen Function
void ClearScreen(){
  if (!cur_term)
  {
    int result;
    setupterm( NULL, STDOUT_FILENO, &result  );
    if (result <= 0) return;
    
  }

  putp( tigetstr( "clear"  )  );
  
}
//defining variables
unsigned int intercept;
unsigned int xres;
unsigned int yres;
int raylength;
double vlinedivisor[255];
string yorp;
signed long vlinelength[256];
int i(1);
int resolutionset(0);
int map[1024][1024];
int screen[256][256];
int mapgen(0);
unsigned char red;
unsigned char green;
unsigned char blue;
int counter(0);
int length = 0;
location camera;
location ray;
location mapcell;
location screencell;
//vline function
void  vline(unsigned int xvalue, int whichvline){
//Turns out I probably only needed one argument, Oh weel.
int px = yres / 2;
length = yres / vlinedivisor[whichvline];
for (px = yres / 2; px < length; px++){
screen[xvalue][px] = 1;
}
for (px = yres /2; px > -length; px++){
screen[xvalue][px] = 1;
}
}
// Raycasting Function
void Raycast(){
	for (double i(-1); i <= 1; i = i + 1 / xres){
        ray.x = camera.x;
        ray.y = camera.y;
cout << i << endl;
cout << "making a ray..." << endl;
	counter = 0;
	while (intercept == 0 && counter == 0){
        ray.y--;
        ray.x += i;
        raylength++;
	if (map[camera.x][(int)(rint(camera.y))] == 1){
intercept = 1;
vlinedivisor[int((i+1)* xres / 2)] = raylength;
                
	}
counter++;        
	}
        
	}

}

void Render(){
ClearScreen();
for (int inc = 1; inc < xres; inc++){
        vline(inc, inc);

}
for (int y = 1; y < yres; y++){
	for (int x = 1; x < xres; x++){
		if (screen[x][y] == 1){
//for rendering a block
cout << (char) 177;
                
		}else{
//for rendering a space
cout << " ";
                
		}
        
	}
cout << endl;

}

}

//Main Function
int main(int argc, char *argv[]){
//Initial Screen Clearing
ClearScreen();
//And Why not some branding
cout << "ZaSH"<< endl;
//Program Loop
while (i == 1){
getline(cin, yorp);	


//Commands
//Setting the resolution
if (yorp == "/setres"){
cout << endl << "Xres: ";
cin >> xres;
cout <<endl << "Yres: ";
cin >> yres;
cout << endl;
if (xres > 255 || yres > 255 || xres % 1 != 0 || yres % 1 != 0){
resolutionset = 0;
cout << "Values must be integers of 255 or less" << endl;
}else{cout << "Resolution has been set." 
<< endl;
resolutionset = 1;
} 
}
//Raycasting
if (yorp == "/raycast"){
if (resolutionset == 1 && mapgen ==1){
cout << "Beginning raycast" << endl;
Raycast();
cout << "Ending Raycast" << endl;
}else{
cout << "The resolution has not been set or the map has not been generated." << endl << "Use \"/setres\" and \"/mapgen\"." << endl;
}
}
//Setting the location of the camera
if (yorp == "/setloc"){
cout << endl;
cout << "Camera.X = ";
cin >> camera.x;
cout << endl << "Camera.Y = ";
cin >> camera.y;
cout << endl;
}
//Generating a map to raycast.
if (yorp == "/mapgen"){
bitmap_image image ("mapbitmap.bmp");
if (!image){
cout << "It didn't work" << endl;
}	
else{
	for ( mapcell.y = 0; mapcell.y < 1024; ++mapcell.y){
	for ( mapcell.x = 0; mapcell.x < 1024; ++mapcell.x){
image.get_pixel(mapcell.x, mapcell.y, red, green, blue);
if (red == 0)
map[mapcell.x][mapcell.y] = 1;
else
map[mapcell.x][mapcell.y] = 0;
		
	}
}
mapgen = 1;
cout << "A Map has been created from a bitmap" << endl;

}
}

if (yorp == "/render"){
Render();
}
	 



//Making sure the map is generated
if (yorp == "/viewmap" && mapgen == 1){
cout << "IT WERKS!" << endl;

}
if (yorp == "/viewmap" && mapgen == 0){
cout << "A Map has not been generated." << endl;
cout << "Type in \"/mapgen\" to generate one" << endl;
}
//Quitting
if (yorp  == "/quit" || yorp == "/exit"){
	cout << "ZaSH is halting" << endl;
	return 0;
	}
//Calling the ClearScreen funtion
if (yorp == "/cls"){
	ClearScreen();
}
//RENDERING!!!!!11
	}
}
