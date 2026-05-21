#ifndef V2PRIMARYGENERATOR_HH
#define V2PRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh" //usually the thing that the class derived from
#include "G4ParticleDefinition.hh"          //defines e, p etc
#include "G4ParticleGun.hh"                 //shoots particles
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4Neutron.hh"
#include "G4UniformRandPool.hh"

class V2PrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    V2PrimaryGenerator();
    ~V2PrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *);

private:
    G4ParticleGun *fParticleGun;
};

#endif