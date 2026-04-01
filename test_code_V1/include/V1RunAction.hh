#ifndef V1RUNACTION_HH
#define V1RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class V1RunAction : public G4UserRunAction
{
public:
    V1RunAction();
    ~V1RunAction();

    virtual void BeginOfRunAction(const G4Run *);
    virtual void EndOfRunAction(const G4Run *);
};
#endif