
// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
#include <math.h>
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
using namespace std;



PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
    SetUpDefault();
    
    
    
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::SetUpDefault()
{
	
     G4ParticleDefinition* particle = particleTable->FindParticle("alpha");
     particleGun->SetParticleDefinition(particle);
     particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
     particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
     particleGun->SetParticleEnergy(5482.0*keV);
     
     

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
     GenerateAlphaIncident(anEvent);
     ++l_cz;
}	

void PrimaryGeneratorAction::GenerateAlphaIncident(G4Event* anEvent)
{
     G4double thetaMin =0*deg;
     G4double thetaMax =180*deg;
     G4double phiMin =0*deg;
     G4double phiMax =360*deg;
     G4ParticleDefinition* particle = particleTable->FindParticle("alpha");
     
	
     G4double r=G4UniformRand()*sin(90*deg)*2.5*cm;
     G4double ang=(G4UniformRand()*360*deg);
     
     G4double X= r*sin(ang);
     G4double Y= r*cos(ang);
     G4double Z =((G4UniformRand()-0.5)*0.0004-0.0012)*mm;
     particleGun->SetParticlePosition(G4ThreeVector(X,Y,Z));
     particleGun->SetParticleDefinition(particle);
     particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection(thetaMin,thetaMax,phiMin,phiMax));
     
     
     G4double en=(G4UniformRand());
     if (en<0.85)
     {
         particleGun->SetParticleEnergy(5486.0*keV);
     }
     else
     {
         if (en<0.98)
	 {
	    particleGun->SetParticleEnergy(5443.0*keV);
	 }
	 else
	 {
	    particleGun->SetParticleEnergy(5388.0*keV);
	 }
     }
    
     particleGun->GeneratePrimaryVertex(anEvent);

     
}	

G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection(G4double thetaMin,G4double thetaMax,G4double phiMin,G4double phiMax)
{
  
   double cosTheta = G4UniformRand()*(cos(thetaMin) - cos(thetaMax)) + cos(thetaMax);

   double sinTheta = pow(1-pow(cosTheta, 2), 0.5);
   double phi = G4UniformRand()*(phiMax-phiMin)+phiMin;

   return G4ThreeVector(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);
   
}

int PrimaryGeneratorAction::l_cz;
