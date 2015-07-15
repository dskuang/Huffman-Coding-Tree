/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/23/15
                                                       
                            Assignment Three

File Name:      HCTree.cpp
Description:    The program contains the build, encode, and decode methods
		in implementing a huffman coding tree. 
****************************************************************************/
#include <queue>
#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include "HCTree.hpp"

using namespace std;

/***************************************************************************
% Routine Name : HCTree::build(const vector<int>& freqs)
% File :         HCTree.cpp
% 
% Description :  This function builds an HCTree from a frequency vector.
		 It pushes all of the leaves into a priority queue as
		 nodes and merges the children nodes
		 from the priority queue into parent nodes.
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% freqs      	a vector of int types
% return	none        
***************************************************************************/
void HCTree::build(const vector<int>& freqs){

	//pushes ascii leaf to priority queue in a loop
	for(int i = 0; i < freqs.size(); i++){
		if(freqs[i]){	
			leaves[i] = new HCNode (freqs[i],(char)i);
			pq.push(leaves[i]);
		}
	}
	
	//checks if queue is empty after loop
	if (pq.empty()){
		root = nullptr;
		return;
	}
	
	//combines children nodes to create a parent
	while(pq.size() > 1){
		HCNode* ch0 = pq.top();
		pq.pop();
		HCNode* ch1 = pq.top();
		pq.pop();
		HCNode* par = new HCNode((ch1->count+ch0->count),
					   ch0->symbol,ch0,ch1);

		ch0->p = par;
		ch1->p = par;
		pq.push(par);
	}	
	root = pq.top();    
}


/***************************************************************************
% Routine Name : HCTree::encode(byte symbol, BitOutputStream& out) const
% File :         HCTree.cpp
% 
% Description :  This function writes to a BitOutputStream the sequence
		 of bits coding the symbol
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% symbol	  a byte type
% out		  a BitoutputStream type
% return	  none         
***************************************************************************/
void HCTree::encode(byte symbol, BitOutputStream& out) const{
	HCNode* temp_node;
	stack<int>coder;

	if((leaves[symbol]->symbol) == symbol){     
		temp_node = leaves[symbol];

		//loops from children node to encode 1 and 0
		while(temp_node->p){		
			if (temp_node->symbol == (temp_node->p->c1->symbol))
				coder.push(1);
			
			else 
				coder.push(0);
			
			temp_node = temp_node->p;
		}

	        //writes to bitoutputstream from stack
		while (!coder.empty()){
			out.writeBit(coder.top());
			coder.pop();
		}
	} 

}

/***************************************************************************
% Routine Name : HCTree::decode(BitInputStream& in) const
% File :         HCTree.cpp
% 
% Description :  This function returns a symbol coded in the sequence of
		 bits from the bitinputstream
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% in		  a BitInputStream type
% return	  an integer type       
***************************************************************************/
int HCTree::decode(BitInputStream& in) const{
	int symbol = 0;
	int next = 0;
	HCNode* temp_node = root;
	
	//reads in each bit from bitinputstream starting from root
	while ((temp_node->c0)&&(temp_node->c1)){
		next = in.readBit();

		if (next == 1)
			temp_node = temp_node->c1;
		else 
			temp_node = temp_node->c0;
				
	}
	//returns symbol after loop cast into an int
	return (int)(temp_node->symbol);
	
}

/***************************************************************************
% Routine Name : HCTree::~HCTree() 
% File :         HCTree.cpp
% 
% Description :  This function is called when the program terminates to
		 deallocate memory.
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% return	  none    
***************************************************************************/
HCTree::~HCTree() {
	deleteAll(root);
  	root = nullptr;
}


/***************************************************************************
% Routine Name : HCTree::deleteAll(HCNode* x)
% File :         HCTree.cpp
% 
% Description :  This function is called by the destructor. It takes in 
		 the root node and deletes all recursively
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% x		  a pointer to a HCNode type
% return	  none    
***************************************************************************/
void HCTree::deleteAll(HCNode* x) {
  	if(x == nullptr) 
		return;
	
   		deleteAll(x->c0);
	
    		deleteAll(x->c1);
    	delete x;
  	x = nullptr;
}



