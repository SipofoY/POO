/*
 * POOSV 2020-21
 * @author:
 */

#include "ToricPosition.hpp"
#include <cmath>
#include "../Utility/Vec2d.hpp"
#include <array>
#include <cassert>
#include <../Utility/Utility.hpp>
#include "../Application.hpp"
#include "../Config.hpp"

ToricPosition::ToricPosition()
: ToricPosition(0.0, 0.0)
{
    // Done.
}

ToricPosition::ToricPosition(double x, double y)
: ToricPosition(Vec2d(x, y))
{
    // Done.
}

ToricPosition::ToricPosition(Vec2d const& position)
    : ToricPosition(position, Vec2d(getAppConfig().simulation_size,
                                    getAppConfig().simulation_size))
{
}

ToricPosition::ToricPosition(Vec2d const& position, Vec2d const& dims)
    : mPosition(position)
    , mWorldSize(dims)
{
    clamp();
}

Vec2d const& ToricPosition::toVec2d() const
{
    return mPosition;
}

double ToricPosition::operator[](unsigned int i) const
{
  assert(i<2);
  return mPosition[i];
}

bool ToricPosition::operator==(const ToricPosition& b) const
{
  return isEqual(x(), b.x()) and isEqual(y(), b.y());
}

ToricPosition operator+(ToricPosition a, const ToricPosition& b)
{
  a+=b;
  return a;
}
ToricPosition& ToricPosition::operator+=(const ToricPosition& b)
{
    return *this += b.mPosition ;
}

ToricPosition& ToricPosition::operator+=(const Vec2d& b)
{
  mPosition += b;
  clamp();
  return *this;
}
static double myfmod(double x, double y)
{
  x = fmod(x, y);
  if (x < 0.0) x += y;
  return x;
}
void ToricPosition::clamp()
{
    // Clamp the position inside the toric world

    auto const width  = mWorldSize.x();
    auto const height = mWorldSize.y();
    mPosition = Vec2d(myfmod(mPosition.x(), width),
                      myfmod(mPosition.y(), height));

}

Vec2d ToricPosition::toricVector(ToricPosition const& to) const
{

    auto const a = mPosition;
    auto const b = to.mPosition;

    auto const width  = mWorldSize.x();
    auto const height = mWorldSize.y();




    auto min_b = b;
    auto min_dist = distance(min_b, a);
    for (auto i : { -1, 0, 1 }) {
        for (auto j : { -1, 0, 1 }) {
            auto const candidate = b + Vec2d{ width * i, height * j };
            auto const candidate_dist = distance(candidate, a);
            if (candidate_dist < min_dist) {
                min_dist = candidate_dist;
                min_b = candidate;
            }
        }
    }

    return min_b - a;
}

double toricDistance(ToricPosition const& from, ToricPosition const& to)
{
    return from.toricVector(to).length();
}

std::ostream& operator<<(std::ostream& out, ToricPosition const& v)
{
  out << "[" << v[0] << ", " << v[1] << "]";
  return out;
}
