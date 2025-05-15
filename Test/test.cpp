#include "../Test/test.h"
#include "../KDtree/KDTree.h"
void test::doTest(char choice)
{
	unordered_map<int, vector<edge>> graph;
	unordered_map<int, vector<edge>> copyGraph;
	unordered_map<int, coordinates> coor;
	unordered_map<int, coordinates> copyCoor;
	vector<query> queries;
	vector<bestPath> p;
	float maxSpeed = -1;
	float timeInterval = 0;
	int speedSize;
	file f;
	string fileName;
	string queryFileName;
	string dir;
	string map;
	if (choice <= '5') {
		dir = "Data/testCases/[1] Sample Cases/input/";
		map = "map" + string(1, choice) + ".txt";
		fileName = dir + map;
		queryFileName = "Data/testCases/[1] Sample Cases/input/queries" + string(1, choice) + ".txt";
	}
	else if (choice == '6') {
		dir = "Data/testCases/[2] Medium Cases/input/";
		map = "OLMap.txt";
		fileName = dir + map;
		queryFileName = "Data/testCases/[2] Medium Cases/input/OLQueries.txt";
	}
	else if (choice == '7') {
		dir = "Data/testCases/[3] Large Cases/input/";
		map = "SFMap.txt";
		fileName = dir + map;
		queryFileName = "Data/testCases/[3] Large Cases/input/SFQueries.txt";
	}
	auto startIO = high_resolution_clock::now();

	coor = f.readFile(fileName, graph, maxSpeed);
	queries = f.readQuery(queryFileName);
	KDTree kd;
	kd.buildTree(coor);

	int sourcePointId;
	int destinationPointID;
	//10 will be replaced with q.
	
	for (query q : queries) {

		copyGraph = graph;
		copyCoor = coor;

		
		unordered_map<int, float> startPoints = kd.queryRadius(q.startCoordinate.x_coordinate,q.startCoordinate.y_coordinate,q.R);
		unordered_map<int, float> endPoints = kd.queryRadius(q.destCoordinate.x_coordinate, q.destCoordinate.y_coordinate, q.R);
		//add the start point and the distenation point in the graph for each qeuery
		sourcePointId = addNode(copyGraph, startPoints);
		destinationPointID = addNode(copyGraph, endPoints);
		addNode(copyCoor, q.startCoordinate);
		addNode(copyCoor, q.destCoordinate);

		A_Star path;
		p.push_back(path.A(copyGraph, sourcePointId, destinationPointID, maxSpeed, q.R, copyCoor));

		}
	

	f.writeFile(map, p);




	auto stopIO = high_resolution_clock::now();
	double elapsedTimeWithIO = duration<float, milli>(stopIO - startIO).count();
	cout << "Not added yet" << " ms" << endl;
	cout << endl;
	cout << elapsedTimeWithIO << " ms" << endl;
}

void test::bounsTest()
{
	unordered_map<int, vector<edge>> graph;
	unordered_map<int, vector<edge>> copyGraph;
	unordered_map<int, coordinates> coor;
	unordered_map<int, coordinates> copyCoor;
	vector<query> queries;
	vector<bestPath> p;
	float maxSpeed = -1;
	float timeInterval = 0;
	int speedSize = 0;
	file f;
	string fileName;
	string queryFileName;

	cout << "[4] BONUS Test Cases.\n";
	cout << "[1] Sample. [2] Medium.\n";
	int choice;
	cin >> choice;
	string dir1 = "Data/testCases/[4] BONUS Test Cases/[1] Sample Cases/Input/";
	string dir2 = "Data/testCases/[4] BONUS Test Cases/[1] Medium Cases/Input/";
	string map1 = "map1B.txt";
	string map2 = "OLMapB.txt";
	fileName = choice == 1 ? dir1 + map1 : dir2 + map2;

	queryFileName = choice == 1 ? "Data/testCases/[4] BONUS Test Cases/[1] Sample Cases/Input/queries1.txt" :
		"Data/testCases/[4] BONUS Test Cases/[1] Medium Cases/Input/OLQueries.txt";

	auto startIO = high_resolution_clock::now();

	coor = f.readFile(fileName, graph, maxSpeed, timeInterval, speedSize);
	queries = f.readQuery(queryFileName);

	int sourcePointId;
	int destinationPointID;
	//10 will be replaced with q.numberOfQueries
	for (query q : queries) {

		copyGraph = graph;
		copyCoor = coor;
		unordered_map<int, float> startPoints = getNodesWithinRadius(q.startCoordinate.x_coordinate, q.startCoordinate.y_coordinate, q.R, copyCoor);
		unordered_map<int, float> endPoints = getNodesWithinRadius(q.destCoordinate.x_coordinate, q.destCoordinate.y_coordinate, q.R, copyCoor);
		//add the start point and the distenation point in the graph for each qeuery
		sourcePointId = addNode(copyGraph, startPoints);
		destinationPointID = addNode(copyGraph, endPoints);
		addNode(copyCoor, q.startCoordinate);
		addNode(copyCoor, q.destCoordinate);

		A_Star path;
		p.push_back(path.A(copyGraph, sourcePointId, destinationPointID, maxSpeed, q.R, copyCoor, timeInterval, speedSize));

	}

	f.writeFile("BounsMap.txt", p);





}
char test::simpleTest()
{
	char choice;
	cout << "[1] Simple Test.\n";
	cout << "[1] Map 1. [2] Map 2. [3] Map 3. [4] Map 4. [5] Map 5.\n";

	cin >> choice;
	return choice;
}
void test::displayTest(char choice) {

	switch (choice) {
	case '1':
		doTest(simpleTest());
		break;
	case '2':
		doTest('6');
		break;
	case '3':
		doTest('7');
		break;
	case '4':
		bounsTest();
		break;
	default:
		cout << "invalid choice";
	}
}
