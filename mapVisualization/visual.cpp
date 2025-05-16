#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace sf;
using namespace std;

struct Node {
    int id;
    float x, y;
};

struct Road {
    int from, to;
    float length, speed;
};

class MapVisualizer {
private:
    const float ZOOM_FACTOR = 1.1f;
    const float PADDING = 50.0f;
    const float WINDOW_WIDTH = 1800.0f;
    const float WINDOW_HEIGHT = 900.0f;

    vector<Node> readFile(vector<Road>& Roads, string file) {
        ifstream infile(file);
        if (!infile) {
            cout << "Failed to open file.\n";
        }

        int numberOfnodes;
        vector<Node> Nodes;
        infile >> numberOfnodes;

        int node;
        float x_coordinate, y_coordinate;

        for (int i = 0; i < numberOfnodes; ++i)
        {
            infile >> node >> x_coordinate >> y_coordinate;
            Node n;
            n.id = node;
            n.x = x_coordinate;
            n.y = y_coordinate;
            Nodes.push_back(n);
        }

        int numberOfEdges;
        infile >> numberOfEdges;
        for (int i = 0; i < numberOfEdges; ++i) {
            Road r;
            infile >> r.from >> r.to >> r.length >> r.speed;
            Roads.push_back(r);
        }

        return Nodes;
    }

    void drawLine(RenderWindow& window, Vector2f start, Vector2f end, Color color) {
        Vertex line[] = {
            Vertex(start, color),
            Vertex(end, color)
        };
        window.draw(line, 2, Lines);
    }

    void scaleAndCenterMap(vector<Node>& nodes, Vector2f& sourcePos, Vector2f& destinationPos, float windowWidth, float windowHeight) {
        float minX = nodes[0].x, maxX = nodes[0].x;
        float minY = nodes[0].y, maxY = nodes[0].y;
        for (const auto& node : nodes) {
            minX = min(minX, node.x);
            maxX = max(maxX, node.x);
            minY = min(minY, node.y);
            maxY = max(maxY, node.y);
        }

        float mapWidth = maxX - minX;
        float mapHeight = maxY - minY;
        float mapCenterX = (minX + maxX) / 2.0f;
        float mapCenterY = (minY + maxY) / 2.0f;

        float scale = min((windowWidth - 2 * PADDING) / mapWidth, (windowHeight - 2 * PADDING) / mapHeight);

        for (auto& node : nodes) {
            node.x = (node.x - mapCenterX) * scale + windowWidth / 2.0f;
            node.y = (node.y - mapCenterY) * scale + windowHeight / 2.0f;
        }

        sourcePos = Vector2f(
            (sourcePos.x - mapCenterX) * scale + windowWidth / 2.0f,
            (sourcePos.y - mapCenterY) * scale + windowHeight / 2.0f
        );
        destinationPos = Vector2f(
            (destinationPos.x - mapCenterX) * scale + windowWidth / 2.0f,
            (destinationPos.y - mapCenterY) * scale + windowHeight / 2.0f
        );
    }

public:
    void startVisualization(vector<int> shortest_path, string txtFile, string fontPath) {
        vector<Node> nodes;
        vector<Road> roads;

        nodes = readFile(roads, txtFile);

        // Define arbitrary source and destination points
        Vector2f rawSource(-0.1, 0.5), rawDest(1.1, 0.15);
        Vector2f sourcePos(rawSource), destinationPos(rawDest);

        scaleAndCenterMap(nodes, sourcePos, destinationPos, WINDOW_WIDTH, WINDOW_HEIGHT);

        //lazem font 3shan le ay text
        Font font;
        if (!font.loadFromFile(fontPath)) {
            cout << "Failed to load font!\n";
            return;
        }

        RenderWindow window(VideoMode(1800, 900), "Map Routing Visualization");
        window.setFramerateLimit(60);

        float zoomLevel = 1.0f;
        Vector2f zoomCenter(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseWheelScrolled) {
                    if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel) {
                        if (event.mouseWheelScroll.delta > 0) {
                            zoomLevel /= ZOOM_FACTOR; //zoom in
                        }
                        else {
                            zoomLevel *= ZOOM_FACTOR; //zoom out
                        }
                        //zoomLevel = max(zoomLevel, 0.1f); //max zoom in
                        //zoomLevel = min(zoomLevel, 5.0f); //max zoom out
                    }
                }
            }

            //lon el background
            window.clear(Color::White);

            //3shan el zoom
            View view;
            view.reset(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
            view.setCenter(zoomCenter);
            view.zoom(zoomLevel);
            window.setView(view);

            CircleShape sourceCircle(6);
            sourceCircle.setFillColor(Color::Magenta);
            sourceCircle.setOrigin(6, 6);
            sourceCircle.setPosition(sourcePos);
            window.draw(sourceCircle);

            Text sourceLabel;
            sourceLabel.setFont(font);
            sourceLabel.setString("Source");
            sourceLabel.setCharacterSize(11);
            sourceLabel.setFillColor(Color::Magenta);
            sourceLabel.setPosition(sourcePos + Vector2f(-15, -20));
            window.draw(sourceLabel);

            CircleShape destinationCircle(6);
            destinationCircle.setFillColor(Color::Red);
            destinationCircle.setOrigin(6, 6);
            destinationCircle.setPosition(destinationPos);
            window.draw(destinationCircle);

            Text destinationLabel;
            destinationLabel.setFont(font);
            destinationLabel.setString("Destination");
            destinationLabel.setCharacterSize(11);
            destinationLabel.setFillColor(Color::Red);
            destinationLabel.setPosition(destinationPos + Vector2f(-25, -20));
            window.draw(destinationLabel);

            int firstShortestPathNodeId = shortest_path.front();
            int lastShortestPathNodeId = shortest_path.back();
            drawLine(window, sourcePos, Vector2f(nodes[firstShortestPathNodeId].x, nodes[firstShortestPathNodeId].y), Color::Green); //line mben source w first shortest path node
            drawLine(window, Vector2f(nodes[lastShortestPathNodeId].x, nodes[lastShortestPathNodeId].y), destinationPos, Color::Green); //line mben last shortest path node w destination

            //roads
            for (const auto& road : roads) {
                drawLine(
                    window,
                    Vector2f(nodes[road.from].x, nodes[road.from].y),
                    Vector2f(nodes[road.to].x, nodes[road.to].y),
                    Color::Black
                );
            }

            //shortest path lono a5dr, mynf3sh int i 3shan momken y7sl overflow
            for (size_t i = 0; i < shortest_path.size() - 1; ++i) {
                int from = shortest_path[i];
                int to = shortest_path[i + 1];
                drawLine(
                    window,
                    Vector2f(nodes[from].x, nodes[from].y),
                    Vector2f(nodes[to].x, nodes[to].y),
                    Color::Green
                );
            }

            //3shan t5ly ay text gya t5leha sbta f mknha 7ta lw 3mlt zoom
            View uiView(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
            window.setView(uiView);

            //display outputInfo
            Text outputInfo;
            outputInfo.setFont(font);
            string pathStr = "Shortest Path: ";
            for (int node : shortest_path) {
                pathStr += to_string(node) + " ";
            }
            outputInfo.setString(pathStr);
            outputInfo.setCharacterSize(16);
            outputInfo.setFillColor(Color::Black);
            outputInfo.setPosition(10, 10);
            window.draw(outputInfo);

            window.display();
        }
    }
};