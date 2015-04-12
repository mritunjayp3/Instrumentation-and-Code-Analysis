/*
 * testable.h
 *
 *  Created on: Feb 13, 2013
 *      Author: rajarshi
 */

#ifndef TESTABLE_H_
#define TESTABLE_H_

//#include <boost/shared_ptr.hpp>

/**
 * Interface to systems on which statistical tests could be
 * carried out to test for properties.
 */
class testable{
    
public:
   // typedef boost::shared_ptr<testable> ptr;
    testable(){}
    virtual ~testable(){}
    /**
     * Computes a simulation run (bounded in time) over the system and
     * checks if the property is satisfied by the system.
     *
     * Returns true if the simulation run satisfies the property, false otherwise.
     * What is the propertry to be tested is application dependant.
     * E.g. For sensitivity analysis, the property will the be QoS of the
     * application under test. The implementation of this function should
     * compare the output of the application and the QoS band. This should
     * return true if the application output is within the QoS band, otherwise
     * false should be returned.
     *
     */
    virtual bool run_sample() = 0;
};



#endif /* TESTABLE_H_ */