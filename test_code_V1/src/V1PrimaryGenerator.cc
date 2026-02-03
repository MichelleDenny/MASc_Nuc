#include "V1PrimaryGenerator.hh"

V1PrimaryGenerator::V1PrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1); // 1 particle per event

    /// ---- Particle type: neutron ----
    G4ParticleDefinition *neutron = G4Neutron::Definition();
    fParticleGun->SetParticleDefinition(neutron);

    // ---- D–T neutron energy ----
    fParticleGun->SetParticleEnergy(14.1 * MeV);

    // ---- Source position (target inside graphite hole) ----
    G4ThreeVector pos(0. * cm, 0. * cm, -1. * cm);
    fParticleGun->SetParticlePosition(pos);
}
V1PrimaryGenerator::~V1PrimaryGenerator()
{
    delete fParticleGun;
}

void V1PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // ---- Isotropic neutron emission ----
    G4double theta = CLHEP::pi * G4UniformRand();
    G4double phi = 2. * CLHEP::pi * G4UniformRand();

    G4ThreeVector direction(
        std::sin(theta) * std::cos(phi),
        std::sin(theta) * std::sin(phi),
        std::cos(theta));

    fParticleGun->SetParticleMomentumDirection(direction);

    // ---- Generate neutron ----
    fParticleGun->GeneratePrimaryVertex(anEvent);
}