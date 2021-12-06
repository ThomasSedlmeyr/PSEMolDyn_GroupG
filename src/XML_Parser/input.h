//
// Created by daniel on 03.12.21.
//

#ifndef PSEMOLDYN_GROUPG_INPUT_H
#define PSEMOLDYN_GROUPG_INPUT_H

#include <string>
#include <vector>


class input
{
public:
    input (double e, double d, const ::std::string& calc, const ::std::string& bNOF,
           int w, const ::std::string& g, ::paramsLJ paramsLJNew, ::boundaryConditions boundaryConditionsNew,
           ::particlesLJ particlesLJNew) : (t_end_ (e), delta_t_ (d), calcType_ (cal), baseNameOutputFiles_ (bNOF),
                   writeFrequency_ (w), gravInput_ (g), paramsLJ_ (paramsLJnew),
                   boundaryConditions_ (boundaryConditionsNew), particlesLJ_ (particlesLJNew))
    {
    }

    double
    t_end () {
        return t_end_;
    }

    double
    delta_t () {
        return delta_t_;
    }

    const ::std::string&
    calcType () {
        return calcType_;
    }

    const ::std::string&
    baseNameOutputFiles () {
        return baseNameOutputFiles_;
    }

    int
    writeFrequency () {
        return writeFrequency_;
    }

    const ::std::string&
    gravInput () {
        return gravInput_;
    }

    ::paramsLJ
    paramsLJ () {
        return paramsLJ_;
    }

    ::boundaryConditions
    boundaryConditions () {
        return boundaryConditions_
    }

    ::particles
    particlesLJ () {
        return particlesLJ_;
    }

private:
    double t_end_;
    double delta_t_;
    std::string calcType_;
    std::string baseNameOutputFiles_;
    int writeFrequency_;
    std::string gravInput_;
    ::paramsLJ paramsLJ_;
    ::boundaryConditions boundaryConditions_;
    ::particlesLJ particlesLJ_;
};

class paramsLJ
{
public:
    paramsLJ (double e, double m, double r, double hNew) : (epsilon_ (e), mass_ (m), rho_ (r), h_ (hNew))
    {
    }

    double
    epsilon () {
        return epsilon_;
    }

    double
    mass () {
        return mass_;
    }

    double
    rho () {
        return rho_;
    }

    double
    h () {
        return h_;
    }

private:
    double epsilon_;
    double mass_;
    double rho_;
    double h_;
};

class boundaryConditions
{
public:
    boundaryConditions (int to, int ri, int bo, int le, int fr, int ba) : (top_ (to), right_ (ri), bottom_ (bo),
            left_ (le), front_ (fr), back_ (ba))
    {
    }

    int
    top () {
        return top_;
    }

    int
    right () {
        return right_;
    }

    int
    bottom () {
        return bottom_;
    }

    int
    left () {
        return left_;
    }

    int
    front () {
        return front_;
    }

    int
    back () {
        return back_;
    }

private:
    int top_;
    int right_;
    int bottom_;
    int left_;
    int front_;
    int back_;
};

class body
{
public:
    body (const ::std::string& bT, const ::std::string& pos, const ::std::string& v,
          const ::std::string& oSF) : (bodyType_ (bT), position_ (pos), velocity_ (v), objectSpecificFormat_ (oSF))
    {
    }

    const ::std::string&
    bodyType () {
        return bodyType_;
    }

    const ::std::string&
    position () {
        return position_;
    }

    const ::std::string&
    velocity () {
        return velocity_;
    }

    const ::std::string&
    objectSpecificFormat () {
        return objectSpecificFormat_;
    }

private:
    std::string bodyType_;
    std::string position_;
    std::string velocity_;
    std::string objectSpecificFormat_;
};

class particlesLJ {
public:
    particlesLJ(std::vector<::body> b) : (bodies_(b))// TODO multiple bodies/einzelne body einfügen
    {
    }

    std::vector<::body>
    body() {
        return bodies;
    }

private:
    std::vector<::body> bodies_;
};

typedef std::vector<body> bodies;


#endif //PSEMOLDYN_GROUPG_INPUT_H
