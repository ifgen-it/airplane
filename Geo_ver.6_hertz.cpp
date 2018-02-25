
#include <iostream>
#include <cstdio>
#include <cmath>
#include <time.h> //nanosleep
#include <clocale>

#define PI 3.14159265

#define HEART 10084
#define SOLID 0x2588

wchar_t Sym1 = L'$';
wchar_t Sym2= L'♡';
wchar_t Space = L' ';
wchar_t SymGeo1= L'○';
wchar_t SymGeo2= L'●';
wchar_t SymGeo3= L'—';
wchar_t SymGeoHead = L'●';
/*
wchar_t Car[2][9] = {
	L"____\\_",
	L"'-o——o—'"
};
*/

const int CarHeight = 13;
const int CarWidth = 23;
/*
wchar_t Car[CarHeight][CarWidth] = {
	L"__/——\\__",
	L"==○==○=="
};
*/

wchar_t Car[CarHeight][CarWidth] = {
L"     11",
L"      11",
L"       111",
L"        111",
L"111      1111",
L" 1111111111111111111",
L"  11111111111111111111",
L" 1111111111111111111",
L"111      1111",
L"        111",
L"       111",
L"      11",
L"     11"
};

// nanosleep parametrs:
	timespec tw = {0, 1000000 };
	timespec tr;
	
	// Display dimensions
const int Cols = 60;
const int Rows = 45;
const float DispRatio = 9/16. ;
const float Ratio = DispRatio* static_cast<float>(Rows)/Cols;

wchar_t Disp[Rows][Cols];

// Axis parametrs
const int AxisXZero = 4; //Cols /2;
const int AxisYZero = Rows /2;
wchar_t AxisX = L'-';
wchar_t AxisY = L'|';



// Letter dimensions
const int LCols = 26;
const int LRows = 20;

// letter start
int LColsS = 16;  //(Cols - LCols)/2;
int LRowsS = 14; //(Rows - LRows)/2;




void PrintArr(wchar_t Arr[][Cols], int Rows, int Cols);
void FillArr( wchar_t Arr[][Cols], int Rows, int Cols );
void PrintArrInt(int Arr[][Rows][Cols], int Rows, int Cols );


// ---++ Geo ++=--

void AddAxises( wchar_t Arr[][Cols], int Rows, int Cols );
void AddLine( float a, float b);
void AddLineWithRate( float a, float b, int r1, int r2);
void DelLine( float a, float b);
void DelLineWithRate( float a, float b, int r1, int r2);

void AddCircle( float a, float b, float r);
void AddCircle1( float a, float b, float r);
void AddCircle2( float a, float b, float r);
void AddCircle3( float a, float b, float r);

void AddCircle4( float a, float b, float r, int cStart , int length, bool clockwise);

void AddSinWithRate( float a, float b, float r1, float r2);
void AddSinWithRate1( float a, float b, float r1, float r2 , wchar_t SymGeo);
void AddSinFillWithRate1( float a, float b, float r1, float r2 , wchar_t SymGeo);
void AddDoubleSinFillWithRate1( float a, float b, float r1, float r2 );
void AddSinWithRateAndHeight( float a, float b, float r1, float r2, int RatioY );
void ShiftArr(wchar_t Arr[][Cols], int Rows, int Cols);

using namespace std;

int main(){
	srand(time(0));
  
    	   float ran1 = 0 ;
    	   float ran2 = 1*PI;
    	  int Counter = 0;
    	  FillArr(Disp, Rows, Cols);
    	  
    	while (true ){   
   	int i = 1 + rand()%13;
   	if ( Counter %2 == 1 ){
   		ran1 = PI;
   		ran2 = 2*PI;
   	}
   	else {
   		ran1 = 0;
   		ran2 = 1*PI;	
   	}
     AddSinWithRateAndHeight ( 1, 0, ran1,  ran2, i);
     Counter++;
    	}

	return 0;
}

// Geo functions
void AddSinWithRateAndHeight( float a, float b, float r1, float r2, int RatioY ){
	int i = 0;
	int j = 0;
	int y ; //= -i + AxisYZero;
	int x; // = j - AxisXZero;
	
	int SinStart = Cols - CarWidth - 5;
	
	float RatioX = 10;
//	float RatioY = 12;
	
	int min = r1*RatioX + AxisXZero;
	int max = r2*RatioX + AxisXZero;
	
	 for (int j = min ; j <= max; j++){
	 		x = j - AxisXZero;
	 		y = (sin(a*x/RatioX) + b)*RatioY;
	 		i = -y + AxisYZero;
	 		
             if ( i >= 0 && i < Rows ){
    	Disp[i][ SinStart ] = SymGeo3;
    	
    	// add car
    	for (int n =0; n < CarHeight ; n++){
    		for (int m = 0; m < CarWidth-1; m++){
    			if ( Car [n][m] ){
    				if ( Car [n][m] == L'1' ){
    Disp[i - CarHeight/2 + n][ SinStart +1+m]=SymGeoHead;
    		  	}
    			}
    			else break;
    		}
    	}
    	
    	// fill
    /*
    	for (int Fill = i+1; Fill < Rows; Fill++){
    	Disp[ Fill ][ Cols - 10 ] = SymGeo3;
    	}
    	*/
    	
         system("cls");
         PrintArr(Disp, Rows, Cols);
         nanosleep(&tw, &tr);
         
         	// delete the car
    	for (int n = 0; n < CarHeight ; n++){
    		for (int m = 0; m < CarWidth-1 ; m++){
    			Disp[i - CarHeight/2 + n][ SinStart +1+m] =Space;
    		}
    	}
    	// shift display
        ShiftArr(Disp, Rows, Cols);
            }
	 }	
};


void AddDoubleSinFillWithRate1( float a, float b, float r1, float r2 ){
	int i1 = 0;
	int i2 = 0;
	int j = 0;
	
	int y1 ; //= -i + AxisYZero;
	int x1 ;// = j - AxisXZero;
	int y2;
	int x2;
	// axis ratio
	float RatioX = 10;
	float RatioY = 10;
	// 1 sin rates
	int min = r1*RatioX + AxisXZero;
	int max = r2*RatioX + AxisXZero;
	int jReal = j - min;
	// 2 sin parametres
	float Delta = PI;
	
	// drawing
	 for (int j = min ; j <= max ; j++){
	 	
	 	  // 1 sin coordinates
	 		x1 = j - AxisXZero;
	 		y1 = (sin(a*x1/RatioX) + b)*RatioY;
	 		i1 = -y1+ AxisYZero;
	 		
	 		// 2 sin coordinates
	 		x2 = x1 + Delta*RatioX;
	 		y2 = (sin(a*x2/RatioX) + b)*RatioY;
	 		i2 = -y2+ AxisYZero;
	 		
	 		jReal = j - min;
	 		// 1st sin
             if ( ( i1 >= 0 && i1 < Rows) &&
       (jReal >= 0 && jReal  < Cols-10) ){
    	Disp[i1][jReal] = SymGeo1;
       }
       // 2nd sin
         if ( ( i2 >= 0 && i2 < Rows) &&
       (jReal >= 0 && jReal < Cols-10) ){
    	Disp[i2 ][jReal] = SymGeo2;
       }
       	// fill between sinusoides
       	
       	    if ( ( i1 >= 0 && i1 < Rows) &&
       (jReal >= 0 && jReal  < Cols-20) ){
       	if ( i2 > i1){
    	for (int Fill = i1+1; Fill < i2; Fill++){
    	Disp[Fill ][jReal ] = SymGeo3;
    	}
       	}
       	else{
       for (int Fill = i2+1; Fill < i1; Fill++){
    	Disp[Fill ][jReal ] = SymGeo3;
    	}
       	}
       }
       	// end filling
       	
       
	 }
 
	
};

void AddSinFillWithRate1( float a, float b, float r1, float r2 , wchar_t SymGeo){
	int i = 0;
	int j = 0;
	int y ; //= -i + AxisYZero;
	int x; // = j - AxisXZero;
	
	float RatioX = 12;
	float RatioY = 12;
	
	int min = r1*RatioX + AxisXZero;
	int max = r2*RatioX + AxisXZero;
	int jReal = j - min;
	
	 for (int j = min ; j <= max; j++){
	 		x = j - AxisXZero;
	 		y = (sin(a*x/RatioX) + b)*RatioY;
	 		i = -y + AxisYZero;
	 		
	 		jReal = j - min;
             if ( ( i >= 0 && i < Rows) &&
       (jReal >= 0 && jReal < Cols) ){
    	Disp[i][jReal ] = SymGeo;
    	for (int Fill = i+1; Fill < Rows; Fill++){
    	Disp[Fill ][jReal ] = SymGeo3;
    	}
    	
            	//	   system("cls");
           //	PrintArr(Disp, Rows, Cols);
          //    nanosleep(&tw, &tr);
            }
	 }	
};

void AddSinWithRate1( float a, float b, float r1, float r2 , wchar_t SymGeo){
	int i = 0;
	int j = 0;
	int y ; //= -i + AxisYZero;
	int x; // = j - AxisXZero;
	
	float RatioX = 12;
	float RatioY = 12;
	
	int min = r1*RatioX + AxisXZero;
	int max = r2*RatioX + AxisXZero;
	int jReal = j - min;
	
	 for (int j = min ; j <= max; j++){
	 		x = j - AxisXZero;
	 		y = (sin(a*x/RatioX) + b)*RatioY;
	 		i = -y + AxisYZero;
	 		
	 		jReal = j - min;
             if ( ( i >= 0 && i < Rows) &&
       (jReal >= 0 && jReal < Cols) ){
    	Disp[i][jReal ] = SymGeo;
            	//	   system("cls");
           //	PrintArr(Disp, Rows, Cols);
          //    nanosleep(&tw, &tr);
            }
	 }	
};




void AddSinWithRate( float a, float b, float r1, float r2){
	int i = 0;
	int j = 0;
	int y ; //= -i + AxisYZero;
	int x; // = j - AxisXZero;
	
	float RatioX = 10;
	float RatioY = 12;
	
	int min = r1*RatioX + AxisXZero;
	int max = r2*RatioX + AxisXZero;
	
	
	 for (int j = min;  j <= max; j++){
	 		x = j - AxisXZero;
	 		y = (sin(a*x/RatioX) + b)*RatioY;
	 		i = -y + AxisYZero;
             if ( ( i >= 0 && i < Rows) &&
       (j >= 0 && j < Cols) ){
    	Disp[i][j] = SymGeo2;
            	//	   system("cls");
           //	PrintArr(Disp, Rows, Cols);
          //    nanosleep(&tw, &tr);
            }
	 }	
};

void AddAxises( wchar_t Arr[][Cols], int Rows, int Cols ){
	// draw axis Y
	for (int i = 0; i < Rows; i++){
		Arr[ i ][ AxisXZero ] = AxisY;
	}

	// draw axis X
		for (int j = 0; j < Cols; j++){
			Arr[ AxisYZero ][ j ] = AxisX;
		}
		
}

// y = a*x + b
void AddLine( float a, float b){
	int i = 0;
	int j = 0;
	int y ; //= -i + AxisYZero;
	int x; // = j - AxisXZero;
	
	 for (int j = 0;  j < Cols; j++){
	 		x = j - AxisXZero;
	 		y = a*x + b;
	 		i = -y + AxisYZero;
if ( i >=0 && i <Rows)Disp[i][j] = SymGeo1;
	 }	
};

void AddLineWithRate( float a, float b, int r1, int r2){
	int i = 0;
	int j = 0;
	int y ; //= -i + AxisYZero;
	int x; // = j - AxisXZero;
	int min = r1 + AxisXZero;
	int max = r2 + AxisXZero;
	
	 for (int j = min;  j <= max; j++){
	 		x = j - AxisXZero;
	 		y = a*x + b;
	 		i = -y + AxisYZero;
if ( i >=0 && i <Rows)Disp[i][j] = SymGeo1;
	 }	
};

void DelLineWithRate( float a, float b, int r1, int r2){
	int i = 0;
	int j = 0;
	int y ; //= -i + AxisYZero;
	int x; // = j - AxisXZero;
	int min = r1 + AxisXZero;
	int max = r2 + AxisXZero;
	
	 for (int j = min;  j <= max; j++){
	 		x = j - AxisXZero;
	 		y = a*x + b;
	 		i = -y + AxisYZero;
if ( i >=0 && i <Rows)Disp[i][j] = Space;
	 }	
};

void DelLine( float a, float b){
	int i = 0;
	int j = 0;
	int y ; //= -i + AxisYZero;
	int x; // = j - AxisXZero;
	
	 for (int j = 0;  j < Cols; j++){
	 		x = j - AxisXZero;
	 		y = a*x + b;
	 		i = -y + AxisYZero;
if ( i >=0 && i <Rows)Disp[i][j] = Space;
	 }	
};


// x2 + y2 = r2
void AddCircle( float a, float b, float r){
	int i = 0;
	int j = 0;
	int y ; //= -i + AxisYZero;
	int x; // = j - AxisXZero;
	
	 for (int j = 0;  j < Cols; j++){
	 		x = j - AxisXZero;
	 		if (abs (x) > r) continue;
	 		y = pow((pow(r,2) - pow(x,2)), 0.5);
	 		i = -y + AxisYZero;
if ( i >=0 && i <Rows){
	Disp[i][j] = SymGeo1;
	Disp[Rows - i][j] = SymGeo1;
}
	 }	
};

void AddCircle1( float a, float b, float r){
	int i = 0;
	int j = 0;
	int step = 1;
for ( int c = 0; c < 360; c+= step){
	float Deg = c* PI /180;
    float y = r*sin(Deg);
    float x = r*cos(Deg);
   	i = -y + AxisYZero - b;
       j = x + AxisXZero + a;
       if ( ( i >= 0 && i < Rows) &&
       (j >= 0 && j < Cols) ){
    	Disp[i][j] = SymGeo1;
    	  // system("cls");
    		//PrintArr(Disp, Rows, Cols);
           // nanosleep(&tw, &tr);
       }
}
	 
};

void AddCircle2( float a, float b, float r){
	int i = 0;
	int j = 0;
	int step = 6;
	int offset = 90;
	
for ( int c = 360; c > 0; c-= step){
	float Deg = (c + 90)* PI /180 ;
    float y = r*sin(Deg);
    float x = r*cos(Deg);
   	i = -y + AxisYZero - b;
       j = x + AxisXZero + a;
       if ( ( i >= 0 && i < Rows) &&
       (j >= 0 && j < Cols) ){
    	Disp[i][j] = SymGeo1;
  
    	   system("cls");
    		PrintArr(Disp, Rows, Cols);
           nanosleep(&tw, &tr);
       }
     
}
	 
};

void AddCircle3( float a, float b, float r){
	int i = 0;
	int j = 0;
	int step = 1;
	int offset = 90;
	
for ( int c = 360; c > 0; c-= step){
	float Deg = (c + 90)* PI /180 ;
    float y = r*sin(Deg);
    float x = r*cos(Deg);
   	i = -y + AxisYZero - b;
       j = x + AxisXZero + a;
       if ( ( i >= 0 && i < Rows) &&
       (j >= 0 && j < Cols) ){
    	Disp[i][j] = SymGeo1;
    /*
    if ( x > 0){
      AddLineWithRate(y/x,  0, 0, x);
    }
    else AddLineWithRate(y/x,  0, x,0);
   */
     // AddLine(y/x,0);
    	   system("cls");
    		PrintArr(Disp, Rows, Cols);
           nanosleep(&tw, &tr);
         /*
            if ( x > 0){
      DelLineWithRate(y/x,  0, 0, x);
    }
    else DelLineWithRate(y/x,  0, x, 0);
         */
       }
     
}
	 
};

void AddCircle4( float a, float b, float r, int cStart , int length, bool clockwise){
	int i = 0;
	int j = 0;
	int step = 2;
	if (clockwise) step = -2;
	
	int offset = 90;
	int repeat = 0;
	
for ( int c = cStart; c > cStart-360; c= c+step ){
	float Deg = (c + 90)* PI /180 ;
    float y = r*sin(Deg) * Ratio;
    float x = r*cos(Deg);
   	i = -y + AxisYZero - b;
       j = x + AxisXZero + a;
       if ( ( i >= 0 && i < Rows) &&
       (j >= 0 && j < Cols) ){
    	Disp[i][j] = SymGeo1;
 
    	   system("cls");
    	PrintArr(Disp, Rows, Cols);
          nanosleep(&tw, &tr);
         
         repeat++;
         if (repeat == length/abs(step)) break;
       }
}
	 
};

void FillArr( wchar_t Arr[][Cols], int Rows, int Cols ){
		// fill Disp 
	wchar_t* p = Arr[0];
	for (int i = 0; i < Rows*Cols; i++){
		*p = Space;
		p++;
	}
}

void ShiftArr(wchar_t Arr[][Cols], int Rows, int Cols){
   for (int j = 0; j < Cols-1; j++){
   	for (int i = 0; i < Rows; i++){
			Arr[i][j] = Arr[i][j+1];
   	}
   }
   for (int i = 0; i < Rows; i++){
			Arr[i][ Cols-1] = Space; 
   	}
}

void PrintArr(wchar_t Arr[][Cols], int Rows, int Cols){
	for (int i = 0; i < Rows; i++){
		for (int j = 0; j < Cols; j++){
			wcout << Arr[i][j] ;
		//	nanosleep(&tw, &tr);
		}
		cout << endl;
	}
}

void PrintArrInt(int Arr[][Rows][Cols], int Rows, int Cols ){
	for (int i = 0; i < Rows; i++){
		for (int j = 0; j < Cols; j++){
			cout << Arr[0][i][j] ;
		//	nanosleep(&tw, &tr);
		}
		cout << endl;
	}
}