/**
============================             
  www.kingstonhack.space    
=============================
  
  edited from minimal example in the rib led library
  created on: 4/4/18
  
  This script will read from the GPIO port, and display a numerical display counting down from 700000
 */

#include <led-matrix.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

const int INPUT_PIN =2;

int flashduration = 0;
int flashnumber =0;

int numbers[10][12][9] = {
{//0
{0,0,0,1,1,1,0,0,0},
{0,0,1,1,0,1,1,0,0},
{0,1,1,0,0,0,1,1,0},
{1,1,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{0,1,1,0,0,0,1,1,0},
{0,0,0,1,1,1,0,0,0}
},

{//1
{0,0,1,1,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,1,1,1,1,0,0}

},

{//2
{0,0,0,1,1,1,0,0,0},
{0,0,1,1,0,1,1,0,0},
{0,1,1,0,0,0,1,1,0},
{1,1,0,0,0,0,0,1,1},
{0,0,0,0,0,0,0,1,1},
{0,0,0,0,0,0,1,1,0},
{0,0,0,0,0,1,1,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,1,1,0,0,0,0,0},
{0,1,1,0,0,0,0,1,1},
{1,1,1,1,1,1,1,1,1}
},

{//3
{0,0,0,1,1,1,0,0,0},
{0,0,1,1,0,1,1,0,0},
{0,1,1,0,0,0,1,1,0},
{1,1,0,0,0,0,0,1,1},
{0,0,0,0,0,0,0,1,1},
{0,0,0,0,0,1,1,0,0},
{0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{0,1,1,0,0,0,1,1,0},
{0,0,1,1,0,1,1,0,0},
{0,0,0,1,1,1,0,0,0}
},

{//4
{0,0,0,0,0,1,1,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,1,1,0,0,0,0},
{0,0,1,1,0,0,0,0,0},
{0,1,1,0,0,0,0,0,0},
{1,1,0,0,0,1,1,0,0},
{1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,1,1,0,0},
{0,0,0,0,0,1,1,0,0},
{0,0,0,0,0,1,1,0,0},
{0,0,0,0,0,1,1,0,0}
},

{//5
{1,1,1,1,1,1,1,1,1},
{1,1,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0},
{1,1,0,0,0,0,0,0,0},
{1,1,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,0,0},
{0,0,0,0,0,0,1,1,0},
{0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{0,1,1,0,0,1,1,0,0},
{0,0,1,1,1,1,0,0,0}
},

{//6
{0,0,0,0,0,1,1,0,0},
{0,0,0,1,1,0,0,0,0},
{0,0,1,1,0,0,0,0,0},
{0,1,1,0,0,0,0,0,0},
{1,1,0,0,0,0,0,0,0},
{1,1,1,1,1,1,0,0,0},
{1,1,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,1,1},
{0,1,1,0,0,0,1,1,0},
{0,0,1,1,0,1,1,0,0},
{0,0,0,1,1,1,0,0,0}
},

{//7
{1,1,1,1,1,1,1,1,1},
{1,1,0,0,0,0,0,1,1},
{0,0,0,0,0,0,0,1,1},
{0,0,0,0,0,0,1,1,0},
{0,0,0,0,0,1,1,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0},
{0,0,0,0,1,1,0,0,0}
},

{//8
{0,0,0,1,1,1,0,0,0},
{0,0,1,1,0,1,1,0,0},
{0,1,1,0,0,0,1,1,0},
{1,1,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{0,1,1,1,1,1,1,1,0},
{0,1,1,1,1,1,1,0,0},
{1,1,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{0,1,1,0,0,0,0,1,0},
{0,0,1,1,1,1,1,0,0}
},

{//9
{0,0,0,1,1,1,0,0,0},
{0,0,1,1,0,1,1,0,0},
{0,1,1,0,0,0,1,1,0},
{1,1,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,1,1},
{0,0,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,1,1},
{0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,1,1,0},
{0,1,1,0,0,1,1,0,0},
{0,0,0,1,1,1,0,0,0}
}

};

int button_press= 0;

int countdown= 000000;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

static void DrawOnCanvas(Canvas *canvas) {
  /*
   * Let's create a simple animation. We use the canvas to draw
   * pixels. We wait between each step to have a slower animation.
   */

  canvas->Fill(0, 0, 0);



  int center_x = canvas->width() / 2;
  int center_y = canvas->height() / 2;
 float radius_max = canvas->width() / 2;
 float angle_step = 1.0 / 360;
 // for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step) {
 //   if (interrupt_received)
 //     return;
  //  float dot_x = cos(a * 2 * M_PI) * r;
  //  float dot_y = sin(a * 2 * M_PI) * r;
  //  canvas->SetPixel(center_x + dot_x, center_y + dot_y,
  //                   255, 0, 0);

 int spacing = 11;
 int x_origin = (canvas->width())-64;
 int y_origin = (canvas->height())-14;


while(true){
	if (interrupt_received)
	return;

//for(int i=0;i<64;i++){
//	for(int j=0; j<16;j++){
//	                canvas->SetPixel(x_origin+i,y_origin+j-2,0,0,0);
//}
//}

for (int i=0; i<6; i++){
	for(int w=0; w<9; w++){
		for (int h=0; h<12; h++){
		int index = (countdown/1)%10;
		int index_1 = (countdown/10)%10;
		int index_2 = (countdown/100)%10;
		int index_3 = (countdown/1000)%10;
		int index_4 = (countdown/10000)%10;
		int index_5 = (countdown/100000)%10;
		if(i==5&&numbers[index_2][h][w]==1){
			 canvas->SetPixel(x_origin+(spacing * i)+w,y_origin+h,255,0,0);}
		else if(i==5&&numbers[index_2][h][w]==0){
			canvas->SetPixel(x_origin+(spacing * i)+w,y_origin+h,0,0,0);} 


		if(i==4&&numbers[index_2][h][w]==1){
			 canvas->SetPixel(x_origin+(spacing * i)+w,y_origin+h,255,0,0);}
		else if(i==4&&numbers[index_2][h][w]==0){
			 canvas->SetPixel(x_origin+(spacing * i)+w,y_origin+h,0,0,0);}   

		if(i==3&&numbers[index_2][h][w]==1){
			canvas->SetPixel(x_origin+(spacing * i)+w, y_origin+h,255,0,0);}
		else if (i==3&&numbers[index_2][h][w]==0){
			canvas->SetPixel(x_origin+(spacing * i)+w,y_origin+h,0,0,0);}

		if(i==2&&numbers[index_3][h][w]==1){
			canvas->SetPixel(x_origin+(spacing * i)+w, y_origin+h,255,0,0);}
		else if (i==2&&numbers[index_3][h][w]==0){
			canvas->SetPixel(x_origin+(spacing * i)+w,y_origin+h,0,0,0);}

		if(i==1&&numbers[index_4][h][w]==1){
			canvas->SetPixel(x_origin+(spacing * i)+w, y_origin+h,255,0,0);}
		else if (i==1&&numbers[index_4][h][w]==0){
			canvas->SetPixel(x_origin+(spacing * i)+w,y_origin+h,0,0,0);}

		if(i==0&&numbers[index_5][h][w]==1){
			canvas->SetPixel(x_origin+(spacing * i)+w, y_origin+h,255,0,0);}
		else if (i==0&&numbers[index_5][h][w]==0){
			canvas->SetPixel(x_origin+(spacing * i)+w,y_origin+h,0,0,0);}
		}
	}
}

if(button_press==1 && countdown<700000){
	countdown+=100;
}
else{
	countdown+=0;
}


if(countdown == 700000){
	flashduration+=1;
if(flashduration<500){
	for(int i=0;i<64;i++){
		canvas->SetPixel(x_origin+i,y_origin-2,0,255,0);
		canvas->SetPixel(x_origin+i,y_origin+13,0,255,0);
	for(int j=0; j<16;j++){
		canvas->SetPixel(x_origin,y_origin-2+j,0,255,0);
                canvas->SetPixel(x_origin+63,y_origin-2+j,0,255,0);
	}	
	}
}
else if(flashduration>500&& flashduration<=999){
	for(int i=0;i<64;i++){
		canvas->SetPixel(x_origin+i,y_origin-2,0,0,0);
		canvas->SetPixel(x_origin+i,y_origin+13,0,0,0);
	}
	for(int j=0; j<16;j++){
                canvas->SetPixel(x_origin,y_origin-2+j,0,0,0);
                canvas->SetPixel(x_origin+63,y_origin-2+j,0,0,0);
        } 	 
}
else if(flashduration>1000){
	if(flashnumber >=3){
	break;}
	flashduration =0;
	flashnumber+=1;
}
}


 usleep(1 * 500);  // wait a little to slow down things. Lower to speed up
}



}


void run_button(){
wiringPiSetup();

button_press = 0;

pinMode (INPUT_PIN,INPUT);
digitalWrite(INPUT_PIN, LOW);
while(true){
if(digitalRead(INPUT_PIN) == HIGH)
{
button_press=1;
printf ("button pressed");
digitalWrite(INPUT_PIN, LOW);
break;
}else{button_press=0;}
}
digitalWrite(INPUT_PIN, LOW);

}

void button_listen(){
button_press=0;
digitalWrite(INPUT_PIN, LOW);
while(true){
if(digitalRead(INPUT_PIN) == HIGH)
{
button_press=1;
printf ("button pressed2");
break;
}else{button_press=0;}
}

}


int main(int argc, char *argv[]) {
run_button();
//wiringPiSetup();

//button_press = 0;

//pinMode (INPUT_PIN,INPUT);
//digitalWrite(INPUT_PIN, LOW);
//while(true){
//if(digitalRead(INPUT_PIN) == HIGH)
//{
//button_press=1;
//printf ("button pressed");
//break;
//}else{button_press=0;}
//}

signal(SIGTERM, InterruptHandler);
signal(SIGINT, InterruptHandler);

while(true){
	if (interrupt_received)
 	return 1;



  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
  defaults.rows = 16;
  defaults.cols = 64;
  defaults.chain_length = 1;
  defaults.parallel = 2;
  defaults.show_refresh_rate = false;



 Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
if (canvas == NULL)
 return 1;



// It is always good to set up a signal handler to cleanly exit when we
// receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
// for that.


DrawOnCanvas(canvas);    // Using the canvas.
countdown =0;
flashduration = 0;
flashnumber=0;


//
  // Animation finished. Shut down the RGB matrix.
  	canvas->Clear();
	delete canvas;
button_listen();  }	
	

 
  return 0;
}

