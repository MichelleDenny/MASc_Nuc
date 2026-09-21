#include "V2PrimaryGenerator.hh"

V2PrimaryGenerator::V2PrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(10000); // 10 particle per event

    /// ---- Particle type: neutron ----
    G4ParticleDefinition *neutron = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
    fParticleGun->SetParticleDefinition(neutron);

    // ---- Neutron energy ----
    fParticleGun->SetParticleEnergy(14.1 * MeV);

    // ---- Source position (target inside graphite hole) ----
    G4ThreeVector pos(0. * cm, 0. * cm, 0 * cm);
    fParticleGun->SetParticlePosition(pos);

    // ---beam is trsvelling a certain direction now; not isotropic
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
}
V2PrimaryGenerator::~V2PrimaryGenerator()
{
    delete fParticleGun;
}

void V2PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // ---- Isotropic neutron emission ----
    /*G4double theta = CLHEP::pi * G4UniformRand();
    G4double phi = 2. * CLHEP::pi * G4UniformRand();

    G4ThreeVector direction(
        std::sin(theta) * std::cos(phi),
        std::sin(theta) * std::sin(phi),
        std::cos(theta));*/

    G4double cosTheta = 2.0 * G4UniformRand() - 1.0;
    G4double sinTheta =
        std::sqrt(1.0 - cosTheta * cosTheta);

    G4double phi =
        2.0 * CLHEP::pi * G4UniformRand();

    G4ThreeVector direction(
        sinTheta * std::cos(phi),
        sinTheta * std::sin(phi),
        cosTheta);

    fParticleGun->SetParticleMomentumDirection(direction);

    // ---- Generate neutron ----
    fParticleGun->GeneratePrimaryVertex(anEvent);
}