#include "TMath.h"
using namespace TMath;

void Test_Reaction_CM_Lab()
{
  double Unit_Mass = 931.494; //1u=931.494 MeV/c2
  
  int Target_A = 124;int Target_Z = 50;
  double Target_Mass_excess = -76.554171; //unit: MeV/c2
  double Target_Mass = Unit_Mass*Target_A+Target_Mass_excess;
  
  int Beam_A = 132; int Beam_Z=50;
  double Beam_Mass_excess = -88.236752;//unit: MeV/c2
  double Beam_Mass = Unit_Mass*Beam_A+Beam_Mass_excess;
  
  Reaction_CM_Lab* Reaction = new Reaction_CM_Lab();
  Reaction->SetBeam(Beam_A,Beam_Z,Beam_Mass);
  Reaction->SetTarget(Target_A,Target_Z,Target_Mass);
  Reaction->SetBeam_Ekin_PerNucleon(270);
  
  Reaction->Initial_Reaction();
  
  Reaction->Print_Info();
  
/*
muon	105.7 MeV/c
pi	139.57
proton	938.3
neutron	939.6
Deuteron	1876.2
Triton	2809.5
3He	2809.5
4He	3728.5
*/
  double Pion_Mass = 139.57; //unit: MeV/c2
  double P_Lab[4] = {0,0,50,Pion_Mass};
  double ETotal_Lab = 0;
  for(int i=0;i<4;i++)
  {
    ETotal_Lab += P_Lab[i]*P_Lab[i];
  }
  P_Lab[3] = Sqrt(ETotal_Lab);
  cout<<"ETotal_Lab: "<<P_Lab[3]<<endl;
  
  double P_CM[4] = {0,0,0,0};
  //Reaction->Lab_to_CM(P_Lab,Pion_Mass,P_CM);
  Reaction->Lab_to_CM(P_Lab,P_CM);
  cout<<"C.M.: "<<P_CM[0]<<"  "<<P_CM[1]<<"  "<<P_CM[2]<<"  "<<P_CM[3]<<endl;
  
  P_Lab[2] = 0; P_Lab[3] = 0;
  //Reaction->CM_to_Lab(P_CM,Pion_Mass,P_Lab);
  Reaction->CM_to_Lab(P_CM,P_Lab);
  cout<<" Lab : "<<P_Lab[0]<<"  "<<P_Lab[1]<<"  "<<P_Lab[2]<<"  "<<P_Lab[3]<<endl;
  double Rapidity = Reaction->Cal_Rapidity_CM(P_CM);
  cout<<"Rapidity : "<<Rapidity<<endl;
  
  //the below is for verificating from the TLorentzVector
  TLorentzVector P_Lab_tem(P_Lab[0],P_Lab[1],P_Lab[2],P_Lab[3]);
  P_Lab_tem.Boost(0,0,-0.365563);
  P_Lab_tem.Print();
  
  cout<<"Rapidity : "<<P_Lab_tem.Rapidity()<<endl;
  
  P_Lab_tem.Boost(0,0,0.365563);
  P_Lab_tem.Print();
}
