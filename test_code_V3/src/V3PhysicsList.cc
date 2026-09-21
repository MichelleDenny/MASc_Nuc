#include "V3PhysicsList.hh"

V3PhysicsList::V3PhysicsList() : QGSP_BIC_AllHP()
{
    RegisterPhysics(new G4IonPhysicsPHP());
} // The QGSP_BIC_HP reference physics list was used to model hadronic
// interactions and high-precision neutron transport

V3PhysicsList::~V3PhysicsList() // destructor
{
}