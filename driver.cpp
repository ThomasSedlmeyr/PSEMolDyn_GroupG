#include <iostream>
#include "input-pskel.hxx"
//#include "libs/libxsd/xsd/cxx/tree/buffer.hxx"

class input_pimpl: public input_pskel
{
public:
    virtual void
    t_end (double e) {
        t_end_ = e;
    }

    virtual void
    delta_t (double d) {
        delta_t_ = d;
    }

    virtual void
    calcType (const ::std::string& calc) {
        calcType_ = calc;
    }

    virtual void
    baseNameOutputFiles (const ::std::string& bNOF) {
        baseNameOutputFiles_ = bNOF;
    }

    virtual void
    writeFrequency (int w) {
        writeFrequency_ = w;
    }

    virtual void
    gravInput (const ::std::string& g) {
        gravInput_ = g;
    }

    virtual void
    paramsLJ (const ::paramsLJ& p) {
        paramsLJ_ = p;
    }

    virtual void
    boundaryConditions (const ::boundaryConditions& bC) {
        boundaryConditions_ = bC;
    }

    virtual void
    particlesLJ (const ::particlesLJ& p) {
        particlesLJ_ = p;
    }

    virtual ::input
    post_input () {
        return ::input(t_end_, delta_t_, calcType_, baseNameOutputFiles_, writeFrequency_, gravInput_, paramsLJ_,
                       boundaryConditions_, particlesLJ_);
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

class paramsLJ_pimpl: public paramsLJ_pskel
{
public:
    virtual void
    epsilon (double e){
        epsilon_ = e;
    }

    virtual void
    mass (double m) {
        mass_ = m;
    }

    virtual void
    rho (double r) {
        rho_ = r;
    }

    virtual void
    h (double hNew) {
        h_ = hNew;
    }

    virtual ::paramsLJ
    post_paramsLJ () {
        return ::paramsLJ(epsilon_, mass_, rho_, h_);
    }

private:
    double epsilon_;
    double mass_;
    double rho_;
    double h_;
};

class boundaryConditions_pimpl: public boundaryConditions_pskel
{
public:
    boundaryConditions_pimpl();

    virtual void
    top (int to) {
        top_ = to;
    }

    virtual void
    right (int ri) {
        right_ = ri;
    }

    virtual void
    bottom (int bo) {
        bottom_ = bo;
    }

    virtual void
    left (int le) {
        left_ = le;
    }

    virtual void
    front (int fr) {
        front_ = fr;
    }

    virtual void
    back (int ba) {
        back_ = ba;
    }

    virtual ::boundaryConditions
    post_boundaryConditions () {
        return ::boundaryConditions(top_, right_, bottom_, left_, front_, back_);
    }

private:
    int top_;
    int right_;
    int bottom_;
    int left_;
    int front_;
    int back_;
};

class particlesLJ_pimpl: public particlesLJ_pskel
{
public:
    virtual void
    body (const ::body& b) {
        bodies.push_back (b);
    }

    virtual ::particlesLJ
    post_particlesLJ () {
        // TODO swap
        ::particlesLJ r;
        std::swap(bodies, r);
        return r;
    }

private:
    ::particlesLJ bodies;
};

class body_pimpl: public body_pskel
{
public:
    virtual void
    bodyType (const ::std::string& bT) {
        bodyType_ = bT;
    }

    virtual void
    position (const ::std::string& pos) {
        position_ = pos;
    }

    virtual void
    velocity (const ::std::string& v) {
        velocity_ = v;
    }

    virtual void
    objectSpecificFormat (const ::std::string& oSF) {
        objectSpecificFormat_ = oSF;
    }

    virtual ::body
    post_body () {
        return ::body(bodyType_, position_, velocity_, objectSpecificFormat_);
    }

private:
    std::string bodyType_;
    std::string position_;
    std::string velocity_;
    std::string objectSpecificFormat_;
};

using namespace std;

int
main (int argc, char* argv[])
{
    // Construct the parser.
    //
    xml_schema::int_pimpl int_p;
    xml_schema::string_pimpl string_p;
    xml_schema::double_pimpl double_p;
    /*
    body_pimpl body_p;
    particlesLJ_pimpl particlesLJ_p;
    boundaryConditions_pimpl boundaryConditions_p;
    paramsLJ_pimpl paramsLJ_p;
    input_pimpl input_p;


    body_p.parsers(string_p, string_p, string_p, string_p);
    particlesLJ_p.parsers(body_p); // TODO
    boundaryConditions_p.parsers(int_p, int_p, int_p, int_p, int_p, int_p);
    paramsLJ_p.parsers(double_p, double_p, double_p, double_p);
    input_p.parsers(double_p, double_p, string_p, string_p, int_p, string_p, paramsLJ_p,
                    boundaryConditions_p, particlesLJ_p); // TODO

    // Parse the document to obtain the object model.
    //
    xml_schema::document doc_p (input_p, "input"); // TODO

    input_p.pre (); // TODO
    doc_p.parse (argv[1]);
    input in = input_p.post_input();

    // Print the object model.
    //
    cout << "t_end: " << in.t_end() << endl
         << "delta_t: " << in.delta_t() << endl
         << "calcType: " << in.calcType() << endl
         << "baseNameOutputFiles: " << in.baseNameOutputFiles() << endl
         << "writeFrequency: " << in.writeFrequency() << endl
         << "gravInput: " << in.gravInput() << endl
         << "paramsLJ: " << in.paramsLJ() << endl // TODO
         << "boundaryConditions: " << in.boundaryConditions() << endl // TODO
         << "particlesLJ: " << in.particlesLJ() << endl// TODO
         << endl;
    */
}