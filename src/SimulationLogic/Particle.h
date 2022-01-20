/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <array>
#include <string>
#include <vector>

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

  /**
   * @brief Determines if particle is allowed to be moved during Simulation
   */
  bool movingIsAllowed;

  /**
   * @brief IDs of the neighbour particles; used for membranes
   */
  std::vector<int> neighbourIDs{};

   /**
   * @brief IDs of the direct neighbour particles; used for membranes
   */
   std::vector<int> directNeighbourIDs{};

   /**
    * @brief If a particle leafs one side and is insert at the opposite side of the domain
    * this will be saved in this array. For example if a particles leafs the domain at the right
    * side the first element of this array  will be incremented. If the particle leafs the left
    * side of the domain the first element will be decremented.
    */
   std::array<short, 3> numberOfTimesCrossedWholeDomain{0, 0, 0};

public:
    [[nodiscard]] const std::array<short, 3> &getNumberOfTimesCrossedWholeDomain() const;

public:
    explicit Particle(int type = 0);

    Particle(const Particle &other);

    Particle(
      // for visualization, we need always 3 coordinates
      // -> in case of 2d, we use only the first and the second
      std::array<double, 3> x_arg, std::array<double, 3> v_arg, double m_arg,
      int type = 0, int ID = -1, bool movingIsAllowed = true);

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

    bool getMovingAllowed() const;

    bool isGhostParticle = false;

    void addParticleToNeighbours(int neighbourID);

    void addParticleToDirectNeighbours(int neighbourID);

    static bool particlesAreNeighbours(const Particle &p1, const Particle &p2);

    static bool particlesAreDirectNeighbours(const Particle &p1, const Particle &p2);

    const std::vector<int> &getNeighbourIDs() const;

    const std::vector<int> &getDirectNeighbourIDs() const;


    /**
     * @brief decrements the number of times the particle crossed the domain in x-direction
     */
    inline void decrementNumberOfTimesCrossedDomainX();

    /**
     * @brief decrements the number of times the particle crossed the domain in y-direction
     */
    inline void decrementNumberOfTimesCrossedDomainY();

    /**
     * @brief decrements the number of times the particle crossed the domain in z-direction
     */
    inline void decrementNumberOfTimesCrossedDomainZ();

    /**
     * @brief increments the number of times the particle crossed the domain in x-direction
     */
    inline void incrementNumberOfTimesCrossedDomainX();

    /**
     * @brief increments the number of times the particle crossed the domain in y-direction
     */
    inline void incrementNumberOfTimesCrossedDomainY();

    /**
     * @brief increments the number of times the particle crossed the domain in z-direction
     */
    inline void incrementNumberOfTimesCrossedDomainZ();

};

std::ostream &operator<<(std::ostream &stream, Particle &p);
