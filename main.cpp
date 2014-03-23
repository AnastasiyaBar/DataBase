#include"functions.h"

int main()
{
	dbEntry* database=NULL;
	int dbSize = 0;
	if (!loadDatabase(&database, &dbSize))
	{
		cout << "Failed to open database, feeding by preset values" << endl;
		initDatabase(&database, &dbSize);
		cout << "Press any key to continue" << endl;
		_getch();
	}
	while (true)
	{
		legend();
		switch (_getch())
		{
			case 'a': addMountain(&database, &dbSize); break;
			case 'w': saveDatabase(database, dbSize); break;
			case 'q': return (0);
			case 'p': showDatabase(database, dbSize); break;
			case 'n': sortDatabase(database, dbSize, cmpname);
				showDatabase(database, dbSize); break;
			case 'N': sortDatabase(database, dbSize, ncmpname);
				showDatabase(database, dbSize); break;
			case 'l': sortDatabase(database, dbSize, cmplocation);
				showDatabase(database, dbSize); break;
			case 'L': sortDatabase(database, dbSize, ncmplocation);
				showDatabase(database, dbSize); break;
			case 'h': sortDatabase(database, dbSize, cmpheight);
				showDatabase(database, dbSize); break;
			case 'H': sortDatabase(database, dbSize, ncmpheight);
				showDatabase(database, dbSize); break;
			case 's': sortDatabase(database, dbSize, cmpsteepness);
				showDatabase(database, dbSize); break;
			case 'S': sortDatabase(database, dbSize, ncmpsteepness);
				showDatabase(database, dbSize); break;
		}
	}
	return 0;
}
