#include "V2EventAction.hh"
#include "G4SDManager.hh"

V2EventAction::V2EventAction()
{
}

V2EventAction::~V2EventAction()
{
}

void V2EventAction::BeginOfEventAction(const G4Event *run)
{
}

void V2EventAction::EndOfEventAction(const G4Event *run)
{
    auto sd = static_cast<V2SensitiveDetector *>(G4SDManager::GetSDMpointer()->FindSensitiveDetector("DetSD"));

    if (!sd)
        return;

    G4int flux = sd->GetFluxCount();
    G4double edep = sd->GetEventEdep();

    G4cout << "Flux = " << flux
           << " Edep = " << edep << G4endl;
}