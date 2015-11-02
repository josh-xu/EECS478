#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <iostream>
#include <vector>

using namespace std;

#include "truthTable.h"

//Define node type
enum nodeType {PRIMARY_INPUT, PRIMARY_OUTPUT, INTERNAL, ZERO_NODE, ONE_NODE};

class Circuit;

class Node
{
  friend class Circuit; //友元类，Circuit可调用Node的所有数据和函数
  
  private:
    string name;
    nodeType type;
    vector<Node*> fanin; // fanin，<vector>
	
	/****** 每个node都有一个truthtable！！！每个node，其实是每个gate！！！ *******/
    TruthTable tt; // tt，TruthTable类对象
    
  public:
    // constructors
    Node():type(INTERNAL) {} // 模式type默认是INTERNAL
    
    Node(const string &nodeName):name(nodeName), type(INTERNAL) {} // 指明nodeName，模式type默认是INTERNAL
    
    // destructor
    ~Node() {};
    
    // returns the vector of fanin nodes
    vector<Node*> getFanin() { return fanin; }
    
    // returns the number of fanin nodes (variables)
    unsigned getNumFanin() { return fanin.size(); }
    
    // adds a fanin node
    int addFanin(Node* &inNode) { fanin.push_back(inNode); return 0; } // 添加fanin？
    
    // returns the name of the node
    string getName() { return name; }
    
    // sets the name of the node
    int setName(const string &n) { name = n; return 0; }
    
    // returns the type of the node
    nodeType getType() {return type; }
    
    // sets the type of the node
    int setType(nodeType t) { type = t; return 0; }
    
    int clearFanin() { fanin.clear(); return 0; } // fain是<vector>，调用vector.clear()清空
    
    int clearTT() { tt.clear(); return 0; } // clears all entries，TruthTable类的数据成员logic，即真值表，是<vector<vector>>，调用vector.clear()清空

    int clear() { name = ""; clearFanin(); clearTT(); return 0; } //全部清零，包括名字
    
    // prints node information
    int print()
    {
      cout << "Name: " << name << " [TYPE = ";
      switch(type)
      {
        case PRIMARY_INPUT : cout << "PRIMARY_INPUT";  break;
        case PRIMARY_OUTPUT: cout << "PRIMARY_OUTPUT"; break;
        case INTERNAL      : cout << "INTERNAL";       break;
        case ZERO_NODE     : cout << "ZERO_NODE";      break;
        case ONE_NODE      : cout << "ONE_NODE";       break;
      }
      cout << "]" << endl;
      
	  // 输入，零，一，均只输出节点，无真值表，也不用输出！
      if (type == PRIMARY_OUTPUT || type == INTERNAL) // 只打印中间输出，或者最终输出的，输出节点的真值表！
      {
        cout << "Fanin nodes: ";
        for (unsigned i = 0; i < fanin.size(); ++i)
          cout << fanin[i]->name << " ";
        cout << endl;
        tt.print(); // 输出该门的真值表？
      }
      
      return 0;
    }
};

#endif

