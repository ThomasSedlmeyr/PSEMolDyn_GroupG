/**
 * @brief Class that manages all Particles
 */
#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include <iterator>
#include <cstddef>

class ParticleContainer {
public:

    /**
     * @return vector of particles
     */
    std::vector<Particle> &getParticles();
    /**
    * @brief writes the actual information of the particles into a vtk file
    * @param iteration iteration in which the information of the particles were saved
    */
    //void plotParticles(int &iteration);

    /**
    * @brief calculates the force for every particle in an easy but inefficient way
    */
    //std::array<double, 3> v; calculateFslower();

    /**
    * @brief calculate the force for all particles
    */
    //void calculateF();

    /**
     * test the fast force calculation compared to slower implementation
     * @return true if results of both calculations match
     */
    //bool testOptimizedFormula();
    void printParticles();
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Particle;
        using pointer           = Particle*;
        using reference         = Particle&;

        //Iterator(pointer ptr) : m_ptr(ptr) {}
        explicit Iterator(Particle& p) : m_ptr(&p) {}

        reference operator*() const;
        pointer operator->();
        Iterator& operator++();
        Iterator operator++(int);
        friend bool operator== (const Iterator& a, const Iterator& b);
        friend bool operator!= (const Iterator& a, const Iterator& b);

    private:
        pointer m_ptr;
    };

    Iterator begin();
    Iterator end();
private:
    std::vector<Particle> particles;



};
