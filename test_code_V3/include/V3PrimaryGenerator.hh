#ifndef V3PRIMARYGENERATOR_HH
#define V3PRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh" //usually the thing that the class derived from
#include "G4ParticleDefinition.hh"          //defines e, p etc
#include "G4ParticleGun.hh"                 //shoots particles
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4Neutron.hh"
#include "G4UniformRandPool.hh"

class V3PrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    V3PrimaryGenerator();
    ~V3PrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *);

private:
    G4ParticleGun *fParticleGun;
};

#endif