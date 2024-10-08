#  Copyright (c) 2024. All rights reserved.
#  This source code is licensed under the CC BY-NC-SA
#  (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
#  This software is protected by copyright law. Reproduction, distribution, or use for commercial
#  purposes is prohibited without the author's permission. If you have any questions or require
#  permission, please contact the author: 2207150234@st.sziit.edu.cn
from ast import AST, parse, NodeVisitor, FunctionDef


for i in range(10):
    print(i)
else:
    print('done')

tmp = 10
while tmp > 0:
    print(tmp)
    tmp -= 1
else:
    print('done')

if tmp > 0:
    print('not done')
elif tmp == 0:
    print('done')
else:
    print('unknown')

match tmp:
    case 0:
        print('done')
    case _:
        print('not done')

class Visitor(NodeVisitor):
    def visit(self, node):
        super().visit(node)
        print(node)


def ast_to_dict(node: AST = None, *args, kw: str = None, **kwargs):
    if isinstance(node, AST):
        return {
            'type': node.__class__.__name__,
            **{field: ast_to_dict(getattr(node, field)) for field in node._fields},
        }
    elif isinstance(node, list):
        return [ast_to_dict(x) for x in node]
    else:
        return node


if __name__ == '__main__':
    from json import dumps
    with open(__file__, 'r', encoding='utf-8') as file:
        module = parse(file.read())

        with open('ast.json', 'w', encoding='utf-8') as f:
            f.write(dumps(ast_to_dict(module), indent=4))
    # print(FunctionDef)
