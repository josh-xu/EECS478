#ifndef __TRUTHTABLE_H__
#define __TRUTHTABLE_H__

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::cerr; // std::cerr是ISO C++标准错误输出流
using std::endl; // 为啥不用using namespace std？

class Node;
class Circuit;

//Define possible values inside truth table
enum truthType {ZERO, ONE, DC}; /***** DC = don't cares *****/

class TruthTable
{
  friend class Node; //友元类，Node可调用TrthTable的所有数据和函数
  friend class Circuit; //友元类，Circuit可调用TrthTable的所有数据和函数
  
  private:
    // number of columns per entry
    unsigned numVars;
    
    // stores the truth table logic
	// ？？？？？？？？
    vector<vector<truthType> > logic; // logic是整个真值表，是二维<vector>
	                                  // 第一维代表真值表行数（对应各个constraints），第二维代表真值表列数（对应各个variable）
    
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

