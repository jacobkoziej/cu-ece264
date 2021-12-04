// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
	   << pData->firstName << " " 
	   << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

#include <climits>
#include <cstdint>


#define MAX_ITEMS 1200000
#define T1_LIMIT  200000


class p2_sort {
private:
	struct uniq_prefix {
		unsigned count;
		struct uniq_prefix *child[UCHAR_MAX + 1];

		uniq_prefix(void) {
			count = 0;
			memset(child, 0, sizeof(child));
		}
	};

	static const string last_names[500];
	struct uniq_prefix *uniq_prefix_root;

	Data **buf;

	static inline bool full_cmp(const Data *a, const Data *b);
	static inline bool ssn_cmp(const Data *a, const Data *b);

	void std_sort(bool (*cmp) (const Data *a, const Data *b));

public:
	uint_fast32_t nodes;
	list<Data *> *src;
	Data *front, *back;

	/*
	 * We're going to fully abuse the fact that we can run
	 * constructors before main().  This will allow for us to
	 * dynamically allocate data structure which are far too tedious
	 * to allocate statically.
	 */
	p2_sort(void);

	inline void t1_sort(void) { std_sort(full_cmp); }
	inline void t2_sort(void) { std_sort(full_cmp); }
	inline void t3_sort(void) { std_sort(full_cmp); }
	inline void t4_sort(void) { std_sort(ssn_cmp); }
};

const string p2_sort::last_names[500] = {
	"ACOSTA",     "ADAMS",      "ADKINS",      "AGUILAR",
	"AGUIRRE",    "ALEXANDER",  "ALLEN",       "ALVARADO",
	"ALVAREZ",    "ANDERSON",   "ANDREWS",     "ARMSTRONG",
	"ARNOLD",     "AUSTIN",     "AVILA",       "AYALA",
	"BAILEY",     "BAKER",      "BALDWIN",     "BANKS",
	"BARBER",     "BARKER",     "BARNES",      "BARNETT",
	"BARRETT",    "BARTON",     "BATES",       "BECK",
	"BECKER",     "BELL",       "BENNETT",     "BENSON",
	"BERRY",      "BISHOP",     "BLACK",       "BLAIR",
	"BLAKE",      "BOWEN",      "BOWMAN",      "BOYD",
	"BRADLEY",    "BRADY",      "BREWER",      "BROOKS",
	"BROWN",      "BRYANT",     "BURGESS",     "BURKE",
	"BURNS",      "BURTON",     "BUSH",        "BUTLER",
	"BYRD",       "CABRERA",    "CALDERON",    "CALDWELL",
	"CAMACHO",    "CAMPBELL",   "CAMPOS",      "CANNON",
	"CARDENAS",   "CARLSON",    "CARPENTER",   "CARR",
	"CARRILLO",   "CARROLL",    "CARTER",      "CASTANEDA",
	"CASTILLO",   "CASTRO",     "CERVANTES",   "CHAMBERS",
	"CHAN",       "CHANDLER",   "CHANG",       "CHAPMAN",
	"CHAVEZ",     "CHEN",       "CHRISTENSEN", "CLARK",
	"CLARKE",     "COHEN",      "COLE",        "COLEMAN",
	"COLLINS",    "COLON",      "CONTRERAS",   "COOK",
	"COOPER",     "CORTEZ",     "COX",         "CRAIG",
	"CRAWFORD",   "CROSS",      "CRUZ",        "CUMMINGS",
	"CUNNINGHAM", "CURRY",      "CURTIS",      "DANIEL",
	"DANIELS",    "DAVIDSON",   "DAVIS",       "DAWSON",
	"DAY",        "DEAN",       "DELACRUZ",    "DELEON",
	"DELGADO",    "DENNIS",     "DIAZ",        "DIXON",
	"DOMINGUEZ",  "DOUGLAS",    "DOYLE",       "DUNCAN",
	"DUNN",       "DURAN",      "EDWARDS",     "ELLIOTT",
	"ELLIS",      "ERICKSON",   "ESPINOZA",    "ESTRADA",
	"EVANS",      "FARMER",     "FERGUSON",    "FERNANDEZ",
	"FIELDS",     "FIGUEROA",   "FISCHER",     "FISHER",
	"FITZGERALD", "FLEMING",    "FLETCHER",    "FLORES",
	"FORD",       "FOSTER",     "FOWLER",      "FOX",
	"FRANCIS",    "FRANCO",     "FRANK",       "FRANKLIN",
	"FRAZIER",    "FREEMAN",    "FUENTES",     "FULLER",
	"GALLAGHER",  "GALLEGOS",   "GARCIA",      "GARDNER",
	"GARNER",     "GARRETT",    "GARZA",       "GEORGE",
	"GIBSON",     "GILBERT",    "GILL",        "GOMEZ",
	"GONZALES",   "GONZALEZ",   "GOODMAN",     "GOODWIN",
	"GORDON",     "GRAHAM",     "GRANT",       "GRAVES",
	"GRAY",       "GREEN",      "GREENE",      "GREGORY",
	"GRIFFIN",    "GRIFFITH",   "GROSS",       "GUERRA",
	"GUERRERO",   "GUTIERREZ",  "GUZMAN",      "HAIL",
	"HALE",       "HALL",       "HAMILTON",    "HAMMOND",
	"HAMPTON",    "HANSEN",     "HANSON",      "HARDY",
	"HARMON",     "HARPER",     "HARRINGTON",  "HARRIS",
	"HARRISON",   "HART",       "HARVEY",      "HAWKINS",
	"HAYES",      "HAYNES",     "HENDERSON",   "HENRY",
	"HERNANDEZ",  "HERRERA",    "HICKS",       "HIGGINS",
	"HILL",       "HINES",      "HODGES",      "HOFFMAN",
	"HOLLAND",    "HOLMES",     "HOLT",        "HOPKINS",
	"HORTON",     "HOWARD",     "HOWELL",      "HUANG",
	"HUBBARD",    "HUDSON",     "HUGHES",      "HUNT",
	"HUNTER",     "INGRAM",     "JACKSON",     "JACOBS",
	"JAMES",      "JENKINS",    "JENNINGS",    "JENSEN",
	"JIMENEZ",    "JOHNSON",    "JOHNSTON",    "JONES",
	"JORDAN",     "JOSEPH",     "JUAREZ",      "KELLER",
	"KELLEY",     "KELLY",      "KENNEDY",     "KHAN",
	"KIM",        "KING",       "KLEIN",       "KNIGHT",
	"LAMBERT",    "LANE",       "LARA",        "LARSON",
	"LAWRENCE",   "LAWSON",     "LE",          "LEE",
	"LEON",       "LEONARD",    "LEWIS",       "LI",
	"LIN",        "LITTLE",     "LIU",         "LOGAN",
	"LONG",       "LOPEZ",      "LOVE",        "LOWE",
	"LUCAS",      "LUNA",       "LYNCH",       "LYONS",
	"MACK",       "MALDONADO",  "MALONE",      "MANN",
	"MANNING",    "MARQUEZ",    "MARSHALL",    "MARTIN",
	"MARTINEZ",   "MASON",      "MATTHEWS",    "MAXWELL",
	"MAY",        "MCCARTHY",   "MCCOY",       "MCDANIEL",
	"MCDONALD",   "MCGEE",      "MCKINNEY",    "MCLAUGHLIN",
	"MEDINA",     "MEJIA",      "MENDEZ",      "MENDOZA",
	"MEYER",      "MILES",      "MILLER",      "MILLS",
	"MIRANDA",    "MITCHELL",   "MOLINA",      "MONTGOMERY",
	"MONTOYA",    "MOORE",      "MORALES",     "MORAN",
	"MORENO",     "MORGAN",     "MORRIS",      "MORRISON",
	"MOSS",       "MULLINS",    "MUNOZ",       "MURPHY",
	"MURRAY",     "MYERS",      "NAVARRO",     "NEAL",
	"NELSON",     "NEWMAN",     "NEWTON",      "NGUYEN",
	"NICHOLS",    "NORMAN",     "NORRIS",      "NUNEZ",
	"OBRIEN",     "OCHOA",      "OCONNOR",     "OLIVER",
	"OLSON",      "ORTEGA",     "ORTIZ",       "OWENS",
	"PACHECO",    "PADILLA",    "PAGE",        "PALMER",
	"PARK",       "PARKER",     "PARKS",       "PARSONS",
	"PATEL",      "PATTERSON",  "PAUL",        "PAYNE",
	"PEARSON",    "PENA",       "PEREZ",       "PERKINS",
	"PERRY",      "PERSON",     "PETERS",      "PETERSON",
	"PHAM",       "PHILLIPS",   "PIERCE",      "PORTER",
	"POTTER",     "POWELL",     "POWERS",      "PRICE",
	"QUINN",      "RAMIREZ",    "RAMOS",       "RAMSEY",
	"RAY",        "REED",       "REESE",       "REEVES",
	"REID",       "REYES",      "REYNOLDS",    "RHODES",
	"RICE",       "RICHARDS",   "RICHARDSON",  "RILEY",
	"RIOS",       "RIVAS",      "RIVERA",      "ROBBINS",
	"ROBERTS",    "ROBERTSON",  "ROBINSON",    "ROBLES",
	"RODGERS",    "RODRIGUEZ",  "ROGERS",      "ROJAS",
	"ROMAN",      "ROMERO",     "ROSALES",     "ROSE",
	"ROSS",       "ROWE",       "RUIZ",        "RUSSELL",
	"RYAN",       "SALAZAR",    "SALINAS",     "SANCHEZ",
	"SANDERS",    "SANDOVAL",   "SANTIAGO",    "SANTOS",
	"SAUNDERS",   "SCHMIDT",    "SCHNEIDER",   "SCHROEDER",
	"SCHULTZ",    "SCHWARTZ",   "SCOTT",       "SERRANO",
	"SHARP",      "SHAW",       "SHELTON",     "SHERMAN",
	"SILVA",      "SIMMONS",    "SIMON",       "SIMPSON",
	"SIMS",       "SINGH",      "SMITH",       "SNYDER",
	"SOLIS",      "SOTO",       "SPENCER",     "STANLEY",
	"STEELE",     "STEPHENS",   "STEVENS",     "STEVENSON",
	"STEWART",    "STONE",      "STRICKLAND",  "SULLIVAN",
	"SUTTON",     "SWANSON",    "TATE",        "TAYLOR",
	"TERRY",      "THOMAS",     "THOMPSON",    "THORNTON",
	"TODD",       "TORRES",     "TOWNSEND",    "TRAN",
	"TRUJILLO",   "TUCKER",     "TURNER",      "VALDEZ",
	"VALENCIA",   "VARGAS",     "VASQUEZ",     "VAUGHN",
	"VAZQUEZ",    "VEGA",       "VELASQUEZ",   "WADE",
	"WAGNER",     "WALKER",     "WALLACE",     "WALSH",
	"WALTERS",    "WALTON",     "WANG",        "WARD",
	"WARNER",     "WARREN",     "WASHINGTON",  "WATERS",
	"WATKINS",    "WATSON",     "WATTS",       "WEAVER",
	"WEBB",       "WEBER",      "WEBSTER",     "WELCH",
	"WELLS",      "WEST",       "WHEELER",     "WHITE",
	"WILLIAMS",   "WILLIAMSON", "WILLIS",      "WILSON",
	"WISE",       "WOLF",       "WOLFE",       "WONG",
	"WOOD",       "WOODS",      "WRIGHT",      "WU",
	"YANG",       "YOUNG",      "ZHANG",       "ZIMMERMAN",
};

inline bool p2_sort::full_cmp(const Data *a, const Data *b)
{
	if (a->lastName != b->lastName) return a->lastName < b->lastName;
	if (a->firstName != b->firstName) return a->firstName < b->firstName;
	return a->ssn < b->ssn;
}

inline bool p2_sort::ssn_cmp(const Data *a, const Data *b)
{
	return a->ssn < b->ssn;
}

void p2_sort::std_sort(bool (*cmp) (const Data *a, const Data *b))
{
	list<Data*>::iterator node = src->begin();

	for (uint_fast32_t i = 0; i < nodes; i++, node++) buf[i] = *node;

	sort(buf, buf + nodes, cmp);

	node = src->begin();
	for (uint_fast32_t i = 0; i < nodes; i++, node++) *node = buf[i];
}

p2_sort::p2_sort(void)
{
	buf = new Data*[MAX_ITEMS];
	uniq_prefix_root = new uniq_prefix;
}

p2_sort p2;


void sortDataList(list<Data*> &l)
{
	p2.nodes = l.size();
	p2.src   = &l;

	if (p2.nodes < T1_LIMIT) {
		cout << "T1 detected!\n";
		p2.t1_sort();
		return;
	}

	p2.front = l.front();
	p2.back  = l.back();

	if (p2.front->lastName == p2.back->lastName) {
		cout << "T4 detected!\n";
		p2.t4_sort();
		return;
	}

	if (p2.front->lastName[0] == 'A' && p2.back->lastName[0] == 'Z') {
		cout << "T3 detected!\n";
		p2.t3_sort();
		return;
	}

	cout << "T2 detected!\n";
	p2.t2_sort();
}
