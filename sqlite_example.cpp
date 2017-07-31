#include <locale.h>
#include <tchar.h>

#include "sqlite3.h"

int main(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "");

    int ret;

    // データベースのオープン
    // オープンに失敗しても、Closeは行う必要がある。
    sqlite3* dp = NULL;
    ret = sqlite3_open("testdb.dat", &dp);
    __try {
        if (ret != SQLITE_OK) {
            printf("エラーメッセージ: %s\n", sqlite3_errmsg16(dp));
            __leave;
        }

        // 作成した行の取得
        stm = NULL;
        ret = sqlite3_prepare_v2(dp, L"SELECT IDX, VAL1, VAL2 FROM TESTTBL ORDER BY IDX", -1, &stm, NULL);
        if (ret == SQLITE_OK && stm) {
            // コメント等、有効なSQLステートメントでないと、戻り値はOKだがstmはNULLになる。
            __try {
                for (;;) {
                    ret = sqlite3_step(stm);
                    if (ret == SQLITE_ROW) {
                        const int idx = sqlite3_column_int(stm, 0); // インデックスは0ベース
                        const void* val1 = sqlite3_column_text(stm, 1);
                        const void* val2 = sqlite3_column_text(stm, 2);
                        printf("%d:%s:%s\n", idx,
                            val1 == NULL ? _TEXT("NULL") : val1,
                            val2 == NULL ? _TEXT("NULL") : val2);
                        continue;
                    }
                    break;
                }
                if (ret == SQLITE_ERROR) {
                    printf("LOOP中の失敗: %s\n", sqlite3_errmsg(dp));
                }
            }
            __finally {
                sqlite3_finalize(stm);
            }
        }
        else {
            printf("PREPAREDの失敗: %s\n", sqlite3_errmsg(dp));
            __leave;
        }
    }
    __finally {
        sqlite3_close(dp);
        _tprintf(_TEXT("closed\n"));
    }
    return 0;
}
