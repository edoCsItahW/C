1. 这个版本的“Hello World”代码较为特别，使用了极少见的语法，能够编译并运行：

```cpp
 %:include<iostream>
 int main()
 <%
   std::string val<:1:>;
   val<:0:> = "Hello World";
   std::cout<<*val<<std::endl;
 %>
```

2. 下面的代码能够编译成功：

```cpp
int main() {
  https://www.zhihu.com
  return 0;
}
```

3. 大家都用过这种三元运算符的写法：

```cpp
x = (y < 0) ? 10 : 20;
```
但很少有人使用这样的写法：

```cpp
(a == 0 ? a : b) = 1;
```
它实际上等价于：

```cpp
if (a == 0)
    a = 1;
else
    b = 1;
```

4. 临时类型可以在 `for` 循环中定义并实例化：

```cpp
for(struct { int a; float b; } loop = { 1, 2 }; ...; ...) {
    // ...
}
```

5. `union` 支持模板参数，尽管很少有人使用，但确实可以：

```cpp
template<typename From, typename To>
union union_cast {
    From from;
    To   to;

    union_cast(From from)
        :from(from) { }

    To getTo() const { return to; }
};
```

6. 加号可以将 lambda 表达式转化为函数指针，这个特性了解的人不少：

```cpp
auto f = +[]{};
static_assert(std::is_same<decltype(f), void (*)()>::value);
```
加号还有其他用法，例如将数组转化为指针：

```cpp
template<typename T>
void f(T const& a, T const& b);

int main() {
  int a[2];
  int b[3];
  f(a, b); // 这个编译不过，因为 a 和 b 的长度不同，类型不同
  f(+a, +b); // 这个可以编译通过，都转换为 int* 了
}
```

7. 数组成员变量的默认值初始化只需一个空括号，这个用法非常简单：

```cpp
class clName
{
  clName():a() // 只需一个空括号，全部初始化为默认值
  {}
  int a[10];
};
```

8. 位域也支持模板，但知晓的人更少，毕竟位域本身用的人就不多：

```cpp
template <size_t X, size_t Y>
struct bitfield
{
    char left  : X;
    char right : Y;
};
```

9. 以下「定义」变量的语法中，有些其实是声明了函数，新手容易混淆，许多老手也会看不出来：

```cpp
SomeType t = u;      // 定义对象
SomeType t(u);      // 定义对象
SomeType t();       // 声明函数
SomeType t;         // 定义对象
SomeType t(SomeType(u)); // 声明函数
```

10. 有些人不喜欢 `reinterpret_cast`，只信任 `static_cast`，那么可以这样替代：

```cpp
int64_t var;
// string *str = reinterpret_cast<string*>(&var);
// 用如下方式替代：
string *str = static_cast<string*>(static_cast<void*>(&var));
```