/************************************************************
             Test class for SPICE Parser Template

Author:
   Chen, Jiajun
   Shi, Guoyong
 
Used for the course project of "Introduction to EDA", 2011

   School of Micro-electronics
   Shanghai Jiaotong University
************************************************************/

#ifndef MYCLASS_H
#define MYCLASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./circuit/circuit.h"

class MyClass
{
	public:
		MyClass();
		~MyClass();

		void ParseRes(char *str, char *node1, char *node2, double value);
		void ParseCap(char *str, char *node1, char *node2, double value);
		void ParseCap(char *str, char *node1, char *node2, double value, double init);
		void ParseInd(char *str, char *node1, char *node2, double value);
		void ParseInd(char *str, char *node1, char *node2, double value, double init);
		void ParseVsrc(char *str, char *node1, char *node2, double value);
		void ParseIsrc(char *str, char *node1, char *node2, double value);
		
		void ParseVCCS(char *str, char *node1, char *node2, char* node3, char* node4, double value);
		void ParseCCCS(char *str, char *node1, char *node2, char* strVname, double value);
		void ParseCCVS(char *str, char *node1, char *node2, char *strVname, double value);
		void ParseVCVS(char *str, char *node1, char *node2, char* node3, char* node4, double value);
		void ParseOpamp(char *str, char *node1, char *node2, char* node3);
		void ParseSwitch(char *str, char *node1, char *node2);
		void ParseDiode(char *str, char *node1, char *node2, double value);
		void ParseMos(char *str, char *node1, char *node2, char* node3, char* type, double value1, double value2);

        circuit* Summarize()
        {
            cir -> organize_address();
            return cir;
        }

	private:                
		circuit *cir;
		
};

#endif
