#include "V1PhysicsList.hh"

V1PhysicsList::V1PhysicsList() : QGSP_BIC_AllHP()
{
    // RegisterPhysics(new G4IonPhysics());
} // The QGSP_BIC_HP reference physics list was used to model hadronic
// interactions and high-precision neutron transport

V1PhysicsList::~V1PhysicsList() // destructor
{
}