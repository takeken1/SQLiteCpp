#ifndef __SQLITE_WP_H__
#define __SQLITE_WP_H__

#include "stdexcept"
#include "sqlite3.h"

class SQLiteException : public std::runtime_error
{
public:
    SQLiteException( const std::string& errorMessage) : std::runtime_error(errorMessage){}
};

class SQLiteWP
{
public:
    SQLiteWP(char* fileName);
    ~SQLiteWP(void);

    void PrepareStatement(char* query);
    int Step();
    void Exec(char* query);
    sqlite3_stmt* GetStatement();
    int BeginTransaction();
    int CommitTransaction();

private:
    sqlite3 *m_pDataBase;
    sqlite3_stmt *m_pStatement;
    bool m_bStatementPrepared;
    bool m_bStepOK;
    bool m_bStepDone;
    bool m_bTransactionBegined;
    bool m_bCommited;
};

#endif
