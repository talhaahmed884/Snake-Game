//============================================================================
// Name       :  Snake
// Author      : Sibt ul Hussain
// Version     : Beta v1.69
// Copyright   : (c) Rights Reserved
// Description : Basic 2D game of Snake
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
#include<ctime>
using namespace std;
int randm();
void gameover();
void gameover1();
/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}
/*
 * Main Canvas drawing function.
 * */
//double startx=320,starty=400;
int U=0,D=0,L=0,R=0,DPx=330,DPy=300,A=0,B,C=0,temX,temY,DPX[10000],DPY[10000],countx,county,SFD=4,CF=15,FDx[10],FDy[10],TMR=750;
int FDBR=85,SCR=0,SNKX=0,SNKY=0,PWR=0,PWRFDx=700,PWRFDy=700,LVL=1,sccr=10,SNKL=2,GMOVR=1500,ext=0,Scr=0,HSCR=0,DR=1,HRDLx[4],HRDLy[4],HRDLTMR=750;
ostringstream scr,lvl;
string SCr,Lvl;
void Display()
{
    // set the background color using function glClearColotgr.s
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    //DrawSquare( 300 , 300 ,100,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
    //DrawString( 50, 600, "Here are some are basic shapes", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
    //DrawString( 50, 570, "You will use these to make your game", colors[MISTY_ROSE]); // this will print given string at x=50 , y=570
    //DrawCircle( 200 , 200 , 50 , colors[5]); // This will draw a circle at x=200,y=200 of radius 50
	//v1( x,y )   v2( x,y )  , v3( x,y ) 
    //DrawTriangle( 300, 50 , 500, 50 , 400 , 250, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
    //DrawLine( 550 , 50 ,  550 , 600 , 20 , colors[MISTY_ROSE] );
	//Background of the field
	for(int a=0;a<65;a++)
	{
		for(int b=0;b<65;b++)
		{
			DrawSquare(a*10,b*10,11,colors[119]);
		}
	}
	//level shashka display
	DrawString(300,660,"Level:",colors[59]);
	lvl.str("");
	lvl<<LVL;
	Lvl=lvl.str();
	DrawString(365,660,Lvl,colors[59]);
	if(SCR>=150)
	{
		LVL++;
		lvl.str("");
		lvl<<LVL;
		Lvl=lvl.str();
		sccr-=2;
		FDBR=85;
		SNKL+=2;
		SCR=0;
	}
	//level 2 shashka
	if(LVL==2 || LVL==3)
	{
		DrawLine(0,3,650,3,10,colors[128]);//along lower x-axis
		DrawLine(3,650,3,0,10,colors[128]);//along left y-axis
		DrawLine(0,650,650,650,10,colors[129]);//along upper x-axis
		DrawLine(646,0,646,650,10,colors[128]);//along right y-axis
	}
	if(LVL==2 || LVL==3)
	{
		if(DPy<5)
		{
			gameover();
		}
		if(DPy>640)
		{
			gameover();
		}
		if(DPx<5)
		{
			gameover();
		}
		if(DPx>640)
		{
			gameover();	
		}
	}
	//level 3 shashka
	if(ext==0)
	{
		if(LVL==3)
		{
			if(HRDLTMR==750)
			{
				for(int a=1;a<=3;a++)
				{
					HRDLx[a-1]=randm();
					while(HRDLx[a-1]<=15 || HRDLx[a-1]>=620)
					{
						HRDLx[a-1]=randm();
					}				
					HRDLy[a-1]=randm();
					while(HRDLy[a-1]<=15 || HRDLy[a-1]>=620)
					{
						HRDLy[a-1]=randm();
					}
					HRDLx[a]=randm();
					while(HRDLx[a]==HRDLx[a-1] || HRDLx[a]<=15 || HRDLx[a]>=620)
					{
						HRDLx[a]=randm();
					}
					HRDLy[a]=randm();
					while(HRDLy[a]==HRDLy[a-1] || HRDLy[a]<=15 || HRDLy[a]>=620)
					{
						HRDLy[a]=randm();
					}
				}
				HRDLTMR=0;
			}
			HRDLTMR++;
		}
	}
	//level 3 shashka display
	if(LVL==3)
	{
		if(ext==0)
		{
			for(int a=0;a<=3;a++)
			{
				DrawSquare(HRDLx[a],HRDLy[a],40,colors[59]);
			}
		}
	}
	//level 3 shashka score display
	if(LVL==3)
	{
		for(int a=0;a<4;a++)
		{
			for(int b=-25;b<=25;b++)
			{
				if((DPx==HRDLx[a]+b && DPy==HRDLy[a]+b) || (DPy==HRDLx[a]+b && DPx==HRDLy[a]+b))
				{
					gameover();
				}
			}
		}
	}
	//level 3 shashka score display
	if(LVL==4)
	{
		gameover1();
	}
	//Score
	if(ext==0)
	{
		scr.str("");
		scr<<SCR;
		SCr=scr.str();
		DrawString( 540, 660, "Score:", colors[59]);
		DrawString(605,660,SCr,colors[59]);
		//Score Bar
		DrawString(20,660,"Snake",colors[59]);
		DrawLine(85,665,FDBR,665,30,colors[59]);
		//movement of snake and control by keys
		//for initial movement and for right key
		if(DR==1)
		{
			DPx+=5;
		}
		//for up key
		if(DR==4)
		{
			DPy+=5;
		}
		//for down key
		if(DR==3)
		{
			DPy-=5;
		}
		//for left key
		if(DR==2)
		{
			DPx-=5;
		}
	}
	//Boundaries
	//on right and left side
	if(LVL==1)
	{
		if(DPx>650)
		{
			DPx=0;
		}
		if(DPx<0)
		{
			DPx=650;
		}
		//on up and down side
		if(DPy>645)
		{
			DPy=0;
		}
		if(DPy<0)
		{
			DPy=645;
		}
	}
	/*//eyes Shashka
	DrawCircle(DPx+2,DPy+2,2,colors[65]);
	DrawCircle(DPx+2,DPy+2,2,colors[65]);*/
	//snake swap and following
	if(ext==0)
	{	
		DrawCircle(DPx,DPy,5,colors[101]);
		countx=DPX[0],county=DPY[0];
		DPX[0]=DPx,DPY[0]=DPy;
		C=0;
		for(int a=1;a<=SFD;a++)
		{
			C-=5;
			temX=DPX[a],temY=DPY[a];
			DPX[a]=countx,DPY[a]=county;
			countx=temX, county=temY;
			DrawSquare(countx+C,county+C,10,colors[101]);
			countx+=5,county+=5;
		}
	}
	 //Power Food shashka
	if(LVL==1 || LVL==2)
	{
		if(PWR==4)
		{
			for(int a=0;a<5;a++)
			{
				FDx[a]=700;
				FDy[a]=700;
			}
			PWRFDx=randm();
			while(PWRFDx==0)
			{
				PWRFDx=randm();
			}
			PWRFDy=randm();
			while(PWRFDy==0)
			{
				PWRFDy=randm();
			}
			PWR=0;
			TMR=0;
		}
	}
	 //Power Food shashka
	if(LVL==3)
	{
		if(PWR==4)
		{
			for(int a=0;a<5;a++)
			{
				FDx[a]=700;
				FDy[a]=700;
			}
			for(int a=0;a<4;a++)
			{
				PWRFDx=randm();
				while(PWRFDx==0 || PWRFDx==HRDLx[a] || PWRFDx==HRDLy[a])
				{
					PWRFDx=randm();
				}
				PWRFDy=randm();
				while(PWRFDy==0 || PWRFDy==HRDLx[a] || PWRFDy==HRDLy[a])
				{
					PWRFDy=randm();
				}
				PWR=0;
				TMR=0;
			}
		}
	}
	//Food of snake for level 1 shashka
	if(LVL==1)
	{
		if(TMR==750)
		{
			FDx[0]=randm();
			while(FDx[0]==0)
			{
				FDx[0]=randm();
			}
			FDy[0]=randm();
			while(FDy==0)
			{
				FDy[0]=randm();
			}
			for(int a=1;a<5;a++)
			{
				FDx[a]=randm();
				FDy[a]=randm();
				while(FDx[a-1]==FDx[a] || FDx[a]==0)
				{
					FDx[a]=randm();
				}
				while(FDy[a-1]==FDx[a])
				{
					FDx[a]=randm();
				}
				while(FDy[a-1]==FDy[a] || FDy[a]==0)
				{
					FDy[a]=randm();
				}
				while(FDx[a-1]==FDy[a])
				{
					FDy[a]=randm();
				}
			}
			TMR=0;
		}
		TMR++;
	}
	//Food of snake for level 2 shashka
	if(LVL==2)
	{	
		if(TMR==750)
		{
			FDx[0]=randm();
			while(FDx[0]==0 || FDx[0]<=10 || FDx[0]>=620)
			{
				FDx[0]=randm();
			}
			FDy[0]=randm();
			while(FDy==0 || FDy[0]<=10 || FDy[0]>=620)
			{
				FDy[0]=randm();
			}
			for(int a=1;a<5;a++)
			{
				FDx[a]=randm();
				FDy[a]=randm();
				while(FDy[a-1]==FDx[a] || FDx[a-1]==FDx[a] || FDx[a]==0 || FDx[a]<=10|| FDx[a]>=620)
				{
					FDx[a]=randm();
				}
				while(FDx[a-1]==FDy[a] || FDy[a-1]==FDy[a] || FDy[a]==0 || FDy[a]<=10 || FDy[a]>=620)
				{
					FDy[a]=randm();
				}
			}
			TMR=0;
		}
		TMR++;
	}
	//Food of snake for level 3 shashka
	if(LVL==3)
	{	
		if(TMR==750)
		{
			FDx[0]=randm();
			FDy[0]=randm();
			for(int a=0;a<4;a++)
			{
				while(FDx[0]==HRDLx[a] || FDx[0]==HRDLy[a] || FDx[0]==0 || FDx[0]<=10 || FDx[0]>=620)
				{
					FDx[0]=randm();
				}
				while(FDy[0]==HRDLx[a] || FDy[0]==HRDLy[a] || FDy==0 || FDy[0]<=10 || FDy[0]>=620)
				{
					FDy[0]=randm();
				}
			}
			for(int a=0;a<5;a++)
			{
				for(int b=0;b<4;b++)
				{
					while(FDx[a]==HRDLx[b] || FDx[a]==HRDLy[b] || FDx[a]<=10 || FDx[a]>=620 || FDx[a]==FDx[a-1] || FDx[a]==FDy[a-1])
					{
						FDx[a]=randm();
					}
					while(FDy[a]==HRDLx[b] || FDy[a]==HRDLy[b] || FDy[a]<=10 || FDy[a]>=620 || FDy[a]==FDx[a-1] || FDy[a]==FDy[a-1])
					{
						FDy[a]=randm();
					}
				}
			}
			TMR=0;
		}
		TMR++;
	}
	if(ext==0)
	{
		//food of snake display
		for(int a=0;a<5;a++)
		{
			DrawSquare(FDx[a]-5,FDy[a]-5,10,colors[101]);
		}
		//power food shashka display
		DrawCircle( PWRFDx , PWRFDy, 10 , colors[80]);
	}
	if(TMR==750)
	{
		PWRFDx=700;
		PWRFDy=700;
	}
	//Food eaten by snake
	for(int a=0;a<5;a++)
	{
		if(DPx==FDx[a] && DPy==FDy[a])
		{
			PWR++;
			SCR+=sccr;
			HSCR+=sccr;
			SFD+=SNKL;
			FDBR+=sccr;
			FDx[a]=randm(),FDy[a]=randm();
			//score
			Scr=SCR;
			scr.str("");
			scr<<Scr;
			SCr=scr.str();
		}
	}
	//power food shashka eaten by snake
	for(int a=-20;a<=20;a++)
	{
		if(DPx==(PWRFDx+a) && DPy==(PWRFDy+a))
		{
			SCR+=20;
			HSCR+=20;
			Scr=SCR;
			SFD+=6;
			FDBR+=20;
			PWRFDx=700;
			PWRFDy=700;
			TMR=750;
		}
	} 
	//collision detection with snake's body
	/*for(int a=1;a<=SFD;a++)
	{
		if((DPx==DPX[a]-5) && (DPy==DPY[a]-5))
		{
			//exit(1);
			cout<<"error"<<endl;
		}
	}*/
	glutSwapBuffers(); // do not modify this line.
}
/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */
 void gameover()
	{
		for(int a=0;a<70;a++)
		{
			for(int b=0;b<70;b++)
			{
				DrawSquare(a*10,b*10,50,colors[131]);
			}
		}
		ext=1;
		DrawString(280,350,"Game Over!!",colors[130]);
		scr.str("");
		scr<<HSCR;
		SCr=scr.str();
		DrawString( 280, 315, "Score:", colors[130]);
		DrawString(345,315,SCr,colors[130]);
		lvl.str("");
		lvl<<LVL;
		Lvl=lvl.str();
		DrawString(280,285,"Level:",colors[130]);
		DrawString(345,285,Lvl,colors[130]);
	}
	//score display for shashka 3
	void gameover1()
	{
		for(int a=0;a<70;a++)
		{
			for(int b=0;b<70;b++)
			{
				DrawSquare(a*10,b*10,50,colors[131]);
			}
		}
		ext=1;
		DrawString(70,350,"congratulations! You have completed all the levels",colors[130]);
		scr.str("");
		scr<<HSCR;
		SCr=scr.str();
		DrawString( 280, 315, "Score:", colors[130]);
		DrawString(345,315,SCr,colors[130]);
	}
void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)// what to do when left key is pressed... 
	{
		if(DR!=1)
		{
			DR=2;
		}
    }
	else if (key == GLUT_KEY_RIGHT  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
	{
		if(DR!=2)
		{	
			DR=1;
		}
    }
	else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ 
	{
		if(DR!=3)
		{
			DR=4;
		}
    }
    else if (key == GLUT_KEY_DOWN)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ 
	{
		if(DR!=4)
		{
			DR=3;
		}
    }
    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
     glutPostRedisplay();
}
/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    else if (int(key) == 13)
    {  
	}
    
    glutPostRedisplay();
}
//random function
int randm()
{
	int F;
	F=(rand()%64)*10;
	return F;
}
/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m)
{
// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 650, height = 700; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("PF's Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...
// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);
// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */
