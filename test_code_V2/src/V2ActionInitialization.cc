#include "V2ActionInitialization.hh"

V2ActionInitialization::V2ActionInitialization()
{
}

V2ActionInitialization::~V2ActionInitialization()
{
}

void V2ActionInitialization::BuildForMaster() const
{
    V2RunAction *runAction = new V2RunAction();
    SetUserAction(runAction);
}
void V2ActionInitialization::Build() const

{
    // hands over primary generator here
    V2PrimaryGenerator *generator = new V2PrimaryGenerator();
    SetUserAction(generator);

    V2RunAction *runAction = new V2RunAction();
    SetUserAction(runAction);

    V2SteppingAction *steppingAction = new V2SteppingAction();
    SetUserAction(steppingAction);

    V2EventAction *eventAction = new V2EventAction();
    SetUserAction(eventAction);
}