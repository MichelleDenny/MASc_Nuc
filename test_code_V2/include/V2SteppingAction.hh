#ifndef V2STEPPINGACTION_HH
#define V2STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class V2SteppingAction : public G4UserSteppingAction
{
public:
    V2SteppingAction();
    ~V2SteppingAction();
};
#endif
