#include "OutputRoot.hh"


OutputRoot::OutputRoot()
{
   rootManager=G4RootAnalysisManager::Instance();
   
   rootManager->SetFirstNtupleId(0);
   

}

void OutputRoot::CreateFile(G4String filename)
{
    rootManager->OpenFile(filename);
    PosTupleId=0;
    CreatePosTuple();
}
void OutputRoot::SaveOutput()
{
   rootManager->Write();
   rootManager->CloseFile();
}

void OutputRoot::CreatePosTuple()
{
   rootManager->CreateNtuple("PosInfo","Position and energy");
   rootManager->CreateNtupleIColumn("eventId");
   rootManager->CreateNtupleDColumn("energy");
   rootManager->CreateNtupleDColumn("pos_x");
   rootManager->CreateNtupleDColumn("pos_y");

   rootManager->FinishNtuple();
}
void OutputRoot::AddPos(int eventId, double energy, double pos_x, double pos_y)
{
    int cloId=0;
    
    rootManager->FillNtupleIColumn(PosTupleId, cloId, eventId);
    rootManager->FillNtupleDColumn(PosTupleId, ++cloId, energy);
    rootManager->FillNtupleDColumn(PosTupleId, ++cloId, pos_x);
    rootManager->FillNtupleDColumn(PosTupleId, ++cloId, pos_y);
    rootManager->AddNtupleRow(PosTupleId);
}


OutputRoot* OutputRoot::instance=0;
