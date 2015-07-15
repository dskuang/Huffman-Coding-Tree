/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/23/15
                                                       
                            Assignment Three

File Name:      BitOutputStream.cpp
Description:    The program has the methods writeBit and flush to write
		 bits to an ostream
****************************************************************************/

#include <iostream>
#include "BitOutputStream.hpp"

/***************************************************************************
% Routine Name : void BitOutputStream::writeBit(int bit)
% File :         BitOutputStream.cpp
% 
% Description :  This function shifts the least significant bit by the 
		 the current index and masks them together
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% bit		  an int type
%returns		  nothing         
***************************************************************************/
void BitOutputStream::writeBit(int bit){
	//checks if buffer is full
	if (bufi > 7)
		flush();

	bit = bit&1;
	bit = bit << (7-bufi);
	nbits = nbits | bit;  
	bufi++;
}


/***************************************************************************
% Routine Name : void flush()
% File :         BitOutputStream.cpp
% 
% Description :  This function outputs buffer then resets it to 0
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------

%returns		  nothing         
***************************************************************************/
void BitOutputStream::flush(){

	if(bufi){
		out.put(nbits);
		out.flush();
		nbits = bufi = 0;
	}
}


