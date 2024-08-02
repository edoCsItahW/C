// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <windows.h>
#include "jdbc/mysql_driver.h"
#include <iostream>
#include <mysqlx/xdevapi.h>

int main()
{
	try
	{
		mysqlx::Session session("localhost", 33060, "root", "135246qq", "mysql");
		std::cout << "Connected to MySQL database successfully!" << std::endl;
		mysqlx::SqlResult res = session.sql("SELECT * FROM users").execute();
		for (auto row : res.fetchAll())
		{
			std::cout << "ID: " << row[0].get<int>() << ", Name: " << row[1].get<std::string>() << std::endl;
		}
		session.close();
	}
	catch (const mysqlx::Error &err)
	{
		std::cerr << "Error: " << err.what() << std::endl;
		return 1;
	}
	return 0;
}
