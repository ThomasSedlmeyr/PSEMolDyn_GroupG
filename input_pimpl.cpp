#include <iostream>
#include "input-pskel.hxx"

class input_pimpl: public input_pskel
{
public:

    input_pimpl(){//double end, double delta, ::calcType calc, ) {
        t_end();
        delta_t();
    }

    virtual void
    t_end (double end)
    {
        t_end_ = end;
    }

    virtual void
    delta_t (double delta)
    {
        delta_t_ = delta;
    }

    virtual void
    calcType ()
    {
        // TODO after class is implemented
    }

    virtual void
    baseNameOutputFiles (const ::std::string& base)
    {
        baseNameOutputFiles_ = base;
    }

    virtual void
    writeFrequency (int frequency)
    {
        writeFrequency_ = frequency;
    }

    virtual void
    gravInput (const ::std::string& grav)
    {
        gravInput_ = grav;
    }

    virtual void
    paramsLJ ()
    {
        // TODO
    }

    virtual void
    boundaryConditions ()
    {
        // TODO
    }

    virtual void
    particlesLJ ()
    {
        // TODO
    }

    virtual ::input_pskel
    post_input ()
    {
        return input_pskel (t_end_, delta_t_, calcType_, baseNameOutputFiles_, writeFrequency_, gravInput_, paramsLJ_, boundaryConditions_, particlesLJ_);
    }

private:
    double t_end_;
    double delta_t_;
    std::string calcType_;
    std::string baseNameOutputFiles_;
    int writeFrequency_;
    std::string gravInput_;
    ::paramsLJ_pskel paramsLJ_;
    ::boundaryConditions_pskel boundaryConditions_;
    ::particlesLJ_pskel particlesLJ_;
};

class calcType_pimpl: public calcType_pskel {
public:

    virtual ::std::string
    post_calcType ()
    {
        // TODO what to return?
        std::string s = post_string ();
        return s;
    }
};

class paramsLJ_pimpl: public paramsLJ_pskel {
public:

    paramsLJ_pimpl(double d, double d1, double d2, double d3) : paramsLJ_pskel(d, d1, d2, d3) {
        epsilon(d);
        mass(d1);
        rho(d2);
        h(d3);
    }

    virtual void
    epsilon (double e)
    {
        epsilon_ = e;
    }

    virtual void
    mass (double m)
    {
        mass_ = m;
    }

    virtual void
    rho (double r)
    {
        rho_ = r;
    }

    virtual void
    h (double h)
    {
        h_ = h;
    }

    virtual ::paramsLJ_pimpl
    post_paramsLJ ()
    {
        return ::paramsLJ_pimpl(epsilon_, mass_, rho_, h_);
    }

private:
    double epsilon_;
    double mass_;
    double rho_;
    double h_;
};

class boundaryConditions_pimpl: public boundaryConditions_pskel {
public:

    boundaryConditions_pimpl(int i, int i1, int i2, int i3) {

    }

    virtual void
    top (int t)
    {
        top_ = t;
    }

    virtual void
    right (int r)
    {
        right_ = r;
    }

    virtual void
    bottom (int b)
    {
        bottom_ = b;
    }

    virtual void
    left (int l)
    {
        left_ = l;
    }

    virtual ::boundaryConditions_pimpl
    post_boundaryConditions ()
    {
        return ::boundaryConditions_pimpl(top_, right_, bottom_, left_);
    }

private:
    int top_;
    int bottom_;
    int right_;
    int left_;
};

class particlesLJ_pimpl: public particlesLJ_pskel {
public:
    virtual void
    body ()
    {

    }

    virtual void
    post_particlesLJ ()
    {

    }
};

class body_pimpl: public body_pskel {
public:
    virtual void
    bodyType (const ::std::string& type)
    {

    }

    virtual void
    position (const ::std::string& pos)
    {

    }

    virtual void
    velocity (const ::std::string& v)
    {

    }

    virtual void
    objectSpecificFormat (const ::std::string& spec)
    {

    }

    virtual void
    post_body ()
    {

    }
};