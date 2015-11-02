#include "truthTable.h"


const char TruthToChar[4] = {'0', '1', '-', '?'}; // “?”好像用不到？

/*
	.names cin g[1] s[0]
	01 1
	10 1

	Name: out[4] [TYPE = PRIMARY_OUTPUT]
	Fanin nodes: orig[2] 
	1 1
*/

// sets the number of variables（fanin + output）
int TruthTable::setNumVars(unsigned nV)
{
  numVars = nV;
  return 0;
}

// adds an emtry (row) to the truth table（constraints）
// 添加单行真值表
int TruthTable::addEntry(const string &newEntry) // newEntry是一个字符串，某一行的真值表
{
  if (newEntry.length() != numVars)
  {
    cout << "ERROR in truthTable::addEntry() - new entry has length "
         << newEntry.length() << " vs. numVars = " << numVars << endl;
    return -1;
  }
  
  vector<truthType> row(newEntry.length()); // <vector>分别记录某一行真值表中不同variable的取值
  
  for (unsigned i = 0; i < newEntry.length(); ++i)
  {
    switch(newEntry[i])
    {
      case '0': row[i] = ZERO; break;
      case '1': row[i] = ONE;  break;
      case '-': row[i] = DC;   break;
      default:
        cout << "ERROR in truthTable::addEntry() - invalid character "
             << newEntry[i] << endl;
        return -1;
    }
  }
  logic.push_back(row); // 放入整个真值表中，某一行constraint
  
  return 0;
}

// returns the number of entries (rows)，有多少个constraint
unsigned TruthTable::getNumEntries()
{
  return logic.size();
}

// returns number of variables (columns)，有多少个variable
unsigned TruthTable::getNumVars()
{
  return numVars;
}

int TruthTable::print()
{
  for (unsigned i = 0; i < logic.size(); ++i)
  {
    for (unsigned j = 0; j < logic[i].size(); ++j)
    {
      switch(logic[i][j])
      {
        case ZERO: cout << "0"; break;
        case ONE:  cout << "1"; break;
        case DC:   cout << "-"; break;
        default:
          cout << "ERROR in truthTable::printTable() - invalid character "
               << logic[i][j] << endl;
          return -1;
      }
    }
    cout << " 1" << endl; // BLIF只需要speify TRUE的情况，其他默认是0，所以output一定是“1”！！！
  }
  return 0;
}

int TruthTable::clear()
{
  logic.clear();
  return 0;
}

