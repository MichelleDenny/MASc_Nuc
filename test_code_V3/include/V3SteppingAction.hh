#ifndef V3STEPPINGACTION_HH
#define V3STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class V3SteppingAction : public G4UserSteppingAction
{
public:
    V3SteppingAction();
    ~V3SteppingAction();
};
#endif
