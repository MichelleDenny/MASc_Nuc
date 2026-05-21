#include "V1ActionInitialization.hh"

V1ActionInitialization::V1ActionInitialization()
{
}

V1ActionInitialization::~V1ActionInitialization()
{
}

void V1ActionInitialization::BuildForMaster() const
{
    V1RunAction *runAction = new V1RunAction();
    SetUserAction(runAction);
}
void V1ActionInitialization::Build() const

{
    // hands over primary generator here
    V1PrimaryGenerator *generator = new V1PrimaryGenerator();
    SetUserAction(generator);

    V1RunAction *runAction = new V1RunAction();
    SetUserAction(runAction);

    V1SteppingAction *steppingAction = new V1SteppingAction();
    SetUserAction(steppingAction);

    V1EventAction *eventAction = new V1EventAction();
    SetUserAction(eventAction);
}