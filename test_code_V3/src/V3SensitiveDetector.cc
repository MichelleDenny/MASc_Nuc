#include "V3SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4ParticleDefinition.hh"

V3SensitiveDetector::V3SensitiveDetector(G4String name)
    : G4VSensitiveDetector(name), fTotalEnergyDeposited(0.)
{
}

V3SensitiveDetector::~V3SensitiveDetector()
{
}

void V3SensitiveDetector::Initialize(G4HCofThisEvent *)
{
    fTotalEnergyDeposited = 0.;
}

G4bool V3SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *)
{

    G4Track *track = step->GetTrack();
    auto particle = track->GetDefinition();

    if (particle != G4Neutron::Definition())
    {
        return false;
    }
    G4cout << "HIT DETECTED" << G4endl;
    /* //  Energy deposited in this step
     G4double edep = step->GetTotalEnergyDeposit();
     G4cout << step->GetTotalEnergyDeposit() / MeV << G4endl;

     if (edep <= 0.)
         return false;
     fTotalEnergyDeposited += edep;
 */
    // Position
    auto pre = step->GetPreStepPoint();
    G4ThreeVector pos = pre->GetPosition();
    // Energy of Neutron
    G4double Ekin = track->GetKineticEnergy();

    G4AnalysisManager *analysis = G4AnalysisManager::Instance();

    // fill the histogram
    analysis->FillH1(0, Ekin / MeV);

    // Fill NTUPLE
    analysis->FillNtupleIColumn(0, 0, G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID());
    analysis->FillNtupleDColumn(0, 1, pos.x());
    analysis->FillNtupleDColumn(0, 2, pos.y());
    analysis->FillNtupleDColumn(0, 3, pos.z());
    analysis->FillNtupleDColumn(0, 4, pre->GetGlobalTime() / ns);
    analysis->FillNtupleDColumn(0, 5, Ekin);

    analysis->AddNtupleRow(0);

    return true;
}

void V3SensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{

    // G4cout << " Total Deposited energy in detector: " << fTotalEnergyDeposited / MeV<< " MeV" << G4endl;
}