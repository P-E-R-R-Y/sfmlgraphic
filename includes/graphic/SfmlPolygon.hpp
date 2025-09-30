/**
 * @file SfmlPolygon.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-09-26
 * 
 * @addtogroup Sfml
 * @{
 */

#ifndef SFMLPOLYGON_HPP_
#define SFMLPOLYGON_HPP_

#include <iostream>
#include <vector>

//Sfml
#include <SFML/Graphics.hpp>

// Interface
#include "IPolygon.hpp"

#include "geometry.hpp"

class SfmlPolygon : public graphic::IPolygon {

public:
    SfmlPolygon(const std::vector<Vector2f>& points): _color({0, 0, 0, 255}), _position({0, 0}) {

        std::vector<Vector2f> triangles = triangulate(points);
        
        originPoints = points; // store original shape
        _vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        _vertices.resize(triangles.size());
        for (size_t i = 0; i < triangles.size(); ++i) {
            _vertices[i].position = sf::Vector2f(static_cast<float>(triangles[i].x),
                                                 static_cast<float>(triangles[i].y));
            _vertices[i].color = sf::Color{_color.r, _color.g, _color.b, _color.a};
        }
    }

    ~SfmlPolygon() = default;

    bool isReady() const override {
        return true;
    }

    Vector2f getPosition() const override {
        return {_position.x, _position.y};
    }

    void setPosition(Vector2f position) override {
        Vector2f diff = { position.x - _position.x, position.y - _position.y };

        for (size_t i = 0; i < _vertices.getVertexCount(); ++i) {
            _vertices[i].position.x += static_cast<float>(diff.x);
            _vertices[i].position.y += static_cast<float>(diff.y);
        }
        _position = position;
    }

    Color getColor() const override {
        return _color; 
    }

    void setColor(Color color) override {
        _color = color;
        for (size_t i = 0; i < _vertices.getVertexCount(); ++i) {
            _vertices[i].color = sf::Color(_color.r, _color.g, _color.b, _color.a);
        }
    }

    std::vector<Vector2f> getPoints() const override {
        return originPoints;
    }

    friend class SfmlWindow;

private:

private:
    // Triangulation using your system Vector2f (safe, avoids Raylib pollution)
    std::vector<Vector2f> triangulate(const std::vector<Vector2f>& points) {
        std::vector<Vector2f> tmp = points;
        std::vector<Vector2f> result;

        while (tmp.size() >= 3) {
            for (size_t i = 0; i < tmp.size(); i++) {
                Vector2f A = tmp[i];
                Vector2f B = tmp[(i+1) % tmp.size()];
                Vector2f C = tmp[(i+2) % tmp.size()];

                if (is_convex(A, B, C)) {
                    bool isEar = true;
                    for (size_t j = 0; j < tmp.size(); j++) {
                        if (j == i || j == (i+1)%tmp.size() || j == (i+2)%tmp.size()) continue;
                        if (is_inside_triangle(tmp[j], A, B, C)) {
                            isEar = false;
                            break;
                        }
                    }
                    if (isEar) {
                        //add triangle 3points to the vector:
                        result.push_back(A); 
                        result.push_back(B);
                        result.push_back(C);
                        tmp.erase(tmp.begin() + (i+1) % tmp.size());
                        break; // restart after ear clip
                    }
                }
            }
        }
        return result;
    }

    std::vector<Vector2f> originPoints;
    sf::VertexArray _vertices;
    Color _color;
    Vector2f _position;
};

#endif /* !SFMLPOLYGON_HPP_ */