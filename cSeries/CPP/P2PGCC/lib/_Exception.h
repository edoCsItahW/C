// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/* 异常类
 *
 * 文件名：Exception.h
 *
 * 日期：2004.5.5
 *
 * 作者：shootingstars(zhouhuis22@sina.com)
 */

#ifndef __HZH_Exception__
#define __HZH_Exception__

#define EXCEPTION_MESSAGE_MAXLEN 256
#include <cstring>

class Exception {
	private:
		char m_ExceptionMessage[EXCEPTION_MESSAGE_MAXLEN]{};

	public:
	Exception(const char *msg) { strncpy(m_ExceptionMessage, msg, EXCEPTION_MESSAGE_MAXLEN); }

		char *GetMessage() { return m_ExceptionMessage; }
};


#endif
