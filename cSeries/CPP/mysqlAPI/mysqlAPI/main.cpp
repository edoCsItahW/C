// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

#include <winsock.h>
#include <mysql.h>
#include <iostream>


int main() {
    MYSQL* conn = mysql_init(nullptr);

    if (conn == nullptr) {
        std::cout << "mysql_init failed" << std::endl;
        return 1;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "135246qq", "temp", 0, nullptr, 0);

    if (conn == nullptr) {
        std::cout << "connect failed" << std::endl;
        return 1;
    }

    std::cout << "Ĭ�ϱ���: " << mysql_character_set_name(conn) << std::endl;

    mysql_set_character_set(conn, "utf8");

    std::cout << "�޸ĺ�: " << mysql_character_set_name(conn) << std::endl;

    std::cout << "���ӳɹ�" << std::endl;

    int res1 = mysql_query(conn, "SELECT * from users");

    if (res1 != 0) {
        std::cout << "��ѯʧ��: " << mysql_error(conn) << std::endl;
        return 1;
    }

    MYSQL_RES* res2 = mysql_store_result(conn);

    if (res2 == NULL) {
        std::cout << "ȡֵʧ��: " << mysql_error(conn) << std::endl;
        return 1;
    }

    int num = mysql_num_fields(res2);

    MYSQL_FIELD* fields = mysql_fetch_fields(res2);

    for (int i = 0; i < num; i++) std::cout << "\t\t" << fields[i].name << std::endl;

    std::cout << "\n" << std::endl;

    MYSQL_ROW row;

}
