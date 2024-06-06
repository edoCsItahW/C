// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: C
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/05/30 上午8:18
 * @Commend:
 *******************************************************/
#include <iostream>
#include <cstdlib>

using namespace std;  //  作用域,using namespace std可以省略std::前缀

void templatePrint() {
	cout << "Hello, world!" << endl;  // 省略std::前缀

	std::cout << "'Hello, world!' using std::cout" << std::endl;  // 加上std::前缀

}

// 引用
void reference() {
	int a = 10;
	int &b = a;  // 引用b指向a,某种意义上相当于a的别名

	// 类似于指针,引用在向函数传递参数时,可以避免拷贝,提高效率
	// 在使用期间,类似于一级指针,不需要使用取地址符&

	int &c = b;  // 引用c指向b,c和b指向同一地址,注意不是说c引用b,而是c和b指向同一地址

}

void nullPointer() {
	int *p = nullptr;  // 空指针,指向不确定地址,不能解引用,不能使用指针运算符*,等价于int *p = 0;

	// 注意需要include<cstdlib>
	int *p1 = NULL;  // 空指针,等价于int *p1 = 0;

	// void*和nullptr的区别:
	// void*可以指向任意类型的地址,nullptr只能指向空指针,不能指向其他地址
	// 但是void*可以转换为任意类型的指针,nullptr不能转换为其他类型的指针

}


// const限定符
void constModifier() {
	const int a = 10;  // 常量,不能修改,只能读取,只能在定义时初始化

	// file1.cpp
//	const int b = func();
	// file2.cpp
//	extern const int b;  // 声明,但不定义,可以引用

	// 顶层const:
	int b = 10;
	const int *p = &b;  // 指针,指向常量对象,不能修改指针指向的值,但可以修改指针指向的地址

	// 底层const:
	const int c = 10;
	const int* p2 = &c;  // 指针,指向常量对象,不能修改指针指向的值,但可以修改指针指向的地址

}

// constexpr限定符
void constexprModifier() {
	constexpr int a = 10;  // 常量表达式,在编译时计算,可以用在任何需要常量的地方,常量表达式的值在编译时就确定

	// 注意constexpr不能用在类中,因为类中不能定义构造函数,析构函数,不能定义虚函数,不能定义引用成员变量,不能定义静态成员变量,不能定义内联函数,不能定义局部变量

	// constexpr int f = func();  只有当func()是一个constexpr函数时才可以这样用

	// constexpr

}

void typeAlias() {

    // typedef: 相较于using,typedef可以给类型起别名

	// using SI = Sales_item;  // 定义类型别名,可以用作类型名,也可以用作变量名

}

void autoKeyword() {
	// auto类型说明符

	// auto可以自动分析表达式所属的类型

	// auto item = x + y;  // item的类型为decltype(x+y)

	// auto i = 0, *p = &i;  // i的类型为int,p的类型为int*

}

void decltypeOperator() {
	// decltype类型说明符


	// decltype: 选择并返回表达式的类型,decltype(expression)

	// decltype(func()) sun = x;  // sun的类型为decltype(func())

	// decltype(*p) x = 10;  // x的类型为int

}

void classType() {
	// 类型

	// c++11规定,可以为数据成员(data member)指定一个类内初始值(in-class initializer)

	struct example {
		std::string name;  // std::string是类名,也可写成string
		int age = 0;  // 类内初始值,age的默认值是0
	};

	// 读入数据
	example e1;
	std::cin >> e1.name >> e1.age;  // 读入e1的name和age成员变量

}

// 预处理变量无视C++作用域规则,可以跨文件使用

void usingDeclare() {
	// using声明: 声明一个命名空间或类型,使得后续代码可以使用该命名空间或类型

	using std::cin;  // 当我们使用cin时,从命名空间std中获取它

	int i;

	cin >> i;  // 正确,使用命名空间std中的cin

	cout << i;  // 错误,没有对应的using声明,无法使用cout

	std::cout << i;  // 正确,显式的从std中使用cout

	// 注意: 头文件中不应该使用using声明,否则会导致命名空间污染,导致命名冲突

}

# include <string>

void stringType(){
    // 字符串类型

	string s1;  // 空字符串
	string s2(s1);  // s2是s1的副本
//	string s2 = s1;  // 等价于上一行
	string s3("value");  //s3是"value"的副本,除了字面值最后的空字符
//	string s3 = "value";  // 等价于上一行
	string s4(10, 'c');  // 把s4初始化为连续的10个字符'c'

	// 直接初始化和拷贝初始化

	/*
	 os << s;  // 将s写到输出流os当中,返回os
	 is >> s;  // 从输入流is中读取字符串赋给s,字符串以空白分隔,返回si
	 getline(is, s);  // 从输入流is中读取一行赋给s,返回is
	 s.empty();  // 判断s是否为空,返回bool值
	 s.size();  // 返回s的长度,返回size_type
	 s[n];  // 返回s的第n个字符的引用,返回char&
	 s1 + s2;  // 连接s1和s2,返回string
	 s1 = s2;  // 拷贝s2的值给s1,返回s1
	 s1 == s2;  // 判断s1和s2是否相等,返回bool值,对大小写敏感
	 <, <=, >=, >;  // 字符串比较,返回bool值,对大小写敏感
	 */

	// 读取未知数量的string对象

	string word;
	while (cin >> word) {
		cout << word << endl;
	}

	// string::size_type类型

	string s5 = "hello world";
	string::size_type len = s5.size();  // len的值为11

	/*
	 isalnum();  // 判断s是否是字母或数字,返回bool值
	 isalpha();  // 判断s是否是字母,返回bool值
	 isdigit();  // 判断s是否是数字,返回bool值
	 islower();  // 判断s是否是小写字母,返回bool值
	 isupper();  // 判断s是否是大写字母,返回bool值
	 isspace();  // 判断s是否是空白字符,返回bool值
	 tolower();  // 将s中的大写字母转换为小写字母,返回string
	 toupper();  // 将s中的小写字母转换为大写字母,返回string
	 isgraph();  // 判断s是否是可见字符,返回bool值
	 isprint();  // 判断s是否是可打印字符,返回bool值
	 ispunct();  // 判断s是否是标点符号,返回bool值
	 */

	// 范围for语句

	for (auto c: s5)
		cout << c << " ";  // 输出s5中的每个字符,空格分隔

	for (auto &c: s5)
		c = toupper(c);  // 将s5中的每个字符转换为大写字母,并输出

	// 下标迭代
	for (decltype(s5.size()) i = 0; i != s5.size(); ++i)
		s5[i] = toupper(s5[i]);  // 将s5中的每个字符转换为大写字母,并输出

}

# include <vector>

// 标准库类型vector
void vectorType() {
	// 类模板(class template)
	// typescript中也有类似的概念,称为接口(interface)

	// 编辑器根据模板创建类或函数的过程称为实例化(instantiation)

	vector<int> v1;  // v1保存int类型的对象
	vector<string> v2;  // v2保存string类型的对象
	vector<vector<int>> v3;  // v3保存vector<int>类型的对象

	vector<int> v4(v1);  // v4中包含了v1的所有元素的副本
//	vector<int> v4 = v1;  // 等价于上一行
	vector<int> v5(10, 42);  // v5中包含10个42的元素
	vector<int> v6(10);  // v6中包含10个默认初始化的元素
	vector<int> v7{1, 2, 3, 4, 5};  // v7中包含5个元素,初始化列表
//	vector<int> v7 = {1, 2, 3, 4, 5};  // 等价于上一行

	v2.push_back("hello");  // 在v2的末尾添加一个string对象

	// 部分操作与string类似

}

// 迭代器
void iteratorType() {
	// 迭代器(iterator)

	vector<int>::iterator iterator;  // 迭代器类型,指向int类型的元素

	string s("some string");  // 字符串s
	auto it = s.begin();  // 迭代器it指向s的第一个元素
	auto itEnd = s.end();  // 迭代器itEnd指向s的最后一个元素的下一位置

	vector<int>::const_iterator cIt;  // 常量迭代器类型,指向const int类型的元素

	// 某些操作会使迭代器失效,比如修改容器的元素,容器的大小,容器的容量,这也很好理解,因为迭代器指向的位置可能已经不再有效了

	// 迭代器运算

	/*
	 iter + n;  // 迭代器加上整数n,返回迭代器,n为正,向后移动,n为负,向前移动,每个元素移动n个位置
	 iter - n;  // 迭代器减去整数n,返回迭代器,n为正,向前移动,n为负,向后移动,每个元素移动n个位置
	 iter++;  // 前置自增运算符,指向下一个元素
	 iter--;  // 前置自减运算符,指向上一个元素
	 iter += n;  // 后置自增运算符,指向下一个元素
	 iter -= n;  // 后置自减运算符,指向上一个元素
	 iter1 - iter2;  // 两个迭代器的距离,返回整数,向前移动为正,向后移动为负
	 <, >, <=, >=;  // 迭代器比较,返回bool值,对元素进行比较
	 */
	// 迭代器相减所得类型为difference_type,即两个迭代器的距离类型,可以用来计算两个迭代器之间的距离

	// vector<int>::difference_type
}

// 数组
void arrayType() {
	// 数组(array)

	int arr[3] = {1, 2, 3};  // 数组arr,保存10个int类型的元素
//	int arr2[] = arr;  // 错误,数组的大小必须在编译时确定,不能用数组名作为初始值
//	arr2 = arr  // 错误,数组的大小必须在编译时确定,不能用数组名作为赋值对象

	int *parr[10];

//	int *p[10] = &parr;  // p指向一个含有10个指针的数组,每个指针指向一个int类型变量
//	int &r = arr;  // r是arr的引用,不能修改r的值,但可以修改arr的值

	// 在使用数组下标时一般将其定义为size_t类型,size_t是一种机器相关的无符号类型,它被设计的足够大以容纳指针值

}

// 标准函数库begin和end
void beginEnd() {
	int ia[] = {1, 2, 3, 4, 5};;

	auto *beg = begin(ia);  // 指向ia的第一个元素的指针
	auto *end = end(ia);  // 指向ia的最后一个元素的下一位置的指针

	*end - *beg;  // 数组的大小,返回整数

}

// 与旧代码的接口
void interface() {
	// 由于有些代码在c++标准库出现之前就已经写就,为了与这些代码兼容,c++11引入了一些新的函数,这些函数可以用来与旧代码的接口

	// 使用数组初始化vector对象

	int int_arr[] = {1, 2, 3, 4, 5};

	vector<int> v1(begin(int_arr), end(int_arr));  // 数组int_arr的前5个元素初始化v1

	vector<int> v2(int_arr, int_arr + 5);  // 数组int_arr的前5个元素初始化v2


}

// 别名简化多维数组的指针
void aliasMultiline() {

	int ia[3][4];   // 数组,大小为3行4列

	using int_array = int[4];  // 类型别名,int_array是一个int类型的数组,大小为4
	typedef int int_array[4];  // 类型别名,int_array是一个int类型的数组,大小为4

	for (int_array *p = ia; p != ia + 3; ++p) {
		for (int *q = *p; q != *p + 4; ++q)
			cout << *q << " ";
		cout << endl;
	}

}

// 重载运算符
void overloadOperator() {
	// 重载运算符(operator overloading)

	// 运算符重载(operator overloading)是指在类的内部定义新的运算符,以便对类的对象进行操作

	// 例如python的魔术方法,__add__

}

// 右值(rvalue,读作'are-value'), 左值(lvalue,读作'ell-value')

/*
 溢出

 short a = 32767;  // 最大的short整数值
  short b = a + 1;  // 超出short整数范围,溢出

  cout << b << endl;  // 输出-32768

  符号位本来为0,由于溢出被改成了1,所以结果为负数,这就是溢出发生的原因

 */

// 成员运算符->等价于(*).

// 移位运算符<<,>>又称IO运算符(input/output operator)

// 隐式类型转换,例如取商int a = 10 / 3;  // a的类型为int,10/3的结果为3,不需要类型转换

// 显式类型转换
/*
 命名的强制类型转换(named type casting)

 形式:
     cast-name<type>(expression)

 例如:
     static_cast: 任何具有明确意义的类型转换,只要不包含底层consnt,都可以使用static_cast
         如: int a = static_cast<int>(3.14);  // a的类型为int,3.14的类型为double,static_cast将double转换为int

	 dynamic_cast: 用于类继承体系中,将基类指针或引用转换为派生类指针或引用,如果转换失败,会抛出bad_cast异常
 	     如: class B{}; class D: public B{}; D d; B *pb = &d; B *pd = dynamic_cast<D*>(pb);  // pd指向d,pb指向d的基类B

	 const_cast: 用于去除对象的const属性,将对象的const性质移除,常用于将常量指针或引用转换为非常量指针或引用
		 如: const int ci = 10; int *pi = const_cast<int*>(&ci);  // pi指向ci,但pi是非常量指针,不能修改ci的值

	 reinterpret_cast: 用于将指针或引用转换为任意类型,但不进行类型安全检查,常用于指针和整数之间的转换
		 如: int a = 10; char *pc = reinterpret_cast<char*>(&a);  // pc指向a的整数值,但pc的类型为char*,不进行类型检查,可能导致意外的结果

 */

/* 运算符优先级表

 结合律          运算符                   功能             用法
  左              ::                   全局作用域         ::name
  左              ::                   类作用域           Class::name
  左              ::                   命名空间作用域       namespace::name
  左              .                   成员访问           object.member
  左              ->                   指针成员           pointer->member
  左              []                   下标访问           array[index]
  左              ()                   函数调用           function(expr_list)
  左              ()                   类型构造           type(expr_list)
  右              ++                   后置自增            x++
  右              --                   后置自减            x--
  右              typeid                类型ID            typeid(type)
  右              typeid                运行时类型ID       typeid(expr)
  右              explicit cast        类型转换           static_cast<type>(expr)
  右              ++                   前置自增            ++x
  右              --                   前置自减            --x
  右              ~                   取反               ~x
  右              !                   逻辑取反           !x
  右              -                   取负               -x
  右              +                   取正               +x
  右              *                   指针解引用         *x
  右              &                   取地址             &x
  右              ()                  类型转换           (type)expr
  右            sizeof                取字节数           sizeof type
  右            sizeof                类型的大小          sizeof(type)
  右            Sizeof                参数包的大小         sizeof...(args)
  右            new                   创建对象             new type
  右            new[]                 创建数组             new type[size]
  右            delete                删除对象             delete ptr
  右            delete[]              删除数组             delete[] ptr
  右            noexcept              异常说明            noexcept(expr)
  左             ->*                  指向成员选择的指针     ptr->*member
  左             .*                   指向成员选择的对象     object.*member
  左             *                    乘法               x * y
  左             /                    除法               x / y
  左             %                    取模               x % y
  左             +                    加法               x + y
  左             -                    减法               x - y
  左             <<                   左移               x << y
  左             >>                   右移               x >> y
  左             <                    小于               x < y
  左             <=                   小于等于            x <= y
  左             >                    大于               x > y
  左             >=                   大于等于            x >= y
  左             ==                   等于               x == y
  左             !=                   不等于             x!= y
  左             &                    按位与             x & y
  左             ^                    按位异或           x ^ y
  左             |                    按位或             x | y
  左             &&                   逻辑与             x && y
  左             ||                   逻辑或             x || y
  右             ? :                  条件表达式         x? y : z
  右             =                    赋值               x = y
  左             *=, /=, %=, +=, -=  乘法赋值            x *= y
  右             throw                 抛出异常           throw expr
  左             ,                    逗号               x, y


 */

// 空语句";"类似python中的pass语句,用于指示一个空语句,可以用来补全代码的结构

// 空块"{}"等价于空语句,用于指示一个空块,可以用来补全代码的结构

/* 悬垂else
 C++规定else与离它最近的尚未匹配的if匹配

 例如:
     if (condition1)  // 你认为else与这个if匹配
         if (condition2)  // 但实际上else与这个if匹配
             statement1;
     else
         statement2;  // 错误,else与if2不匹配,应为if2的else

*/

/*
 switch (ch) {
     case 'a': case 'b':
         statement1;
         break;
 }

 出现了a,b中的任何一个都会执行statement1

 */

/* 传统for循环

 for (initializer; condition; expression) {
     statement;
 }

 for (decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]); ++index)
         s[index] = toupper(s[index]);

 // 多重定义
 for (int i, j = 0; j != i; ++i) {
     statement;
 }

 // 省略for头
 for (; condition; expression) {}

 // 范围for循环
 for (declaration : expression) statement;

 */

/* 跳转语句

 break: 从离它最近的while, do while, for , switch语句,并从这些语句的下一条语句开始继续执行
 continue: 从离它最近的循环语句的下一次迭代开始执行
 goto: 无条件跳转到指定位置的语句
     例如:
	     label:

			  goto label;

 */

// try-catch-throw
/*
 try {
     // 可能产生异常的代码
 }
 catch (exception_type1 e1) {
 	 cout << "捕获到异常1: " << e1.what() << endl;
 }

 // 标准异常
 exception: 基类,所有异常的基类
 runtime_error: 运行时错误,一般是程序逻辑错误
 range_error: 范围错误,一般是数值溢出
 overflow_error: 算术溢出,一般是数值计算结果过大
 underflow_error: 算术下溢出,一般是数值计算结果过小
 logic_error: 逻辑错误,一般是程序逻辑错误
 domain_error: 域错误,一般是逻辑上无效的输入
 invalid_argument: 无效参数,一般是函数调用的参数无效
 length_error: 长度错误,一般是容器的长度超出范围
 out_of_range: 越界错误,一般是容器访问超出范围
 bad_alloc: 内存分配失败,一般是内存不足
 bad_cast: 类型转换失败,一般是dynamic_cast转换失败
 bad_typeid: 运行时类型ID失败,一般是typeid操作失败
 bad_function_call: 函数调用失败,一般是std::function调用失败


 // 异常安全(exception safe)
 // 常规的异常安全性技术

 */

// 局部静态变量
// static局部变量,在函数的生命周期内只初始化一次,在函数的每个实例中都有一份拷贝,可以用来保存函数内的状态信息

// 函数声明
/*

 // 函数声明,声明了一个名为print的函数,该函数接受两个const_iterator作为参数,返回值为空
 void print(vector<int>::const_iterator begin, vector<int>::const_iterator end)

 // 尽量使用常量引用
 string::size_type find_char(string &s, char c, string::size_type &occurs);
 这样在find_char("Hello World", 'o', ctr)这样调用时就会出现错误,因为"Hello World"是常量对象



 */

void print(const char *cp) {
	if (cp)
		while (*cp)
			cout << *cp++;  // 输出并将指针向前移动
}

// 标准库规范
void sprint(const int *beg, const int *end) {
	while (beg!= end)
		cout << *beg++ << endl;  // 输出并将指针向前移动
}

// 数组引用形参
void uprint(int (&arr)[10]) {
	// f(int &arr[10])  // 表示将arr声明为了引用的数组
	// f(int (&arr)[10])  // arr是具有10个整数的整型数组的引用

	for (auto i : arr)
		cout << i << endl;  // 输出数组元素
}

// 可变形参的函数
void func(...) {

}

void func(initializer_list<string> il) {
	for (auto s : il)
		cout << s << endl;  // 输出initializer_list中的元素
}

// 不要返回引用或局部对象
const string &manip() {
	string ret;

	if (!ret.empty()) return ret;  // 错误,返回局部对象,会导致对象在生命周期结束后被释放

	else return "Empty";  // 错误,"Empty"是一个局部临时变量

}

// 列表初始化返回值
vector<string> process() {
    string expected, actual;

	if (expected.empty()) return {};
	else if (expected == actual) return {"functionX", "okay"};
	else return {"functionX", expected, actual};
}

// main 返回值
// EXIT_SUCCESS, EXIT_FAILURE

// 返回数组指针
//typedef int arrT[10];
using arrT = int[10];

arrT *func(int i);  // 返回一个指向含有10个整数的数组的指针

void func() {
	int arr[10];
	int *p1[10];

	int (*p2)[10] = &arr;  // 指向含有10个整数的数组的指针的指针

//	int (*func(int i))[10];

// 尾置返回类型
	auto func(int i) -> int(*)[10];  // 尾置返回类型,返回一个指向含有10个整数的数组的指针的函数指针

	// decltype
	decltype(arr) *p3 = &arr;  // 指向含有10个整数的数组的指针的指针

}

// 函数重载
// 当多个函数有相同的名称,但参数列表不同时,会发生函数重载,编译器会根据参数列表选择最匹配的函数进行调用,但main函数不能被重载
// 重载和const形参
// func(arg);和func(arg*); 等价于 func(const arg)和func(arg* const)
// func(arg&);和func(arg*);不等于func(const arg&)和func(const arg*)

// const_cast和重载
const string &shorter(const string &s1, const string &s2) {
	return s1.size() < s2.size()? s1 : s2;
}
string &shorter(string &s1, string &s2) {
	auto &r = shorter(const_cast<const string&>(s1), const_cast<const string&>(s2));

	return const_cast<string&>(r);

}

string read();
void print(const string &);
void print(double );
void fooBar(int ival) {
	bool read = false;

//	string s = read();  // 新作用域: 隐藏了外层的read()

	void print(int);

//	print("Value: ");  // 错误print(const string&)被隐藏掉了

	print(ival);  // 正确: 当前print(int)可见

	print(3.14);  // 正确: 调用print(double)

}

// 默认实参
void func1(int ival = 0);  // 但是只能在最末尾

// 内联函数
inline double square(int x) { /* ... */ }

// 头文件保护技术
#ifndef MY_HEADER_H
#define MY_HEADER_H

#endif

// assert 预处理宏
#include <cassert>
//assert(condition)

// NDEBUG 预处理宏
// 定义NDEBUG时,assert宏会被忽略,可以用来禁用assert

// __func__ 一个局部静态变量,用来保存当前函数的名字
// __FILE__ 一个字符串常量,用来保存当前源文件的文件名
// __LINE__ 一个整型常量,用来保存当前源文件中的行号
// __DATE__ 一个字符串常量,用来保存当前日期
// __TIME__ 一个字符串常量,用来保存当前时间

// 函数指针形参
// void func(const string &s, bool (*p)(const string &, const string &))

// 类

struct Example {
	std::string name;
	[[nodiscard]] std::string func1() const {  // [[nodiscard]]用于标记一个函数或枚举类的返回不应被忽略
		return name;
	}
	[[nodiscard]] double func2() const;
	Example& returnThis(const Example& other);
};

// this: 指向当前对象的指针,可以通过this指针访问对象的成员变量和成员函数
// 常量成员函数

// 外部定义成员函数
double Example::func2() const {
	if (name.empty())
		return 0.0;
	else
		return 1.0;
}

// 返回this的函数
Example& Example::returnThis(const Example& other) {
	name = other.name;
	return *this;
}

istream &read_(istream &is, Example &item) {
	string name;
	is >> item.name >> name;
	return is;
}

/* 构造函数
 // 合成的默认构造函数

 如果存在类内初始值,则使用该值来初始化成员
 否则,默认初始化该成员

 */
struct Sales_data {
	Sales_data() = default;  // 合成的默认构造函数

	Sales_data(const string &s): bookNo(s) {};  // 构造函数,参数为const string&

	Sales_data(const string &s, unsigned n, double p):
		bookNo(s), units_sold(n), revenue(p * n) {};  // 构造函数,参数为const string&, unsigned, double

	const string &bookNo;   // 成员变量,const修饰,表示该成员只能在构造函数初始化
	unsigned units_sold = 0;  // 成员变量,默认初始化为0
	double revenue = 0.0;  // 成员变量,默认初始化为0.0

	// = default; 该语句的意义是,如果没有其他构造函数,则使用默认构造函数

	// 构造函数初始值列表:
	//    它负责创建一个或多个初始值,每个成员后面紧跟括号/花括号的成员赋初值
    // 在类的外部定义构造函数

};

// 访问控制与封装
class example {
public:  // 公有成员,对所有用户可见
	example() = default;

private:  // 私有成员,对本类可见,对派生类不可见
	int data;
};

// class与struct的区别
// 默认访问权限：
// class的默认成员访问权限是private。这意味着，如果你在class定义中没有明确指定成员的访问权限（如public、protected或private），那么这些成员默认是private的。
// struct的默认成员访问权限是public。如果你没有指定成员的访问权限，它们默认是public的。

// 友元
// 友元关系是一种特定的类间关系，它允许一个类访问另一个类的私有和保护成员。友元关系是一种“间接访问”关系，因为它不要求两个类之间有继承关系。
class A {
	friend A add(const A&, const A&);  // 声明友元函数
	friend istream &read(istream&, A&);  // 声明友元函数
	friend void print(const A&);  // 声明友元函数

public:
	A() = default;
	A(const std::string &s): name(s) {};

	// 函数后面加const表示该函数不会修改类内的成员变量
	// 定义在类内部的函数是自动内联的
	char get() const {return 'A';};  // 隐式内联
	inline char get() const;  // 显式内联

	// 基于const的重载
	A &func(ostream &os) {return *this;}
	const A &func(ostream &os) const {return *this;}


private:
	std::string name;

};

A add(const A& a1, const A& a2);
istream &read(istream&, A&);

// 即使两个类的成员完全一样,这两个类也是不同的类型,A ins1; B ins2 = ins1; 错误: ins1和ins2的类型不同
A ins1;  // 默认初始化
class A ins1;  // 等价的声明

// 类的声明
class B;

class C {
	string name;
	int age;
};

// 但类中有命名是和其它上层可被访问作用域的命名冲突时,会先寻找当前作用域的命名,如果没有找到,才会去上层作用域寻找

// C++11的新标准: 委托构造函数
class D {
public:

	D(int x, string s): age(x), name(s) {};
	D(): D(0, "") {};  // 委托构造函数,调用默认构造函数
	D(int x): D(x, "") {};  // 委托构造函数,调用前一个构造函数
	explicit D(string s): D(0, s) {};  // 委托构造函数,调用前一个构造函数
	// explicit 关键字用于指示构造函数只能用于直接初始化,不能用于隐式转换

private:
	int age;
	string name;

};

class Debug {
public:
	constexpr Debug(bool b = true): hw(b) {}

	void set_io(bool b) {io = b;}

private:
	bool hw;
	bool io;

};

// 类的静态成员
class E {
public:
	static int count;  // 静态成员变量,所有对象共享同一个变量

private:
	static string name;  // 静态成员变量,所有对象共享同一个变量
	static double staticFunc();  // 静态成员函数,所有对象共享同一个函数

};

// C++标准库

/* IO库

 * istream: (输入流)类型,提供输入操作
 * ostream: (输出流)类型,提供输出操作
 * cin: 一个istream对象,从标准输入读取数据
 * cout: 一个ostream对象,向标准输出写入数据
 * cerr: 一个ostream对象,向标准错误输出写入数据
 * >>: 用来从一个istream对象读取输入数据
 * <<: 用来向一个ostream对象写入输出数据
 * getline(): 从一个istream对象读取一行输入数据

 // IO类
 * iostream: (输入/输出流)类型,提供对iostream类型对象的读写操作
     * istream, wistream: 从流读取数据
     * ostream, wostream: 向流写入数据
     * iostream, wiostream: 同时读写流

 * fstream: (文件流)类型,提供对文件的读写操作
     * ifstream, wifstream: 从文件读取数据
     * ofstream, wofstream: 向文件写入数据
     * fstream, wfstream: 同时读写文件

 * sstream: (字符串流)类型,提供对字符串的读写操作
     * istringstream, wistringstream: 从字符串读取数据
     * ostringstream, wostringstream: 向字符串写入数据
     * stringstream, wstringstream: 同时读写字符串

     // 宽字符串支持
     // > 为了支持宽字符串,标准库定义了一组类型和对象来操作wchar_t类型的数据

     * wcin: cin的宽字符版本
     * wcout: cout的宽字符版本
     * wcerr: cerr的宽字符版本

 // NOTE: 我们无效考虑是从哪里读取的数据,也无需考虑需要char还是wchar_t存储,因为通过继承机制实现了.

 // IO对象无拷贝或赋值

 ofstream out1, out2;
 out1 = out2;  // 错误: 不能对流对象赋值
 ofstream print(ofstream);  // 错误: 不能初始化ofstream参数
 out2 = print(out2);  // 错误: 不能拷贝流对象

 // 条件状态
 设'strm'为一种IO类型

 strm::iostate: iostate是一种机器相关的类型,提供了表达条件状态的完整功能
 strm::badbit: 用来指出流已崩溃
 strm::failbit: 用来指出流操作失败
 strm::eofbit: 用来指出流已到达文件尾
 strm::goodbit: 用来指出流处于正常状态
 s.eof(): 若流s的eofbit置位,则返回true
 s.fail(): 若流s的failbit职位,则返回true
 s.bad(): 若流s的badbit职位,则返回true
 s.good(): 若流s的eofbit和failbit职位都不置位,则返回true(或说处于有效状态)
 s.clear(): 重置流s的条件状态,将所有位都清零
 s.clear(flags): 重置流s的条件状态,将指定的位复位位
 s.setstate(flags): 将指定的位置位
 (复位与置位: 置位是将某个位置的位设置为1,复位是将某个位置的位设置为0)
 s.rdstate(): 返回流s的条件状态

 例如我们在期望读取整数的输入流中输入了字符串,就会导致流的failbit置位,此时调用s.fail()会返回true,调用s.rdstate()会返回strm::failbit,调用s.clear()会将流的条件状态重置为strm::goodbit,调用s.clear(strm::failbit)会将流的failbit位复位,调用s.setstate(strm::failbit)会将流的条件状态设置为strm::failbit,调用s.good()会返回false,调用s.eof()会返回false.

 // 记住cin的当前状态
 auto old_state = cin.rdstate();  // 记住cin的当前状态
 cin.clear();  // 使cin有效
 process_input();  // 使用cin
 cin.setstate(oled_state);  // 恢复cin的状态

 // 复位failbit位badbit,保持其他标志位不变
 cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);

 // 管理输出缓存
 os << "Hello World!";  // 文本串可能立即就打印出来,但也可能被输出到缓冲区中
 // 有了缓存机制,程序就可以将程序的多个输出操作组合成单一的系统级写操作,从而提高效率

 // 导致缓存刷新的原因:
     * 程序正常结束: 作为main函数的return操作的一部分,缓冲区会被刷新
     * 缓冲区满: 当缓冲区满时,程序会自动刷新缓冲区
     * 操作符endl: 可以使用操作符endl来刷新缓冲区
     * 调用flush函数: 可以调用flush函数来刷新缓冲区
     * unitbuf操作符: 可以使用操作符unitbuf来设置流的内部状态,来清空缓冲区.对cerr是设置unitbuf的,所以写入cerr的内容都是立即刷新的.
     * 输出流关联: 一个输出流可能关联到另一个输出流.该情况下,但读写被关联的流时,关联到的流的缓冲区会被刷新.
     例如,默认情况下,cin和cerr都关联到cout,因此,读cin或写cerr都会导致cout的缓冲区被刷新.

 // 刷新输出缓冲区
 cout << "hi!" << endl;  // 输出hi和一个换行,然后刷新缓冲区
 cout << "hi!" << flush;  // 输出hi,然后刷新缓冲区,不附加任何额外字符
 cout << "hi!" << ends;  // 输出hi和一个空字符,然后刷新缓冲区

 // unitbuf操作符
 cout << unitbuf;  // 所有输出操作后都会立即刷新缓冲区
 // 任何输出都立即刷新,无缓冲
 cout << nounitbuf;  // 恢复正常的缓冲区操作

 // NOTE: 如果程序崩溃,缓冲区不会被刷新

 // 关联输入输出流
 cin >> ival;  // 导致cout的缓冲区被刷新

 tie: 关联两个流对象,使它们的输入输出操作同步,有两个重载版本
 cin.tie(&cout);  // 使cin和cout同步
 ostream *old_tie = cin.tie(nullptr);  // cin不再与其他流关联
 cin.tie(&cerr);  // 将cin与cerr关联,但并不推荐这样
 cin.tie(old_tie);  // 重建cin和cout间的正常关联

 // 文件输入输出
 ifstream: 从文件读取数据
 ofstream: 向文件写入数据
 fstream: 同时读写文件

 fstream fstrm: 创建一个未绑定的文件流.fstream是头文件中的一个类型
 fstream fstrm: 创建一个fstream,并打开名为s的文件.s可以是string类型,或者是一个指向C风格字符串的指针.这些构造函数都是explicit的.默认的文件模式mode依赖于fstream的类型
 fstream fstrm(s, mode): 打开名为s的文件,并以mode模式打开
 fstrm.open(s): 打开名为s的文件,并将文件与fstrm绑定.s可以是string或C风格字符串指针.mode依赖于fstream的类型
 fstrm.close(): 关闭与fstrm绑定的文件
 fstrm.is_open(): 如果与fstrm绑定的文件打开,则返回true,否则返回false

 // 用fstream代替iostream&
 ifstream input(argv[1]);  // 打开销售记录文件
 ofstream output(argv[2]);  // 打开输出文件
 Sales_data total;  // 总销售数据
 if (read(input, total)) {  // 读取第一条销售记录
     Sales_data trans;  // 单个销售记录
     while (read(input, trans)) {  // 读取剩余的销售记录

     	if (total.isbn()  == trans.isbn()) {  // 检查isbn

     	    total.combine(trans);  // 更新销售总额

     	}
     	else {

     	    print(output, total) << endl;  // 输出总销售数据
     	    total = trans;  // 更新总销售数据

		}

		print(output, total) << endl;  // 打印最后一本书的销售额

     }
     else {
         cerr << "No data?" << endl;  // 出错处理
     }

     // 成员函数open和close
     ifstream in(ifile);  // 构筑一个ifstream并打开给定文件
     ofstream out;  // 输出文件流未与任何文件相关联
     out.open(ifile + ".xxx");  // 打开指定文件
     // 如果打开失败,failbit会被置位,所以进行open成功检查是个好习惯
     if (out)

     in.close();  // 关闭ifstream

	// 文件模式
	    * in: 读模式
	    * out: 写模式
	    * ate: 打开文件时指针指向文件末尾
	    * app: 每次写操作前均先定位到文件末尾
	    * trunc: 截断文件
	    * binary: 以二进制模式打开文件

	// string流
 	    * istringstream: 从字符串读取数据
	    * ostringstream: 向字符串写入数据
	    * stringstream: 同时读写字符串

	    * sstream strm: strm是一个未绑定的stringstream对象
	    * sstream strm(s): 保存string s的一个拷贝。且次构造函数是explicit的
	    * strm.str(): 返回str所保存的string的拷贝
	    * strm.str(s): 将string s拷贝到strm中

 */

// 析构函数
// 析构函数是类的一个特殊成员函数,它负责释放对象占用的资源,在对象被销毁时自动调用.
// 析构函数的声明:
//    ~ClassName()
// 析构函数不能有返回值,不能有参数,不能被重载,不能被const修饰,不能被virtual修饰.

/*

 #include <iostream>
#include <regex>
#include <string>

int main() {
   std::string s = "Hello, world! 123";
   std::regex e ("\\d+");   // 匹配一个或多个数字

   // 使用 std::sregex_iterator 进行迭代，找到所有匹配项
   std::sregex_iterator next(s.begin(), s.end(), e);
   std::sregex_iterator end;

   while (next != end) {
	   std::smatch match = *next;
	   std::string match_str = match.str();
	   std::cout << "Found: " << match_str << '\n';
	   next++;
   }

   return 0;
}

 */

/* 顺序容器

 * vector: 动态数组,支持快速随机访问,在尾部之外的位置插入或删除元素可能很慢
 * deque: 双端队列,支持快速随机访问,在头尾两端插入或删除元素很快
 * list: 双向链表,支持双向顺序访问,在list中任何位置进行插入/删除的操作速度都很块
 * forward_list: 单向链表.只支持单向顺序访问.在链表任何位置进行插入/删除操作速度都很快
 * array: 固定大小数组,支持随机访问,不能添加或删除元素
 * string: 与vector类似的容器,但专门用于保存字符.支持随机访问,在尾部插入/删除元素很快

 // 如果要求随机访问,应使用vector或deque
 // 如果程序有很多小的元素,且空间的额外开销很重要,则不要使用list或forward_list
 // 如果程序要求在头尾位置插入或删除元素,但不会在中间位置进行插入或删除操作,则使用deque
 // 如果程序要求在容器中间插入或删除元素,应使用list或forward_list
 // 如果在读取期间需要向容器中间插入元素,随后需要随机访问
     * 处理数据时可以向vector追加数据,然后使用sort重排容器中的元素
     * 如果必须在中间插入,考虑使用list,在输入完后,将list中的内容拷贝到一个vector中

 * forward_list有专用版本的insert和emplace
 * vector和string不支持push_front和emplace_front
 * c.push_back(t)/emplace_back(args): 在c的尾部创建一个值为t或由args创建的元素
 * c.push_front(t)/emplace_front(args): 在c的头部创建一个值为t或由args创建的元素
 * c.insert(p, t)/emplace(p, args): 在c的位置p之前插入一个值为t或由args创建的元素
 * c.insert(p, n, t): 在c的位置p之前插入n个值为t的元素,返回指向新元素的指针
 * c.insert(p, b, e): 在c的位置p之前插入区间[b, e)中的元素,返回指向新元素的指针
 * c.insert(p, il): 在c的位置p之前插入il中的元素,返回指向新元素的指针

 // 改变容器大小,resize
     list<int> ilist(10, 42);
     ilist.resize(15);  // 将5个值为0的元素添加到ilist的末尾
     ilist.resize(25, -1);  // 将10个值为-1的元素添加到ilist的末尾
     ilist.resize(5);  // 从ilist中删除最后5个元素

 // capacity和size
 size: 指已经保存的元素的数量
 capacity: 指在不分配新内存的情况下,可以保存多少元素

 string.insert(pos, args)
 string.erase(pos, len)
 string.assign(args)
 string.append(args)
 string.replace(range, args)

 string.find(args)
 string.rfind(args)
 string.find_first_of(args)
 string.find_last_of(args)
 string.find_first_not_of(args)
 string.find_last_not_of(args)

 // 数值转换
 stod: 字符串转double
 to_string: 返回值的string表示
 stoi: 字符串转int
 stoll: 字符串转long long
 stoull: 字符串转unsigned long long
 stof: 字符串转float
 stold: 字符串转long double

// 容器适配器
// 容器适配器是一种容器,它包装另一个容器,并提供一个不同的接口,使得容器的行为看起来更像是另一个容器.
// 容器适配器的目的是提供一个统一的接口,使得程序员无需了解底层容器的实现细节,就可以使用容器的各种操作.

 stack<int> stk(deq);  // 构造一个stack,其底层容器是deq
 stack<string, vector<string>> str_stk;
 // 栈适配器
 // 队列适配器


 */

/* 泛型算法
 // 大多算法都定义在algorithm头文件中,numeric中定义了一些数值算法,以及用于容器的算法.

 */

// 谓词
// 谓词是一个函数对象,它接受一个参数,返回一个布尔值.
/*

 // 一元谓词

 // 二元谓词
 bool isShorter(const string &s1, const string &s2) {
     return s1.size() < s2.size();
 }

 sort(words.begin(), words.end(), isShorter)



 */

// lambda表达式
// 具有如下形式: [capture list](parameter list) -> return type { function type }

/*

 * capture list: 捕获列表，用于指定 Lambda表达式可以访问的外部变量，以及是按值还是按引用的方式访问。捕获列表可以为空，表示不访问任何外部变量，也可以使用默认捕获模式 & 或 = 来表示按引用或按值捕获所有外部变量，还可以混合使用具体的变量名和默认捕获模式来指定不同的捕获方式。
 * parameter list: 参数列表，用于表示 Lambda表达式的参数，可以为空，表示没有参数，也可以和普通函数一样指定参数的类型和名称，还可以在 c++14 中使用 auto 关键字来实现泛型参数。
 * return type: 返回值类型，用于指定 Lambda表达式的返回值类型，可以省略，表示由编译器根据函数体推导，也可以使用 -> 符号显式指定，还可以在 c++14 中使用 auto 关键字来实现泛型返回值。
 * function body: 函数体，用于表示 Lambda表达式的具体逻辑，可以是一条语句，也可以是多条语句，还可以在 c++14 中使用 constexpr 来实现编译期计算。

 capture list 示例:
     * [&x] 按引用捕获 x
     * [=] 按值捕获所有外部变量
     * [&, x] 按引用捕获所有外部变量，但 x 按值捕获
     * [this] 按值捕获当前对象的所有成员变量
     * [=, &y] 按值捕获所有外部变量，但 y 按引用捕获
     * 初始值捕获: [z = x + 5]

 */

// auto f = []() { return 42; }
// auto f = [](int x) { return x * x; }
// auto f = [](int x, int y) { return x + y; }
// void f = []() { cout << "Hello, world!" << endl; }
// []() -> int { return 42; }

// 可变lambda
// [&x]() mutable { return ++x; }

// bind函数
// 接受一个可调用对象和一组参数,返回一个新的可调用对象,该对象包装了原可调用对象,并绑定了参数.
// bind(func, arg1, arg2, ...)
// 类似python中的partial函数
// 但是bind函数可以指定位置,使用_1, _2, _3等来表示参数位置
// 如: bind(func, _1, 42)
// 而_n都定义在placeholders命名空间中
// 还可以改变顺序
/*

 auto f = bind(func, a, _2, b, _1);  // 表示将参数第1个参数绑定到第4个,第2个参数绑定到第3个

 // 如果希望bind拷贝参数而不是移动参数,可以使用ref和cref函数


 */

/*

 * 插入迭代器: 这些迭代器被绑定到一个容器上,可以来向容器插入元素
     * back_inserter: 创建一个使用push_back的迭代器
     * front_inserter: 创建一个使用push_front的迭代器
     * inserter: 创建一个使用insert的迭代器,此函数接受第二个参数,这个参数必须是一个指向给定容器的迭代器,元素将被插入给定迭代器所表示的元素之前
 * 流迭代器: 这些迭代器被绑定到输入或输出流上,可以用来遍历所有关联的IO流
     * istream_iterator: 从输入流读取元素
     * ostream_iterator: 向输出流写入元素
     * ostreambuf_iterator: 向输出流写入字符
     * istreambuf_iterator: 从输入流读取字符
     // 懒惰求值: 只有当迭代器被使用时,才会执行IO操作,这可以避免不必要的IO操作,提高效率
 * 反向迭代器: 这些迭代器向后而不是向前移到,除了forward_list之外的标准库容器都有反向迭代器
 * 移到迭代器: 这些专用的迭代器不是拷贝其中的元素,而是移到它们
 * 输入迭代器, 输出迭代器, 前向迭代器, 双向迭代器, 随机访问迭代器: 这些迭代器都可以用来访问容器中的元素,并提供对元素的随机访问.
 * 类迭代器: 这些迭代器被绑定到一个类上,可以用来遍历类的成员变量,并提供对元素的随机访问.

 // 运算方式
 *out, ++out, out++: 引用和移动指针

 */

// 标准库谓词
/*

 * ==: comp
 * <: less
 * <=: less_equal
 *!=: not_equal_to
 * >=: greater_equal
 * >: greater
 * &&: logical_and
 * ||: logical_or
 * !: logical_not
 * ?: conditional
 * *=: multiplies
 * /=: divides
 * %=: modulus
 * +=: plus
 * -=: minus
 * &=: bit_and
 * |=: bit_or
 * ^=: bit_xor
 * <<=: left_shift
 * >>=: right_shift
 * ==: equal_to
 * !=: not_equal_to
 * <: less
 * <=: less_equal
 * >=: greater_equal
 * >: greater
 * &&: logical_and
 * ||: logical_or
 * !: logical_not
 * ?: conditional
 * *=: multiplies
 * /=: divides
 * %=: modulus
 * +=: plus
 * -=: minus
 * &=: bit_and
 * |=: bit_or

 // _if版本算法
 find - find_if
 // 接受一个谓词,返回一个迭代器,指向第一个匹配的元素

 // 是否拷贝
 find_if - find_copy_if
 // 接受一个谓词,一个输入迭代器,一个输出迭代器,拷贝所有匹配的元素到输出迭代器

 */

// splice成员
// 链表数据结构所特有:
// lst.splice(args)或flst.splice_after(args)
// (p, lst2):
// (p, lst2, p2):
// (p, lst2, b, e):

// 关联容器
/*

 # 有序
 * map: 关联数组,保存键值对
 * set: 关键字即值,即只保存关键字的容器
 * multimap: 关键字可以重复出现的map
 * multiset: 关键字可以重复出现的set

 # 无序
 * unordered_map: 哈希表实现的map
 * unordered_set: 哈希表实现的set
 * unordered_multimap: 哈希表实现的multimap
 * unordered_multiset: 哈希表实现的multiset

 // 有序容器的关键字类型
 // 严格弱序: 要求关键字类型支持<=运算符
     * 两个关键字不能同时"小于等于"对方
     * 如果k1<=k2,且k2<=k3,那么k1必须小于等于k3

 // pair类型
 // utility头文件中定义的pair类型,可以用来保存两个不同类型的值

 pair<string, string> anon;  // 保存两个string
 pair<string, size_t> word_count;  // 保存一个string和一个size_t值
 pair<string, vectro<int>> line;  // 保存一个string和一个vector<int>值

 return { arg1.back(), v.back().size()) };  // 列表初始化,返回一个pair<string, size_t>值
 // 或者make_pair函数
 return pair<string, int>(v.back(), v.back().size());  // 早期C++版本必须显式创建pair对象

 * key_type: 关键字类型
 * mapped_type: 值类型
 * value_type: 元素类型,即pair<key_type, mapped_type>

 map<string, size_t> word_count;

 string word;

 while (cin >> word) {

     auto ret = word_count.insert({word, 1});

     if (!ret.second)
         ++ret.first->second;

 }

 // equal_range: 返回一个pair,包含指向具有给定关键字的元素的迭代器,以及指向具有大于该关键字的元素的迭代器

 // 无序容器
 // 桶管理
 # 桶接口
 * c.bucket_count():  正在使用的桶的数量
 * c.max_bucket_count():  最大桶的数量
 * c.bucket_size(n):  桶n中元素的数量
 * c.bucket(k):  关键字k所属的桶

 # 桶迭代
 * local_iterator: 指向当前桶中的元素的迭代器
 * const_local_iterator: 指向当前桶中的元素的常量迭代器
 * c.begin(n):  桶n中的第一个元素的迭代器
 * c.end(n):  桶n中的最后一个元素的迭代器
 * c.cbegin(n):  桶n中的第一个元素的常量迭代器
 * c.cend(n):  桶n中的最后一个元素的常量迭代器

 # 哈希策略
 * c.load_factor():  平均元素数/桶的数量
 * c.max_load_factor():  最大负载因子
 * c.rehash(n):  重新分配内存,使得桶的数量为n,并重哈希所有元素
 * c.reserve(n):  预分配内存,使得桶的数量至少为n,并重哈希所有元素

 */

/* 动态内存

 // new运算符
 // 申请一块内存,并返回指向它的指针
 // delete运算符
 // 释放由new分配的内存

 * NOTE: 如果内存空间耗尽,new运算符会抛出bad_alloc异常

 // shared_ptr和new结合使用
 * shared_ptr<int> p1 = new int(1024);

 */

/* 智能指针

 * shared_ptr: 共享指针,用于管理动态分配的对象,可以自动管理引用计数,并在引用计数为0时释放对象
 * unique_ptr: 独占指针,用于管理动态分配的对象,独占所有权,不支持转移
 * weak_ptr: 弱指针,用于管理shared_ptr,可以用来跟踪shared_ptr的生命周期,但不影响shared_ptr的引用计数

 // shared_ptr和unique_ptr共同支持的操作
 * shared_ptr<T> sp: 空智能指针
 * unique_ptr<T> up: 空智能指针
 * p: 将p用作一个条件判断,若p指向一个对象,则为true
 * *p: 解引用指针,获得它指向的对象
 * p->mem: 访问指针所指向的对象的mem成员
 * p.get(): 返回p中保存的指针
 * swap(p, q): 交换p和q指向的对象

 // shared_ptr特有的操作
 * make_shared<T>(args): 返回一个share_ptr,指向一个动态分配的类型为T的对象,使args初始化此对象
 * shared_ptr<T> p (q): p是shared_ptr q的拷贝: 此操作会递增q的引用计数.q中的指针必须都能被转换为T*
 * p = q: p和q都是shared_ptr, 所保存的指针必须能相互转换.此操作会递减p的引用计数,递增q的引用计算: 若p的引用计数变为0,则将其管理的原内存释放
 * p.unique(): 若p.use_count()为1,返回true: 否则返回false
 * p.use_count(): 返回p的引用计数

 // make_shared函数
 shared_ptr<int> p3 = make_shard<int>(42);
 shared_ptr<string> p4 = make_shared<string>(10, '9');
 shared_ptr<int> p5 = make_shared<int>();  // 空智能指针

 // 引用计数
 // 引用计数是指指向对象的指针的个数,当一个指针指向一个对象时,它的引用计数就加1,当引用计数为0时,对象被释放.

 // NOTE: 每个类都有一个析构函数,并且shared_ptr会自动释放相关联的内存

 // 使用了动态生存期资源的类的原因
 1. 程序不知道自己需要使用多少对象
 2. 程序不知道所需的对象的准确类型
 3. 程序需要在多个对象间共享数据

 //

 */
