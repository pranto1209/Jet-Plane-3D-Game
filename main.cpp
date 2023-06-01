#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <cmath>
#include <bits/stdc++.h>
#include "BmpLoader.h"
#include "curve_object.h"

using namespace std;


int state = 0;

const int w_width = 500;
const int w_height = 400;
const float rat = 1.0 * w_width / w_height;

float length = 1800;
float width = 1;
float height = 600;

bool l_on1 = true;
bool l_on2 = true;
bool l_on3 = true;
bool ambflag=true;
bool difflag=true;
bool specflag=true;


GLfloat eyeX = 0;
GLfloat eyeY = 400;
GLfloat eyeZ = length/3+200;

GLfloat lookX = 0;
GLfloat lookY = eyeY - 13;
GLfloat lookZ = eyeZ-35;

GLfloat eyex = eyeX;
GLfloat eyey = eyeY;
GLfloat eyez = eyeZ;

GLfloat lookx = lookX;
GLfloat looky = lookY;
GLfloat lookz = lookZ;


float light_height = 0;
float light_width =400;
float light_length = 600;

float light1_height = 35;
float light1_width = 70;
float light1_length = 0;

float spt_cutoff = 30;

int pt_rad = 9;

bool l_on = true;
bool s_on = false;

float rot = 0;

unsigned int ID;

float ptx=0,pty=eyeY-43,ptz=eyeZ-100;

float wx=0,wy=0,wz=0;


float ox[] = {-120,35,180,-120,35,180,-120,35,180};
float oy[] = {405,405,405,405,405,405,405,405,405};
float oz[] = {0,-50,-80,-200,-250,-300,-400,-460,-500};

float uox[] = {-240,-165,-85,-5,80,160,240,-200,-100-50,200,100,50};
float uoy[] = {pty+100,pty+100,pty+100,pty+100,pty+100,pty+100,pty+100,pty+100,pty+100,pty+100,pty+100,pty+100,pty+100};
float uoz[] = {ptz,ptz,ptz,ptz,ptz,ptz,ptz,ptz,ptz,ptz,ptz,ptz,ptz};

float lox[] = {-155,-75,75,145,190};
float loy[] = {pty+100,pty+100,pty+100,pty+100,pty+100};
float loz[] = {ptz,ptz,ptz,ptz,ptz};

float bx=0,by=0,bz=0;

float sx=0,sy=0,sz=0;

float rotX=0,rotY=0,rotZ=0;

float speed = 1;

float mov = 10;

bool k = true,k0=true, k1=true, k2=true, k3=true, k4=true, k5 = true;

bool shoot = false, shoot_on = false, X5=false, X2 = false;

float range = 900;

int c = 200;

float score = 0,t_score;

bool em = true;


static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {3,1,5,7},  //front
    {6,4,0,2},  //back
    {2,3,7,6},  //top
    {1,0,4,5},  //bottom
    {7,5,4,6},  //right
    {2,0,1,3}   //left
};


void cube(float R=0.5, float G=0.5, float B=0.5, bool em=false, bool l = false)
{

    set_material(R,G,B,em,l);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        glTexCoord2f(0,1);
        glVertex3fv(&v_cube[c_ind[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[c_ind[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_cube[c_ind[i][2]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_cube[c_ind[i][3]][0]);
    }
    glEnd();
}

//void light()
//{
//    //light
//    GLfloat l_no[] = {0, 0, 0, 1.0};
//    GLfloat l_amb[] = {0.2, 0.2, 0.2, 1.0};
//    GLfloat l_dif[] = {1,1,1,1};
//    GLfloat l_spec[] = {1,1,1,1};
//    GLfloat l_pos[] = {light_width,light_height,light_length,1.0};
//
//    glEnable(GL_LIGHT0);
//
//    if(l_on) glLightfv(GL_LIGHT0, GL_AMBIENT, l_amb);
//    else glLightfv(GL_LIGHT0, GL_AMBIENT, l_no);
//    if(l_on) glLightfv(GL_LIGHT0, GL_DIFFUSE, l_dif);
//    else glLightfv(GL_LIGHT0, GL_DIFFUSE, l_no);
//    if(l_on) glLightfv(GL_LIGHT0, GL_SPECULAR, l_spec);
//    else glLightfv(GL_LIGHT0, GL_SPECULAR, l_no);
//
//    glLightfv(GL_LIGHT0, GL_POSITION, l_pos);
//
//}
//
//void light1()
//{
//    //light
//    GLfloat l_no[] = {0, 0, 0, 1.0};
//    GLfloat l_amb[] = {0.2, 0.2, 0.2, 1.0};
//    GLfloat l_dif[] = {1,1,1,1};
//    GLfloat l_spec[] = {1,1,1,1};
//    GLfloat l_pos[] = {ptx,pty+5,ptz-30,1.0};
//
//    glEnable(GL_LIGHT1);
//
//    if(s_on) glLightfv(GL_LIGHT1, GL_AMBIENT, l_amb);
//    else glLightfv(GL_LIGHT1, GL_AMBIENT, l_no);
//    if(s_on) glLightfv(GL_LIGHT1, GL_DIFFUSE, l_dif);
//    else glLightfv(GL_LIGHT1, GL_DIFFUSE, l_no);
//    if(s_on) glLightfv(GL_LIGHT1, GL_SPECULAR, l_spec);
//    else glLightfv(GL_LIGHT1, GL_SPECULAR, l_no);
//
//    glLightfv(GL_LIGHT1, GL_POSITION, l_pos);
//
//    GLfloat spt_dir[] = {0,0,-1,1};
//    GLfloat spt_ct[] = {spt_cutoff};
//    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spt_dir);
//    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spt_ct);
//
//}

void light()
{

    //light
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat l_dif[] = {1,1,1,1};
    GLfloat l_spec[] = {1,1,1,1};
    GLfloat l_pos1[] = {light_width,light_height,light_length,1.0};
    GLfloat l_pos2[] = {ptx,pty+5,ptz-30,1.0};
    //GLfloat l_pos1[] = {0,50,50,1.0};
    //GLfloat l_pos2[] = {0,50,-850,1.0};
    //GLfloat l_pos3[] = {l3posx,l3posy,l3posz,1.0};


    //if(l_on1)
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);
    if(l_on1)
    {
        if(ambflag)
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        }
        if(difflag)
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        }
        if(specflag)
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT0,GL_POSITION,l_pos1);



    if(l_on2)
    {

        if(ambflag)
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        }
        if(difflag)
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        }
        if(specflag)
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT1,GL_POSITION,l_pos2);
}

void plane()
{
    glPushMatrix();

    glRotatef(90,0,1,0);

    //main

    glPushMatrix();
    set_material(0,.5,.25);
    glScaled(22,4,4);
    glutSolidSphere(1,30,30);
    glPopMatrix();

    glPushMatrix();
    set_material(0,.15,0.25);
    glTranslatef(12,4,0);
    glScaled(10,4,5);
    glutSolidSphere(0.45,30,30);
    glPopMatrix();

    //front fan

    //right

    glPushMatrix();
    glTranslatef(2,0,2.7);
    glRotated(-50,0,1,0);
    glScalef(7,1,15);
    glRotated(25,0,1,0);
    cube(0,.15,0.25);
    glPopMatrix();


    glPushMatrix();
    set_material(0,.25,0.15);
    glTranslatef(1,-1,10);
    glRotated(90,0,1,0);
    glScaled(1,1,7);
    glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    glPushMatrix();
    set_material(0,.25,0.15);
    glTranslatef(3,-1,7);
    glRotated(90,0,1,0);
    glScaled(1,1,7);
    glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    //left
    glPushMatrix();
    glTranslatef(-6,0,-13.5);
    glRotated(50,0,1,0);
    glScalef(7,1,15);
    glRotated(-25,0,1,0);
    cube(0,.15,0.25);
    glPopMatrix();

    glPushMatrix();
    set_material(0,.25,0.15);
    glTranslatef(2,-1,-10);
    glRotated(90,0,1,0);
    glScaled(1,1,7);
    glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    glPushMatrix();
    set_material(0,.25,0.15);
    glTranslatef(4.5,-1,-7);
    glRotated(90,0,1,0);
    glScaled(1,1,7);
    glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    //back fan

    //right
    glPushMatrix();
    glTranslatef(-15,0,2);
    glRotatef(-30,0,1,0);
    glScalef(4,1,7);
    glRotatef(10,0,1,0);
    cube(0,.15,0.25);
    glPopMatrix();

    //left
    glPushMatrix();
    glTranslatef(-19,0,-8.5
                );
    glRotatef(30,0,1,0);
    glScalef(4,1,7);
    glRotatef(-10,0,1,0);
    cube(0,.15,0.25);
    glPopMatrix();

    //top fan
    glPushMatrix();
    glTranslated(-16,2.5,0);
    glRotated(45,0,0,1);
    glScaled(5,10,1);
    glRotated(-20,0,0,1);
    cube(0,.15,0.25);
    glPopMatrix();

    glPopMatrix();

}

void walll()
{

    //floor
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);

    glPushMatrix();
    glScalef(height,width,length);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.9,0.9,0.9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(0,height,0);
    glScalef(height,width,length);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.9,0.9,0.9);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();
    glTranslatef(height/2,-width,0);
    glScalef(width,height,length);
    glTranslatef(0,0,-0.5);
    cube(0.741, 0.718, 0.420);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-height/2-1,-width,0);
    glScalef(width,height,length);
    glTranslatef(0,0,-0.5);
    cube(0.741, 0.718, 0.420);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




}
void frontt() //backgroud ekdom pichoner ta
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glPushMatrix();
    glTranslatef(0,-width,-length/1.5-1);
    glScalef(length,height,width);
    glTranslatef(-0.5,0,0);
    cube(0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void face()
{
    float v_height = 10;
    float t_height = 1.5;
    float t_width = 1.5;

    glPushMatrix();
    glScalef(3,3,3);
    glTranslatef(30,63,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);

    glPushMatrix();
    glScalef(v_height,v_height,v_height);
    cube(0.741, 0.718, 0.420);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    for(float i = 0; i<10; i+=2.5)
    {
        glPushMatrix();
        glTranslatef(i,-t_height,v_height-0.5);
        glScalef(t_width,t_height,0.5);
        cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,-t_height,i);
        glScalef(0.5,t_height,t_height);
        cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(v_height-0.5,-t_height,i);
        glScalef(0.5,t_height,t_height);
        cube(1,1,1);
        glPopMatrix();
    }

    glPushMatrix();
    glRotatef(20,1,0,0);
    glPushMatrix();
    glTranslatef(0,-v_height/2+1,0);
    glScalef(v_height,1.5,v_height);
    cube(0,0,0);
    glPopMatrix();

    for(int i=0; i<10; i+=2.5)
    {
        glPushMatrix();
        glTranslatef(i,-v_height/2+1+t_height,v_height-0.5);
        glScalef(t_width,t_height,0.5);
        cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,-v_height/2+1+t_height,i);
        glScalef(0.5,t_height,t_height);
        cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(v_height-0.5,-v_height/2+1+t_height,i);
        glScalef(0.5,t_height,t_height);
        cube(1,1,1);
        glPopMatrix();
    }

    glPopMatrix();

    glPopMatrix();
}


void body()
{
    float b_length = 60;
    float b_height = 25;
    float b_width = 1;

    float i = 0;

    glPushMatrix();
    glTranslatef(0,80,0);
    glScalef(3,3,3);
    glPushMatrix();
    glScalef(b_length,b_height,b_width);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    cube(1,1,1);

    glPopMatrix();

    for(i = 0; i<14; i+=2)
    {
        glPushMatrix();
        glTranslatef(2+i,2-i,0);
        glScalef(b_length-i-i,2,b_width);
        cube(1,1,1);
        glPopMatrix();
    }
    for(i; i<18; i+=2)
    {
        glPushMatrix();
        glTranslatef(2+i,2-i,0);
        glScalef(b_length-i-i,2,b_width);
        cube(1,1,1);
        glPopMatrix();
    }

    float k = 0;

    i=k*2;

    for(i; i<38; i+=2)
    {
        glPushMatrix();
        glTranslatef(2+i,2-i,0);
        glScalef(b_length-i-i,2,b_width);
        cube(1,1,1);
        glPopMatrix();
    }

    k = 0;
    for(k; k<10; k+=2)
    {

        glPushMatrix();
        glTranslatef(b_length/2+k,b_height,0);
        glScalef(2,b_length/2-k,b_width);
        cube(1,1,1);
        glPopMatrix();
    }
    float j = 0;
    for(j; j<4; j++)
    {
        glPushMatrix();
        glTranslatef(b_length/2+k+j*2,b_height,0);
        glScalef(2,b_length/2-k+2,b_width);
        cube(1,1,1);
        glPopMatrix();
    }
    float l = 1;
    for(l; l<4; l++)
    {
        glPushMatrix();
        glTranslatef(b_length/2+k+l*2,b_height,0);
        glScalef(2,b_length/2-k+2+l*2,b_width);
        cube(1,1,1);
        glPopMatrix();
    }
    float m = 0;
    for(m; m<6; m++)
    {
        glPushMatrix();
        glTranslatef(b_length/2+k+l*2+m*2,b_height,0);
        glScalef(2,b_length/2-k+2+l*2-m*2,b_width);
        cube(1,1,1);
        glPopMatrix();
    }

    k = 0;
    glPushMatrix();
    glTranslatef(-b_length/2,0,0);
    for(k; k<10; k+=2)
    {

        glPushMatrix();
        glTranslatef(b_length/2+k,b_height,0);
        glScalef(2,b_length/2-k,b_width);
        cube(1,1,1);
        glPopMatrix();
    }
    j = 0;
    for(j; j<4; j++)
    {
        glPushMatrix();
        glTranslatef(b_length/2+k+j*2,b_height,0);
        glScalef(2,b_length/2-k+2,b_width);
        cube(1,1,1);
        glPopMatrix();
    }
    l = 1;
    for(l; l<4; l++)
    {
        glPushMatrix();
        glTranslatef(b_length/2+k+l*2,b_height,0);
        glScalef(2,b_length/2-k+2+l*2,b_width);
        cube(1,1,1);
        glPopMatrix();
    }
    m = 0;
    for(m; m<6; m++)
    {
        glPushMatrix();
        glTranslatef(b_length/2+k+l*2+m*2,b_height,0);
        glScalef(2,b_length/2-k+2+l*2-m*2,b_width);
        cube(1,1,1);
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();
}

void boss()
{
    glPushMatrix();
    glTranslatef(-10,0,0);
    face();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-80,0,0);
    face();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(60,0,0);
    face();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glPushMatrix();
    body();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void planet()
{
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    set_material(1,1,0);
    glTranslatef(0,30,0);

    glutSolidSphere(pt_rad, 30.0, 30.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    set_material(1,1,0);
    glTranslatef(0,30,-200);

    glutSolidSphere(pt_rad, 30.0, 30.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void pumpkin()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glPushMatrix();

    set_material(1,1,1);
    //glTranslatef(0,400,600);
    glScalef(2,2,2);
    show_curve();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void collision(float cx, float cy, float cz)
{
    if((ptx>cx-pt_rad && ptx<cx+pt_rad+20) && (ptz-15 == cz || ptz-15 == cz-200) && (pty>cy-pt_rad && pty<cy+pt_rad+20))
    {
        state = 2;
        t_score = score;
        score = 0;
    }
}

void u_collision(float bx, float by)
{
    if((ptx>bx-10 && ptx<bx+9+10) && (pty==by))
    {
        state = 2;
        t_score = score;
        score = 0;
    }
}

void l_collision(float bx, float by)
{
    if((ptx>bx-10 && ptx<bx+10) && (pty==by))
    {
        X2 = true;
        c = 200;
        score*=2;

    }
}


void s_collision(float cx, float cy, float cz, float ax, float ay, float az)
{
    if((ax>cx-pt_rad-30 && ax<cx+pt_rad+30) && (az-5 == cz || az-5 == cz-200) && (ay>cy-pt_rad-30 && ay<cy+pt_rad+30))
    {
        k=false;
        shoot_on=false;
        X5 = true;
        c = 200;
        score*=5;
    }
}

void shot()
{
    if(shoot)
    {
        sx = ptx-2.5;
        sy = pty;
        sz = ptz-35;
        shoot = false;
        shoot_on = true;
    }
    if(shoot_on)
    {
        glPushMatrix();
        glTranslatef(sx,sy,sz);
        glScalef(5,5,20);
        cube(.5,2,1);
        glPopMatrix();
    }
    sz-=speed*2;
}

void timer2(float a, float b, float c)
{

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.0);

    glPushMatrix();
    set_material(0,1,1);
    glTranslatef(a,b,c);
    glScalef(0.5,0.5,0.5);
    string s = "X5 ";


    for(int i=0; i<s.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);

    glPopMatrix();

}

void timer3(float a, float b, float c)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.0);

    glPushMatrix();
    set_material(0,1,1);
    glTranslatef(a,b,c);
    glScalef(0.5,0.5,0.5);
    string s = "X2 ";


    for(int i=0; i<s.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);

    glPopMatrix();
}


void draw()
{

    if(ptx>height/2-25)
    {
        ptx = height/2-25;
        eyeX = height/2-25;
        lookX = height/2-25;
    }
    if(ptx<-height/2+25)
    {
        ptx = -height/2+25;
        eyeX = -height/2+25;
        lookX = -height/2+25;
    }
    if(pty>height-50)
    {
        pty = height-50-43;
        eyeY = height-50;
        lookY = height-50-13;
    }
    if(pty<10)
    {
        pty = 10;
        eyeY = 10+43;
        lookY = 10+30;
    }

    glPushMatrix();
    glTranslatef(ptx,pty,ptz);
    glRotated(rotX,1,0,0);
    glRotated(rotY,0,1,0);
    glRotated(rotZ,0,0,1);
    plane();

    glPopMatrix();

    glPushMatrix();
    glScalef(2,2,2);
    glTranslatef(-80,30,0);
    //boss();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(wx,wy,wz);
    walll();
    glPopMatrix();

    for(int i=0; i<12; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,5);
        glPushMatrix();
        glTranslatef(uox[i],uoy[i],uoz[i]);
        u_collision(uox[i],uoy[i]);
        glScalef(9,9,9);
        cube(1,1,1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

    for(int i=0; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(lox[i],loy[i],loz[i]);
        l_collision(lox[i],loy[i]);
        pumpkin();
        glPopMatrix();
    }


    if(k)
    {
        for(int i=0; i<9; i++)
        {
            glPushMatrix();
            glTranslatef(ox[i],oy[i],oz[i]);
            collision(ox[i],oy[i],oz[i]);
            s_collision(ox[i],oy[i],oz[i],sx,sy,sz);
            planet();
            glPopMatrix();
        }
    }
    if(X5)
    {
        timer2(sx,sy,sz);
        c--;
        if(c==185)
        {
            X5 = false;
        }

    }
    if(X2)
    {
        timer3(ptx,pty,ptz-100);
        c--;
        if(c==185)
        {
            X2 = false;
        }

    }

    if( k == false)
    {

        k = true;
        for(int i = 0; i<9; i++)
        {
            oz[i] = 0;
        }
    }

    if(k0)
    {
        oy[0]=oy[0]-speed;
        if(oy[0]==100)
        {
            k0 = false;
        }
    }

    if(k1)
    {
        oy[1]=oy[1]-speed;
        if(oy[0]==200)
        {
            k1 = false;
        }
    }
    if(k2)
    {
        oy[2]=oy[2]-speed;
        if(oy[0]==150)
        {
            k2 = false;
        }
    }
    if(k3)
    {
        oy[3]=oy[3]-speed;
        if(oy[3]==300)
        {
            k3 = false;
        }
    }
    if(k4)
    {
        oy[4]=oy[4]-speed;
        if(oy[4]==350)
        {
            k4 = false;
        }
    }
    if(k5)
    {
        oy[5]=oy[5]-speed;
        if(oy[5]==400)
        {
            k5 = false;
        }
    }


    shot();

    glPushMatrix();
    glTranslatef(0,0,-50);
    //face();
    glPopMatrix();
}

void timer()
{

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.0);

    glPushMatrix();
    set_material(0,1,1);
    glTranslatef(-200,500,100);
    glScalef(0.25,0.25,0.25);
    score +=1;
    ostringstream ss_score;
    string str_score;
    string s = "total score : ";

    ss_score << score;
    str_score = ss_score.str();

    s += str_score;

    glPopMatrix();
}
void timer1()
{

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);

    glLineWidth(4.0);

    glPushMatrix();
    set_material(1,1,1);
    glTranslatef(-200,500,100);
    glScalef(0.5,0.5,0.5);
    string s = "Game Over !!";



    for(int i=0; i<s.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);

    glPopMatrix();

    glPushMatrix();
    set_material(1,1,1);
    glTranslatef(-700,50,100);
    glScalef(0.5,0.5,0.5);
    s = "Press Space to start again!";



    for(int i=0; i<s.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);

    glPopMatrix();

    glPushMatrix();
    set_material(1,1,1);
    glTranslatef(-500,-100,100);
    glScalef(0.5,0.5,0.5);
    s = "Press M to go to Main!";



    for(int i=0; i<s.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);

    glPopMatrix();

    glPushMatrix();
    set_material(1,1,1);
    glTranslatef(-500,350,100);
    glScalef(0.5,0.5,0.5);
    ostringstream ss1_score;
    string str1_score;
    s = "total score : ";

    ss1_score << t_score;
    str1_score = ss1_score.str();

    s += str1_score;



    for(int i=0; i<s.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);

    glPopMatrix();

}



void first()
{

    glPushMatrix();
    glTranslatef(-600,-500,600);
    glRotatef(45,0,1,0);
    glScalef(4,4,4);
    //face();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-100,-500,100);
    glRotatef(-40,0,1,0);
    glScalef(4,4,4);
    //face();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-160,-400,-400);
    glScalef(20,20,20);
    plane();
    glPopMatrix();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.0);

    glPushMatrix();
    set_material(0,1,1);
    glTranslatef(-500,600,100);
    glScalef(0.7,0.7,0.7);
    string s = "JET PLANE GAME";


    for(int i=0; i<s.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);

    glPopMatrix();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.0);

    glPushMatrix();
    set_material(0,1,1);
    glTranslatef(-1000,-1200,-100);
    glScalef(1,1.5,1);
    s = "Press Space to Start";


    for(int i=0; i<s.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);

    glPopMatrix();


}


void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}



void animate()
{

    wz = wz + speed;
    oz[0] = oz[0] + speed;    //balls from boss
    oz[1] = oz[1] + speed;
    oz[2] = oz[2] + speed;
    oz[3] = oz[3] + speed;
    oz[4] = oz[4] + speed;
    oz[5] = oz[5] + speed;
    oz[6] = oz[6] + speed;
    oz[7] = oz[7] + speed;
    oz[8] = oz[8] + speed;

    uoy[0] = uoy[0] - speed;
    uoy[1] = uoy[1] - speed;
    uoy[2] = uoy[2] - speed;
    uoy[3] = uoy[3] - speed;
    uoy[4] = uoy[4] - speed;
    uoy[5] = uoy[5] - speed;
    uoy[6] = uoy[6] - speed;
    uoy[7] = uoy[7] - speed;
    uoy[8] = uoy[8] - speed;
    uoy[9] = uoy[9] - speed;
    uoy[10] = uoy[10] - speed;
    uoy[11] = uoy[11] - speed;
    uoy[12] = uoy[12] - speed;

    loy[0] = loy[0] - speed;
    loy[1] = loy[1] - speed;
    loy[2] = loy[2] - speed;
    loy[3] = loy[3] - speed;
    loy[4] = loy[4] - speed;

    if(loy[0]<-10)
    {
        loy[0]=pty+500;
    }

    if(loy[1]<-10)
    {
        loy[1]=pty+850;
    }

    if(loy[2]<-10)
    {
        loy[2]=pty+1200;
    }

    if(loy[3]<-10)
    {
        loy[3]=pty+500;
    }

    if(loy[4]<-10)
    {
        loy[4]=pty+850;
    }


    if(uoy[0]<-10)
    {
        uoy[0]=pty+100;
    }

    if(uoy[1]<-10)
    {
        uoy[1]=pty+150;
    }

    if(uoy[2]<-10)
    {
        uoy[2]=pty+300;
    }

    if(uoy[3]<-10)
    {
        uoy[3]=pty+250;
    }

    if(uoy[4]<-10)
    {
        uoy[4]=pty+280;
    }

    if(uoy[5]<-10)
    {
        uoy[5]=pty+200;
    }

    if(uoy[6]<-10)
    {
        uoy[6]=pty+170;
    }
    if(uoy[7]<-10)
    {
        uoy[7]=pty+220;
    }
    if(uoy[8]<-10)
    {
        uoy[8]=pty+270;
    }
    if(uoy[9]<-10)
    {
        uoy[9]=pty+230;
    }
    if(uoy[10]<-10)
    {
        uoy[10]=pty+130;
    }
    if(uoy[11]<-10)
    {
        uoy[11]=pty+320;
    }
    if(uoy[12]<-10)
    {
        uoy[12]=pty+160;
    }

    if(wz>550)
    {
        wz = 0;
    }


    if(oz[0]>range)
    {
        oz[0] = 0;
        oy[0] = 405;
        k0=true;
    }

    if(oz[1]>range)
    {
        oz[1] = 0;
        oy[1] = 405;
        k1=true;
    }
    if(oz[2]>range)
    {
        oz[2] = 0;
        oy[2] = 405;
        k2=true;
    }
    if(oz[3]>range)
    {
        oz[3] = 0;
        oy[3] = 405;
        k3=true;
    }

    if(oz[4]>range)
    {
        oz[4] = 0;
        oy[4] = 405;
        k4=true;
    }
    if(oz[5]>range)
    {
        oz[5] = 0;
        oy[5] = 405;
        k5=true;
    }

    glutPostRedisplay();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;
    case 'u':
        em = em - 1;
        break;
    case ' ':
        state = 1;
        break;
    case 'm':
        state = 0;
        break;
    case 'k':
        k0 = 1 - k0;
    case 'l':
        shoot = 1 - shoot;
        break;
    case ',':
        rot+=0.01;
        break;
    case '.':
        rot-=0.01;
        break;
    case 'a':
        eyeX--;
        lookX--;
        break;
    case 'd':
        eyeX++;
        lookX++;
        break;
    case 'w':
        eyeY++;
        lookY++;
        break;
    case 's':
        eyeY--;
        lookY--;
        break;
    case '+':
        eyeZ-=mov;
        lookZ-=mov;
        break;
    case '-':
        eyeZ+=mov;
        lookZ+=mov;
        break;
        case 'f':
    case 'F':
        l_on1=1-l_on1;
        break;
    case 'g':
    case 'G':
        l_on2=1-l_on2;
        break;

    case 'r':
    case 'R':
        ambflag=1-ambflag;
        break;

    case 't':
    case 'T':
        difflag=1-difflag;
        break;
    case 'y':
    case 'Y':
        specflag=1-specflag;
        break;
//    case 't':
//        l_on = 1 - l_on;
//        break;
//    case 'y':
//        s_on = 1 - s_on;
//        break;
    case '1':
        ptz = ptz + mov;

        break;

    case '0':
        ptz = ptz - mov;
        break;
    }

    glutPostRedisplay();
}

void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        pty = pty + mov;

        break;
    case GLUT_KEY_DOWN:
        pty = pty - mov;

        break;
    case GLUT_KEY_RIGHT:
        ptx = ptx + mov;

        break;

    case GLUT_KEY_LEFT:
        ptx = ptx - mov;
        break;
    }
    glutPostRedisplay();
}


static void resize(int width, int height)
{
    glViewport(width/2-height*rat/2,0,height*rat,height);

}

void init(float a,float b, float c)
{
    // Set "clearing" or background color
    glClearColor(a,b,c,1); // Black and opaque
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 3.0, 2000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);

    glRotatef(rot, 0,1,0);
    light();
    //light1();

    switch ( state )
    {
    case 0:

        init(1,1,1);
        first();   //first page ta jekhane duita face ekta plane r ekta string
        break;

    case 1: //game er page e point dekha

        draw();
        frontt();
        timer();
        init(0,0,0);
        break;

    case 2: // game over hoile je page ashe
        glPushMatrix();
        gluLookAt(eyex,eyey,eyez, lookx,looky,lookz, 0,1,0);
        init(0,0,0);
        glTranslatef(0,300,500);
        glScalef(1.1,1.1,1.1);
        timer1(); // point dekha r oi tin line
        glPopMatrix();
        break;
    }

    glutSwapBuffers();
}



int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(w_width,w_height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Game Window");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(animate);
    glutSpecialFunc(specialKeyListener);
    glutReshapeFunc(resize);


    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);

    LoadTexture("G:\\Graphics_Project\\MyGame\\image\\image_1.bmp");
    LoadTexture("G:\\Graphics_Project\\MyGame\\image\\image_2.bmp");
    LoadTexture("G:\\Graphics_Project\\MyGame\\image\\image_1.bmp");
    LoadTexture("G:\\Graphics_Project\\MyGame\\image\\image_3.bmp");
    LoadTexture("G:\\Graphics_Project\\MyGame\\image\\image_5a.bmp");
    LoadTexture("G:\\Graphics_Project\\MyGame\\image\\image_6.bmp");
    LoadTexture("G:\\Graphics_Project\\MyGame\\image\\image_7.bmp");
    LoadTexture("G:\\Graphics_Project\\MyGame\\image\\image_8.bmp");


    glutMainLoop();

}
