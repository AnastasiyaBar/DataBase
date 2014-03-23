#include <fstream>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>
using namespace std;

struct dbEntry
{
	char name[64];
	float height;
	char location[64];
	float steepness;
};
void addRecord(dbEntry** database, int* dbSize, dbEntry* newRecord);
bool loadDatabase(dbEntry** database, int* dbSize);
bool saveDatabase(dbEntry* database, int dbSize);
void initDatabase(dbEntry** database, int* dbSize);
void showDatabase(dbEntry* database, int dbSize);
typedef int(*cmpptr)(dbEntry& left, dbEntry& right);
int cmpname(dbEntry& left, dbEntry& right);
int cmplocation(dbEntry& left, dbEntry& right);
int cmpheight(dbEntry& left, dbEntry& right);
int cmpsteepness(dbEntry& left, dbEntry& right);
int ncmpname(dbEntry& left, dbEntry& right);
int ncmplocation(dbEntry& left, dbEntry& right);
int ncmpheight(dbEntry& left, dbEntry& right);
int ncmpsteepness(dbEntry& left, dbEntry& right);
void Repair(dbEntry *database, int i, int dbSize, cmpptr fcompare);
void Build(dbEntry *database, int dbSize, cmpptr fcompare);
void sortDatabase(dbEntry *database, int dbSize, cmpptr fcompare);
void legend();
void addMountain(dbEntry** database, int* dbSize);
