#ifndef __TRUTHTABLE_H__
#define __TRUTHTABLE_H__

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::cerr; // std::cerr��ISO C++��׼���������
using std::endl; // Ϊɶ����using namespace std��

class Node;
class Circuit;

//Define possible values inside truth table
enum truthType {ZERO, ONE, DC}; /***** DC = don't cares *****/

class TruthTable
{
  friend class Node; //��Ԫ�࣬Node�ɵ���TrthTable���������ݺͺ���
  friend class Circuit; //��Ԫ�࣬Circuit�ɵ���TrthTable���������ݺͺ���
  
  private:
    // number of columns per entry
    unsigned numVars;
    
    // stores the truth table logic
	// ����������������
    vector<vector<truthType> > logic; // logic��������ֵ���Ƕ�ά<vector>
	                                  // ��һά������ֵ����������Ӧ����constraints�����ڶ�ά������ֵ����������Ӧ����variable��
    
  public:
    // constructors
    TruthTable():numVars(0) {} 
    
    TruthTable(unsigned nV): numVars(nV) {}
    
    TruthTable(unsigned nV,const vector<vector<truthType> > &l): numVars(0), logic(l) {}
    
    // destructor
    ~TruthTable() {};
    
    // sets the number of variables
    int setNumVars(unsigned nV);
    
    // adds an emtry (row) to the truth table
    int addEntry(const string &newEntry);
    
    // returns the number of entries (rows)
    unsigned getNumEntries();
    
    // returns number of variables (columns)
    unsigned getNumVars();
    
    // prints the contents of the table
    int print();
    
    // clears all entries
    int clear();
};

#endif

