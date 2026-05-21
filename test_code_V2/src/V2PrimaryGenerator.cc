#include "V2PrimaryGenerator.hh"

V2PrimaryGenerator::V2PrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(60000); // 6000 particle per event

    /// ---- Particle type: deuteron ----
    G4ParticleDefinition *deuteron = G4ParticleTable::GetParticleTable()->FindParticle("deuteron");
    fParticleGun->SetParticleDefinition(deuteron);

    // ---- Deuteron energy ----
    fParticleGun->SetParticleEnergy(500 * keV);

    // ---- Source position (target inside graphite hole) ----
    G4ThreeVector pos(0. * cm, 0. * cm, -4 * cm);
    fParticleGun->SetParticlePosition(pos);

    // ---beam is trsvelling a certain direction now; not isotropic
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
}
V2PrimaryGenerator::~V2PrimaryGenerator()
{
    delete fParticleGun;
}

void V2PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
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