#include <iostream>
#include <lmdb.h>
#include <ctime>
#include <rpc.h>
#define _CRT_RAND_S  

#include <stdio.h>  

#pragma comment(lib,"Rpcrt4.lib")
using namespace std;

int WriteRandom()
{
	cout<<"Press any key to start random writes..."<<endl;
	getchar();
	cout<<"Started writing random data"<<endl;
    int i = 0, j = 0, rc;
    UUID id;
    MDB_env *env;

    MDB_val key, data;

    MDB_stat mst;
    MDB_cursor *cursor;
    char sval[128*3];
    clock_t start = clock(), end;
	
    rc = mdb_env_create(&env);
    rc = mdb_env_set_mapsize(env, 1024*1024*768);
    rc = mdb_env_set_flags(env, MDB_WRITEMAP, 1);

	//change this path to empty folder that is already created
    rc = mdb_env_open(env, "E:\\data\\lmdb2\\random", 0, 0664);
	if(rc != 0)
	{
		mdb_env_close(env);
		return rc;
	}
    key.mv_size = sizeof(UUID);
    data.mv_size = sizeof(sval);
    data.mv_data = sval;
    
    for (i=0;i<100;i++) {    
        MDB_txn *txn;
        MDB_dbi dbi;

        rc = mdb_txn_begin(env, NULL, 0, &txn);
        rc = mdb_open(txn, NULL, 0, &dbi);

        for (j= 0; j < 100; j++)
        {
            UuidCreate(&id);
            
            key.mv_data = &id;
            rc = mdb_put(txn, dbi, &key, &data, 0);
        }

        rc = mdb_txn_commit(txn);
        mdb_close(env, dbi);
    }

    end = clock();

    printf("%i", (end - start));
    fgetc(stdin);
    mdb_env_close(env);
}

int WriteSequential()
{
	cout<<"Press any key to start sequential writes..."<<endl;
	getchar();
	cout<<"Started writing sequential data"<<endl;
    int i = 0, j = 0, rc;
    UUID id;
    MDB_env *env;

    MDB_val key, data;

    MDB_stat mst;
    MDB_cursor *cursor;
    char sval[128*3];
    clock_t start = clock(), end;
	
    rc = mdb_env_create(&env);
    rc = mdb_env_set_mapsize(env, 1024*1024*768);
    rc = mdb_env_set_flags(env, MDB_WRITEMAP, 1);
	
	//change this folder to valid and empty
    rc = mdb_env_open(env, "E:\\data\\lmdb2\\sequential", 0, 0664);
	if(rc != 0)
	{
		mdb_env_close(env);
		return rc;
	}
    key.mv_size = sizeof(UUID);
    data.mv_size = sizeof(sval);
    data.mv_data = sval;
    
    for (i=0;i<100;i++) {    
        MDB_txn *txn;
        MDB_dbi dbi;

        rc = mdb_txn_begin(env, NULL, 0, &txn);
        rc = mdb_open(txn, NULL, 0, &dbi);

        for (j= 0; j < 100; j++)
        {
            UuidCreateSequential(&id);
            
            key.mv_data = &id;
            rc = mdb_put(txn, dbi, &key, &data, 0);
        }

        rc = mdb_txn_commit(txn);
        mdb_close(env, dbi);
    }

    end = clock();

    printf("%i", (end - start));
    fgetc(stdin);
    mdb_env_close(env);
}

int main(int argc,char * argv[])
{
	WriteRandom();
	WriteSequential();

    return 0;
}

