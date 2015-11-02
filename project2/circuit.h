#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <assert.h>

using namespace std;

#include "node.h"

typedef map<string,Node*>::iterator mapIter; // 内部用map存的dictionary！mapIter作为Iterator迭代器，它是指针！
class Circuit
{
  private:
    map<string,Node*> nodeMap; // 主要的数据就在nodeMap里，访问的时候要用mapIter迭代
	// circuit里的主要元素就是Node！！！
    string name;
    
  public:
    Circuit() {};
    
    Circuit(const string &circuitName):name(circuitName) {}
    
    // destructor
    ~Circuit();
    
    // get number of nodes in the circuit
    unsigned getNumNodes() { return nodeMap.size(); }     // 电路里总node数
    
    // get and set the name of the circuit
    string getName() { return name; }
    int setName(const string &modelName) { name = modelName; return 0; }       // 设置电路的name
    
    // get primary inputs and outputs
	// 返回的是vector？？？
    vector<Node*> getPIs();
    vector<Node*> getPOs();
    
    // sets the node of <string> as primary input and output
    int setPI(const string &input);
    int setPO(const string &output);
    
    // set (assign) nodes in specific format as primary inputs and outputs from [startBit,endBit)
    // for a given string <string> and numBits, format is <string>[startBit] ... <string[endBit-1]
    int setPIs(const string &input, unsigned int startBit, unsigned int endBit);       // 设置主输入，cpp里定义
    int setPOs(const string &output, unsigned int startBit, unsigned int endBit);       // 设置主输出，cpp里定义
    
    // check to see if a node is there
    Node* findNode(const string &nodeName);
    
    // create an empty node - will return NULL if node already exists
    Node* createNode(const string &nodeName);
    
    // prints out the contents of the circuit
    int print();    // 输出整个电路，cpp里定义
    
    // writes circuit in BLIF format
    int writeBLIF(const string &filename);    // 写出blif电路表示文件，cpp里定义
    
    // erases the contents of the entire circuit
    int clear();
    
    // start library definitions
	/************* library.cpp *******************/
    int createONENode(Node* node);
    int createZERONode(Node* node);
    int createBUF1Node(Node* input, Node* output);
    int createOR2Node(Node* input1, Node* input2, Node* output);
    int createAND2Node(Node* input1, Node* input2, Node* output);
    int createXOR3Node(Node* input1, Node* input2, Node* input3, Node* output);
    int createMUX4Node(Node* select1, Node* select2,
                       Node* input1, Node* input2, Node* input3, Node* input4, Node* output);
    
    // start module definitions
	/************* modules.cpp *******************/
    int createADDModule(const string &input1, const string &input2, const string &cin, const string &output, const string &cout, unsigned int numBits);
    int createSUBModule(const string &input1, const string &input2, const string &output, unsigned int numBits);
    int createSHIFTModule(const string &input, const string &output, unsigned int numBits, unsigned int numShift);
    
    // start datapath definitions
	/************* datapaths.cpp *******************/
    int createABSMIN5X3YModule(const string &input1, const string &input2, const string &output);
};

#endif

