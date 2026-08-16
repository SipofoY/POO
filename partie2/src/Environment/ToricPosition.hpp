/*
 * POOSV 2020-21
 * @author:Clara Chappuis & Yann Sipofo
 */

#pragma once
#ifndef INFOSV_TORICPOSITION_HPP
#define INFOSV_TORICPOSITION_HPP

#include "../Utility/Vec2d.hpp"

/*!
 * @brief Handle toric coordinate, distance and other basic math operation in a toric world
 *
 * @note It use the dimension of the world from getAppConfig()
 */
class ToricPosition
{
public:
    /*!
     * @brief Constructor from {x, y}, Vec2d or copy construction
     */
    ToricPosition();
    ToricPosition(double x, double y);
    ToricPosition(Vec2d const& position);
        ToricPosition(Vec2d const& position, Vec2d const & dims);
    ToricPosition(ToricPosition const& position) = default;

    /*!
     * @brief Assignment operation, works with {x, y}, Vec2d and ToricPosition
     */
    ToricPosition& operator=(ToricPosition const& position) = default;

    /*!
     * @brief Explicit conversion to Vec2d
     *
     * @return a Vec2d object clamped into the toric world
     */
    Vec2d const& toVec2d() const;

  /*!
   * @brief Explicit conversion to Vec2d
   *
   * 0return a reference to either coordinate
   */
  //double& operator[](unsigned int);
  double operator[](unsigned int) const;

    /// Addition operations
    ToricPosition& operator+=(ToricPosition const& b);
    /// Addition operations
    ToricPosition& operator+=(Vec2d const& b);
    // Add more more operations here if it feels right !

        const Vec2d& getPosition() const {
                return mPosition;
        }
        bool operator==(const ToricPosition& b) const;

         // Coordinates getters
    double x() const { return mPosition.x(); }
    double y() const { return mPosition.y(); }
/*!
 * @brief Compute the "true" vector between this and another point in a toric world
 */
Vec2d toricVector(ToricPosition const& to) const;

private:
    /// Clamp the position into the toric world
    void clamp();

private:
    Vec2d mPosition; ///< Position clamped to the toric world
        Vec2d mWorldSize;
};



/*!
 * @brief Compute the "true" distance between two points in a toric world
 *
 * @see distance(Vec2d, Vec2d)
 */
double toricDistance(ToricPosition const& a, ToricPosition const& b);

ToricPosition operator+(ToricPosition a, const ToricPosition& b);
std::ostream& operator<<(std::ostream&, const ToricPosition&);


#endif // INFOSV_TORICPOSITION_HPP



