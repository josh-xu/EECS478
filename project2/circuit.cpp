#include "circuit.h"

/******************Circuit Implementation********************/

Circuit::~Circuit()
{
  clear();
}

vector<Node*> Circuit::getPIs()
{
  vector<Node*> PIs;
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    // it��map�ĵ�������first��ʾ�±꣡����second��ʾֵ������
	/*
	MapForSort[99] = 1000000;
	it->first�����±꣬��99
	it->second��ֵ����1000000
	*/
    if (it->second->type == PRIMARY_INPUT)
      PIs.push_back(it->second); // �ŵ�vector��
  }
  return PIs;
}

vector<Node*> Circuit::getPOs()
{
  vector<Node*> POs;
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_OUTPUT)
      POs.push_back(it->second);
  }
  return POs;
}

int Circuit::setPI(const string &input)
{
  Node *in = findNode(input);    // check to see if a node is there��ͬʱ����node in��in�����ֲ����ظ�����������Ϊ***�ֲ�����***������
                                 // ��Ȼ���ǣ�������ЩnodeMap���ֵ��֮ǰcreate��ʱ��͵���createNode()�����ˣ�����
  // assert() -> if false, then assert!
  assert(in != NULL);            // ���ֵΪ�٣��򱨴�����Ҫ�棬����in������NULL�����������Ҫ����Node inһ��Ҫ�Ѿ���circuit���ˣ�����
  
  in->type = PRIMARY_INPUT;
  return 0;
}

int Circuit::setPO(const string &output)
{
  Node *out = findNode(output);
  assert(out != NULL);
  
  out->type = PRIMARY_OUTPUT;
  return 0;
}

int Circuit::setPIs(const string &input, unsigned int startBit, unsigned int endBit)
{
  for (unsigned i = startBit; i < endBit; ++i)
  {
    stringstream sstr;
    sstr << i;
    
    string name = input + "[" + sstr.str() + "]"; // ����ͬһ��������ĸ�Ĳ�ͬ�±��*�ַ���*������
    setPI(name);  // ���������������涨���setPI();
  }
  return 0;
}

int Circuit::setPOs(const string &output, unsigned int startBit, unsigned int endBit)
{
  for (unsigned i = startBit; i < endBit; ++i)
  {
    stringstream sstr;
    sstr << i;
    
    string name = output + "[" + sstr.str() + "]";
    setPO(name);
  }
  return 0;
}

Node* Circuit::findNode(const string &nodeName) // NULL����û���ҵ����ҵ��򷵻����Node
{
  mapIter it = nodeMap.find(nodeName);
  return (it != nodeMap.end() ? it->second : NULL);
}

Node* Circuit::createNode(const string &nodeName) // ����node������ǰ��check��
{
  Node* newNode = findNode(nodeName);
  if (newNode == NULL)
  {
    newNode = new Node(nodeName);
	/************** circuit nodeMap **********************/
    nodeMap.insert(make_pair(nodeName, newNode)); // insert��nodeMap���nodeName��Ϊdictionary��Key��newNode(Node�����)��ΪValue������
  }
  
  return newNode;
}

// ��ӡcircuit�������node��������Ϣ
int Circuit::print()
{
  cout << "Circuit Name: " << name << " contains " << nodeMap.size() << " nodes." << endl;
  cout << "Primary Inputs: ";
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_INPUT)
      cout << it->second->name << " ";
  }
  cout << endl;
  cout << "Primary Outputs: ";
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_OUTPUT)
      cout << it->second->name << " ";
  }
  cout << endl;
  
  cout << "Nodes:" << endl;
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    it->second->print(); // ��ӡ����Node����Ϣ
    cout << endl;
  }

  return 0;
}

// д��blif�ļ�������
int Circuit::writeBLIF(const string &filename)
{
  ofstream outFile(filename.c_str());
  if (!outFile.good())
  {
    cout << "ERROR  in writeBLIF() - cannot open "
         << filename << " for writing." << endl;
    return -1;
  }
  
  // print model name
  outFile << ".model " << name << endl << endl;
  
  // print primary inputs
  outFile << ".inputs ";
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_INPUT)
      outFile << it->first << " ";
  }
  outFile << endl << endl;
  
  // print primary outputs
  outFile << ".outputs ";
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_OUTPUT)
      outFile << it->first << " ";
  }
  outFile << endl << endl;
  
  // print nodes
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    // must explicitly write 0 node
    if (it->second->type == ZERO_NODE)
    {
      outFile << ".names " << it->second->name << endl;
      outFile << endl;
    }
    // must explicitly write 1 node
    else if (it->second->type == ONE_NODE)
    {
      outFile << ".names " << it->second->name << endl;
      outFile << "1" << endl << endl;
    }
    else if (it->second->type != PRIMARY_INPUT)
    {
      outFile << ".names ";
      for (unsigned i = 0; i < it->second->getNumFanin(); ++i)
        outFile << it->second->getFanin()[i]->name << " ";
      outFile << it->second->name << endl;
      
      const TruthTable &theTT = it->second->tt;
      for (unsigned i = 0; i < theTT.logic.size(); ++i)
      {
        for (unsigned j = 0; j < theTT.logic[i].size(); ++j)
        {
          switch(theTT.logic[i][j])
          {
            case ZERO: outFile << "0"; break;
            case ONE:  outFile << "1"; break;
            case DC:   outFile << "-"; break;
          }
        }
        outFile << " 1" << endl;
      }
      outFile << endl;
    }
  }
  
  outFile << ".end" << endl;
  outFile.close();
  
  cout << "File " << filename << " successfully written." << endl;
  
  return 0;
}

int Circuit::clear() // ��������
{
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second != NULL)
      delete it->second;
  }
  nodeMap.clear();
  return 0;
}


