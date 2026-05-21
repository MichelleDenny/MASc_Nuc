#ifndef V1STEPPINGACTION_HH
#define V1STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class V1SteppingAction : public G4UserSteppingAction
{
public:
    V1SteppingAction();
    ~V1SteppingAction();
};
#endif
