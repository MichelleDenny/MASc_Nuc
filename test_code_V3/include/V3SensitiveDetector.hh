#ifndef V3SENSITIVEDETECTOR_HH
#define V3SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "globals.hh"
#include "G4Neutron.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class V3SensitiveDetector : public G4VSensitiveDetector
{
public:
    V3SensitiveDetector(G4String);
    ~V3SensitiveDetector();

    // virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);

    virtual void Initialize(G4HCofThisEvent *) override;
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *) override;
    virtual void EndOfEvent(G4HCofThisEvent *) override;

private:
    G4double fTotalEnergyDeposited;
};

#endif