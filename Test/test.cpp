#include "../Test/test.h"
#include "../KDtree/KDTree.h"
#include "../mapVisualization/visual.cpp" 


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

    // Select data set paths based on choice
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

    // Read map and queries
    f.readFile(fileName, graph, maxSpeed, coor);           // O(|V| + |E|)
    f.readQuery(queryFileName, queries);                    // O(Q)

    auto startIO = high_resolution_clock::now();

    KDTree kd;
    kd.buildTree(coor);                                     // O(|V| log |V|)

    int sourcePointId;
    int destinationPointID;

    for (query q : queries) {                               // O(Q)
        copyGraph = graph;                                  // O(|V| + |E|) (copying unordered_map and vectors)
        copyCoor = coor;                                    // O(|V|)

        vector<pair<int, double>> startPoints, endPoints;
        startPoints.reserve(128);
        endPoints.reserve(128);
        double radiusSquared = q.R * q.R;

        kd.radiusSearch(kd.root, q.startCoordinate.x_coordinate, q.startCoordinate.y_coordinate,
            q.destCoordinate.x_coordinate, q.destCoordinate.y_coordinate, radiusSquared, startPoints, endPoints, 0);
        // radiusSearch complexity depends on radius and tree structure, approx O(log |V| + P) where P = # points in radius

        // Add start/destination nodes to graph for this query
        sourcePointId = addNode(copyGraph, startPoints);   // O(P)
        destinationPointID = addNode(copyGraph, endPoints); // O(P)

        copyCoor.push_back(q.startCoordinate);             // O(1)
        copyCoor.push_back(q.destCoordinate);               // O(1)

        A_Star path;
        p.push_back(path.A(copyGraph, sourcePointId, destinationPointID, maxSpeed, q.R, copyCoor));
        // A* search complexity: O(|S| * |E'| log |V'|), depends on graph explored

        startPoints.clear();
        endPoints.clear();
    }

    auto stopIO = high_resolution_clock::now();

    f.writeFile(map, p);                                   // O(Q * L), L = avg path length

    double elapsedTimeWithIO = duration<double, milli>(stopIO - startIO).count();
    cout << "Not added yet" << " ms" << endl;
    cout << endl;
    cout << elapsedTimeWithIO << " ms" << endl;

    return p[0];
}

// Simple menu for map selection
char test::simpleTest()
{
    char choice;
    cout << "[1] Simple Test.\n";
    cout << "[1] Map 1. [2] Map 2. [3] Map 3. [4] Map 4. [5] Map 5.\n";

    cin >> choice;
    return choice;
}

// Visualization function (left commented as requested)
/*
void test::visual()
{
    MapVisualizer m;
    cout << "[1] Sample Test. [2] Medium Test. [3] Large Test. [4] Bonus Test.";
    char choice;
    cin >> choice;
    bestPath path;
    string dir = "Data/testCases/[3] Large Cases/input/";
    string map = "SFMap.txt";
    switch (choice) {
    case '1':
        path = doTest(simpleTest());
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
}
*/

// Dispatch test based on choice
void test::displayTest(char choice)
{
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
        break;
    default:
        cout << "invalid choice";
    }
}
