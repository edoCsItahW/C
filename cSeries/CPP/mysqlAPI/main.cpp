// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: ProcessRoundCheck
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/07/12 ÏÂÎç9:38
 * @Commend:
 *******************************************************/
#include <format>
#include <iostream>
#include <mysql.h>
#include <string>

class Mysql {
    private:
        MYSQL* conn;

    public:
        Mysql(const std::string& user, const std::string& passwd, const std::string& db, const std::string& host = "localhost", int port = 0)
            : conn(mysql_real_connect(mysql_init(nullptr), host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, nullptr, 0)) {}

        void assert(bool expr, std::string msg = "") {
            if (!expr) {
                auto err = mysql_error(conn);
                std::cerr << std::format("Error: {} - {}", err ? err : "Unknown reason", msg) << std::endl;
            }
        }

        void execute(const std::string& cmd) {
            int sec = mysql_query(conn, cmd.c_str());

            assert(sec == 0, "Failed to execute command");

            MYSQL_RES* res = mysql_store_result(conn);

            assert(res, "Failed to retrieve result set");

            int num = mysql_num_rows(res);

            MYSQL_FIELD* fields = mysql_fetch_fields(res);

            for (int i = 0; i < num; ++i)
                std::cout << fields[i].name << " ";

            std::cout << std::endl;

            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)))
                for (int i = 0; i < num; i++)
                    std::cout << row[i] << " ";

            std::cout << std::endl;

            mysql_free_result(res);
        }
};

int main() {
    Mysql mysql("root", "135246qq", "temp");

    mysql.execute("SHOW DATABASES");

    return 0;
}
