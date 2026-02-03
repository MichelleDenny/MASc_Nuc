#ifndef V1PRIMARYGENERATOR_HH
#define V1PRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh" //usually the thing that the class derived from
#include "G4ParticleDefinition.hh"          //defines e, p etc
#include "G4ParticleGun.hh"                 //shoots particles
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4Neutron.hh"
#include "G4UniformRandPool.hh"

class V1PrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    V1PrimaryGenerator();
    ~V1PrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *);

private:
    G4ParticleGun *fParticleGun;
};

#endif