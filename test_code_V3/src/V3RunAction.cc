#include "V3RunAction.hh"

V3RunAction::V3RunAction()
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetVerboseLevel(1);
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetNtupleMerging(true);

    analysisManager->CreateH1("NeutronEnergy", "Neutron Energy Spectrum", 200, 0.0, 8.0 * MeV);

    analysisManager->CreateNtuple("Output_data", "Data");
    analysisManager->CreateNtupleIColumn("iEvent");
    analysisManager->CreateNtupleDColumn("fX");
    analysisManager->CreateNtupleDColumn("fY");
    analysisManager->CreateNtupleDColumn("fZ");
    analysisManager->CreateNtupleDColumn("fGlobalTime");
    analysisManager->CreateNtupleDColumn("fKinE");
    analysisManager->FinishNtuple(0);
}

V3RunAction::~V3RunAction()
{
}

void V3RunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    // analysisManager->OpenFile("output.root"); //"output.root"
    G4int runID = run->GetRunID();

    std::stringstream strRunID; // convert int to string
    strRunID << runID;

    analysisManager->OpenFile("output" + strRunID.str() + ".root");
}

void V3RunAction::EndOfRunAction(const G4Run *run)
{

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();
    analysisManager->CloseFile(); // false was inside
    // analysisManager->Reset();

    G4int runID = run->GetRunID();

    G4cout << "Finishing run " << runID << G4endl;
}
