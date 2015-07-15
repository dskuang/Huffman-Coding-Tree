/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/23/15
                                                       
                            Assignment Three

File Name:      uncompress.cpp
Description:    The program creates the frequency vector by reading in the 
		file, constructs the huffman tree from the vector, outputs
		the header to a new file, and encodes the file to a new
		file
****************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include "HCNode.hpp"
#include "HCTree.hpp"


int main(int argc, char**argv){
	int size = 0;
	ifstream input;
	ofstream output;
	byte b;

	vector<int> freqs(256, 0);
	

	//checks for correct amount of arguments
	if (argc != 3){
		cerr << "Incorrect # of arguments" << endl;
		return -1;
	}
	
	//checks if inputfile is corrupt
	input.open(argv[1], ios::binary);		
	if(!input) {
    		cerr << "File cannot be opened" << endl;
   		return -1;
  	}

	//increments frequency vector 
	while(1){			
		b = input.get();
		if(input.eof())
			break;
		
		freqs[b]++;		
		size++;			
	}

	//checks to see if file is at the end 
	if(!input.eof()) {
    	        cerr << "There was a problem reading in file" << endl;
    		return -1;
        }

	HCTree tree;		
	tree.build(freqs);
	

	output.open(argv[2],ios::binary);
	BitOutputStream out(output);

	//outputs header to file
	for (size_t j = 0; j < freqs.size(); j++) {
		output.write(((char *) &freqs[j]), sizeof(int));
	}


	input.clear();
	input.seekg(0, ios::beg);

	//calls hctree encode method
	for (int k = 0; k < size; k++){
		b = input.get();
		tree.encode(b, out);
	} 

	//flushes stream to output file
	out.flush();
	
	output.close();
	input.close();


	return 0;
}

