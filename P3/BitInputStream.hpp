/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/23/15
                                                       
                            Assignment Three

File Name:      BitInputStream.hpp
Description:    The program has the underlying methods to read bits to
		an istream
****************************************************************************/

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP
#include <iostream>


using namespace std;

class BitInputStream {
	private:
		
		char buf;     
		int nbits; 
		istream& in;      

	public:

		BitInputStream(istream& is) : in(is), buf(0), nbits(8) { }

		int readBit();
		void fill();


};

#endif 
