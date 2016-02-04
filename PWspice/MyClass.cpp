/************************************************************
             Test class for SPICE Parser Template

Author:
   Chen, Jiajun
   Shi, Guoyong
 
Used for the course project of "Introduction to EDA", 2011

   School of Micro-electronics
   Shanghai Jiaotong University
************************************************************/


#include "MyClass.h"

MyClass::MyClass()
{
	cir = new circuit;
}

MyClass::~MyClass()
{
	delete cir;
}

void MyClass::ParseRes(char *str, char *node1, char *node2, double value)
{
	cir -> append_RES_DEVICE(  str , node1 , node2 , value /*, int type*/);
}

void MyClass::ParseCap(char *str, char *node1, char *node2, double value)
{
	cir -> append_CAP_DEVICE(  str , node1 , node2 , value, 0 /*, int type*/);
        
}

void MyClass::ParseCap(char *str, char *node1, char *node2, double value, double init)
{
	cir -> append_CAP_DEVICE(  str , node1 , node2 , value, init /*, int type*/);
}

void MyClass::ParseInd(char *str, char *node1, char *node2, double value)
{
	cir -> append_IND_DEVICE(  str , node1 , node2 , value, 0 /*, int type*/);        
}

void MyClass::ParseInd(char *str, char *node1, char *node2, double value, double init)
{
	cir -> append_IND_DEVICE(  str , node1 , node2 , value, init /*, int type*/);
}

void MyClass::ParseVsrc(char *str, char *node1, char *node2, double value)
{
        cir -> append_VSRC_DEVICE( str , node1 , node2 , value /*, int type*/);   
}

void MyClass::ParseIsrc(char *str, char *node1, char *node2, double value)
{
	cir -> append_ISRC_DEVICE( str , node1 , node2 , value /*, int type*/);
}

void MyClass::ParseVCCS(char *str, char *node1, char *node2, char* node3, char* node4, double value)
{
	cir -> append_CONT_VC_DEVICE( str , node1 , node2 , node3 , node4 , value , 0);
}
void MyClass::ParseCCCS(char *str, char *node1, char *node2, char* strVname, double value)
{
	cir -> append_CONT_CC_DEVICE( str , node1 , node2 , strVname , value , 0);
}
void MyClass::ParseCCVS(char *str, char *node1, char *node2, char *strVname, double value)
{
	cir -> append_CONT_CC_DEVICE( str , node1 , node2 , strVname , value , 1);
}
void MyClass::ParseVCVS(char *str, char *node1, char *node2, char* node3, char* node4, double value)
{
	cir -> append_CONT_VC_DEVICE( str , node1 , node2 , node3 , node4 , value , 1);
}
void MyClass::ParseOpamp(char *str, char *node1, char *node2, char* node3)
{
	return;
}
void MyClass::ParseSwitch(char *str, char *node1, char *node2)
{
	return;
}
void MyClass::ParseDiode(char *str, char *node1, char *node2, double value)
{
	cir -> append_DIODE_DEVICE(str , node1 , node2 , value);
}
void MyClass::ParseMos(char *str, char *node1, char *node2, char* node3, char* type, double value1, double value2)
{
	cir -> append_MOS_DEVICE(  str , node1 , node2 , node3 , type , value1 , value2 );
}






