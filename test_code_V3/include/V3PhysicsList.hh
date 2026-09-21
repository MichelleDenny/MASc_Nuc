#ifndef V3PHYSICSLIST_HH
#define V3PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
#include "QGSP_BIC_AllHP.hh"
#include "G4IonPhysicsPHP.hh"

class V3PhysicsList : public QGSP_BIC_AllHP // define class and inherit it from the modularlist
{
public:
    V3PhysicsList();  // constructor
    ~V3PhysicsList(); // destructor
};

#endif