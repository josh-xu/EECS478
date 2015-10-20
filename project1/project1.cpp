/*
 * Contains the the apply function, the cofactors and quantification functions.
 *
 * For Project 1, implement
 * (1) apply, also handles probabilities
 * (2) negative_cofactor
 * (3) positive_cofactor, 
 * (4) boolean_difference
 * (5) sort by influence
 */

#include "project1.h"

using namespace std;

// wrapper function to allow calling with the operation, i.e apply(bdd1, bdd2, "or")
bdd_ptr apply(bdd_ptr bdd1, bdd_ptr bdd2, string o)
{
  operation dop;
  if (!dop.set_operation(o))
  {
    return 0;
  }
  
  return apply(bdd1, bdd2, dop);
}

// apply implements an arbitrary operation (specified in op) on two BDDs
// bdd_tables is used to handle the book keeping (see bdd_tables.h).
//
// apply works recursively one the idea that given an arbitrary operation $, 
// and functions f and g: f $ g = a'(fa' $ ga') + a(fa $ ga), 
// where a is a variable, fa' is the negative cofactor etc.
bdd_ptr apply(bdd_ptr bdd1, bdd_ptr bdd2, operation &op) // bdd1 = f; bdd2 = g;
{
  // get reference to tables
  bdd_tables& tables = bdd_tables::getInstance();
  
  /*******************************************************/ //(add probability)
  // ... your code goes here

  // In general, the operations will return a pointer to a bdd_node **if the operation was terminal**, or 0 if not (the operation will ***only work if at least one of the nodes is terminal***).
  if(bdd1->is_terminal() || bdd2->is_terminal())
  {
	  bdd_ptr base_cmp = op(bdd1, bdd2); // 'cmp' = computed
	  return base_cmp;
  }
  
  std::string op_cmd = op.get_operation(); // 'cmd' = command
  bdd_ptr already_cmp = tables.find_in_computed_table(op_cmd, bdd1, bdd2);
  if(already_cmp != NULL) return already_cmp;
  
  // returns the next var (actually not next, because it is from bdd1's var & bdd2's var) to be split on (used in Apply). Lower value vars have precedence.
  char var = find_next_var(bdd1, bdd2); // defined in bdd_node.cpp
  
  bdd_ptr f0 = bdd1->neg_cf;
  bdd_ptr f1 = bdd1->pos_cf;
  bdd_ptr g0 = bdd2->neg_cf;
  bdd_ptr g1 = bdd2->pos_cf;
  // bdd_ptr f0 = negative_cofactor(bdd1, var);
  // bdd_ptr f1 = positive_cofactor(bdd1, var);
  // bdd_ptr g0 = negative_cofactor(bdd2, var);
  // bdd_ptr g1 = positive_cofactor(bdd2, var);
  bdd_ptr neg_cmp = apply(f0, g0, op);
  bdd_ptr pos_cmp = apply(f1, g1, op);
  
  // apply "Rule 1"
  if(neg_cmp == pos_cmp) return neg_cmp; // 'neg_cmp' = negative computed 

  // apply "Rule 2"
  bdd_ptr ret = tables.find_in_unique_table(var, neg_cmp, pos_cmp); // 'ret' = returned
  if (ret == NULL)
  {
	  ret = tables.create_and_add_to_unique_table(var, neg_cmp, pos_cmp);
	  // probability
  }

  tables.insert_computed_table(op_cmd, bdd1, bdd2, ret);

  // change the return value when you're finished
  return ret;
  /*******************************************************/
}

// negative_cofactor takes the BDD pointed to by np, 
// and returns the negative cofactor with respect to var.
bdd_ptr negative_cofactor(bdd_ptr np, char var)
{
  // get reference to tables
  bdd_tables& tables = bdd_tables::getInstance();
  
  /*******************************************************/
  //... your code goes here

  if(np->is_terminal()) return bdd_node::zero;
  else if(np->var == var) return np->neg_cf;

  bdd_ptr left negative_cofactor(np->neg_cf, var);
  bdd_ptr right negative_cofactor(np->neg_cf, var);

  // apply "Rule 1"
  if(left == right) return left;

  // apply "Rule 2"
  bdd_ptr ret = tables.find_in_unique_table(np->var, left, right); // 'ret' = returned
  if (ret == NULL)
  {
	  ret = tables.create_and_add_to_unique_table(var, left, right);
	  // probability
  }

  // once you add your code, remove this and return your own result
  return np;
  /*******************************************************/
}

// posative_cofactor takes the BDD pointed to by np, 
// and returns the posative cofactor with respect to var.
bdd_ptr positive_cofactor(bdd_ptr np, char var)
{
  // get reference to tables
  bdd_tables& tables = bdd_tables::getInstance();
  
  /*******************************************************/
  //... your code goes here
  
  if(np->is_terminal()) return bdd_node::one; // is there any possibility that np is terminal? -> only if directed called from main()? -> because in apply, it's base case and already been filtered (need not be called in apply...!!!)
  else if(np->var == var) return np->pos_cf;

  bdd_ptr left positive_cofactor(np->neg_cf, var);
  bdd_ptr right positive_cofactor(np->pos_cf, var);

  // apply "Rule 1"
  if(left == right) return left;

  // apply "Rule 2"
  bdd_ptr ret = tables.find_in_unique_table(np->var, left, right); // 'ret' = returned
  if (ret == NULL)
  {
	  ret = tables.create_and_add_to_unique_table(var, left, right);
	  // probability
  }

  // once you add your code, remove this and return your own result
  return ret;
  /*******************************************************/
}

// boolean_difference takes the BDD pointed to by np, 
// and returns the boolean difference with respect to var.
bdd_ptr boolean_difference(bdd_ptr np, char var)
{
  // get reference to tables
  bdd_tables& tables = bdd_tables::getInstance();
  
  /*******************************************************/
  //... your code goes here
  
  bdd_ptr ret = apply(negative_cofactor(np, var), positive_cofactor(np, var), "xor");

  // once you add your code, remove this and return your own result
  return ret; 
  /*******************************************************/
}


// sort_by_influence calculates the influence of all the variables in np
// and displays them in descending order (most influent variable is
// shown first). For this task you can assume the number of variable
// is no greater than 20.
bdd_ptr sort_by_influence(bdd_ptr np)
{
  /*******************************************************/
  //... your code goes here
  
  /*******************************************************/

  // this function does not alter the current node, so np must be
  // returned at the end
  return np; 
}


