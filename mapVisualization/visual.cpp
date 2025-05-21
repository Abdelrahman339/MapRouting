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
    const float MOVEMENT_SPEED = 5.0f;

    vector<Node> readFile(vector<Road>& roads, string file) {
        ifstream infile(file);
        if (!infile) {
            cout << "Failed to open file.\n";
        }

        int numberOfNodes;
        vector<Node> nodes;
        infile >> numberOfNodes;

        int node;
        float x_coordinate, y_coordinate;

        for (int i = 0; i < numberOfNodes; ++i) {
            infile >> node >> x_coordinate >> y_coordinate;
            nodes.push_back({ node, x_coordinate, y_coordinate });
        }

        int numberOfEdges;
        infile >> numberOfEdges;
        for (int i = 0; i < numberOfEdges; ++i) {
            Road r;
            infile >> r.from >> r.to >> r.length >> r.speed;
            roads.push_back(r);
        }

        return nodes;
    }

    void drawLine(RenderWindow& window, Vector2f start, Vector2f end, Color color) {
        Vertex line[] = {
            Vertex(start, color),
            Vertex(end, color)
        };
        window.draw(line, 2, Lines);
    }

    void scaleAndCenterMap(vector<Node>& nodes, float windowWidth, float windowHeight) {
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

    }

public:
    void startVisualization(vector<int> shortest_path, string txtFile, string fontPath) {
        vector<Node> nodes;
        vector<Road> roads;

        nodes = readFile(roads, txtFile);



        scaleAndCenterMap(nodes, WINDOW_WIDTH, WINDOW_HEIGHT);

        // lazem font 3shan le ay text
        Font font;
        if (!font.loadFromFile(fontPath)) {
            cout << "Failed to load font!\n";
            return;
        }

        RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Map Routing Visualization");
        window.setFramerateLimit(60);

        float zoomLevel = 1.0f;
        View view;
        view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        view.setCenter(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseWheelScrolled) {
                    if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel) {
                        if (event.mouseWheelScroll.delta > 0)
                            zoomLevel /= ZOOM_FACTOR;
                        else
                            zoomLevel *= ZOOM_FACTOR;

                        zoomLevel = max(zoomLevel, 0.1f);
                        zoomLevel = min(zoomLevel, 5.0f);
                        view.setSize(WINDOW_WIDTH * zoomLevel, WINDOW_HEIGHT * zoomLevel);
                    }
                }
            }

            float moveSpeed = MOVEMENT_SPEED * zoomLevel;
            if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
                view.move(0, -moveSpeed);
            if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
                view.move(0, moveSpeed);
            if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
                view.move(-moveSpeed, 0);
            if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
                view.move(moveSpeed, 0);

            //lon el background
            window.clear(Color::White);
            window.setView(view);

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
            Text info;
            info.setFont(font);
            string pathStr = "Shortest Path: ";
            for (int node : shortest_path)
                pathStr += to_string(node) + " ";
            info.setString(pathStr);
            info.setCharacterSize(16);
            info.setFillColor(Color::Black);
            info.setPosition(10, 10);
            window.draw(info);

            window.display();
        }
    }
};

