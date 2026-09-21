#include "V2SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4Neutron.hh"

V2SensitiveDetector::V2SensitiveDetector(G4String name) : G4VSensitiveDetector(name), fTotalEnergyDeposited(0.)
{
}

V2SensitiveDetector::~V2SensitiveDetector()
{
}

void V2SensitiveDetector::Initialize(G4HCofThisEvent *)
{
    fTotalEnergyDeposited = 0.;
    fFluxCount = 0;
    fEventEdep = 0.;
}

G4bool V2SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *)
{
    //  Energy deposited in this step
    G4double edep = step->GetTotalEnergyDeposit();
    auto track = step->GetTrack();
    auto particle = track->GetDefinition();

    if (step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary)
    {
        if (track->GetDefinition() == G4Neutron::Definition())
        {
            fFluxCount++;
        }
    }

    // ENERGY DEPOSITION (event level accumulation)
    // -------------------------
    if (edep > 0.)
    {
        fTotalEnergyDeposited += edep;
        fEventEdep += edep;
    }
    /*Edep code
    if (edep <= 0.)
        return false;

    G4cout << "HIT DETECTED: "
           << track->GetParticleDefinition()->GetParticleName()
           << " Edep = "
           << edep / MeV << " MeV"
           << G4endl;
fTotalEnergyDeposited += edep;
     */

    // Position (optional but useful)
    auto pre = step->GetPreStepPoint();
    G4ThreeVector pos = pre->GetPosition();

    // Particle info (debug)
    // auto particle = step->GetTrack()->GetDefinition();

    G4AnalysisManager *analysis = G4AnalysisManager::Instance();

    // Fill NTUPLE
    analysis->FillNtupleIColumn(0, 0, G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID());

    analysis->FillNtupleDColumn(0, 1, pos.x());
    analysis->FillNtupleDColumn(0, 2, pos.y());
    analysis->FillNtupleDColumn(0, 3, pos.z());

    analysis->FillNtupleDColumn(0, 4, pre->GetGlobalTime());

    analysis->FillNtupleDColumn(0, 5, edep);
    analysis->AddNtupleRow(0);

    return true;
}

void V2SensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    G4AnalysisManager *analysis = G4AnalysisManager::Instance();

    // IMP: use NAME, not index
    analysis->FillH1(0, fTotalEnergyDeposited / MeV);

    // OPTIONAL: store event-level quantities properly
    analysis->FillH1(1, fFluxCount); // if you want distribution
    // G4cout << " Total Deposited energy in detector: " << fTotalEnergyDeposited / MeV<< " MeV" << G4endl;
}