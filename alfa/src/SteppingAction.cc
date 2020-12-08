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
     output.open("data_kol.txt");
}

SteppingAction::~SteppingAction() 
{
     G4double Akt=1.96;
     G4int liczba_cz=PrimaryGeneratorAction::l_cz;
     
     G4double e_J=dep_en/(6.24*pow(10,12));
     G4double masa=1000*(3.1412*pow(0.015,2)*2.*pow(10,-6));
     
     std::cout << "--------  W  Y  N  I  K  I  ---------" <<std::endl;
     std::cout <<"liczba czastek w symulacji: " << liczba_cz << std::endl;
     std::cout <<"calkowita energia zdeponowana w komorkach to: "<< dep_en << " MeV = " << e_J << "J"<< std::endl;
     std::cout <<"aktywnosc zrodla: "<<Akt<<" MBq"<< std::endl;
     G4double e_calk=((Akt*pow(10,6))*e_J/liczba_cz);
     
     std::cout <<"w czasie 1 sekundy energia zdeponowana w komorkach wynosi: "<< (Akt*pow(10,6))*dep_en/liczba_cz<<" MeV = "<<e_calk<<" J"<<std::endl;
     std::cout << "Dawka zdeponowana w komorkach w czasie 1 sekundy = "<<e_calk/masa<<" Gy/s = "<< 3600000*e_calk/masa<<" mGy/h"<<std::endl;
     std::cout << masa/e_calk << " s na 1 Gy"<<std::endl;
     std::cout<< "LET: "<< dep_en/tr_len<< " MeV/mm"<<std::endl;
     
     
     outputFile->SaveOutput();
     output.close();
     
}


G4int licz=0;
G4double dep_en=0;
G4double tr_len=0;


void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
    
    G4Track* theTrack = theStep->GetTrack();
    G4String volumeName = theTrack->GetVolume()->GetName();    
    G4double energy = theStep ->GetDeltaEnergy();
    G4double len = theTrack->GetStepLength();

    if (energy != 0 and volumeName=="cellPhys")
    {
       G4StepPoint* prePoint = theStep-> GetPreStepPoint();
       G4double pos_x = prePoint ->GetPosition().x();
       G4double pos_y = prePoint ->GetPosition().y();
       energy=(-energy);
       outputFile->AddPos(licz,energy,pos_x,pos_y);
       output << energy << "\t"<< len<< "\t"<< pos_x<< "\t"<<pos_y<<std::endl;
       ++licz;
       tr_len+=len;
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

double SteppingAction::tr_len=0;
double SteppingAction::dep_en=0;
int SteppingAction::nrOfSec=0;

