/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/23/15
                                                       
                            Assignment Three

File Name:      BitOutputStream.hpp
Description:    The program has the underlying methods to write bits to
		an ostream
****************************************************************************/

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP
#include <iostream>

using namespace std;


class BitOutputStream {

	private:
		ostream& out; 
		char nbits;     
		int bufi;    

	public:
		BitOutputStream(ostream& o) : out(o), nbits(0), bufi(0) { }


		void writeBit(int bit);

		void flush();

};

#endif 

