#include "../Test/test.h"
#include "../KDtree/KDTree.h"
#include "../mapVisualization/visual.cpp"
//#include "../mapVisualization/visual.cpp"

string fileName;
bestPath test::doTest(char choice)
{
	unordered_map<int, vector<edge>> graph;
	unordered_map<int, vector<edge>> copyGraph;
	vector<coordinates> coor;
	vector<coordinates> copyCoor;
	vector<query> queries;
	vector<bestPath> p;
	double maxSpeed = -1;
	double timeInterval = 0;
	int speedSize;
	file f;
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

	f.readFile(fileName, graph, maxSpeed, coor);
	f.readQuery(queryFileName, queries);
	auto startIO = high_resolution_clock::now();
	KDTree kd;
	kd.buildTree(coor);

	int sourcePointId;
	int destinationPointID;

	for (query q : queries) {

		copyGraph = graph;
		copyCoor = coor;


		vector<pair<int, double>> startPoints, endPoints;
		startPoints.reserve(128);
		endPoints.reserve(128);
		double radiusSquared = q.R * q.R;
		kd.radiusSearch(kd.root, q.startCoordinate.x_coordinate, q.startCoordinate.y_coordinate,
			q.destCoordinate.x_coordinate, q.destCoordinate.y_coordinate, radiusSquared, startPoints, endPoints, 0);
		//add the start point and the distenation point in the graph for each qeuery
		sourcePointId = addNode(copyGraph, startPoints);
		destinationPointID = addNode(copyGraph, endPoints);
		copyCoor.push_back(q.startCoordinate);
		copyCoor.push_back(q.destCoordinate);


		A_Star path;
		p.push_back(path.A(copyGraph, sourcePointId, destinationPointID, maxSpeed, q.R, copyCoor));
		startPoints.clear();
		endPoints.clear();
	}

	auto stopIO = high_resolution_clock::now();

	f.writeFile(map, p);

	double elapsedTimeWithIO = duration<double, milli>(stopIO - startIO).count();
	cout << "Not added yet" << " ms" << endl;
	cout << endl;
	cout << elapsedTimeWithIO << " ms" << endl;


	return p[0];


}

void test::bounsTest()
{
	//unordered_map<int, vector<edge>> graph;
	//unordered_map<int, vector<edge>> copyGraph;
	//unordered_map<int, coordinates> coor;
	//unordered_map<int, coordinates> copyCoor;
	//vector<query> queries;
	//vector<bestPath> p;
	//double maxSpeed = -1;
	//double timeInterval = 0;
	//int speedSize = 0;
	//file f;
	//string fileName;
	//string queryFileName;

	//cout << "[4] BONUS Test Cases.\n";
	//cout << "[1] Sample. [2] Medium.\n";
	//int choice;
	//cin >> choice;
	//string dir1 = "Data/testCases/[4] BONUS Test Cases/[1] Sample Cases/Input/";
	//string dir2 = "Data/testCases/[4] BONUS Test Cases/[1] Medium Cases/Input/";
	//string map1 = "map1B.txt";
	//string map2 = "OLMapB.txt";
	//fileName = choice == 1 ? dir1 + map1 : dir2 + map2;

	//queryFileName = choice == 1 ? "Data/testCases/[4] BONUS Test Cases/[1] Sample Cases/Input/queries1.txt" :
	//	"Data/testCases/[4] BONUS Test Cases/[1] Medium Cases/Input/OLQueries.txt";


	//f.readFile(fileName, graph, maxSpeed, timeInterval, speedSize, coor);
	//f.readQuery(queryFileName, queries);

	//auto startIO = high_resolution_clock::now();
	//int sourcePointId;
	//int destinationPointID;
	////10 will be replaced with q.numberOfQueries
	//for (query q : queries) {

	//	copyGraph = graph;
	//	copyCoor = coor;
	//	unordered_map<int, double> startPoints = getNodesWithinRadius(q.startCoordinate.x_coordinate, q.startCoordinate.y_coordinate, q.R, copyCoor);
	//	unordered_map<int, double> endPoints = getNodesWithinRadius(q.destCoordinate.x_coordinate, q.destCoordinate.y_coordinate, q.R, copyCoor);
	//	//add the start point and the distenation point in the graph for each qeuery
	//	sourcePointId = addNode(copyGraph, startPoints);
	//	destinationPointID = addNode(copyGraph, endPoints);
	//	addNode(copyCoor, q.startCoordinate);
	//	addNode(copyCoor, q.destCoordinate);

	//	A_Star path;
	//	p.push_back(path.A(copyGraph, sourcePointId, destinationPointID, maxSpeed, q.R, copyCoor, timeInterval, speedSize));

	//}

	//f.writeFile("BounsMap.txt", p);





}
char test::simpleTest()
{
	char choice;
	cout << "[1] Simple Test.\n";
	cout << "[1] Map 1. [2] Map 2. [3] Map 3. [4] Map 4. [5] Map 5.\n";

	cin >> choice;
	return choice;
}
void test::visual() 
{
	MapVisualizer m;
	cout << "[1] Sample Test. [2] Meduim Test. [3] Large Test. [4] Bouns Test.";
	char choice;
	cin >> choice;
	bestPath path;
	string dir = "Data/testCases/[3] Large Cases/input/";
	string map = "SFMap.txt";
	switch (choice) {
	case '1':
		path=doTest(simpleTest());
		break;
	case '2':
		path = doTest('6');
		break;
	case '3':
		fileName = dir + map;
		path.nodes = {1,2,3,4};
		break;
	case '4':
		bounsTest();
		break;

	default:
		cout << "invalid choice";
	}

	vector<int> bestpath;
	while (!path.nodes.empty())
	{
		bestpath.push_back(path.nodes.front());
		path.nodes.pop_front();
	}
	m.startVisualization(bestpath, fileName, "forVisualization/Open_Sans/OpenSans.ttf");

};
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
	case'5':
		visual();
		break;

	default:
		cout << "invalid choice";
	}
}
