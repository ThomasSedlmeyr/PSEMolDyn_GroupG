//
// Created by thomas on 30.11.21.
//
#pragma once
#include "BoundaryCondition2D.h"
namespace twoD {
    class OutFlowCondition2D : public BoundaryCondition2D {

    protected:

        /**
         *@brief Deletes all particles which are located in the halo cells
         */
        void calculateBoundaryCondition();


    public:
        OutFlowCondition2D(int conditionType, int side);

        void doWorkAfterCalculationStep() override;
    };
}