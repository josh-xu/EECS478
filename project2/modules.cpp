#include "circuit.h"


// 写这里？？？？？？？
int Circuit::createADDModule(const string &input1, const string &input2, const string &cin, const string &output, const string &cout, unsigned int numBits)
{
  /************* P2 Add Code Here: Begin*************/

  Node* node;
  string name, name1, name2, name3, name4;

  ////// PRIMARY INPUT: create input nodes, insert into nodeMap of Circuit class
  // "a[]" PIs & "b[]" PIs
  for (unsigned int i = 0; i < numBits; i++)
  {
    stringstream sstr;
    sstr << i;
    name1 = input1 + "[" + sstr.str() + "]";
    name2 = input2 + "[" + sstr.str() + "]";
    
    node = createNode(name1); // the returned node have no use, what we need is to insert the node into nodeMap by calling createNode(name)
	node = createNode(name2);
  }
  // "cin" PI
  node = createNode(cin);

  ////// INTERNAL: create internal nodes, insert into nodeMap of Circuit class
  // **cin[1-15]** as internal inputs, also regarded as internal output **cout[0-14]**
  // "cin[1-14]" INTERNALs & "cout[1-14]" INTERNALs
  for (unsigned int i = 1; i < numBits - 1; i++)
  {
    stringstream sstr;
    sstr << i;
    name1 = cin + "[" + sstr.str() + "]";
    name2 = cout + "[" + sstr.str() + "]";
    
    node = createNode(name1);
    node = createNode(name2);
  }
  // "cin[15]" INTERNALs & "cout[0]" INTERNALs
  name1 = cin + "[15]";
  name2 = cout + "[0]";
  node = createNode(name1);
  node = createNode(name2);

  ////// PRIMARY OUTPUT: create output nodes, insert into nodeMap of Circuit class
  // "s[]" POs
  for (unsigned int i = 0; i < numBits; i++)
  {
    stringstream sstr;
    sstr << i;
    name = output + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  // "cout" PO
  node = createNode(cout);

  ////// LSB
  //// assign "XOR3(a[0], b[0], cin)" to s[0]
  //// assign "MAJORITY3(a[0], b[0], cin)" to cout[0]
  //// assign cout[0] to cin[1]

  ////// MSB
  //// assign "XOR3(a[15], b[15], cin[15])" to s[15]
  //// assign "MAJORITY3(a[15], b[15], cin[15])" to cout

  ////// Internal Bit
  //// assign "XOR3(a[i], b[i], cin[i])" to s[i], i = 1-14
  //// assign "MAJORITY3(a[i], b[i], cin[i])" to cout[i], i = 1-14
  //// assign cout[i] to cin[i+1]
  for (unsigned int i = 0; i < numBits; i++)
  {
    stringstream sstr;
    sstr << i;

	name1 = input1 + "[" + sstr.str() + "]";   // a[i]
    name2 = input2 + "[" + sstr.str() + "]";   // b[i]
	if(i == 0) name3 = cin;                    // cin
	else name3 = cin + "[" + sstr.str() + "]"; // cin[i]
    name4 = output + "[" + sstr.str() + "]";   // s[i]
    Node* a_i = findNode(name1);
    Node* b_i = findNode(name2);
    Node* cin_i = findNode(name3);
    Node* s_i = findNode(name4);

    createXOR3Node(a_i, b_i, cin_i, s_i); // s_i is "s[i]"

    if(i == 15) name = cout;                   // cout
	else name = cout + "[" + sstr.str() + "]"; // cout[i]
    Node* cout_i = findNode(name);

	createMAJORITY3Node(a_i, b_i, cin_i, cout_i);

	if(i == 15) {}
	else
	{
		sstr << i + 1;
		name = cin + "[" + sstr.str() + "]";  // cin[i+1]
		Node* cin_ii = findNode(name);

		createBUF1Node(cout_i, cin_ii);
	}
  }

  // when you have implemented this function,
  // change 'return -1' to 'return 0'
  return 0;

  /************* P2 Add Code Here: End *************/
}

// 写这里？？？？？？？
int Circuit::createSUBModule(const string &input1, const string &input2, const string &output, unsigned int numBits)
{
  // when you have implemented this function,
  // change 'return -1' to 'return 0'
  return -1;
}

// 已经写好了？？！！！
/*******************************************/
// 重点看这里！！！！！！！！！！！！！！
/*******************************************/
int Circuit::createSHIFTModule(const string &input, const string &output, unsigned int numBits, unsigned int numShift)
{
  Node* node;
  // create input nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create output nodes
  for (unsigned int i = 0; i < numBits+numShift; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // assign '0's to the least numShift bits
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode); // 直接调用Circuit类内部的函数
  
  for (unsigned int i = 0; i < numShift; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    Node* outNode = findNode(name); // 找到与name相同的node，并返回操作
    assert(outNode != NULL);
    
    createBUF1Node(zeroNode, outNode); // 建buffer？？？buffer是用来连线的！！！
  }
  
  // assign inputs to the remaining numBits bits
  for (unsigned int i = numShift; i < numBits+numShift; ++i)
  {
    string name;
    
    // find input node[i-numShift]
    stringstream inStr;
    inStr << i-numShift;
    name = input + "[" + inStr.str() + "]";
    Node* inNode = findNode(name);
    assert(inNode != NULL);
    
    // find output node[i]
    stringstream outStr;
    outStr << i;
    name = output + "[" + outStr.str() + "]";
    Node* outNode = findNode(name);
    assert(outNode != NULL);
    
    // assign
    createBUF1Node(inNode, outNode);
  }
  
  return 0;
}