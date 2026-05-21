#ifndef V1ACTIONINITIALIZATION_HH
#define V1ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

#include "V1PrimaryGenerator.hh"
#include "V1RunAction.hh"
#include "V1SteppingAction.hh"
#include "V1EventAction.hh"

class V1ActionInitialization : public G4VUserActionInitialization
{
public:
    V1ActionInitialization();
    ~V1ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
    // these are virtual funcs cause we have to overwrite those that are already implemented
};
#endif