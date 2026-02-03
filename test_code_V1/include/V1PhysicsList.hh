#ifndef V1PHYSICSLIST_HH
#define V1PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
#include "QGSP_BIC_HP.hh"

class V1PhysicsList : public QGSP_BIC_HP // define class and inherit it from the modularlist
{
public:
    V1PhysicsList();  // constructor
    ~V1PhysicsList(); // destructor
};

#endif