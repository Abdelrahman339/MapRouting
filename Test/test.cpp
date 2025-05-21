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
    auto startIO = high_resolution_clock::now();
    f.readFile(fileName, graph, maxSpeed, coor);           // O(|N| + |E|)
    f.readQuery(queryFileName, queries);                    // O(Q)


    auto startWithoutIO = high_resolution_clock::now();

    KDTree kd;
    kd.buildTree(coor);                                     // O(|N| log |N|)

    int sourcePointId;
    int destinationPointID;

    for (query q : queries) {                               // O(Q)
        copyGraph = graph;                                  // O(|N| + |E|)
        copyCoor = coor;                                    // O(|N|)

        vector<pair<int, double>> startPoints, endPoints;
        double radiusSquared = q.R * q.R;

        kd.radiusSearch(kd.root, q.startCoordinate.x_coordinate, q.startCoordinate.y_coordinate,
            q.destCoordinate.x_coordinate, q.destCoordinate.y_coordinate, radiusSquared, startPoints, endPoints, 0);
        // O(log |N| + P) , P = # points in radius

        // Add start/destination nodes to graph for this query
        sourcePointId = addNode(copyGraph, startPoints);   // O(P)
        destinationPointID = addNode(copyGraph, endPoints); // O(P)

        copyCoor.push_back(q.startCoordinate);             // O(1)
        copyCoor.push_back(q.destCoordinate);               // O(1)

        A_Star path;
        p.push_back(path.A(copyGraph, sourcePointId, destinationPointID, maxSpeed, q.R, copyCoor));

        startPoints.clear();
        endPoints.clear();
    }
    auto stopWithoutIO = high_resolution_clock::now();
    auto stopIO = high_resolution_clock::now();
    double elapsedTimeWithIO = duration<double, milli>(stopIO - startIO).count();
    double elapsedTimeWithoutIO = duration<double, milli>(stopWithoutIO - startWithoutIO).count();
    f.writeFile(map, p,elapsedTimeWithIO, elapsedTimeWithoutIO);                                   // O(Q * L), L = avg path length


   

    return p[0];
}


char test::simpleTest()
{
    char choice;
    cout << "[1] Simple Test.\n";
    cout << "[1] Map 1. [2] Map 2. [3] Map 3. [4] Map 4. [5] Map 5.\n";

    cin >> choice;
    return choice;
}

// Visualization function

void test::visual()
{
    MapVisualizer m;
    cout << "[1] Sample Test. [2] Medium Test. [3] Large Test"<<endl;
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
        path = doTest('7');
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
        visual();
        break;
    default:
        cout << "invalid choice";
    }
}
