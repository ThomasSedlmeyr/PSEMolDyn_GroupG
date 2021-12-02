#include <iostream>
#include "input-pskel.hxx"

class input_pimpl: public input_pskel
{// TODO
public:
    virtual void
    greeting (const std::string& g)
    {
        greeting_ = g;
    }

    virtual void
    name (const std::string& n)
    {
        std::cout << greeting_ << ", " << n << "!" << std::endl;
    }

private:
    std::string greeting_;
};

class calcType_pimpl: public calcType_pskel, public xml_schema::string_pimpl
{
public:
    virtual std::string
    post_calcType ()
    {
        std::string s = post_string ();
        return s;
    }
};

class paramsLJ_pimpl: public paramsLJ_pskel
{
public:
    virtual void
    epsilon (double e){
        epsilon_ = e;
    }

    virtual void
    mass (double);

    virtual void
    rho (double);

    virtual void
    h (double);

    virtual paramsLJ_pimpl
    post_paramsLJ ();
};