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
  friend class Circuit; //��Ԫ�࣬Circuit�ɵ���Node���������ݺͺ���
  
  private:
    string name;
    nodeType type;
    vector<Node*> fanin; // fanin��<vector>
	
	/****** ÿ��node����һ��truthtable������ÿ��node����ʵ��ÿ��gate������ *******/
    TruthTable tt; // tt��TruthTable�����
    
  public:
    // constructors
    Node():type(INTERNAL) {} // ģʽtypeĬ����INTERNAL
    
    Node(const string &nodeName):name(nodeName), type(INTERNAL) {} // ָ��nodeName��ģʽtypeĬ����INTERNAL
    
    // destructor
    ~Node() {};
    
    // returns the vector of fanin nodes
    vector<Node*> getFanin() { return fanin; }
    
    // returns the number of fanin nodes (variables)
    unsigned getNumFanin() { return fanin.size(); }
    
    // adds a fanin node
    int addFanin(Node* &inNode) { fanin.push_back(inNode); return 0; } // ���fanin��
    
    // returns the name of the node
    string getName() { return name; }
    
    // sets the name of the node
    int setName(const string &n) { name = n; return 0; }
    
    // returns the type of the node
    nodeType getType() {return type; }
    
    // sets the type of the node
    int setType(nodeType t) { type = t; return 0; }
    
    int clearFanin() { fanin.clear(); return 0; } // fain��<vector>������vector.clear()���
    
    int clearTT() { tt.clear(); return 0; } // clears all entries��TruthTable������ݳ�Աlogic������ֵ����<vector<vector>>������vector.clear()���

    int clear() { name = ""; clearFanin(); clearTT(); return 0; } //ȫ�����㣬��������
    
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
      
	  // ���룬�㣬һ����ֻ����ڵ㣬����ֵ��Ҳ���������
      if (type == PRIMARY_OUTPUT || type == INTERNAL) // ֻ��ӡ�м������������������ģ�����ڵ����ֵ��
      {
        cout << "Fanin nodes: ";
        for (unsigned i = 0; i < fanin.size(); ++i)
          cout << fanin[i]->name << " ";
        cout << endl;
        tt.print(); // ������ŵ���ֵ��
      }
      
      return 0;
    }
};

#endif

