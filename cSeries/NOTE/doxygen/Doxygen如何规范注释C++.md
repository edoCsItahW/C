# Doxygen如何规范注释C++

---

## 简介
Doxygen是一款开源的文档生成工具,它可以从注释中提取代码信息,并生成一份完整的文档。Doxygen可以自动生成文档,包括类、函数、变量、宏、枚举、类型定义、文件、全局变量、全局函数、全局定义等。

Doxygen的注释语法遵循标准的Javadoc语法,因此,熟悉Javadoc的注释语法,就可以很容易上手Doxygen的注释语法。

## 注释风格
Doxygen注释遵循Javadoc注释风格,包括以下几点:

- 注释块以 /** 和 */ 包裹,并以 @ 符号开头。
- 注释块中,每行以 * 开头,并以空格或制表符进行缩进。

## @相关标签

文档中的所有命令都以反斜杠(\)或at符号(@)开头。如果您愿意,可以将下面以反斜杠开头的所有命令替换为以at符号开头的对应命令。
某些命令有一个或多个参数。每个参数都有一定的范围:
如果使用<sharp>大括号,则参数是一个单词。
如果使用(圆)大括号,则参数将一直延伸到找到命令的行的末尾。
如果使用{花括号},则参数将延伸到下一段。段落由空行或节指示符分隔。请注意,{花括号}也用于命令选项,这里的大括号是必需的,只是“普通”字符。起始花括号必须直接跟在命令后面,因此没有空格。
如果除了上述参数说明符外,还使用了\[方]括号,则该参数是可选的,除非它们放在引号之间,在这种情况下,它们是命令参数的强制性部分。

### @addtogroup <名称> [(标题)]
像 \defgroup 一样定义一个组,但与使用相同的 <name> 命令相比,多次不会导致警告,而是一个具有合并文档的组,并在任何命令中找到第一个标题。

title 是可选的,因此此命令还可用于使用如下方式将多个实体添加到现有组:@{@}

```c++
/** \addtogroup mygrp
 *  Additional documentation for group 'mygrp'
 *  @{
 * */

/**
 * A function 
 * */
void func1() {
}

/** Another function */
void func2() {
}

/** @} */
```

### @callgraph
当将此命令放入函数或方法的注释块中并且 HAVE_DOT 设置为 时,Doxygen 将为该函数生成一个调用图(前提是该函数或方法的实现调用了其他记录的函数)。无论 CALL_GRAPH 的值如何,都会生成调用图。YES

### @hidecallgraph
当将此命令放入函数或方法的注释块中时,Doxygen 将不会为该函数生成调用图。无论 CALL_GRAPH 的值如何,都不会生成调用图。

### @showrefby
当将此命令放入函数、方法或变量的注释块中时,Doxygen 将为调用/使用它的函数、方法、变量、记录的函数和方法生成概述。无论 REFERENCED_BY_RELATION 的值如何,都会生成概览。

### @hiderefby
当将此命令放入函数、方法或变量的注释块中时,Doxygen 将不会为调用/使用它的函数、方法或变量生成概述。无论 REFERENCED_BY_RELATION 的值如何,都不会生成概览。

### @showrefs
当将此命令放入函数或方法的注释块中时,Doxygen 将为该函数或调用它的函数和方法生成概述。无论 REFERENCES_RELATION 的值如何,都将生成概览。

### \hiderefs
当将此命令放入函数或方法的注释块中时,Doxygen 将不会为该函数或调用它的函数和方法生成概述。无论 REFERENCES_RELATION 的值如何,都不会生成概览。

### \showinlinesource
当将此命令放入函数、多行宏、枚举或列表初始化变量的注释块中时,Doxygen 将为该成员生成内联源。无论 INLINE_SOURCES 的值如何,都会生成内联源。

### \hideinlinesource
当将此命令放入函数、多行宏、枚举或列表初始化变量的注释块中时,Doxygen 将不会为该成员生成内联源。无论 INLINE_SOURCES 的值如何,都不会生成内联源。

### \includegraph
当将此命令放入文件的注释块中时,Doxygen 将为该文件生成一个包含图。无论 INCLUDE_GRAPH 的值如何,都将生成包含图。

### \hideincludegraph
当将此命令放入文件的注释块中时,Doxygen 不会为该文件生成包含图。无论 INCLUDE_GRAPH 的值如何,都不会生成包含图。

### \includedbygraph
当将此命令放入包含文件的注释块中时,Doxygen 将为该包含文件生成一个包含者图。无论 INCLUDED_BY_GRAPH 的值如何,都将生成 included by 图表。

### \hideincludedbygraph
当将此命令放入包含文件的注释块中时,Doxygen 不会为该包含文件生成包含者图。无论 INCLUDED_BY_GRAPH 的值如何,都不会生成 included by 图。

### \directorygraph
当此命令放入目录的注释块中时(参见 \dir 部分),则 Doxygen 将为该目录生成一个目录图。无论 DIRECTORY_GRAPH 的值如何,都将生成目录图。

### \hidedirectorygraph
当此命令放在目录的注释块中时(参见 \dir 部分),则 Doxygen 不会为该目录生成目录图。无论 DIRECTORY_GRAPH 的值如何,都不会生成目录图。

### \collaborationgraph
当将此命令放入类的注释块中时,Doxygen 将为该类生成协作图。无论 COLLABORATION_GRAPH 的值如何,都将生成协作图。

### \hidecollaborationgraph
当将此命令放入类的注释块中时,Doxygen 将不会为该类生成协作图。无论 COLLABORATION_GRAPH 的值如何,都不会生成协作图。

### \inheritancegraph['{option}']
当将此命令放入类的注释块中时,Doxygen 将为该类生成一个符合 .将生成继承图,符合 ,而不管 CLASS_GRAPH 的值如何。的可能值与可与 CLASS_GRAPH 一起使用的值相同。如果指定了 no,则假定该值。optionoptionoptionoptionYES

### \hideinheritancegraph
当此命令被放入类的注释块中时,Doxygen 将不会为该类生成继承图。无论 CLASS_GRAPH 的值如何,都不会生成继承图。

### \groupgraph
当将此命令放入 \defgroup 命令的注释块中时,Doxygen 将为该组生成一个组依赖关系图。无论 GROUP_GRAPHS 的值如何,都会生成组图。

### \hidegroupgraph
当将此命令放入 \defgroup 命令的注释块中时,Doxygen 不会为该组生成组依赖关系图。无论 GROUP_GRAPHS 的值如何,都不会生成组图。

### \showenum值
当将此命令放入枚举的注释块中时,doxygen 将显示该枚举的指定枚举值,而不管 SHOW_ENUM_VALUES 的值如何。

### \hideenum值
当将此命令放入枚举的注释块中时,无论 SHOW_ENUM_VALUES 的值如何,doxygen 都不会显示该枚举的指定枚举值。

### \qualifier \<label> |“(文字)”

使用此命令,可以向成员和类添加自定义限定符标签。这些标签将在输出中以与自动生成的标签(如 “static”、“inline” 和 “final”) 相同的方式显示。

例如,要表明一个函数仅用于测试目的,可以添加\qualifier test

### \class <名称> [<头文件>] [<头名称>]
指示注释块包含名称为 \<name> 的类的文档。(可选)可以指定头文件和头名称。如果指定了头文件,则 HTML 文档中将包含指向头文件的逐字副本的链接。\<header-name> 参数可用于将类文档中使用的链接名称覆盖为 \<header-file> 以外的内容。如果包含名称不在默认包含路径上(如 <X11/X.h>),这可能很有用。使用 \<header-name> 参数,您还可以通过在名称周围添加引号或尖括号来指定 include 语句的外观。如果只给出名称,则使用尖括号。请注意,最后两个参数也可以使用 \headerfile 命令指定。

例:
```c++
/* 虚拟类 */
class Test {
};

/** @class test class.h "inc/class.h"
 * @brief 这是一个测试类。
 *
 * 有关 Test 类的一些详细信息。
 * */
```

### \concept <名称>
指示注释块包含名称为 \<name> 的 C++20 概念的文档。另请参见 \headerfile 命令以指定用户应包含的 Headers 以使用该概念。

### \def <名称>
指示注释块包含宏的文档。#define

例:
```c++
/** @file define.h 文件
 * @brief testing 定义
 *
 * 这是为了测试 defines 的文档。
 * */

/**
 * @def MAX(x, y)
 * 计算 @a x 和 @a y 的最大值。
 * */

/**
 * @brief 计算其参数 @a x 的绝对值。
 * @param x 输入值。
 * @return @a x 的绝对值。
 * */
#define ABS(x) x > 0 ? x : -x
#define MAX(x,y) x > y ? x : y
#define MIN(x,y) x > y ? y : x
/**< 计算 @a x 和 @a y 的最小值。 */
```

### \defgroup \<name> （组标题）
指示注释块包含类、模块、概念、文件或命名空间的主题的文档。这可用于对元件进行分类，并记录这些类别。您还可以将组用作其他组的成员，从而构建组的层次结构。

\<name> 参数应为单字标识符。

### \dir [<路径片段>]
指示注释块包含目录的文档。“path fragment” 参数应包含目录名称和足够的路径，以便相对于项目中的其他目录是唯一的。STRIP_FROM_PATH 选项确定在完整路径显示在输出中之前从完整路径中剥离的内容。

### \enum <名称>
指示注释块包含名称为 \<name> 的枚举的文档。如果枚举是类的成员，并且文档块位于类定义之外，则还应指定类的作用域。如果注释块位于枚举声明的正前方，则可以省略注释。\enum

注意：
匿名枚举的类型无法记录，但匿名枚举的值可以记录。
例：
```c++
class Enum_Test {
public:
    enum TEnum { Val1, Val2 };

    /** 另一个枚举，带有内联文档 */
    enum AnotherEnum {
        V1, /**< 值 1 */
        V2 /**< 值 2 */
    };
};

/** @class Enum_Test
 * 类描述。
 * */

/** @enum Enum_Test::TEnum
 * 枚举类型的描述。
 * */

/** @var Enum_Test::TEnum Enum_Test::Val1
 * 第一个枚举值的描述。
 * */
```

### \example['{lineno}'] <文件名>
指示注释块包含源代码示例的文档。源文件的名称为 \<file-name>。此文件的内容将包含在文档中，紧跟在注释块中包含的文档之后。如果需要，您可以添加选项以启用示例的行号。所有示例都放在一个列表中。扫描源代码以查找记录的成员和类。如果找到任何名称，则名称将与文档交叉引用。可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定源文件或目录。{lineno}

如果 \<file-name> 本身对于 EXAMPLE_PATH 标记指定的示例文件集不唯一，则可以包含绝对路径的一部分以消除歧义。

如果示例需要多个源文件，则可以使用 \include 命令。

例：
```c++
/** Example_Test类。
 * 有关此课程的更多详细信息。
 * */

class Example_Test {
public:
    /** 示例成员函数。
     * 有关此功能的更多详细信息。
     * */
    void example();
};

void Example_Test::example() {}

/** @example example_test.cpp
 * 这是如何使用 Example_Test 类的示例。
 * 有关此示例的更多详细信息。
 * */
```
其中示例文件如下所示：example_test.cpp
```c++
void main() {
    Example_Test t;
    t.example();
}
```

### \endinternal
此命令将结束以 \internal 命令启动的文档片段。仅当 INTERNAL_DOCS 设置为 时，\internal 和 之间的文本才可见。\endinternalYES

### \extends \<name>
当编程语言本身不支持此概念时（例如 C），此命令可用于手动指示继承关系。

example 目录中的文件显示了如何使用此命令（有关完整文件，另请参阅 \memberof）。manual.c

### \file [<名称>]
指示注释块包含名称为 \<name> 的源文件或头文件的文档。如果文件名本身不是唯一的，则文件名可以包含路径（部分）。如果省略文件名（即后面的行留空），则包含该命令的文档块将属于它所在的文件。\file\file

> [!CAUTION]
> 仅当全局函数、变量、typedef 和枚举所在的文件也已记录或EXTRACT_ALL设置为 .YES

例：
```c++
/** @file file.h
 * 简要的文件描述。
 * 更详细的文件描述。
 * */

/**
 * 全局整数值。
 * 有关此值的更多详细信息。
 * */
extern int globalValue;
```

### \fileinfo['{'option'}']
显示放置此命令的文件名的（部分）。可以是 、 、 、 或 、 、 其中optionnameextensionfilenamedirectoryfull

- name不带扩展名的文件的名称
- extension文件的扩展名
- filename文件名，即 加nameextension
- directory给定文件的目录
- full给定文件的完整路径和文件名。
如果未指定任何选项，则使用 ，除非 FULL_PATH_NAMES 设置为 ，否则使用大小写。filenameYESfull

> [!NOTE]
> 命令 \fileinfo 不能用作 \file 命令的参数

### \lineinfo
显示放置此命令的文件内的行号。

### \fn （函数声明）
指示注释块包含函数的文档（全局或作为类的成员）。仅当注释块未放置在函数声明或定义的前面（或后面）时，才需要此命令。

如果你的注释块在函数声明或定义的前面，那么这个命令可以（为了避免冗余）被省略。

应在命令后单行指定包含参数的完整函数声明，因为参数在行尾结束！\fn

此命令等效于 \var、\typedef 和 \property。

> [!CAUTION]
> 如果不是绝对需要，请不要使用此命令，因为它会导致信息重复，从而导致错误。

例：
```c++
class Fn_Test {
public:
    const char* member(char, int) throw(std::out_of_range);
};

const char* Fn_Test::member(char c, int n) throw(std::out_of_range) {}

/** @class Fn_Test
 * @brief Fn_Test类。
 *
 * 有关Fn_Test的详细信息。
 * */

/** @fn const char *Fn_Test::member(char c, int n)
 * @brief A 成员函数。
 * @param c 字符。
 * @param n 一个整数。
 * @exception std::out_of_range 参数超出范围。
 * @return 一个字符指针。
 * */
```

### \headerfile <头文件> [\<header-name>]
旨在用于 class、struct 或 union 文档，其中文档位于定义前面。此命令的参数与 \class 的第二个和第三个参数相同。\<header-file> 名称是指应用程序应包含的文件，以获取类、结构或联合的定义。\<header-name> 参数可用于将类文档中使用的链接名称覆盖为 \<header-file> 以外的内容。如果包含名称不在默认包含路径上（如 <X11/X.h>），这可能很有用。

使用 \<header-name> 参数，您还可以通过在名称周围添加双引号或尖括号来指定 include 语句的外观。默认情况下，如果只给出名称，则使用尖括号。

如果为 \<header-file> 或 \<header-name> 参数提供了一对双引号，则将使用当前文件（在其中找到该命令），但使用引号。因此，对于文件内带有命令的注释块，以下三个命令是等效的：\headerfiletest.h

    \headerfile test.h "test.h"
    \headerfile test.h ""
    \headerfile ""
要获得尖括号，您无需指定任何内容，但如果您想明确表示，可以使用以下任何一项：

    \headerfile test.h <test.h>
    \headerfile test.h <>
    \headerfile <>
要将默认的 include 表示形式全局反转为本地包含，可以将 FORCE_LOCAL_INCLUDES 设置为 。YES

要完全禁用包含信息，请将 SHOW_HEADERFILE 设置为 。NO

### \hideinitializer
默认情况下，将显示 define 的值和变量的初始值设定项，除非它们的长度超过 30 行。通过将此命令放在 define 或 variable 的 comment 块中，初始化器始终处于隐藏状态。可以通过配置参数 MAX_INITIALIZER_LINES 来更改初始化行的最大数量，默认值为 30。

### \idlexcept <名称>
指示注释块包含名称为 \<name> 的 IDL 异常的文档。

### \implements \<name>
当编程语言本身不支持此概念时（例如 C），此命令可用于手动指示继承关系。

example 目录中的文件显示了如何使用此命令（有关完整文件，另请参阅 \memberof）。manual.c

### \ingroup （<组名> [<组名>]*）
如果命令放置在复合实体 （如类、文件或命名空间） 的注释块中，则它将被添加到由 （s） 标识的组中。对于成员（如 variable、functions、typedef 和 enum），成员将仅添加到一个组中（以避免在成员未记录在其类、命名空间或文件的上下文中，而仅作为组的一部分可见时出现模棱两可的链接目标）。\ingroup<groupname>

### \interface <名称> [<头文件>] [<头名称>]
指示注释块包含名称为 \<name> 的接口的文档。参数等于 \class 命令的参数。

### \internal
此命令将启动仅供内部使用的文档片段。片段自然会在注释块的末尾结束。您还可以使用 \endinternal 命令强制 internal 部分提前结束。

如果命令放在一个部分内（例如参见 \section），则该命令之后的所有小节也被视为内部的。只有同一级别的新部分才会结束被视为 internal 的片段。\internal

您可以在配置文件中使用 INTERNAL_DOCS 来显示或隐藏 （） 内部文档。YESNO

### \mainpage [（标题）]

如果将命令放置在注释块中，则该块用于自定义索引页（在 HTML 中）或第一章（在 {\LaTeX}中）。\mainpage

title 参数是可选的，它替换了 Doxygen 通常生成的默认标题。如果您不需要任何标题，则可以指定为 的参数。notitle\mainpage

下面是一个示例：
```c++
/** @mainpage My Personal Index Page
 *
 * @section intro_sec Introduction
 *
 * This is the introduction.
 *
 * @section install_sec Installation
 *
 * @subsection step1 Step 1: Opening the box
 *
 * etc...
 * */
```
您可以使用以下方法引用主页： .\ref index

### \memberof <名称>
此命令以类似于 \relate 的方式使函数成为类的成员，只有使用此命令，函数才表示为类的真实成员。当编程语言本身不支持成员函数的概念（例如 C）时，这可能很有用。

也可以将此命令与 \public、\protected 或 \private 一起使用。

例：
example 目录中的文件显示了如何使用此命令：manual.c
```c++
/**
 * @file manual.c
 * */

typedef struct Object Object; //!< 对象类型
typedef struct Vehicle Vehicle; //!< 车辆类型
typedef struct Car Car; //!< 汽车类型
typedef struct Truck Truck;  //!< 卡车类型

/**
 * 基对象类。
 * */
struct Object {
    int ref; //!< @private 引用计数。
};

/**
 * 将对象引用计数增加 1。
 * @public @memberof Object
 * */
static Object* objRef(Object* obj);

/**
 * 将对象引用计数递减 1。
 * @public @memberof Object
 * */
static Object* objUnref(Object* obj);

/**
 * 车辆类别。
 * @extends 对象
 * */
struct Vehicle {
    Object base;  //!< @protected 基类。
};


/**
 * 启动车辆。
 * @public @memberof Vehicle
 * */
void vehicleStart(Vehicle* obj);


/**
 * 停止车辆。
 * @public @memberof Vehicle
 * */
void vehicleStop(Vehicle* obj);


/**
 * 汽车类。
 * @extends Vehicle
 * */
struct Car {
  Vehicle base;  //!< @protected 基类。
};


/**
 * 卡车类。
 * @extends Vehicle
 * */
struct Truck {
    Vehicle base;  //!< @protected 基类。
};


/**
 * 主要功能。
 *
 * 参考 vehicleStart(), objRef(), objUnref()。
 * */
int main(void) {
  Car c;
  vehicleStart((Vehicle*) &c);
}
```

### \module <名称>
指示注释块包含名称为 <name> 的 C++20 模块的文档。

### \name [（标题）]
此命令将注释块转换为成员组的标头定义。注释块后面应跟一个 ... 块。@{@}

### \namespace <名称>
指示注释块包含名称为 <name> 的命名空间的文档。

### \nosubgrouping
此命令可以放在类的文档中。它可以与成员分组结合使用，以避免 Doxygen 将成员组作为 Public/Protected/Private/...部分。

### \overload [（函数声明）]
此命令可用于为重载成员函数生成以下标准文本：

> 这是一个重载成员函数，为方便起见而提供。它与上述函数的不同仅在于它接受的参数。

如果重载成员函数的文档不在函数声明或定义的前面，则应使用可选参数来指定重载函数的正确声明。当然，当命令位于重载成员函数的正前方并且使用了 optional 参数时，这也应该是重载函数的正确声明。\overload

文档块内的任何其他文档都将附加到生成的消息之后。

注 1：
    您有责任确保确实有一个较早记录的成员被这个成员重载。为防止该文档对文档重新排序，在这种情况下，您应该将 SORT_MEMBER_DOCS 设置为 。NO
注 2：
   注释块中只能存在一个命令。\overload
例：
```c++
class Overload_Test {
public:
    void drawRect(int, int, int, int);
    void drawRect(const Rect &r);
};

void Overload_Test::d rawRect(int x, int y, int w, int h) {}
void Overload_Test::d rawRect(const Rect &r) {}

/** @class Overload_Test
 * @brief 简短的描述。
 *
 * 更多文本。
 * */

/** @fn void Overload_Test::d rawRect(int x, int y, int w, int h)
 * 此命令在 (@a x , @a y )， 处绘制一个左上角的矩形
 * 宽度 @a w 和高度 @a h。
 * */

/**
 * @overload void Overload_Test::d rawRect(const Rect &r)
 * */
```

### \package <名称>
指示注释块包含名称为 <name> 的 Java 包的文档。

### \page <name> （标题）
指示注释块包含与某个特定类、文件或成员没有直接关系的文档。HTML 生成器将创建一个包含文档的页面。生成器在 {\LaTeX} 'Page documentation' 一章中开始一个新的部分。

例：
```c++
/** @page page1 文档页面
 * @tableofcontents
 * 前导文本。
 * @section sec 示例部分
 * 本页包含小节 @ref subsection1 和 @ref subsection2。
 * 有关更多信息，请参见 page @ref page2。
 * @subsection subsection1 第一小节
 * 文本。
 * @subsection subsection2 第二小节
 * 更多文本。
 * */

/** @page page2 另一页
 * 更多信息。
 * */
```

注意：
<name> 参数由字母和数字的组合组成。如果您希望在 <name> 参数中使用大写字母（例如 ）或混合大小写字母（例如 ），则应将 CASE_SENSE_NAMES 设置为 .但是，仅当您的文件系统区分大小写时，才建议这样做。否则（为了更好的可移植性），您应该在对页面的所有引用中使用所有小写字母（例如 <name> 。MYPAGE1MyPage1YESmypage1

### \private
表示 comment 块记录的成员是私有的，即只能由同一类中的其他成员访问。

请注意，Doxygen 会自动检测面向对象语言中成员的保护级别。此命令仅在语言本身不支持保护级别概念（例如 C、PHP 4）时使用。

要以类似于 C++ 中的 “private：” 类标记的方式开始私有成员部分，请使用 \privatesection。

### \privatesection
以类似于 C++ 中的 “private：” 类标记的方式开始私有成员部分。表示 comment 块记录的成员是私有的，即只能由同一类中的其他成员访问。

### \property (qualified property name)
指示注释块包含属性（全局或作为类的成员）的文档。此命令等效于 \fn、\typedef 和 \var。

### \protected
以类似于 C++ 中的 “protected：” 类标记的方式开始受保护成员的部分。表示 comment 块记录的成员受到保护，即只能由相同类或派生类中的其他成员访问。

### \public
表示 comment 块记录的成员是 public，即可以被任何其他类或函数访问。

请注意，Doxygen 会自动检测面向对象语言中成员的保护级别。此命令仅在语言本身不支持保护级别概念（例如 C、PHP 4）时使用。

要以类似于 C++ 中的 “public：” 类标记的方式开始公共成员部分，请使用 \publicsection。

### \publicsection
以类似于 C++ 中的 “public：” 类标记的方式开始公共成员部分。表示 comment 块记录的成员是 public，即可以被任何其他类或函数访问。

### \pure
指示 comment 块记录的成员是纯虚拟的，即它是抽象的，并且没有与之关联的实现。

此命令仅在语言本身不支持纯虚方法的概念（例如 C、PHP 4）时使用。

### \relate <名称>
此命令可用于非成员函数 <name> 的文档。它将函数放在类文档的 'related function' 部分。此命令可用于记录与某个类强耦合的非友元函数。它消除了必须记录文件的需要，但仅适用于函数。

例：
```c++
/**
 * 一个 String 类。
 * */

class String {
    friend int strcmp(const String&, const String&);
};

/**
 * 比较两个字符串。
 * */
int strcmp(const String& s1, const String& s2) {}

/** @relate 字符串
 * 字符串调试函数。
 * */
void stringDebug() {}
```

### \related <名称>
等价于 \relations

### \relatesalso <name>
此命令可用于非成员函数 <name> 的文档。它将函数放在类文档的 'related function' 部分，并将其保留在其正常的文件文档位置。此命令可用于记录与某个类强耦合的非友元函数。它仅适用于函数。

### \relatedalso <name>
等价于 \relatesalso

### \showinitializer
默认情况下，仅当 define 的值和变量的初始值设定项的长度小于 30 行时，才会显示它们。通过将此命令放在 define 或 variable 的 comment 块中，将无条件地显示初始化器。可以通过配置参数 MAX_INITIALIZER_LINES 来更改初始化行的最大数量，默认值为 30。

### \static
指示注释块记录的成员是静态的，即它适用于类，而不是类的实例。

此命令仅在语言本身不支持静态方法的概念（例如 C）时使用。

### \struct <名称> [<头文件>] [<头名称>]
指示注释块包含名称为 <name> 的结构的文档。参数等于 \class 命令的参数。

### \typedef （typedef 声明）
指示注释块包含 typedef 的文档（全局或作为类的成员）。此命令等效于 \fn、\property 和 \var。

### \union <名称> [<头文件>] [<头名称>]
指示注释块包含名称为 <name> 的联合的文档。参数等于 \class 命令的参数。

### \var （变量声明）
指示注释块包含变量或枚举值（全局值或作为类的成员）的文档。此命令等效于 \fn、\property 和 \typedef。

### \vhdlflow [（流程图的标题）]
这是一个 VHDL 特定的命令，可以放在一个进程的文档中，以生成该进程中 logic 的流程图。（可选）可以指定流程图的标题。

> [!NOTE]
> 目前，流程图将仅显示在 HTML 输出中。

### \weakgroup <名称> [（title）]
可以像 \addtogroup 一样使用，但在解决冲突的分组定义时优先级较低。

### \attention { 注意文本 }
开始一个段落，其中可能会输入需要注意的消息。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。当遇到空行或某些其他分段命令时，命令结束。\attention\attention

### \author { 作者列表 }
开始一个段落，可在其中输入一个或多个作者姓名。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个作者描述将开始一个新行。或者，一个命令可能会提及多个作者。当遇到空行或某些其他分段命令时，命令结束。\author\author\author

例：
```c++
/**
 * @brief     相当不错的课程。
 * @details   这个类用于演示许多 section 命令。
 * @author    John Doe
 * @author    Jan Doe
 * @version   4.1a
 * @date      1990-2011
 * @pre       首先初始化系统。
 * @bug       删除此类的对象时，并非所有内存都会被释放。
 * @warning   使用不当可能会导致您的应用程序崩溃
 * @copyright GNU 公共许可证。
 * */
class SomeNiceClass {};
```

### \authors { 作者列表 }
等效于 \author。

### \brief { 简要描述 }
开始一个用作简要说明的段落。对于类和文件，简要描述将在列表和文档页面的开头使用。对于类和文件成员，简要说明将放在成员的声明中，并添加到详细说明的前面。简短的描述可能跨越几行（尽管建议保持简短！当遇到空行或其他分段命令时，简要说明结束。如果存在多个命令，则它们将被联接。有关示例，请参阅 section \author 。\brief

与 \short 同义。

### \bug { 错误描述 }
开始一个段落，其中可能会报告一个或多个 Bug。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个 bug 描述都将从新行开始。或者，一个命令可能会提到多个 bug。当遇到空行或某些其他分段命令时，命令结束。有关示例，请参阅 section \author 。\bug\bug\bug

描述还会将一个项目添加到单独的 Bug 列表中，并且描述的两个实例将被交叉引用。Bug 列表中的每个项目前面都有一个标题，指示该项目的来源。

可以通过将 Bug 列表和相应的条目设置为 GENERATE_BUGLIST 来禁用 。NO

### \cond [（节标签）]
开始一个条件部分，该部分以相应的 \endcond 命令结尾，该命令通常位于另一个注释块中。这对命令的主要目的是（有条件地）将文件的一部分排除在处理之外（在旧版本的 Doxygen 中，这只能使用 C 预处理器命令来实现）。

可以通过将其 section 标签添加到 ENABLED_SECTIONS 配置选项来包含 和 \endcond 之间的部分。如果省略了 section 标签，则该 section 将被无条件地排除在处理之外。部分标签可以是部分标签、圆括号、&& （AND）、||（OR） 和 ！（不是）。如果使用表达式，则需要将其括在圆括号中，即 .\cond\cond (!LABEL1 && LABEL2)

对于注释块中的条件部分，应使用 \if ...\endif 块。当使用且条件不满足时，当前注释块将结束，直到匹配的 \endcond 之前的所有内容都被删除，并在其中启动一个新的命令块。\cond

条件部分可以嵌套。在这种情况下，仅当包含嵌套部分及其包含部分时，才会显示嵌套部分。

下面是一个显示命令操作的示例：
```c++
/** 一个接口 */
class Intf {
public:
    /** 一个方法 */
    virtual void func() = 0;

    /// @cond TEST

    /** 一个用来测试的方法 */
    virtual void test() = 0;

    /// @endcond
};

/// @cond DEV
/**
 * 接口的实现。
 * */
class Implementation : public Intf {
public:
   void func();

   /// @cond TEST
   void test();
   /// @endcond

   /// @cond
   /** 这个方法已经废弃，不在文档中显示。
    * */
   void obsolete();
   /// @endcond
};

/// @endcond
```

输出会有所不同，具体取决于 ENABLED_SECTIONS 是否包含 ，或者TESTDEV

### \copyright { 版权说明 }
开始一个段落，可在其中描述实体的版权。此段落将缩进。段落的文本没有特殊的内部结构。有关示例，请参阅 section \author 。

### \date { 日期描述 }
开始一个段落，其中可以输入一个或多个日期。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个日期描述都将从新行开始。或者，一个命令可以提及多个日期。当遇到空行或某些其他分段命令时，命令结束。有关示例，请参阅 section \author 。\date\date\date

### \showdate “<format>” [ <date_time> ]
根据给定的 <format> 和 <date_time> 显示日期和时间。其中 <format> 是一个字符串，其中以下标记具有特殊含义：

| 法典  | 描述                               |
|-----|----------------------------------|
| %y	 | 不带世纪的年份，作为填充零的十进制数。              |
| %Y	 | 年份，以十进制数表示世纪。                    |
| %m	 | Month 作为填充零的十进制数。                |
| %-m | 	以十进制数表示的月份。                     |
| %b	 | Month 作为区域设置的缩写名称。               |
| %B	 | Month 作为区域设置的全名。                 |
| %d	 | 以填充零的十进制数表示的月份中的日期。              |
| %-d | 	以十进制数表示的月份中的日期。                 |
| %u	 | 工作日为十进制数 （1-7），其中 Monday 为 1。    |
| %w	 | 工作日以十进制数 （0-6） 表示，其中 Sunday 为 0。 |
| %a	 | Weekday 作为区域设置的缩写名称。             |
| %A	 | Weekday 作为区域设置的全名。               |
|     |                                  |
| %H	 | 小时 （24 小时制） 作为填充零的十进制数。          |
| %-H | 	小时 （24 小时制） 作为十进制数。             |
| %我	 | Hour （12 小时制） 作为填充零的十进制数。        |
| %-我 | 	小时（12 小时制）表示十进制数。               |
| %M	 | Minute 作为填充零的十进制数。               |
| %-M | 	Minute 表示为十进制数。                 |
| %S	 | Second 作为填充零的十进制数。               |
| %-S | 	second 作为十进制数。                  |
| %p	 | Locale 相当于 AM 或 PM。              |
|     |                                  |
| %%	 | % 字符。                            |
请注意，<format> 必须位于双引号之间。

如果指定了 <date_time>，则它必须具有以下表示形式：

* optional 其中 is：datedate
   * 4 位数字代表年份
   * 减号
   * 月份的 1 位或 2 位数字
   * 减号
   * 日期的 1 位或 2 位数字
* optional 其中 is：timetime
   * 空白
   * 1 位或 2 位数字表示小时
   * 冒号
   * 1 位或 2 位数字表示分钟
   * 当格式包含 %S 或 %-S 时
      * 冒号
      * 2 位数字表示秒
      如果未指定<date_time>，则使用当前日期和时间。

下面是一个示例：

    - \showdate “%A %d-%m-%Y” 2015-3-14
    - \showdate “%a %d-%m-%y” 2015-3-14
    - \showdate “%-m.%d%y” 2015-3-14
    - \showdate “%A %d-%m-%Y %H：%M：%S” 2015-3-14 03：04：15
    - \showdate “%A %d-%m-%Y %H：%M” 2015-3-14 03：04
如果这会导致：OUTPUT_LANGUAGE=english

* 星期六 14-03-2015
* 周六 14-03-15
* 3.1415
* 星期六 14-03-15 03：04：15
* 星期六 14-03-15 03：04
如果这会导致：OUTPUT_LANGUAGE=dutch
* zaterdag 14-03-15
* ZA 2015 年 3 月 14 日
* 3.1415
* zaterdag 14-03-15 03：04：15
* zaterdag 14-03-15 03：04

### \deprecated { 描述 }
开始一个段落，指示此文档块属于已弃用的实体。可用于描述替代品、预期寿命等。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个弃用描述都将从新行开始。当遇到空行或某些其他分段命令时，命令结束。\deprecated\deprecated

描述还会将项目添加到单独的 Deprecated 列表中，并且描述的两个实例将交叉引用。Deprecated （已弃用） 列表中的每个项目前面都有一个标题，指示该项目的来源。

可以通过将 GENERATE_DEPRECATEDLIST 设置为 来禁用 Deprecated 列表和相应的条目。NO

### \details { 详细说明 }
就像 \brief 开始一个简短的描述，开始详细的描述。您也可以开始一个新段落（空行），然后不需要该命令。\details\details

### \noop （ 要忽略的文本 ）
直到行尾的所有文本（包括命令）都将被忽略。该命令最常与 ALIASES 结合使用，以忽略其他处理工具中存在的不支持的命令。

### \raisewarning （ 显示为警告的文本 ）
直到行尾的所有文本（不包括命令）实际上都显示为文档警告。文本 （包括命令） 将从输出中删除。该命令最常与 ALIASES 结合使用，以显示特定警告。

例:

    \raisewarning My specific warning
    
    \warnNoDoc
    
    \warnNoDoc{My specific warning}
与 ： 一起将导致：

    ALIASES  = warnNoDoc="\raisewarning Missing documentation"
    ALIASES += warnNoDoc{1}="\raisewarning Incomplete documentation: \1"
    ex_1.md:1: warning: My specific warning
    ex_1.md:3: warning: Missing documentation
    ex_1.md:5: warning: Incomplete documentation: My specific warning

### else
如果未启用上一个条件部分，则启动条件部分。上一节应该以 \if、\ifnot 或 \elseif 命令开始。

### \elseif （节标签）
如果上一个部分未启用，则启动条件文档部分。默认情况下，条件部分处于禁用状态。要启用它，您必须将 section-label 放在配置文件中的 ENABLED_SECTIONS 标签之后。部分标签可以是部分名称、圆括号、&& （AND）、||（OR） 和 ！（不是）。条件块可以嵌套。仅当所有封闭部分都已启用时，才会启用嵌套部分。

### \endcond
结束由 \cond 开始的条件节。

### endif
结束以 \if 或 \ifnot 开头的条件部分：对于每个 \if 或 \ifnot，后面必须跟着一个且只有一个匹配的 \endif。

### \exception <exception-object> { 异常描述 }
为名称为 <exception-object> 的异常对象启动异常描述。后跟异常的描述。不检查异常对象是否存在。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个异常描述都将从新行开始。当遇到空行或其他一些分段命令时，描述结束。有关示例，请参见 section \fn 。\exception\exception

### \if （节标签）
启动条件文档部分。该部分以匹配的 \endif 命令结束。默认情况下，条件部分处于禁用状态。要启用它，您必须将 section-label 放在配置文件中的 ENABLED_SECTIONS 标签之后。

部分标签可以是部分名称、圆括号、&& （AND）、||（OR） 和 ！（不是）。如果使用表达式，则需要将其括在圆括号中，即 .\if (!LABEL1 && LABEL2)

条件块可以嵌套。仅当所有封闭部分都已启用时，才会启用嵌套部分。

和相应的 \endif 必须位于同一个注释块中。当条件块需要跨越多个注释块时，必须使用 \cond ...\endcond 的\if

例：
```c++
/** 无条件展示的文本
 *  @if Cond1
 *    仅当Cond1设置时包含.
 *  @endif
 *  @if Cond2
 *    仅当Cond2设置时包含.
 *    @if Cond3
 *      仅当Cond2和Cond3都设置时包含.
 *    @endif
 *    更多文本
 *  @endif
 *  无条件文本
 * */
```
您还可以在别名中使用条件命令。要用两种语言记录一个类，例如，你可以使用：

示例 2：
```c++
/** @english
 * This is English.
 * @endenglish
 * @dutch
 * Dit is Nederlands.
 * @enddutch
 * */
class Example {};
```
其中，配置文件中定义了以下别名：

    ALIASES  = "english=@if english" \
    "endenglish=@endif" \
    "dutch=@if dutch" \
    "enddutch=@endif"
和 ENABLED_SECTIONS 可用于启用 OR 。englishdutch

### \ifnot （节标签）
启动条件文档部分。该部分以匹配的 \endif 命令结束。默认情况下，此条件部分处于启用状态。要禁用它，您必须将 section-label 放在配置文件中的 ENABLED_SECTIONS 标签之后。部分标签可以是部分名称、圆括号、&& （AND）、||（OR） 和 ！（不是）。

### \important { 重要文本 }
开始一个段落，其中可以输入需要 important 的消息。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。当遇到空行或某些其他分段命令时，命令结束。\important\important

### \invariant { 不变量的描述 }
开始一个段落，其中可以描述实体的不变量。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个固定条件描述都将从新行开始。或者，一个命令可能会提及多个不变量。当遇到空行或某些其他分段命令时，命令结束。\invariant\invariant\invariant

### \note { 文本 }
开始一个段落，可在其中输入注释。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个注释描述都将从新行开始。或者，一个命令可能会提及多个注释。当遇到空行或某些其他分段命令时，命令结束。有关示例，请参见 section \par 。\note\note\note

### \par [（段落标题）] { 段落 }
如果给出了段落标题，则此命令以用户定义的标题开始段落。标题一直延伸到行尾。命令后面的段落将缩进。

如果未给出段落标题，则此命令将开始一个新段落。这也可以在其他段落命令（如 \param 或 \warning）中工作，而无需结束该命令。

段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。当遇到空行或某些其他分段命令时，命令结束。\par

例：
```c++
/** @class Par_Test
 * 普通文本。
 *
 * @par 用户定义的段落：
 * 段落内容。
 *
 * @par
 * 同一标题下的新段落。
 *
 * @note
 * 本说明由两段组成。
 * 这是第一段。
 *
 * @par
 * 这是第二段。
 *
 * 更普通的文本。
 * */
class Par_Test {};
```

### \param[\<dir>] <parameter-name> { 参数描述 }
使用名称 <parameter-name> 启动函数参数的参数描述，后跟参数说明。检查参数是否存在，如果此（或任何其他）参数的文档缺失或不存在于函数声明或定义中，则会发出警告。

该命令具有一个可选属性 \<dir>，用于指定参数的方向。可能的值为 “[in]”、“[out]” 和 “[in，out]”;请注意此描述中的 [square] 括号。对于双向值，可以按任意顺序指定 “in” 和 “out” 方向，它们可以完全书写，也可以用逗号 （） 或空格分隔。这意味着，例如，值 “[outin]” 或 “[in out]” 也是有效的。请注意，也可以在 command 和 \<dir> 之间放置空格。当参数既是 input 又是 output 时，[in，out] 用作属性。以下是该函数的示例\param,memcpy:

```c++
/**
 * 将字节从源内存区域复制到目标内存区域，
 * 两个区域不能重叠。
 * @param[out] dest 要复制到的内存区域。
 * @param[in] src 要从中复制的内存区域。
 * @param[in] n 要复制的字节数
 * */
void memcpy(void *dest, const void *src, size_t n);
```
参数描述是一个没有特殊内部结构的段落。所有视觉增强命令都可以在段落内使用。

多个相邻的命令将合并为一个段落。每个参数描述都将从新行开始。当遇到空行或其他一些分段命令时，描述结束。有关示例，请参见 section \fn 。\param\param

请注意，您还可以使用逗号分隔列表通过单个命令记录多个参数。下面是一个示例：\param
```c++
/** 设置位置。
 * @param x，y，z 3D 空间中位置的坐标。
 * */
void setPosition(double x, double y, double z, double t) {}
```

### \parblock
对于需要单个段落作为参数的命令（例如 \par、\param 和 \warning），\parblock 命令允许开始涵盖多个段落的描述，然后以 \endparblock 结束。

例：
```c++
/** 描述由两段组成的param命令示例
 * @param p
 * @parblock
 * 参数描述的第一段。
 *
 * 参数描述的第二段。
 * @endparblock
 * 评论块的其余部分继续。
 * */
```
请注意，该命令也可能直接出现在 \param 的第一个参数之后。\parblock

### \endparblock
这将结束以 \parblock 开头的段落块。

### \tparam <template-parameter-name> { 描述 }
使用名称 <template-parameter-name> 启动类或函数模板参数的模板参数，后跟模板参数的说明。

否则类似于 \param。

### \post { 后置条件的描述 }
开始一个段落，可在其中描述实体的后置条件。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个后置条件都将从新行开始。或者，一个命令可以提到几个 postcondition。当遇到空行或某些其他分段命令时，命令结束。\post\post\post

### \pre { 前提条件的描述 }
开始一个段落，其中可以描述实体的前提条件。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个前提条件都将从新行开始。或者，一个命令可以提及多个前提条件。当遇到空行或某些其他分段命令时，命令结束。\pre\pre\pre

### \remark { 备注文本 }
开始一个段落，可在其中输入一个或多个备注。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个评论都将从新行开始。或者，一个命令可能会提及多个备注。当遇到空行或某些其他分段命令时，命令结束。\remark\remark\remark

### \remarks { 备注文本 }
等同于 \remark。

### \result { 结果值的描述 }
相当于 \return 。

### \return { 返回值描述 }
启动函数的返回值描述。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。当遇到空行或其他一些分段命令时，描述结束。有关示例，请参见 section \fn 。\return\return

### \returns { 返回值的描述 }
相当于 \return 。

### \retval <返回值> { 描述 }
以 name <return value> 开始函数的返回值的描述，后跟返回值的描述。构成说明的段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个返回值描述都将从新行开始。当遇到空行或其他一些分段命令时，描述结束。\retval\retval

### \sa { 引用 }
在其中可以指定对类、函数、方法、变量、文件或 URL 的一个或多个交叉引用的段落。由 either 或 连接的两个名称被理解为引用一个类及其成员之一。可以通过在方法名称后包含带括号的参数类型列表来选择多个重载方法或构造函数之一。::#

与 \see 同义。

### \see { 参考资料 }
等效于 \sa。引入是为了与 Javadoc 兼容。

### \short { 简短描述 }
相当于 \brief 。

### \since { 文本 }
此命令可用于指定实体何时（版本或时间）可用。下面的段落没有任何特殊的内部结构。所有视觉增强命令都可以在段落内使用。当遇到空行或其他一些分段命令时，描述结束。\since\since

### \test { 描述测试用例的段落 }
开始一个段落，其中可以描述一个或多个测试用例。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个测试用例描述都将从新行开始。或者，一个命令可能会提及多个测试用例。当遇到空行或某些其他分段命令时，命令结束。\test\test\test

描述还会将一个项目添加到单独的 Test 列表中，并且描述的两个实例将被交叉引用。Test （测试） 列表中的每个项目前面都有一个标题，指示该项目的来源。

通过将 GENERATE_TESTLIST 设置为 ，可以禁用 Test 列表和相应的条目。NO

### \throw <exception-object> { 异常描述 }
同义词 \exception。

注意：
命令 \throws 是此命令的同义词。

### \throws <exception-object> { 异常描述 }
相当于 \throw 。

### \todo { 描述要做什么的段落 }
开始描述一个或多个 todo 项的段落。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个 todo 描述都将从新行开始。或者，一个命令可能会提到几个 todo 描述。当遇到空行或某些其他分段命令时，命令结束。\todo\todo\todo

描述还会将一个项目添加到单独的 Todo 列表中，并且描述的两个实例将被交叉引用。Todo 列表中的每个项目前面都有一个标题，指示该项目的来源。

可以通过将 GENERATE_TODOLIST 设置为 来禁用 Todo 列表和相应的条目。NO

### \version { 版本号 }
开始一个段落，其中可以输入一个或多个版本字符串。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个版本描述都将从新行开始。或者，一个命令可能会提及多个版本字符串。当遇到空行或其他一些分段命令时， \version 命令结束。有关示例，请参阅 section \author 。\version\version

### \warning { warning message }
开始一个段落，其中可以输入一条或多条警告消息。该段落将缩进。段落的文本没有特殊的内部结构。所有视觉增强命令都可以在段落内使用。多个相邻的命令将合并为一个段落。每个警告描述都将从新行开始。或者，一个命令可能会提及多个警告。当遇到空行或某些其他分段命令时，命令结束。有关示例，请参阅 section \author 。\warning\warning\warning

### \xrefitem <键> “标题” “列表标题” { 文本 }
此命令是 \todo 和 \bug 等命令的泛化。它可用于创建用户定义的文本部分，这些文本部分在发生位置和将生成的相关页面之间自动交叉引用。在相关页面上，将收集相同类型的所有部分。

第一个参数 <key> 是唯一表示节类型的标识符。第二个参数是一个带引号的字符串，表示作为第四个参数传递的文本所在的部分的标题。第三个参数 （list title） 用作相关页面的标题，该页面包含具有相同键的所有项目。第二个和第三个 string 参数不能包含换行符。键 、 和 是预定义的。"todo""test""bug""deprecated"

要了解如何使用该命令及其效果，请考虑 todo 列表，该列表（对于英语输出）可以看作是命令的别名\xrefitem

    \xrefitem todo "Todo" "Todo List"
由于对每个部分重复命令的前三个参数非常繁琐且容易出错，因此该命令应与配置文件中的 ALIASES 选项结合使用。例如，要定义 new command ，应在配置文件中添加以下行：\reminder

    ALIASES += "reminder=\xrefitem reminders \"Reminder\" \"Reminders\""
请注意命令的第二个和第三个参数使用了转义引号。\xrefitem

如果参数 “（heading）” 为空字符串，则不会生成标题。当与 \page 命令结合使用时，这可能很有用，例如
```c++
/** @page my_errors My Errors
 * @brief Errors page
 *
 * Errors page contents.
 * */

/** @error ERROR 101: in case a file can not be opened.
 * Check about file system read/write access. */
#define MY_ERR_CANNOT_OPEN_FILE                   101

/** @error ERROR 102: in case a file can not be closed.
 * Check about file system read/write access. */
#define MY_ERR_CANNOT_CLOSE_FILE                  102
```
定义为\error

    ALIASES += "error=\xrefitem my_errors \"\" \"\"" 

### \addindex （文本）
此命令将 （text） 添加到 {\LaTeX} 、 DocBook 和 RTF 索引中

### \anchor <word>
此命令将一个不可见的命名锚点放入文档中，您可以使用 \ref 命令引用该锚点。

### \cite <标签>
在文本和书目参考列表中添加书目参考。<label> 必须是有效的 BibTeX 标签，可以在 CITE_BIB_FILES 中列出的 .bib 文件之一中找到。对于输出，{\LaTeX}可以使用 LATEX_BIB_STYLE 配置文本中引用的格式。对于其他输出格式，使用固定表示形式。请注意，使用此命令需要该工具出现在搜索路径中。bibtex

### \endlink
此命令结束使用 \link 命令启动的链接。

### \link <链接对象>
由 Doxygen 自动生成的链接始终具有它们指向的对象的名称（作为链接文本）。

该命令可用于创建指向具有用户指定链接文本的对象（文件、类或成员）的链接。link 命令应以 \endlink 命令结尾。和 \endlink 命令之间的所有文本都用作指向 <link-object> 的链接的文本，该链接指定为 的第一个参数。\link\link\link

### \ref <名称> [“（文本）”]
创建对命名元件、文件、节、子节、页面或锚点的引用。

对于 HTML 文档，reference 命令将生成指向该部分的链接。对于部分或子部分，该部分的标题将用作链接的文本。对于锚点，将使用引号之间的可选文本，如果未指定文本，则为 <name>。

如果 <name> 有空格（例如，如果它引用的文件名包含空格），你需要在 <name> 两边加上双引号，例如 “my file.md”。

对于{\LaTeX}文档，除非 PDF_HYPERLINKS 选项已设置为 ，否则 reference 命令将相同，在这种情况下，它会生成章节的章节标题或文本（如果 <name> 引用锚点后跟页码。NO

### \refitem <名称>
就像 \ref 命令一样，此命令创建对命名节的引用，但此引用出现在以 \secreflist 开头并以 \endsecreflist 结尾的列表中。可以在页面顶部看到此类列表的示例。

### \secreflist
启动一个 item 的索引列表，使用 \refitem 创建，每个 item 都链接到一个命名部分。

### \endsecreflist
结束以 \secreflist 开头的索引列表。

### \subpage <名称> [“（文本）”]
此命令可用于创建页面层次结构。可以使用 \defgroup 和 \ingroup 命令创建相同的结构，但对于页面，该命令通常更方便。主页面（参见 \mainpage）通常是层次结构的根。\subpage

此命令的行为类似于 \ref ，因为它创建对标记为 <name> 的页面的引用，并在第二个参数中指定的可选链接文本。

它与 \ref 命令的不同之处在于它仅适用于页面，并在页面之间创建父子关系，其中子页面（或子页面）由标签 <name> 标识。

如果您想在不创建多个页面的情况下添加结构，请参阅 \section 和 \subsection 命令。

> [!NOTE]
> 每个页面只能是另一个页面的子页面，并且不允许循环关系，即页面层次结构必须具有树结构。

下面是一个示例：
```c++
/** @mainpage A simple manual
 * 
 * Some general info.
 * 
 * This manual is divided in the following sections:
 * - @subpage intro
 * - @subpage advanced "Advanced usage"
 * */

//-----------------------------------------------------------

/** @page intro Introduction
 * This page introduces the user to the topic.
 * Now you can proceed to the @ref advanced "advanced section".
 * */

//-----------------------------------------------------------

/** @page advanced Advanced Usage
 * This page is for advanced users.
 * Make sure you have first read @ref intro "the introduction".
 * */
```

### \tableofcontents['{'[option[：level]][，option[：level]]*'}']
在页面顶部创建目录，列出页面中的所有部分和子部分。可以是 或 或 或 。指定 a 时，这意味着显示的最大嵌套级别。的值应在 1..6 范围内，超出此范围的值被视为 6。如果指定了 case no 设置为 6 （show all） ，则 case no 。的作用就像只指定了 and 一样。如果页面中有多个命令，则 （s） 将在已指定的 （） 之外使用 （s），但只有 的最后一个有效。optionHTMLLaTeXXMLDocBooklevellevellevelleveloption\tableofcontentsoptionHTMLXML\tableofcontentsoptionoptionleveloption

> [!CAUTION]
> 此命令仅适用于相关页面文档，不适用于其他文档块，并且仅在指定输出中有效！

### \section <section-name> （章节标题）
创建名称为 <section-name> 的部分。该部分的标题应指定为命令的第二个参数。\section

> [!CAUTION]
> 此命令仅适用于相关页面文档，不适用于其他文档块！

### \subsection <subsection-name> （小节标题）
创建一个名称为 <subsection-name> 的子部分。小节的标题应指定为命令的第二个参数。\subsection

> [!CAUTION]
> 此命令仅在相关页面文档块的某个部分内有效，而在其他文档块中无效！

### \subsubsection <subsubsection-name> （小节标题）
创建一个名称为 <subsubsection-name> 的子小节。小节的标题应指定为命令的第二个参数。\subsubsection

> [!CAUTION]
> 此命令仅在相关页面文档块的子部分内有效，而在其他文档块中无效！

### \paragraph <段落名称> （段落标题）
创建名称为 <paragraph-name> 的命名段落。段落的标题应指定为命令的第二个参数。\paragraph

> [!CAUTION]
> 此命令仅适用于相关页面文档块的子部分，而不适用于其他文档块！

### \subparagraph <subparagraph-name> （子段落标题）
创建名称为 <subparagraph-name> 的命名子段落。应将子段落的标题指定为命令的第二个参数。\subparagraph

> [!CAUTION]
> 这个命令只在相关页面文档块的段落中有效，在其他文档块中无效！

### \subsubparagraph <subsubparagraph-name> （子段落标题）
创建名称为 <subsubparagraph-name> 的命名子段落。subsubparagraph 的标题应指定为命令的第二个参数。\subsubparagraph

> [!CAUTION]
> 此命令仅在相关页面文档块的子段落中有效，而在其他文档块中无效！

### \dontinclude['{lineno}'] <文件名>
此命令可用于解析源文件，而无需实际将其逐字包含在文档中（就像 \include 命令一样）。如果要将源文件划分为较小的部分并在这些部分之间添加文档，这将非常有用。可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定源文件或目录。

如果需要，您可以添加选项来为包含的代码启用行号。lineno

在解析包含命令的注释块期间，将“记住”代码片段中的类和成员声明和定义。\dontinclude

对于源文件的逐行描述，可以使用 \line、\skip、\skipline 和 \until 命令显示示例的一行或多行。内部指针用于这些命令。该命令将指针设置为示例的第一行。\dontinclude

例：
```c++
/** 一个测试类。 */
class Include_Test {
public:
    /// 一个成员函数
    void example();
};

/** @page pag_example
 * @dontinclude include_test.cpp
 * 我们的主要功能是这样开始的：
 * @skip main
 * @until {
 * 首先，我们创建一个 Include_Test 类的对象 @c t。
 * @skipline Include_Test
 * 然后我们调用示例成员函数
 * @line 示例
 * 之后，我们的小测试程序结束。
 * @line }
 * */
```
其中示例文件如下所示：include_test.cpp
```c++
void main() {
  Include_Test t;
  t.example();
}
```

### \include['{'option'}'] <文件名>
此命令可用于将源文件作为代码块包含在内。该命令将包含文件的名称作为参数。可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定源文件或目录。

如果 <file-name> 本身对于 EXAMPLE_PATH 标记指定的示例文件集不唯一，则可以包含绝对路径的一部分以消除歧义。

使用该命令等效于将文件插入到文档块中，并用 \code 和 \endcode 命令将其括起来。\include

该命令的主要目的是避免在示例块包含多个源文件和头文件的情况下出现代码重复。\include

对于源文件的逐行描述，请将 \dontinclude 命令与 \line、\skip、\skipline 和 \until 命令结合使用。

或者，可以使用 \snippet 命令仅包含源文件的片段。要使其正常工作，必须标记 fragment。

> [!NOTE]
> Doxygen 的特殊命令在代码块中不起作用。不过，允许在代码块中嵌套 C 风格的注释。

可以是 、 或 ，另外还可以指定。optionlinenodoclocal

* 如果需要，这可用于为包含的代码启用行号。optionlineno
* 这可用于将文件视为文档而不是代码。optiondoc
* 这可用于使 Doxygen 解释代码，就好像它位于出现 include 命令的类或命名空间中一样，而不是在全局命名空间中。optionlocal

使用 option 时，还可以指定一个选项，以将引用文件中找到的所有部分提高一定量。例如docraise

    \include{doc,raise=1} file.dox
会将 中找到的任何级别 1 视为 级别 2 ，并将任何级别 2 视为级别 3 ，以此类推。同样，对于 Markdown，一个部分将被视为一个部分。\sectionfile.dox\subsection\subsection\subsubsection###

此外，还有一个选项可用于为包含部分的每个标签添加前缀，以便它们保持唯一。例如：prefix

    \include{doc,prefix=fn_} file.dox
将治疗例如 中找到 ，就好像它被指定为 一样。\section s1file.dox\section fn_s1

> [!NOTE]
> 包含的文档不应包含注释符号，因为它们也会出现在文档中。

### \includelineno <文件名>
此命令已过时，出于向后兼容性原因仍受支持，其工作方式与 \include{lineno} 相同

### \includedoc['{'option'}'] <文件名>
此命令已过时，出于向后兼容性原因仍受支持，其工作方式与 \include{doc} 相同

s 与使用选项 时可与 一起使用的 s 相同。optionoption\includedoc

### \line （ 模式 ）
此命令逐行搜索上次使用 \include 或 \dontinclude 包含的示例，直到找到非空行。如果该行包含指定的模式，则会将其写入输出。

用于跟踪示例中当前行的内部指针被设置为找到的非空行之后的行的行首（如果找不到此类行，则设置为示例的末尾）。

### \skip （ 模式 ）
此命令在上次使用 \include 或 \dontinclude 包含的示例中逐行搜索，直到找到包含指定模式的行。

用于跟踪示例中当前行的内部指针设置为包含指定模式的行的开头（如果找不到模式，则设置为示例的末尾）。

### \skipline （ 模式 ）
此命令在上次使用 \include 或 \dontinclude 包含的示例中逐行搜索，直到找到包含指定模式的行。然后，它将该行写入输出。

用于跟踪示例中当前行的内部指针被设置为写入行之后的行的行首（如果找不到模式，则设置为示例的末尾）。

注意：
命令：等效于：

    \skipline pattern
    
    \skip pattern
    \line pattern

### \snippet['{'option'}'] <文件名> （ block_id ）
如果 \include 命令可用于将完整文件作为源代码包含在内，则此命令可用于仅引用源文件的片段。In case 用作 <file-name> 时，当前文件将作为从中获取代码片段的文件。this

例如，将以下命令放在文档中，引用了位于子目录中的文件中的代码段，该子目录应由 EXAMPLE_PATH 指向。example.cpp

    \snippet snippets/example.cpp Adding a resource
文件名后面的文本是代码片段的唯一标识符。这用于分隔相关代码段文件中的带引号代码，如以下示例所示，该示例对应于上述命令：\snippet

    QImage 图片（64， 64， QImage：：Format_RGB32）;
    图片.fill（qRgb（255， 160， 128））;
```c++
//![添加资源]
document->addResource(QTextDocument::ImageResource,
QUrl("mydata://image.png"), QVariant(图像));
//![添加资源]
```
请注意，包含块标记的行将不包括在内，因此输出将为：

    document->addResource（QTextDocument：：ImageResource，
    QUrl（“mydata://image.png”）， QVariant（图像））;
另请注意，[block_id] 标记在源文件中应恰好出现两次。

可以是 、 或 ，另外还可以指定。optionlinenotrimleftdoclocal

* 如果需要，这可用于为包含的代码启用行号。optionlineno
* 这 可以用来删除所有行前面的公共间距（还要考虑 TAB_SIZE 标签的设置）。optiontrimleft
* 这可用于将文件视为文档而不是代码。optiondoc
* 这可用于使 Doxygen 解释代码，就好像它位于出现 include 命令的类或命名空间中一样，而不是在全局命名空间中。optionlocal

使用 option 时，还可以指定一个选项，以将引用文件中找到的所有部分提高一定量。例如docraise

    \snippet{doc,raise=1} file.dox XXX
会将找到的任何 1 级代码段视为 2 级，将任何 2 级视为 3 级，以此类推。同样，对于 Markdown，一个部分将被视为一个部分。\section\subsection\subsection\subsubsection###

此外，还有一个选项可用于为包含部分的每个标签添加前缀，以便它们保持唯一。例如：prefix

    \include{doc,prefix=fn_} file.dox
将治疗例如 中找到 ，就好像它被指定为 一样。\section s1file.dox\section fn_s1

> [!NOTE]
> 包含的文档不应包含注释符号，因为它们也会出现在文档中

### \snippetdoc['{'option'}'] <文件名> （ block_id ）
此命令已过时，出于向后兼容性原因仍受支持，其工作方式与 \snippet{doc} 相同

s 与使用选项 时可与 一起使用的 s 相同。optionoption\snippetdoc

### \until （ 模式 ）
此命令将上次使用 \include 或 \dontinclude 包含的示例的所有行写入输出，直到找到包含指定模式的行。包含 pattern 的行也将被写入。

用于跟踪示例中当前行的内部指针被设置为最后写入的行之后的行首（如果找不到模式，则设置为示例的末尾）。

### \verbinclude <文件名>
此命令包括文档中的文件 <file-name> 的内容。该命令等效于将文件内容粘贴到文档中，并在其周围放置 \verbatim 和 \endverbatim 命令。

Doxygen 应查找的文件或目录可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定。

### \htmlinclude['[block]'] <文件名>
此命令包括文件的内容 <file-name> 与 HTML 文档中的相同，并在生成的 XML 输出中使用标记。该命令等效于将文件内容粘贴到文档中，并在其周围放置 \htmlonly 和 \endhtmlonly 命令。<htmlonly>

通常，\htmlinclude 指示的文件内容按原样插入。当您想插入一个具有块范围的 HTML 片段时，例如表格或列表，它应该出现在 <p>.</p>，这可能会导致无效的 HTML。您可以使用 使 Doxygen 结束当前段落，并在包含文件后重新启动。\htmlinclude[block]

Doxygen 应查找的文件或目录可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定。

### \latexinclude <文件名>
此命令包括{\LaTeX}文件的内容 <file-name> 与文档中相同，并在生成的 XML 输出中使用标记。该命令等效于将文件内容粘贴到文档中，并在其周围放置 \latexonly 和 \endlatexonly 命令。<latexonly>

Doxygen 应查找的文件或目录可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定。

### \rtfinclude <文件名>
此命令包括文件的内容 <file-name> 如 RTF 文档中所示，并在生成的 XML 输出中使用标记。该命令等效于将文件内容粘贴到文档中，并在其周围放置 \rtfonly 和 \endrtfonly 命令。<rtfonly>

Doxygen 应查找的文件或目录可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定。

### \maninclude <文件名>
此命令包括文件的内容 <file-name> 与 MAN 文档中相同，并在生成的 XML 输出中使用标记。该命令等效于将文件内容粘贴到文档中，并在其周围放置 \manonly 和 \endmanonly 命令。<manonly>

Doxygen 应查找的文件或目录可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定。

### \docbookinclude <文件名>
此命令包括文件的内容 <file-name> 与 DocBook 文档中的内容相同，并在生成的 XML 输出中使用标记。该命令等效于将文件内容粘贴到文档中，并在其周围放置 \docbookonly 和 \enddocbookonly 命令。<docbookonly>

Doxygen 应查找的文件或目录可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定。

### \xmlinclude <文件名>
此命令包括文件 <file-name> 的内容，如 XML 文档中所示。该命令等效于将文件内容粘贴到文档中，并在其周围放置 \xmlonly 和 \endxmlonly 命令。

Doxygen 应查找的文件或目录可以使用 Doxygen 配置文件的 EXAMPLE_PATH 标签指定。

### \a <字>
以斜体显示参数 <word>。使用此命令可强调单词。使用此命令可引用运行文本中的成员参数。

例：

    ... the \a x and \a y coordinates are used to ...
   这将产生以下文本：

   ...X 和 Y 坐标用于...
等效于 \e 和 \em。要强调多个单词，请使用 <em>multiple words</em>。

### \arg { 项目描述 }
此命令有一个参数，该参数一直持续到第一个空行或遇到另一个空行。该命令可用于生成简单的、非嵌套的参数列表。每个参数都应以 command 开头。\arg\arg

例：
Typing： 将生成以下文本：

    \arg \c AlignLeft left alignment.
    \arg \c AlignCenter center alignment.
    \arg \c AlignRight right alignment
    
    No other types of alignment are supported.

* AlignLeft左对齐。
* AlignCenter居中对齐。
* AlignRight右对齐

不支持其他类型的对齐方式。
注意：
对于嵌套列表，应使用 HTML 命令。
等效于 \li

### \b <字>
使用粗体显示参数 <word>。等效于 <b>word</b>。要将多个单词加粗，请使用 <b>multiple words</b>。

### \c <word>
使用打字机字体显示参数 <word>。用它来指代代码词。等效于 <tt>word</tt>。

例：
键入：将生成以下文本：

...此函数返回 and not ...

    ... This function returns \c void and not \c int ...
voidint
等价于 \p。要在打字机字体中使用多个单词，请使用 <tt>multiple words</tt>。

### \code['{'<word>'}']
启动一个代码块。代码块的处理方式与普通文本不同。它被解释为源代码。类和成员以及其他记录的实体的名称会自动替换为指向文档的链接。

默认情况下，语法高亮显示采用的语言基于找到块的位置。例如，如果 Python 文件的这一部分，语法高亮将根据 Python 语法完成。\code

如果从上下文中不清楚哪种语言（例如，注释在 or 文件中），那么您还可以通过将文件扩展名（通常是 Doxygen 与该语言关联的）放在代码块后面的大括号中来明确指示语言。下面是一个示例：.txt.markdown

    \code{.py}
    class Python:
    pass
    \endcode
    
    \code{.cpp}
    class Cpp {};
    \endcode
如果代码块的内容是 Doxygen 无法解析的语言，Doxygen 将只按原样显示输出。您可以使用 .unparsed 显式表示这一点，或者通过提供 Doxygen 不支持的其他扩展名来明确这一点，例如

    \code{.unparsed}
    Show this as-is please
    \endcode
    
    \code{.sh}
    echo "This is a shell script"
    \endcode

### \copydoc <链接对象>
从 <link-object> 指定的对象复制文档块，并将其粘贴到命令的位置。此命令可用于避免必须复制文档块的情况，或者它可以用于扩展继承成员的文档。

链接对象可以指向成员（类、文件或组）、类、命名空间、组、页面或文件（按此顺序选中）。请注意，如果指向的对象是成员（函数、变量、typedef 等），则还应记录包含它的复合（类、文件或组），以便进行复制。

要复制类成员的文档，例如，可以在文档中放置以下内容：
```c++
/** @copydoc MyClass::myfunction()
 * More documentation.
 * */
```
如果成员重载，则应显式指定参数类型（不带空格），如下所示：

    //! @copydoc MyClass::myfunction(type1,type2)
仅当找到文档块的上下文需要限定名称时，才需要限定名称。

该命令可以递归使用，但关系中的循环将被打破并标记为错误。\copydoc\copydoc

请注意，这大致等同于执行：\copydoc foo()

    \brief \copybrief foo()
    \details \copydetails foo()

### \copybrief <链接对象>
工作方式与 \copydoc 类似，但只会复制简要描述，而不是详细文档。

### \copydetails <链接对象>
的工作方式与 \copydoc 类似，但只会复制详细文档，而不是简要描述。

### \docbookonly
启动一个文本块，该文本块将仅逐字包含在生成的 DocBook 文档中，并在生成的 XML 输出中使用标记。该块以 \enddocbookonly 命令结尾。<docbookonly>

### \dot [“标题”] [<sizeindication>=<size>]
启动一个文本片段，该片段应包含点图的有效描述。文本片段以 \enddot 结尾。Doxygen 会将文本传递给 dot 并将生成的图像（和图像映射）包含在输出中。

第一个参数是可选的，可用于指定显示在图像下方的标题。必须在引号之间指定此参数，即使它不包含任何空格。在显示标题之前，引号会被去除。

第二个参数也是可选的，可用于指定图像的宽度或高度。有关可能性的描述，请参阅使用 \image 命令的 Size indicate 段落。

可以使用 URL 属性使图形的节点可单击。通过在 URL 值中使用命令 \ref，您可以方便地链接到 Doxygen 中的项目。下面是一个示例：

> [!NOTE]
> 使用此命令需要将 HAVE_DOT 设置为YES
> Doxygen 会创建一个临时文件，除非 DOT_CLEANUP 标签设置为 .NO
```c++
/** B 类 */
class B {};

/** C 类 */
class C {};

/** @mainpage
 *
 * 通过内联点图表示的类关系：
 * @dot
 * 二合图示例 {
 * 节点 [形状=记录， 字体名称=Helvetica， fontsize=10];
 * b [ label=“class B” URL=“\ref B”];
 * c [ label=“class C” URL=“\ref C”];
 * b -> c [ arrowhead=“open”， style=“dashed” ];
 *  }
 * @enddot
 * 请注意，上图中的类是可点击的
 *（在 HTML 输出中）。
 * */
```

### \emoji “名称”
此命令将生成一个给定其名称的表情符号字符。

支持的名称是 GitHub 也支持的名称，并在此处列出 https://gist.github.com/rxaviers/7360908

您可以使用带或不带冒号的名称，即 与写入 相同。当不支持表情符号时，名称 with by places in text with in the text （名称 with places in in in in the text in the following and and in the row （即 将在输出中生成。Doxygen 还会给出一条警告消息。\emoji smile\emoji :smile:\emoji unsupported:unsupported:

有关详细信息，另请参阅[表情符号支持页面](https://www.doxygen.nl/manual/emojisup.html)。

### \msc [“标题”] [<sizeindication>=<size>]
启动一个文本片段，该片段应包含消息序列图的有效描述。有关示例，请参阅 https://www.mcternan.me.uk/mscgen/。文本片段以 \endmsc 结尾。

第一个参数是可选的，可用于指定显示在图像下方的标题。必须在引号之间指定此参数，即使它不包含任何空格。在显示标题之前，引号会被去除。

第二个参数也是可选的，可用于指定图像的宽度或高度。有关可能性的描述，请参阅使用 \image 命令的 Size indicate 段落。

> [!NOTE]
> 文本片段应仅包含消息序列图中位于块内的部分（这与 \mscfile 不同）。msc {...}
> mscgen 现在内置于 Doxygen 中
> Doxygen 会创建一个临时文件，除非 DOT_CLEANUP 标签设置为 .NO

下面是该命令的使用示例。\msc
```c++
/** Sender 类。可用于向服务器发送命令。
 * 接收方将通过调用 Ack（） 来确认命令。
 * @msc
 * 发送者、接收者;
 * 发送者 >接收者 [label=“Command（）”， URL=“\ref Receiver：：Command（）”];
 * 发送方<接收方 [label=“Ack（）”， URL=“\ref Ack（）”， ID=“1”];
 * @endmsc
 * */
class Sender {
public:
    /** 来自服务器的确认 */
    void Ack(bool ok);
};

/** 接收器类。可用于接收和执行命令。
 * 执行命令后，接收方将发送确认
 * @msc
 * 接收者，发送者;
 * 接收者<发送者 [label=“Command（）”， URL=“\ref Command（）”];
 * Receiver->Sender [label=“Ack（）”， URL=“\ref Sender：：Ack（）”， ID=“1”];
 * @endmsc
 * */
class Receiver {
public:
    /** 在服务器上执行命令 */
    void Commend(int commandId);
};
```

### \startuml ['{'option[，option]'}'] [“caption”] [<sizeindication>=<size>]

启动一个文本片段，该片段应包含 PlantUML 图的有效描述。有关示例，请参阅 https://plantuml.com/。文本片段以 \enduml 结尾。

> [!NOTE]
> 如果要使用此命令，则需要安装 Java 和 PlantUML 的 jar 文件。在 {\LaTeX} 中使用 PlantUML 时，您必须下载更多文件，有关详细信息，请参阅 PlantUML 文档。这也对 s 和 有效。应使用 PLANTUML_JAR_PATH 指定 PlantUML 文件的位置。其他 jar 文件也应位于此目录中。jar<engine>latexmath
> 由于 PlantUML 仅支持格式，而 Doxygen 需要临时输出，因此无法使用 {\LaTeX} the 。<engine>ditaapngeps

并非所有图表都可以使用 PlantUML 命令创建，但需要另一个 PlantUML 命令。这将类似于当前支持的位置是以下 s： ， ， ，默认情况下，为 .可以指定为选项。此外，还可以通过选项指定要写入结果图像的文件，有关详细信息，请参阅第一个（可选）参数的描述。当然，只能指定一个，而且文件名只能指定一次。@startuml@start...@start<engine><engine>umlbpmwiredotditaasaltmathlatexganttmindmapwbsyamlcreolejsonflowboardgithclregexebnffileschenchronology<engine>uml<engine><engine>

第一个参数是可选的，是为了与在运行 Doxygen 之前运行 PlantUML 作为预处理步骤兼容，您还可以在大括号后面和内部添加图像文件的名称作为选项，即\startuml

    @startuml{myimage.png} "Image Caption" width=5cm
    Alice -> Bob : Hello
    @enduml
指定映像名称后，Doxygen 将生成具有该名称的映像。如果没有名称，Doxygen 将自动选择一个名称。

第二个参数是可选的，可用于指定显示在图像下方的标题。必须在引号之间指定此参数，即使它不包含任何空格。在显示标题之前，引号会被去除。

第三个参数也是可选的，可用于指定图像的宽度或高度。有关可能性的描述，请参阅使用 \image 命令的 Size indicate 段落。

> [!NOTE]
> Doxygen 在设计上不支持像 ， 这样的 Plantuml 命令，但用户可以通过在 Doxygen 设置文件中添加来支持：@startjson
    ALIASES += startjson=@startuml{json}
    ALIASES += endjson=@enduml
> Doxygen 会创建一个临时文件，除非 DOT_CLEANUP 标签设置为 .NO

下面是该命令的使用示例。\startuml
```c++
/** Sender 类。可用于向服务器发送命令。
 * 接收方将通过调用 Ack（） 来确认命令。
 * @startuml
 * 发送方->接收方 ： Command（）
 * 发送方<--接收方 ： ack（）
 * @enduml
 * */
class Sender {
public:
    /** 来自服务器的确认 */
    void Ack(bool ok);
};

/** 接收器类。可用于接收和执行命令。
 * 执行命令后，接收方将发送确认
 * @startuml
 * 接收者<发送者 ： Command（）
 * 接收方-->发送方 ： Ack（）
 * @enduml
 * */
class Receiver {
    public:
    /** 在服务器上执行命令 */
    void Commend(int commandId);
};
```

### \dotfile \<file> [“标题”] [<sizeindication>=<size>]
将 dot from \<file> 生成的图像插入到文档中。

第一个参数指定图像的文件名。Doxygen 将在您在 DOTFILE_DIRS 标签后指定的路径（或文件）中查找文件。如果找到点文件，它将用作点工具的输入文件。生成的图像将被放入正确的输出目录中。如果点文件名包含空格，则必须在其周围加上引号 （“...”）。

第二个参数是可选的，可用于指定显示在图像下方的标题。必须在引号之间指定此参数，即使它不包含任何空格。在显示标题之前，引号会被去除。

第三个参数也是可选的，可用于指定图像的宽度或高度。有关可能性的描述，请参阅使用 \image 命令的 Size indicate 段落。

> [!NOTE]
> 使用此命令需要将 HAVE_DOT 设置为YES

### \mscfile \<file> [“caption”] [<sizeindication>=<size>]
将 mscgen 生成的图像从 \<file> 插入到文档中。有关示例，请参阅 https://www.mcternan.me.uk/mscgen/。

第一个参数指定图像的文件名。Doxygen 将在您在 MSCFILE_DIRS 标签后指定的路径（或文件）中查找文件。如果找到 msc 文件，它将用作内置 mscgen 工具的输入文件。生成的图像将被放入正确的输出目录中。如果 msc 文件名包含空格，则必须在它周围加上引号 （“...”）。

第二个参数是可选的，可用于指定显示在图像下方的标题。必须在引号之间指定此参数，即使它不包含任何空格。在显示标题之前，引号会被去除。

第三个参数也是可选的，可用于指定图像的宽度或高度。有关可能性的描述，请参阅使用 \image 命令的 Size indicate 段落。

> [!NOTE]
> 文本片段应包括序列图的 part 消息以及开始和结束（这与 \msc 不同）。msc {}

### \diafile \<file> [“caption”] [<sizeindication>=<size>]
将 dia 从 \<file> 生成的图像插入到文档中。

第一个参数指定图像的文件名。Doxygen 将在您在 DIAFILE_DIRS 标签后指定的路径（或文件）中查找文件。如果找到 dia 文件，它将用作输入文件 dia。生成的图像将被放入正确的输出目录中。如果 dia 文件名包含空格，则必须在其周围加上引号 （“...”）。

第二个参数是可选的，可用于指定显示在图像下方的标题。必须在引号之间指定此参数，即使它不包含任何空格。在显示标题之前，引号会被去除。

第三个参数也是可选的，可用于指定图像的宽度或高度。有关可能性的描述，请参阅使用 \image 命令的 Size indicate 段落。

### \doxyconfig <config_option>
显示 Doxygen 配置文件中使用的配置选项的值，该配置文件在处理此命令时正在使用。<config_option>

例：
   创建本手册时，以下内容：给出：
   ...项目名称 = Doxygen ...

    ... Project name = \doxyconfig PROJECT_NAME ...

### \e <word>
以斜体显示参数 <word>。使用此命令可强调单词。

例：
键入：将生成以下文本：

...这是一个很好的例子......

    ... this is a \e really good example ...
等效于 \a 和 \em。要强调多个单词，请使用 <em>multiple words</em>。

### \em <word>
以斜体显示参数 <word>。使用此命令可强调单词。

例：
键入：将生成以下文本：

...这是一个很好的例子......
    
    ... this is a \em really good example ...
等效于 \a 和 \e。要强调多个单词，请使用 <em>multiple words</em>。

### \endcode
结束代码块。

### \enddocbookonly
结束以 \docbookonly 命令启动的文本块。

### \enddot
结束以 \dot 开头的块。

### \endmsc
结束以 \msc 开头的块。

### \enduml
结束以 \startuml 开头的块。

### \endhtmlonly
结束以 \htmlonly 命令启动的文本块。

### \endlatexonly
结束以 \latexonly 命令启动的文本块。

### \endmanonly
结束以 \manonly 命令开头的文本块。

### \endrtfonly
结束以 \rtfonly 命令启动的文本块。

### \endverbatim
结束以 \verbatim 命令开头的文本块。

### \endxmlonly
结束以 \xmlonly 命令启动的文本块。

### \f$

标记文本内公式的开始和结束。

### \f（

标记文本内公式的开始，但与 \f$ 相反，它不会在 中{\LaTeX}显式打开数学模式 。

### \f）

标记以 \f（.

### \f[

标记在单独行中央显示的长公式的开头。

### \f]

标记在单独行中央显示的长公式的结尾。

### \f{环境}{

标记特定环境中的公式的开始。

> [!NOTE]
> 第二个是可选的，只是为了帮助编辑者（例如 ）通过使左大括号和右大括号的数量相同来进行正确的语法高亮。{Vim

### \f}

标记特定环境中的公式的结尾。

### \htmlonly['[块]']
启动一个文本块，该文本块将仅逐字包含在生成的 HTML 文档中，并在生成的 XML 输出中使用标记。该块以 \endhtmlonly 命令结尾。<htmlonly>

此命令可用于包含对 Doxygen 来说过于复杂的 HTML 代码（即需要特定属性的 applet、java-scripts 和 HTML 标记）。

通常，\htmlonly 和 \endhtmlonly 之间的内容按原样插入。当您想插入一个具有块范围的 HTML 片段时，例如表格或列表，它应该出现在 <p>.</p>，这可能会导致无效的 HTML。您可以使用 使 Doxygen 结束当前段落，并在 之后重新启动它。\htmlonly[block]\endhtmlonly

> [!NOTE]
> 环境变量（如 $（HOME） ）在仅限 HTML 的块中解析。

### \image['{'option[，option]'}'] <format> <file> [“caption”] [<sizeindication>=<size>]
将图像插入到文档中。此命令是特定于格式的，因此如果要插入多个格式的图像，则必须对每种格式重复此命令。

第一个参数指定图像应嵌入的输出格式。目前，支持以下值：、、 、 和 。htmllatexdocbookrtfxml

第二个参数指定图像的文件名。Doxygen 将在您在 IMAGE_PATH 标签后指定的路径（或文件）中查找文件。如果找到图像，则会将其复制到正确的输出目录。如果图像名称包含空格，则必须在名称周围加上引号 （“...”）。您还可以指定绝对 URL 而不是文件名，但 Doxygen 不会复制映像，也不会检查其是否存在。

第三个参数是可选的，可用于指定显示在图像下方的标题。此参数必须在单行和引号之间指定，即使它不包含任何空格。在显示标题之前，引号会被去除。

第四个参数也是可选的，可用于指定图像的宽度或高度。这对于 DocBook 输出（即 format= 或 format=）很有用{\LaTeX}。latexdocbook

尺寸指示
可以指定要使用的宽度或高度（或组合）。中的大小说明符{\LaTeX}（例如 or 或符号宽度，如 ）。sizeindication10cm4in\textwidth
目前仅支持 options 和 。如果指定了该选项，则图像将放置在“行中”，当存在标题时，它将在 HTML 中显示为工具提示（其他格式忽略）。对于选项，语法为： .inlineanchorinlineanchoranchor:<anchorId>

以下是注释块的示例：

    /** Here is a snapshot of my new application:
     *  @image html application.jpg
     *  @image latex application.eps "My application" width=10cm
     * */

这是配置文件的相关部分的示例：

    IMAGE_PATH     = my_image_dir

> [!CAUTION]
> HTML 的图像格式仅限于您的浏览器支持的格式。
> 对于 {\LaTeX}，{\LaTeX}命令必须支持图像格式，即封装的 PostScript （eps）、便携式网络图形 （png）、联合摄影专家组 （jpg / jpeg）。
>   
> Doxygen 不会检查图像的格式是否正确。所以你必须确保这是这种情况！\includegraphics

### \latexonly
启动一个文本块，该文本块将仅逐字包含在生成的{\LaTeX}文档中，并在生成的 XML 输出中使用标记。该块以 \endlatexonly 命令结尾。<latexonly>

此命令可用于包含{\LaTeX}对 Doxygen 来说过于复杂的代码（即图像、公式、特殊字符）。您可以使用 \htmlonly 和 \endhtmlonly 对来提供适当的 HTML 替代方案。

注意：环境变量（如 $（HOME） ）在 {\LaTeX}-only 块中解析。

### \manonly
启动一个文本块，该文本块将仅逐字包含在生成的 MAN 文档中，并在生成的 XML 输出中使用标记。该块以 \endmanonly 命令结尾。<manonly>

此命令可用于将 groff 代码直接包含在 MAN 页中。您可以使用 \htmlonly 和 \endhtmlonly 以及 \latexonly 和 \endlatexonly 对来提供适当的 HTML 和{\LaTeX}替代项。

### \li { 项目描述 }
此命令有一个参数，该参数一直持续到第一个空行或遇到另一个空行。该命令可用于生成简单的、非嵌套的参数列表。每个参数都应以 command 开头。\li\li

例：
Typing： 将生成以下文本：

    \li \c AlignLeft left alignment.
    \li \c AlignCenter center alignment.
    \li \c AlignRight right alignment
    
    No other types of alignment are supported.


* AlignLeft左对齐。
* AlignCenter居中对齐。
* AlignRight右对齐

不支持其他类型的对齐方式。
注意：
对于嵌套列表，应使用 HTML 命令。
等价于 \arg

### \n
强制换行。相当于 <br> 并受到函数的启发。printf

### \p <word>
使用打字机字体显示参数 <word>。您可以使用此命令在运行文本中引用成员函数参数。

例：

    ... the \p x and \p y coordinates are used to ...
这将产生以下文本：

...和 坐标用于 ...xy
等效于 \c。要在打字机字体中使用多个单词，请使用 <tt>multiple words</tt>。

### \rtfonly
启动一个文本块，该文本块将仅逐字包含在生成的 RTF 文档中，并在生成的 XML 输出中使用标记。该块以 \endrtfonly 命令结尾。<rtfonly>

此命令可用于包含对 Doxygen 来说过于复杂的 RTF 代码。

注意：环境变量（如 $（HOME） ）在仅限 RTF 的块中解析。

### \verbatim
启动一个文本块，该文本块将逐字包含在文档中。该块应以 \endverbatim 命令结尾。所有命令都在逐字块中被禁用。

> [!CAUTION]
> 确保为每个命令包含一个 \endverbatim 命令，否则解析器会感到困惑！\verbatim

### \xmlonly
启动一个文本块，该文本块将仅逐字包含在生成的 XML 输出中。该块以 \endxmlonly 命令结尾。

此命令可用于包含自定义 XML 标记。

### \\
此命令将反斜杠字符 （） 写入输出。在某些情况下，反斜杠必须转义，因为 Doxygen 使用它来检测命令。\

### \@
此命令将 at-sign （） 写入输出。在某些情况下，必须对 at 符号进行转义，因为 Doxygen 使用它来检测 Javadoc 命令。@

### \~[语言 ID]
此命令启用/禁用特定于语言的筛选器。这可用于将不同语言的文档放入一个注释块中，并使用 OUTPUT_LANGUAGE 标签仅过滤掉特定语言。用于仅启用特定语言的输出，并启用所有语言的输出（这也是默认模式）。\~language_id\~

例：

    /*! \~english This is English \~dutch Dit is Nederlands \~german Dies ist
    Deutsch. \~ output for all languages.
    */
### \&
此命令将字符写入输出。这个字符必须转义，因为它在 HTML 中具有特殊含义。&

### \$
此命令将字符写入输出。在某些情况下，必须对此字符进行转义，因为它用于扩展环境变量。$

### \#
此命令将字符写入输出。在某些情况下，必须对此字符进行转义，因为它用于引用记录的实体。#

### \<
此命令将字符写入输出。这个字符必须转义，因为它在 HTML 中具有特殊含义。<

### \>
此命令将字符写入输出。这个字符必须转义，因为它在 HTML 中具有特殊含义。>

### \%
此命令将字符写入输出。在某些情况下，必须对这个字符进行转义，因为它用于防止自动链接到也是记录的类或结构的单词。%

### \"
此命令将字符写入输出。在某些情况下，必须对此字符进行转义，因为它成对使用以表示未格式化的文本片段。"

### \.
此命令将点 （） 写入输出。这对于防止在启用JAVADOC_AUTOBRIEF时结束简要说明或防止在行首的数字后面的点后开始编号列表非常有用。.

### \=
此命令将等号 （） 写入输出。在某些情况下，此字符序列必须转义，因为它用于 Markdown 标头处理。=

### \::
此命令将双冒号 （） 写入输出。在某些情况下，必须对此字符序列进行转义，因为它用于引用记录的实体。::

### \|
此命令将管道符号 （|） 写入输出。在某些情况下，必须对此字符进行转义，因为它用于 Markdown 表。

### \--
此命令将两个短划线 （--） 写入输出。这允许将两个连续的破折号写入输出，而不是一个 n 破折号 （–）。

### \---
此命令将三个短划线 （---） 写入输出。这允许将三个连续的破折号写入输出，而不是一个 m 破折号 （—）。
