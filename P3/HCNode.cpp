/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/23/15
                                                       
                            Assignment Three

File Name:      HCNode.cpp
Description:    The program contains the < operator overloading method
		for two HCNodes
****************************************************************************/
#include "HCNode.hpp"

bool HCNode::operator<(const HCNode& other) {
	if(count != other.count) 
		return count > other.count;
	
	return symbol < other.symbol;
}
