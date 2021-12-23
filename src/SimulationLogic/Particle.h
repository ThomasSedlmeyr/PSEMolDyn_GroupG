/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <array>
#include <string>

class Particle {

private:
  /**
   * Position of the particle
   */
  std::array<double, 3> x{};

  /**
   * Velocity of the particle
   */
  std::array<double, 3> v{};

  /**
   * Force effective on this particle
   */
  std::array<double, 3> f{};

  /**
   * Force which was effective on this particle
   */
  std::array<double, 3> old_f{};

  /**
   * Mass of this particle
   */
  double m;

  /**
   * Type of the particle.
   */
  int type;

    /**
     * Unique identifier for everyParticle
     */
  int ID;

public:
    explicit Particle(int type = 0);

    Particle(const Particle &other);

    Particle(
      // for visualization, we need always 3 coordinates
      // -> in case of 2d, we use only the first and the second
      std::array<double, 3> x_arg, std::array<double, 3> v_arg, double m_arg,
      int type = 0, int ID = -1);

    Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg, double m_arg, int type_arg,
             std::array<double, 3> f_arg, std::array<double, 3> f_old_arg, int id_arg);

    virtual ~Particle();

    int getId() const;

    /**
     * @return reference of f
     */
    std::array<double, 3> &getFRef();

    std::array<double, 3> &getVRef();

    const std::array<double, 3> &getX() const;

    const std::array<double, 3> &getV() const;

    const std::array<double, 3> &getF() const;

    const std::array<double, 3> &getOldF() const;

    double getM() const;

  int getType() const;

  bool operator==(Particle &other);
  bool operator==(const Particle &other);

  std::string toString() const;

    void setX(const std::array<double, 3> &x);

    void setV(const std::array<double, 3> &v);

    void setF(const std::array<double, 3> &f);

    void setOldF(const std::array<double, 3> &oldF);

    void setIsGhostParticle(const bool& b);

    /**
     * @brief sets old_f to f and sets f to zeroes to allow for new calculation of f
     */
    void prepareForNewForce();

    /**
     * @brief formats the particle into one line
     * @return returns the particles attributes in one line
     */
    std::string toString();

    std::array<double, 3> &getXRef();

    bool isGhostParticle = false;
};

std::ostream &operator<<(std::ostream &stream, Particle &p);
