#include "ynhsql.h"

Ynhsql::Ynhsql()
{
    m_conn = mysql_init(nullptr);
    if (m_conn == nullptr )
    {
        std::cout << "mysql_init failed" << std::endl;
    }
    

    mysql_set_character_set(m_conn, "utf8");
}

Ynhsql::~Ynhsql()
{
    if(m_conn != nullptr)
    {
        mysql_close(m_conn);
    }
    freeRes();
}

bool Ynhsql::connect(std::string user, std::string passwd, std::string dbName, std::string ip, unsigned int port)
{
    MYSQL* ptr = mysql_real_connect(m_conn, ip.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), port, nullptr, 0);
    return ptr != nullptr;
}

bool Ynhsql::update(std::string sql)
{
    if (mysql_query(m_conn, sql.c_str()))
    {
        return false;
    }
    return true;
}

bool Ynhsql::query(std::string sql)
{
    freeRes();
    if (mysql_query(m_conn, sql.c_str()))
    {
        return false;
    }
    m_res = mysql_store_result(m_conn);
    return true;
}

bool Ynhsql::next()
{
    if(m_res != nullptr)
    {
        m_row = mysql_fetch_row(m_res);
        if(m_row != nullptr)
        {
            return true;
        }
    }
    return false;
}

std::string Ynhsql::value(int index)
{
    int columCount = mysql_num_fields(m_res);
    if(index >= columCount || index < 0)
    {
        return std::string();
    }
    char* val = m_row[index];
    unsigned long length =  mysql_fetch_lengths(m_res)[index];
    return std::string(val, length);
}

bool Ynhsql::transaction()
{
    return mysql_autocommit(m_conn, false);
}

bool Ynhsql::commit()
{
    return mysql_commit(m_conn);
}

bool Ynhsql::rollback()
{
    return mysql_rollback(m_conn);
}

void Ynhsql::freeRes()
{
    if(m_res)
    {
        mysql_free_result(m_res);
        m_res = nullptr;
    }
}

void Ynhsql::refreshAliveTime()
{
    m_alivetime = std::chrono::steady_clock::now();
}

long long Ynhsql::getAliveTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_alivetime).count();
}