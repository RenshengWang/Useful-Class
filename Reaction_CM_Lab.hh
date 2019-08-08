#ifndef Reaction_CM_Lab_h
#define Reaction_CM_Lab_h 1

#include "TObject.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "iostream"
#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "fstream"

using namespace std;
using namespace TMath;

class Reaction_CM_Lab : public TObject
{
public:
  Reaction_CM_Lab();
  ~Reaction_CM_Lab();

public:
  int Beam_A; int Beam_Z; double Beam_Mass;
  double Beam_Ekin_PerNucleon;
  double Beam_Ekin_Total;
  double Beam_E_Total;
  
  double Beam_gamma; double Beam_beta;
  double Beam_Pz;
  
  int Target_A; int Target_Z; double Target_Mass;
  double Target_E_Total;
  
  void SetBeam(int A,int Z, double Mass) { Beam_A=A; Beam_Z=Z; Beam_Mass=Mass; }
  void SetTarget(int A,int Z, double Mass) { Target_A=A; Target_Z=Z; Target_Mass=Mass; }
  void SetBeam_Ekin_PerNucleon(double Ekin){ Beam_Ekin_PerNucleon = Ekin; }
  
public:
  //the below is for calculating the information in the CM
  double Beta_CM; double Gamma_CM;
  double Beam_Pz_CM;
  double Target_Pz_CM;
  double Beam_Momentum_CM[4];
  double Rapidity_Beam_CM;

  void Lab_to_CM(double* P_Lab,double Mass,double* P_CM);
  void Lab_to_CM(double* P_Lab,double* P_CM);
  void CM_to_Lab(double* P_CM,double Mass,double* P_Lab);
  void CM_to_Lab(double* P_CM,double* P_Lab); 
  double Cal_Rapidity_CM(double* P_CM);
  double Get_BeamRapidity_CM() { return Rapidity_Beam_CM; }

public:
  void Initial_Reaction();
  void Print_Info();

  ClassDef(Reaction_CM_Lab,1)
};

#endif
