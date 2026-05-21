#ifndef V2ACTIONINITIALIZATION_HH
#define V2ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

#include "V2PrimaryGenerator.hh"
#include "V2RunAction.hh"
#include "V2SteppingAction.hh"
#include "V2EventAction.hh"

class V2ActionInitialization : public G4VUserActionInitialization
{
public:
    V2ActionInitialization();
    ~V2ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
    // these are virtual funcs cause we have to overwrite those that are already implemented
};
#endif