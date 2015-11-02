#include "circuit.h"

/*
	Circuit Name: shifter contains 19 nodes.
	Primary Inputs: orig[0] orig[1] orig[2] orig[3] orig[4] orig[5] orig[6] orig[7] 
	Primary Outputs: out[0] out[1] out[2] out[3] out[4] out[5] out[6] out[7] out[8] out[9] 

	Nodes:

	Name: ZERO [TYPE = ZERO_NODE]

	Name: orig[0] [TYPE = PRIMARY_INPUT]

	Name: out[0] [TYPE = PRIMARY_OUTPUT]
	Fanin nodes: ZERO 
	1 1

	Name: out[1] [TYPE = PRIMARY_OUTPUT]
	Fanin nodes: ZERO 
	1 1
*/

// creates a constant '1' node
// 可用于参考！！！！！！
int Circuit::createONENode(Node* node)
{
  assert(node != NULL);
  
  node->clearTT();
  node->clearFanin();
  
  node->type = ONE_NODE;
  return 0;
}

// creates a constant '0' node
// 可用于参考！！！！！！
int Circuit::createZERONode(Node* node)
{
  assert(node != NULL);
  
  node->clearTT();
  node->clearFanin();
  
  node->type = ZERO_NODE;
  
  return 0;
}

// creates a 1-input BUFFER node
// 可用于参考！！！！！！
int Circuit::createBUF1Node(Node* input, Node* output)
{
  assert(input != NULL);
  assert(output != NULL);
  
  output->clearTT();
  output->clearFanin();
  
  output->addFanin(input);
  output->tt.setNumVars(1);
  
  output->tt.addEntry("1");
  
  return 0;
}

// creates a 2-input OR node
// 可用于参考！！！！！！创建gate，其实就是手动specify真值表！！！
/*******************************************/
// 仅修改***output node***所属的真值表！！！！！！！！
int Circuit::createOR2Node(Node* input1, Node* input2, Node* output)
{
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(output != NULL);
  
  output->clearTT();
  output->clearFanin();
  
  output->addFanin(input1);
  output->addFanin(input2);
  output->tt.setNumVars(2);
  
  output->tt.addEntry("-1");
  output->tt.addEntry("1-");

  return 0;
}

// creates a 2-input AND node
// 写这里？？？？？？？
int Circuit::createAND2Node(Node* input1, Node* input2, Node* output)
{
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(output != NULL);

  /******************************/

  output->clearTT();
  output->clearFanin();

  output->addFanin(input1);
  output->addFanin(input2);
  output->tt.setNumVars(2);

  output->tt.addEntry("11"); // only "1" AND "1", can get "1"

  // after you implement this function,
  // change 'return -1' to 'return 0'
  return 0;

  /******************************/
}

// creates a 3-input XOR node
// 写这里？？？？？？？->直接写真值表了？？？
int Circuit::createXOR3Node(Node* input1, Node* input2, Node* input3, Node* output)
{
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(input3 != NULL);
  assert(output != NULL);

  /******************************/
  
  output->clearTT();
  output->clearFanin();

  output->addFanin(input1);
  output->addFanin(input2);
  output->addFanin(input3);
  output->tt.setNumVars(3);

  output->tt.addEntry("11");

  // after you implement this function,
  // change 'return -1' to 'return 0'
  return 0;

  /******************************/
}

// creates a 4-input MUX node (with two select bits)
// ordering from msb to lsb is:
// select2 select1
// input4 input3 input2 input1
// 写这里？？？？？？？->要调用其他的？？？
int Circuit::createMUX4Node(Node* select1, Node* select2,
                            Node* input1, Node* input2, Node* input3, Node* input4, Node* output)
{
  assert(select1 != NULL);
  assert(select2 != NULL);
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(input3 != NULL);
  assert(input4 != NULL);
  assert(output != NULL);
  
  // after you implement this function,
  // change 'return -1' to 'return 0'
  return -1;
}