/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/23/15
                                                       
                            Assignment Three

File Name:      BitInputStream.cpp
Description:    The program has the methods readBit and fill to write
		bits to an istream
****************************************************************************/

#include "BitInputStream.hpp"
#include <iostream>


/***************************************************************************
% Routine Name : void BitInputStream::fill()
% File :         BitInputStream.cpp
% 
% Description :  This functions fills the buffer from file
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
%returns	     none   
***************************************************************************/
void BitInputStream::fill(){
	buf = in.get();
	nbits = 0;
}


/***************************************************************************
% Routine Name : void BitInputStream::readBit()
% File :         BitInputStream.cpp
% 
% Description :  This function checks if the buffer is empty and reads the
		 least significant bit
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
%returns	     none   
***************************************************************************/
int BitInputStream::readBit(){
	int bit = 0;

	if(nbits == 8)
		fill();

	if(in.eof())
		return -1;

	bit = (buf >> (7-nbits)) & 1;
	nbits++;
	return bit;

}




