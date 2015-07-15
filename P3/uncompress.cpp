/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/23/15
                                                       
                            Assignment Three

File Name:      uncompress.cpp
Description:    The program creates the frequency vector by reading the
		header, reconstructs the huffman tree, and decodes the 
		file
****************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>  
#include "HCTree.hpp"


using namespace std;

int main(int argc, char**argv){
	ofstream output;
	ifstream input;
	
	int size = 0;
	int b = 0;
	int symbols = 0; 
	vector<int> freqs(256, 0);
	
	//checks if there are 3 arguments
	if (argc != 3) {
		cerr << "Incorrect # of arguments" << endl;
		return -1;
	}


	input.open(argv[1], ios::binary);
	
	//checks if there is a problem with the input file
	if(!input) {
    		cerr << "File cannot be opened" << endl;
   		return -1;
  	}
			
	//recreate frequency vector from header
	for (size_t j = 0; j < freqs.size(); j++){
		input.read(((char*)(&freqs[j])), sizeof(int));		
		size += freqs[j];		
	}
	
	HCTree tree;
	tree.build(freqs);
	
	output.open(argv[2], ios::binary);
	BitOutputStream out(output);	
	BitInputStream in(input);

	//seek to beginning of file past the header
	input.seekg(ios::beg + (256*sizeof(int)));

	//decode the file
	for (int x = 0; x < size; x++){ 
		b = tree.decode(in);
		output.write((char*)&b, 1);
	}

	
	output.close();
	input.close();

	return 0;
}

