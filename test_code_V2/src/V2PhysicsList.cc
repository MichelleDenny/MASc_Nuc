#include "V2PhysicsList.hh"

V2PhysicsList::V2PhysicsList() : QGSP_BIC_AllHP()
{
    // RegisterPhysics(new G4IonPhysics());
} // The QGSP_BIC_HP reference physics list was used to model hadronic
// interactions and high-precision neutron transport

V2PhysicsList::~V2PhysicsList() // destructor
{
}