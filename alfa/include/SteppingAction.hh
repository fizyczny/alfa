//
// $Id: SteppingAction.hh 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.hh
/// \brief Definition of the SteppingAction class
//
#ifndef SteppingAction_H
#define SteppingACtion_H 1

#include "G4UserSteppingAction.hh"
#include "OutputRoot.hh"

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction();
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*);
    static double dep_en; 
    static double tr_len;
    //static double licznik;
    static int nrOfSec;
    
  private:
     void PrintStep(const G4Step* theStep);
     OutputRoot* outputFile;
     std::ofstream output;
     
    
};

#endif
