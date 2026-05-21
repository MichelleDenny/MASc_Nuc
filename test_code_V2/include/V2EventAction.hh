#ifndef V2EVENTACTION_HH
#define V2EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class V2EventAction : public G4UserEventAction
{
public:
    V2EventAction();
    ~V2EventAction();

    virtual void BeginOfEventAction(const G4Event *);
    virtual void EndOfEventAction(const G4Event *);
};
#endif