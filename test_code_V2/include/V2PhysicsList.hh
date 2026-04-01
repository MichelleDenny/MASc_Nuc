#ifndef V2PHYSICSLIST_HH
#define V2PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
#include "QGSP_BIC_AllHP.hh"

class V2PhysicsList : public QGSP_BIC_AllHP // define class and inherit it from the modularlist
{
public:
    V2PhysicsList();  // constructor
    ~V2PhysicsList(); // destructor
};

#endif