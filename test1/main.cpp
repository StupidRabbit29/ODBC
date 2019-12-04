#include<iostream>
#include<Windows.h>
#include<sql.h>
#include <sqlext.h>

using namespace std;

int main()
{
	SQLHENV env = SQL_NULL_HENV;//����
	SQLHDBC conn = SQL_NULL_HDBC;//����
	SQLHSTMT stmt = SQL_NULL_HSTMT;//���
	SQLRETURN ret;//����״̬

	char Sector_ID1[50] = { '\0' };
	char Sector_ID2[50] = { '\0' };
	int lenOut1 = 0;
	int lenOut2 = 0;

	const char* query = "select S.CITY as CITY1, N.CITY as CITY2 into NewENODEB \
							from ENODEB as S, ENODEB as N; ";
	
	//���价��
	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
	cout << ret << endl;
	//����ODBC�汾
	ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	cout << ret << endl;

	//ret = SQLSetConnectAttr(conn, SQL_ATTR_LOGIN_TIMEOUT, (void*)5, 0);

	//��������
	ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &conn);
	cout << ret << endl;

	//��������Դ
	ret = SQLConnect(conn, (SQLCHAR*)"TD_LTE2", SQL_NTS, (SQLCHAR*)"test", SQL_NTS, (SQLCHAR*)"123", SQL_NTS);
	cout << ret << endl;
	
	//�������
	SQLAllocHandle(SQL_HANDLE_STMT, conn, &stmt);
	cout << ret << endl;

	//��ʱ
	ret = SQLSetStmtAttr(stmt, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)1, SQL_IS_INTEGER);
	cout << ret << endl;
	
	//��ѯ
	ret = SQLExecDirect(stmt, (SQLCHAR*)query, SQL_NTS);
	cout << ret << endl;

	if (ret == SQL_SUCCESS)
	{
		SQLBindCol(stmt, 1, SQL_C_CHAR, Sector_ID1, 50, (SQLLEN*)&lenOut1);
		SQLBindCol(stmt, 2, SQL_C_CHAR, Sector_ID2, 50, (SQLLEN*)&lenOut2);

		while (SQLFetch(stmt) == SQL_SUCCESS)
		{
			cout << Sector_ID1 << "\t" << Sector_ID2 << endl;
		}
	}
	else
		cout << "Failed!" << ret << endl;
	
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);//�ͷ����
	SQLDisconnect(conn);//�Ͽ�����
	SQLFreeHandle(SQL_HANDLE_DBC, conn);//�ͷ�����
	SQLFreeHandle(SQL_HANDLE_ENV, env);//�ͷŻ���


	return 0;
}