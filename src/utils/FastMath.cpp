//
// Created by thomas on 01.12.21.
//

#include <cstdlib>

bool checkIfSquareRootOfNumberIsBiggerThanCertainValue(double number, double certainValue){
    //Code of the newton iteration adapted from: https://stackoverflow.com/questions/40333800/newton-raphson-using-recursion-in-c
    double val = number; // initial guess
    for(;;) {
        double last = val;
        val = (val + number / val) * 0.5; // iterative
        double error = abs(val - last);

        //If the root is certainly smaller
        if(val + error < certainValue){
            return false;
        }
        //If the root is certainly bigger t
        if(val - error > certainValue){
            return true;
        }
    }
}