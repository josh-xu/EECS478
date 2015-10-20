#ifndef SMART_POINTER_H
#define SMART_POINTER_H

/* smart_Pointer class template
see R.B. Murray, C++ Strategy and Tactics. Addison-Wesley, 1993

Usage:

1. Inherit classes from Reference_Counted_Object

	class My_class : public Reference_Counted_Object {
	// rest of declaration as usual
	};

2. Always allocate objects with new and assign to a smart_pointer

		smart_pointer<const My_class> ptr = new My_class;
		or
		smart_pointer<const My_class> ptr(new My_class);
		
3. Can copy or assign smart_pointers in any way desired, e.g. with 
Standard Library containers.

4. When last smart_pointer pointing to an object is destructed,
or set to 0, pointed-to object will be deleted automatically.

5. Don'ts: Never delete the pointed-to object explicitly. 
Don't assign to a built-in pointer type except temporarily. 
Never assign a smart_pointer to point to a stack object. 
Effects of breaking these rules is undefined.
*/

/*
Reference_Counted_Objects should only be allocated using new, never the stack.
Other classes increment and decrement the use count.
If the use count hits zero as a result of decrement, the object deletes itself.
The reference count is declared mutable to allow increment/decrement_ref_count
to be declared const, so that using a smart_pointer on an object does not
require it to be non-const. 
*/
class Reference_Counted_Object {
public:
	Reference_Counted_Object () : ref_count(0)
		{}
	Reference_Counted_Object (const Reference_Counted_Object&) : ref_count(0)
		{}
	virtual ~Reference_Counted_Object()                                           //????????????????????? -> 虚函数
		{}
	void increment_ref_count() const
		{++ref_count;}
	void decrement_ref_count() const
		// suicidal - destroys this object                                           //????????????????????? -> decrement后检查ref_count，如果可以则自动删除
		{if (--ref_count == 0) delete this;}
	unsigned int get_ref_count() const
		{return ref_count;}
private:
	mutable unsigned int ref_count;                                           //????????????????????? -> mutable
};

/* Template for smart_pointer class
overloads *, ->, and =, provides conversion to built-in type.
Simply increments and decrements the reference count when smart_pointers
are initialized, copied, assigned, and destructed.
*/
template <class T> class smart_pointer {                                           //!!!!!!!!!!!!!!!!!!!!! -> 类模板 -> T = bdd_node
public:
	// constructor with pointer argument - copy and increment_ref_count count
	smart_pointer(T* arg = 0) : ptr(arg)                                           //构造
		{if (ptr) ptr->increment_ref_count();}                                           //????????????????????? -> 调用模板的时候，T是bdd_node，有Reference_Counted_Object类声明，所以可以用increment_ref_count()函数 -> if(ptr)啥意思？指针不为空？非terminal？
	// templated constructor to support implicit conversions to other smart_pointer type                                           //????????????????????? -> to other type??? 可以不管？
	template <class U> smart_pointer(const smart_pointer<U> other) : ptr(other.get_raw_ptr()) 
		{if (ptr) ptr->increment_ref_count();}
	// copy constructor - copy and increment_ref_count
	smart_pointer(const smart_pointer<T>& arg): ptr(arg)                                            //复制构造
		{if (ptr) ptr->increment_ref_count();}
	// destructor - decrement ref count
	~smart_pointer()                                           //析构
		{if (ptr) ptr->decrement_ref_count();}
	// assignment - decrement lhs, increment rhs                                           //assign to another object
	const smart_pointer<T>& operator= (const smart_pointer<T>& rhs)
		{
			if (ptr != rhs.ptr) {						//check for aliasing
				if (ptr) ptr->decrement_ref_count();
				ptr = rhs.ptr;
				if (ptr) ptr->increment_ref_count();
				}
			return *this;
		}
	// use these with caution - preferably only in a call, or input to smart_pointer ctor
	T* get_raw_ptr() const {return ptr;}	// accessor
	operator T*() const {return ptr;}   	// conversion to pointer type
	// overloaded operators
	T& operator* () {return *ptr;}
	T* operator-> () const {return ptr;}
private:
	T* ptr;                                           //!!!!!!!!!!!!!!!!!!!!! -> ptr定义！！！->T类型指针 -> bdd_node类型指针
};

#endif


