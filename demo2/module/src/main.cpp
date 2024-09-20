#include <iostream>
#include "ynhsql.h"

int query()
{
    Ynhsql conn;
    if(!conn.connect("root", "@ynh123", "mydatabase", "127.0.0.1"))
    {
        std::cout << "mysql connect failed " << std::endl;
    }
    std::string sql = "INSERT INTO person VALUES(4, 23, 'woman', 'luna');";
    bool flag = conn.update(sql);
    std::cout << "flag val: " << flag << std::endl;

    sql = "SELECT * FROM person";
    conn.query(sql);
    while(conn.next())
    {
        std::cout << conn.value(0) << ", "
                << conn.value(1) << ", "
                << conn.value(2) << ", "
                << conn.value(3) << std::endl;
    } 
    return 0;
}

int main()
{
    query();
    return 0;
}