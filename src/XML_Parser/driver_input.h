#ifndef PSEMOLDYN_GROUPG_DRIVER_INPUT_H
#define PSEMOLDYN_GROUPG_DRIVER_INPUT_H

#include <iostream>
#include <list>
#include "input.h"
#include "../GeometricObjects/Cuboid.h"
#include "../GeometricObjects/Tetrahedron.h"
#include "../GeometricObjects/Sphere.h"

class driver_input {
private:
    static double t_end_p;
    static double delta_t_p;
    static int calcType_p;
    static std::string baseNameOutputFiles_p;
    static int writeFrequency_p;
    static std::string gravInput_p;

    static double epsilon_p;
    static double mass_p;
    static double rho_p;
    static double h_p;
    static std::vector<std::tuple<std::string, double>> params_p;

    static int top_p;
    static int right_p;
    static int bottom_p;
    static int left_p;
    static int front_p;
    static int back_p;

    static std::list<Body*> bodies_p;

public:
    static bool parseXML(const std::string);

    double get_t_end();
    double get_delta_t();
    int get_calcType();
    std::string get_baseNameOutputFiles();
    int get_writeFrequency();
    std::string get_gravInput();

    double get_epsilon();
    double get_mass();
    double get_rho();
    double get_h();
    std::vector<std::tuple<std::string, double>> get_params_p();

    int get_top();
    int get_right();
    int get_bottom();
    int get_left();
    int get_front();
    int get_back();

    std::list<Body*> get_bodies_p;
};

#endif //PSEMOLDYN_GROUPG_DRIVER_INPUT_H