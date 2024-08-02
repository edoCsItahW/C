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
 * @Date: 2024/05/21 上午11:18
 * @Commend:
 *******************************************************/
#include <string.h>
#include <ctype.h>

/** 关于各类型值的枚举
 *
 * */
typedef enum {
	Int,
	Char,
	String,
	Float,
	Double,
	Bool,
	Void,
	Array_,
	Dict_,
	IntArr,
	StrArr
} Type;

char* typeNames[] = {
	"int",
	"char",
	"char*",
	"float",
	"double",
	"_Bool",
	"void",
	"Array_",
	"Dict_",
	"int*",
	"char**",
};

#define getType(value) _Generic((value), \
	int: Int,                               \
	char: Char,                             \
	char*: String,                          \
	float: Float,                           \
	double: Double,                         \
	_Bool: Bool,                            \
	int*: IntArr,                           \
	char**: StrArr,                         \
 	default: Void                          \
 )


#define getTypeName(value) _Generic((value), \
	int: "int",                               \
	char: "char",                             \
	char*: "char*",                          \
	float: "float",                           \
	double: "double",                         \
	_Bool: "_Bool",                            \
	int*: "int*",                           \
	char**: "char**",                         \
 	default: "void"                          \
 )

typedef struct {
	char* str;
	Type type;
} TypeMapping;

TypeMapping typeMap[] = {
	{"Int", Int},
	{"int", Int},
	{"Char", Char},
	{"char", Char},
	{"String", String},
	{"char*", String},
	{"Float", Float},
	{"float", Float},
	{"Double", Double},
	{"double", Double},
	{"Bool", Bool},
	{"_Bool", Bool},
	{"Void", Void},
	{"void", Void},
	{"Array_", Array_},
	{"Dict_", Dict_},
	{"IntArr", IntArr},
	{"int*", IntArr},
	{"StrArr", StrArr},
	{"char**", StrArr},
};

#define strType(type) #type

char* lower(char *str) {
	for (int i = 0; i < strlen(str); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}

Type _getStrType(char* type) {

	for (int i = 0; i < sizeof(typeMap) / sizeof(typeMap[0]); i++)
	{
		if (strcmp(lower(type), typeMap[i].str) == 0)
		{
			return typeMap[i].type;
		}
	}
	return Void;

}

#define getStrType(type) _getStrType(strType(type))
