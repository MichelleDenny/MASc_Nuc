#include "V3ActionInitialization.hh"

V3ActionInitialization::V3ActionInitialization()
{
}

V3ActionInitialization::~V3ActionInitialization()
{
}

void V3ActionInitialization::BuildForMaster() const
{
    V3RunAction *runAction = new V3RunAction();
    SetUserAction(runAction);
}
void V3ActionInitialization::Build() const

{
    // hands over primary generator here
    V3PrimaryGenerator *generator = new V3PrimaryGenerator();
    SetUserAction(generator);

    V3RunAction *runAction = new V3RunAction();
    SetUserAction(runAction);

    V3SteppingAction *steppingAction = new V3SteppingAction();
    SetUserAction(steppingAction);

    V3EventAction *eventAction = new V3EventAction();
    SetUserAction(eventAction);
}