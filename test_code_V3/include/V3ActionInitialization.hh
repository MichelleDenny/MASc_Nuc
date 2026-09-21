#ifndef V3ACTIONINITIALIZATION_HH
#define V3ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

#include "V3PrimaryGenerator.hh"
#include "V3RunAction.hh"
#include "V3SteppingAction.hh"
#include "V3EventAction.hh"

class V3ActionInitialization : public G4VUserActionInitialization
{
public:
    V3ActionInitialization();
    ~V3ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
    // these are virtual funcs cause we have to overwrite those that are already implemented
};
#endif