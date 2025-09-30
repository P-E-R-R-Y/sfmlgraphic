/**
 * @file SfmlCamera.hpp
 * @author @Perry-Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2025-09-29
 * 
 * @addtogroup Sfml
 * @{
 */

#ifndef SFMLCAMERA_HPP_
#define SFMLCAMERA_HPP_

//Sfml

//Interface
#include "ICamera.hpp"

/**
 * @brief Sfml Camera class
 */class SfmlCamera : public graphic::ICamera {
public:
    SfmlCamera()
        : _position{0.f, 0.f, 0.f},
          _target{0.f, 0.f, 0.f},
          _up{0.f, 1.f, 0.f},
          _fov(45.f),
          _mode(ICamera::Mode::FREE),
          _projection(ICamera::Projection::PERSPECTIVE)
    {}

    ~SfmlCamera() override = default;

    float getFov() const override { return _fov; }
    void setFov(float fov) override { _fov = fov; }

    ICamera::Mode getMode() const override { return _mode; }
    void setMode(ICamera::Mode mode) override { _mode = mode; }

    Vector3f getPosition() const override { return _position; }
    void setPosition(Vector3f position) override { _position = position; }

    ICamera::Projection getProjection() const override { return _projection; }
    void setProjection(ICamera::Projection projection) override { _projection = projection; }

    Vector3f getTarget() const override { return _target; }
    void setTarget(Vector3f target) override { _target = target; }

    Vector3f getUp() const override { return _up; }
    void setUp(Vector3f up) override { _up = up; }

private:
    Vector3f _position;
    Vector3f _target;
    Vector3f _up;
    float _fov;
    ICamera::Mode _mode;
    ICamera::Projection _projection;
};

#endif /* !SFMLMODEL2_HPP_ */