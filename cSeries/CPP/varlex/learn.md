## EBNF(扩展巴科斯范式)
### 符号定义
| 符号        | 说明   |
|-----------|------|
| =         | 定义   |
| ,         | 连接   |
| ;         | 结束   |
| \|        | 或    |
| ()        | 分组   |
| \[...]    | 可选   |
| {...}     | 重复   |
| "..."     | 字符串  |
| '...'     | 字符串  |
| (* ... *) | 注释   |
| ?...?     | 特殊序列 |
| -         | 除外   |

### 语法规则

1. 使用了如下约定:
   EBNF的每个元标识符(__meta-identifier__)都被写为用连字符(“-“, hyphens)连接起来的一个或多个单词；
   以 `-symbol` 结束的元标识符是EBNF的终端符号。

2. 用普通字符表示的EBNF操作符按照优先级(顶部为最高优先级)排序为:
   * **`*`: repetition-symbol**(重复符)
   * **`-`: except-symbol**(除去符)
   * **`,`: concatenate-symbol**(连接符)
   * **`|`: definition-separator-symbol**
   * **`=`: defining-symbol**(定义符)
   * **`;`: terminator-symbol**(结束符)
   * **`.`: terminator-symbol**(结束符)

3. 以下的括号对(__bracket pairs__)能够改变优先级，括号对间也有优先级(顶部为最高优先级):
   * **`'`  first-quote-symbol            first-quote-symbol `'`**    (\* 引用 *)
   * **`"`  second-quote-symbol          second-quote-symbol `"`**    (\* 引用 *)
   * **`(*` start-comment-symbol          end-comment-symbol `*)`**    (\* 注释 *)
   * **`(`  start-group-symbol              end-group-symbol `)`**    (\* 分组 *)
   * **`[`  start-option-symbol            end-option-symbol `]`**    (\* 可选 *)
   * **`{`  start-repeat-symbol            end-repeat-symbol `}`**    (\* 重复 *)
   * **`?`  special-sequence-symbol   special-sequence-symbol`?`**    (\* 特殊序列 *)

   下例示范了怎么表达重复：
   ```ebnf
      aa = "A";
      bb = 3 * aa, "B";
      cc = 3 * [aa], "C";
      dd = {aa}, "D";
      ee = aa, {aa}, "E";
      ff = 3 * aa, 3 * [aa], "F";
      gg = {3 * aa}, "D";
   ```
   
   这些规则定义的终端字符串如下:
   ```ebnf
      aa: A
      bb: AAAB
      cc: C AC AAC AAAC
      dd: D AD AAD AAAD AAAAD etc.
      ee: AE AAE AAAE AAAAE AAAAAE etc.
      ff: AAAF AAAAF AAAAAF AAAAAAF
      gg: D AAAD AAAAAAD etc.
   ```

4. 扩展
   除了标准的定义，在FREESCALE文档中还使用了以下约定：
   
   * 计数重复
      任何由`{`和`}`括起来并后跟一个上标x的东西必须准确地重复出现x次。x也可能是一个非终端字符。比如下例中，Stars相当于四个星号：
      Stars = {“*”}4.
   * 字节数
      见到任何紧跟着由一对中括号`[`和`]`括起来的数字n的标识符，都应该认为它是一个高位字节在前的二进制数，并且字节数为n，如：
      Struct=RefNo FilePos[4].
   在一些例子中，我们会使用”<”和”>”括起来一些文本。这些文本是 元文本(meta–literal)，它们的位置应该被它们所描述的东西替代掉，如，对于 < any char >，它的位置可以插入任意字符。
   
   示例
   以下提供一些示例以直观的理解EBNF。
   ```ebnf
       digit excluding zero = "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
       digit                = "0" | digit excluding zero ;
       natural number = digit excluding zero, { digit } ;
       integer = "0" | [ "-" ], natural number ;
   ```

   digit excluding zero 可以是 1到9任意一个字符，digit则扩展为0到9任意一个字符。
   natural number可以是1、2、…、10、…、12345、…，因为{}代表重复任意次，包括0次。
   integer则可以是0或者可能带个负号的自然数。

* 这是用EBNF描述的EBNF自身语法：
```ebnf
   Production     = NonTerminal "=" Expression ".".
   Expression     = Term {"|" Term}.
   Term           = Factor {Factor}.
   Factor         = NonTerminal
   | Terminal
   | "(" Expression ")"
   | "[" Expression "]"
   | "{" Expression "}".
   Terminal       = Identifier | “"“ <any char> “"“.
   NonTerminal    = Identifier.
```

非终端符号可以是任意你喜欢的名字，而终端符号则要不然是出现在被描述的语言中的标识符，要不然就是任何被引号括起来的字符序列。
然后Factor(参数)可以是终端字符、非终端字符、三种括号中任意一种括起来的表达式。
Term(术语)由起码一个Factor组合而成……

用EBNF描述的一个只能赋值的类PASCAL编程语言：
```ebnf
   (* a simple program syntax in EBNF − Wikipedia *)
   program = 'PROGRAM', white space, identifier, white space,
   'BEGIN', white space,
   { assignment, ";", white space },
   'END.' ;
   identifier = alphabetic character, { alphabetic character | digit } ;
   number = [ "-" ], digit, { digit } ;
   string = '"' , { all characters - '"' }, '"' ;
   assignment = identifier , ":=" , ( number | identifier | string ) ;
   alphabetic character = "A" | "B" | "C" | "D" | "E" | "F" | "G"
   | "H" | "I" | "J" | "K" | "L" | "M" | "N"
   | "O" | "P" | "Q" | "R" | "S" | "T" | "U"
   | "V" | "W" | "X" | "Y" | "Z" ;
   digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
   white space = ? white space characters ? ;
   all characters = ? all visible characters ? ;
```

对应的语法正确的程序如下：
```pascal
   PROGRAM DEMO1
   BEGIN
   A:=3;
   B:=45;
   H:=-100023;
   C:=A;
   D123:=B34A;
   BABOON:=GIRAFFE;
   TEXT:="Hello world!";
   END.
```

