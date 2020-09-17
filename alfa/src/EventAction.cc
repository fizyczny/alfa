// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"




EventAction::EventAction()
{
     outputFile=OutputRoot::GetInstance();
    
}
 
EventAction::~EventAction()
{
     outputFile->SaveOutput();
    }


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
    
}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{	

}
