//
// $Id: SteppingAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
#include "SteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"

#include "OutputRoot.hh"
#include "PrimaryGeneratorAction.hh"

SteppingAction::SteppingAction():G4UserSteppingAction()
{
     outputFile=OutputRoot::GetInstance();
     outputFile->CreateFile("POS.root");
}

SteppingAction::~SteppingAction() 
{
     G4double Akt=1.96;
     G4int liczba_cz=PrimaryGeneratorAction::l_cz;
     std::cout << "--------  W  Y  N  I  K  I  ---------" <<std::endl;
     std::cout <<"liczba czastek w symulacji: " << liczba_cz << std::endl;
     std::cout <<"calkowita energia zdeponowana w komorkach to: "<< dep_en << " MeV = " << dep_en/(6.24*pow(10,12)) << "J"<< std::endl;
     std::cout <<"aktywnosc zrodla: "<<Akt<<" MBq"<< std::endl;
     G4double e_calk=((Akt*pow(10,6))*dep_en/liczba_cz)/(6.24*pow(10,12));
     
     std::cout <<"w czasie 1 sekundy energia zdeponowana w komorkach wynosi: "<< (Akt*pow(10,6))*dep_en/liczba_cz<<" MeV = "<<e_calk<<" J"<<std::endl;
     std::cout << "Dawka zdeponowana w komorkach w czasie 1 sekundy = "<<e_calk/(8.48*pow(10,-6))<<" Gy"<<std::endl;
     std::cout << "Moc dawki = " << 1/(e_calk/(8.48*pow(10,-6)))<<" s/Gy"<< std::endl;
     
     outputFile->SaveOutput();
     
}


G4int licz=0;
G4double dep_en=0;


void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
    
    G4Track* theTrack = theStep->GetTrack();
    G4String volumeName = theTrack->GetVolume()->GetName();    
    G4double energy = theStep ->GetDeltaEnergy();

    if (energy != 0 and volumeName=="cellPhys")
    {
       G4StepPoint* prePoint = theStep-> GetPreStepPoint();
       G4double pos_x = prePoint ->GetPosition().x();
       G4double pos_y = prePoint ->GetPosition().y();
       energy=(-energy);
       outputFile->AddPos(licz,energy,pos_x,pos_y);
       ++licz;
       dep_en+=energy;
       //std::cout << "nr "<< licz << " X_pos "<< pos_x<< " Y_pos "<< pos_y<< " energia "<< energy<<std::endl;
    }
    
    
    
}

void SteppingAction::PrintStep(const G4Step* theStep)
{

    G4Track* theTrack = theStep->GetTrack();
    G4String particleName = theTrack->GetDefinition()->GetParticleName();      
    G4String processName =theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    
    G4double energy = theTrack->GetKineticEnergy() ;
    G4String volumeName = theTrack->GetVolume()->GetName();
    G4double deltaEn = theStep->GetDeltaEnergy();
    int trackNr = theTrack->GetTrackID ();    

    std::cout << " trackNr: " << trackNr
              << " particle: " << particleName
	      << " process: " << processName
	      << " kinetic energy " << energy
	      << " delta en: " << deltaEn
	      << " voulme name: " << volumeName << std::endl;

}

double SteppingAction::dep_en=0;
int SteppingAction::nrOfSec=0;

