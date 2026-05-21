#ifndef V1EVENTACTION_HH
#define V1EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class V1EventAction : public G4UserEventAction
{
public:
    V1EventAction();
    ~V1EventAction();

    virtual void BeginOfEventAction(const G4Event *);
    virtual void EndOfEventAction(const G4Event *);
};
#endif