#include"functions.h"

dbEntry startup[] = //начальные данные при пустой базе
{
	{ "Everest(Qomolangma)", 8848, "Mahalangur - Himal, Himalayas", 60 },
	{ "K2(Chogori)", 8611, "Baltoro Muztagh, Karakoram", 55 },
	{ "Kanchenjunga", 8586, "Kanchenjunga, the Himalayas", 50 },
	{ "Lhotse", 8516, "Mahalangur - Himal, Himalayas", 52 },
	{ "Makalu", 8485, "Mahalangur - Himal, Himalayas", 47 },
	{ "Cho - Oyu", 8188, "Mahalangur - Himal, Himalayas", 58 },
	{ "Dhaulagiri", 8167, "Dhaulagiri Himalaya", 30 },
	{ "Manaslu", 8163, "Manaslu Himalayas", 39 },
	{ "Nanga Parbat", 8126, "Nanga Parbat, the Himalayas", 57 },
	{ "Annapurna I", 8091, "Annapurna, Himalayas", 42 },
	{ "Gasherbrum I", 8080, "Baltoro Muztagh, Karakoram", 50 },
	{ "Broad Peak", 8051, "Baltoro Muztagh, Karakoram", 44 },
	{ "Gasherbrum II", 8034, "Baltoro Muztagh, Karakoram", 51 },
	{ "Shisha - Pangma", 8027, "Langtang, Himalayas", 41 },
	{ "Giachung Kang", 7952, "Mahalangur - Himal, Himalayas", 45 },
	{ "Gasherbrum III", 7946, "Baltoro Muztagh, Karakoram", 40 },
	{ "Annapurna II", 7937, "Annapurna, Himalayas", 53 },
	{ "Gasherbrum IV", 7932, "Baltoro Muztagh, Karakoram", 46 },
	{ "Himalchuli", 7893, "Manaslu Himalayas", 52 },
	{ "Dastoghil", 7884, "Hispar Muztagh, Karakoram", 48 },
	{ "Ngadi Chuli", 7871, "Manaslu Himalayas", 47 },
	{ "", 0, "", 0 }
};

void addRecord(dbEntry** database, int* dbSize, dbEntry* newRecord)
{
	dbEntry* newDb = new dbEntry[(*dbSize)+1];
	for (int cnt = 0; cnt < *dbSize; cnt++)
		newDb[cnt] = (*database)[cnt];
	newDb[*dbSize] = *newRecord;
	(*dbSize)++;
	if (*database)
		delete[] * database;
	*database = newDb;
}

bool loadDatabase(dbEntry** database, int* dbSize)
{
	fstream dbfile;
	dbfile.open("mountains.txt", ios::in | ios::binary);
	if (!dbfile.is_open())
		return false;
	while (!dbfile.eof())
	{
		dbEntry record;
		dbfile.read((char*)&record, sizeof(dbEntry));
		if (!dbfile.fail())
			addRecord(database, dbSize, &record);
	}
	dbfile.close();
	return true;
}

bool saveDatabase(dbEntry* database, int dbSize)
{
	fstream dbfile;
	dbfile.open("mountains.txt", ios::out | ios::binary);
	if (!dbfile.is_open())
		return false;
	for (int cnt = 0; cnt<dbSize; cnt++)
		dbfile.write((char*)&database[cnt], sizeof(dbEntry));
	dbfile.close();
	return true;
}

void initDatabase(dbEntry** database, int* dbSize)
{
	for (*dbSize = 0;; (*dbSize)++)
		if (!startup[*dbSize].name[0])
			break;
	if (*database)
		delete[] *database;
	*database = new dbEntry[*dbSize];
	for (int cnt = 0; cnt<*dbSize; cnt++)
		(*database)[cnt]=startup[cnt];
}

void showDatabase(dbEntry* database, int dbSize)
{
	int maxname = 0;
	int maxlocation = 0;
	char pgraph[] = "+-|";
	for (int cnt = 0; cnt < dbSize; cnt++)  //вычисляем максимальные размеры полей названия и места расположения
	{
		int len = strlen(database[cnt].name);
		if (len>maxname) maxname = len;
		len = strlen(database[cnt].location);
		if (len>maxlocation) maxlocation = len;
	}
	cout << " " << pgraph[0];  // шапка
	for (int cnt = 0; cnt < maxname + 2; cnt++) cout << pgraph[1];
	cout << pgraph[0];
	for (int cnt = 0; cnt < maxlocation + 2; cnt++) cout << pgraph[1];
	cout << pgraph[0];
	for (int cnt = 0; cnt < 6; cnt++) cout << pgraph[1]; //высота - 4 символа
	cout << pgraph[0];
	for (int cnt = 0; cnt < 4; cnt++) cout << pgraph[1]; //крутизна - 2 символа
	cout << pgraph[0] << endl;

	for (int cnt = 0; cnt < dbSize; cnt++)
	{
		cout << " " << pgraph[2] << " " << setw(maxname) << database[cnt].name;
		cout << " " << pgraph[2] << " " << setw(maxlocation) << database[cnt].location;
		cout << " " << pgraph[2] << " " << setw(4) << database[cnt].height;
		cout << " " << pgraph[2] << " " << setw(2) << database[cnt].steepness << " " << pgraph[2] << endl;

		if (cnt && !(cnt % 20)) //каждые 20 строк "придерживаем" вывод, т.к. "легенда" занимает 3 строки и первые строки может "смыть" выводом
		{
			cout << "Press any key to continue\r";
			_getch();
		}
	}

	cout << " " << pgraph[0]; // хвост таблицы
	for (int cnt = 0; cnt < maxname + 2; cnt++) cout << pgraph[1];
	cout << pgraph[0];
	for (int cnt = 0; cnt < maxlocation + 2; cnt++) cout << pgraph[1];
	cout << pgraph[0];
	for (int cnt = 0; cnt < 6; cnt++) cout << pgraph[1]; //высота - 4 символа
	cout << pgraph[0];
	for (int cnt = 0; cnt < 4; cnt++) cout << pgraph[1]; //крутизна - 2 символа
	cout << pgraph[0] << endl;
}

int cmpname(dbEntry& left, dbEntry& right)
{
	return strcmp(left.name, right.name);
}

int cmplocation(dbEntry& left, dbEntry& right)
{
	return strcmp(left.location, right.location);
}

int cmpheight(dbEntry& left, dbEntry& right)
{
	float tmp = left.height - right.height;
	if (tmp == 0.0) return 0;
	if (tmp < 0) return -1;
	return 1;
}

int cmpsteepness(dbEntry& left, dbEntry& right)
{
	float tmp=left.steepness - right.steepness;
	if (tmp == 0.0) return 0;
	if (tmp < 0) return -1;
	return 1;
}

int ncmpname(dbEntry& left, dbEntry& right)
{
	return -cmpname(left, right);
}

int ncmplocation(dbEntry& left, dbEntry& right)
{
	return -cmplocation(left, right);
}

int ncmpheight(dbEntry& left, dbEntry& right)
{
	return -cmpheight(left, right);
}

int ncmpsteepness(dbEntry& left, dbEntry& right)
{
	return -cmpsteepness(left, right);
}

void Repair(dbEntry *database, int i, int dbSize, cmpptr fcompare)
{
    int l=2*i+1;
    int r=2*i+2;
    int larg=i;
    if(l<dbSize && fcompare(database[l],database[i])>0)larg=l;
    if(r<dbSize && fcompare(database[larg],database[r])<0)larg=r;
    if(larg!=i)
    {
        swap(database[larg], database[i]);
        Repair(database, larg, dbSize, fcompare);
    }
}

void Build(dbEntry *database, int dbSize, cmpptr fcompare)
{
    for(int i=dbSize/2; i>=0; --i)
        Repair(database, i, dbSize, fcompare);
}

void sortDatabase(dbEntry *database, int dbSize, cmpptr fcompare)
{
    Build(database, dbSize, fcompare);
    for(int i=dbSize-1; i>=1; --i)
    {
        swap(database[0], database[i]);
        Repair(database,0,i,fcompare);
    }
}

void legend()
{
	cout << "Command:\n a: add record\n p: print records\n w: write/save database\n q: quit;" << endl;
	cout << "Sort database(ascending/descending):\n n/N: by name\n l/L: by location\n h/H: by height\n s/S: by steepness;" << endl;
}

void addMountain(dbEntry** database, int* dbSize)
{
	dbEntry newRecord;
	cout << "New mountain name:";
	cin >> newRecord.name;
	cout << "New mountain location:";
	cin >> newRecord.location;
	cout << "New mountain height:";
	cin >> newRecord.height;
	cout << "New mountain steepness:";
	cin >> newRecord.steepness;
	addRecord(database, dbSize, &newRecord);
}
