#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_BIC_AllHP.hh"

#include "V3PhysicsList.hh"
#include "V3DetectorConstruction.hh"
#include "V3ActionInitialization.hh"

int main(int argc, char **argv)
{
    G4UIExecutive *ui = nullptr;

#ifdef G4MULTITHREADED
    G4MTRunManager *runManager = new G4MTRunManager;

#else
    G4RunManager *runManager = new G4RunManager();

#endif

    // Physics List
    runManager->SetUserInitialization(new V3PhysicsList());

    runManager->SetUserInitialization(new QGSP_BIC_AllHP());

    // Detector Construction
    runManager->SetUserInitialization(new V3DetectorConstruction());

    // Action Initialization
    runManager->SetUserInitialization(new V3ActionInitialization());

    if (argc == 1)
    {
        ui = new G4UIExecutive(argc, argv); // this command is called if only the number of command line arguments is 1
    }

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialise();

    G4UImanager *UIManager = G4UImanager::GetUIpointer();
    if (ui) // pointer exists and is not in null mode
    {       // // interactive mode
        UIManager->ApplyCommand("/control/execute vis.mac");
        UIManager->ApplyCommand("/control/execute run.mac");
        ui->SessionStart();
        delete ui;
    }
    else // pointer is null pointer
    {    // BATCH MODE?
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UIManager->ApplyCommand(command + fileName);
    }
    delete visManager;
    delete runManager;

    // return 0;
}
