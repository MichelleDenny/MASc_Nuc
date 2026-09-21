#include "V3PrimaryGenerator.hh"

V3PrimaryGenerator::V3PrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(10000); // 100 particle per event

    /// ---- Particle type: deutron ----
    G4ParticleDefinition *deuteron = G4ParticleTable::GetParticleTable()->FindParticle("deuteron");
    fParticleGun->SetParticleDefinition(deuteron);

    // ---- Deuteron energy ----
    fParticleGun->SetParticleEnergy(500 * keV); // testing d-d miniature gen stripped down

    // ---- Source position (target inside graphite hole) ----
    G4ThreeVector pos(0. * cm, 0. * cm, -4 * cm);
    fParticleGun->SetParticlePosition(pos);

    // ---beam is trsvelling a certain direction now; not isotropic
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
}
V3PrimaryGenerator::~V3PrimaryGenerator()
{
    delete fParticleGun;
}

void V3PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // ---- Isotropic neutron emission ----
    /* G4double cosTheta = 2.0 * G4UniformRand() - 1.0;
    G4double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    G4double phi =
        2.0 * CLHEP::pi * G4UniformRand();

    G4ThreeVector direction(
        sinTheta * std::cos(phi),
        sinTheta * std::sin(phi),
        cosTheta);*/

    // Directed neutron emission
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));

    // ---- Generate neutron ----
    fParticleGun->GeneratePrimaryVertex(anEvent);
}