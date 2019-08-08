#include "Reaction_CM_Lab.hh"
ClassImp(Reaction_CM_Lab);

Reaction_CM_Lab::Reaction_CM_Lab()
{
  Beam_A = 0; Beam_Z=0; Beam_Mass=0;
  Beam_Ekin_PerNucleon=0;
  
  Target_A=0; Target_Z=0; Target_Mass=0;
  
  Beam_gamma=0; Beam_beta=0;
  Beam_Pz=0;
}

Reaction_CM_Lab::~Reaction_CM_Lab()
{;}

void Reaction_CM_Lab::Initial_Reaction()
{
  Beam_Ekin_Total = Beam_A*Beam_Ekin_PerNucleon;
  
  Beam_gamma = Beam_Ekin_Total/Beam_Mass+1;
  Beam_beta = Sqrt(1-1/Power(Beam_gamma,2));
  Beam_E_Total = Beam_Mass*Beam_gamma;
  
  Beam_Pz = Beam_Mass*Beam_beta*Beam_gamma;
  Target_E_Total = Target_Mass;
  
  //the below is for CM
  Beta_CM = (Beam_Pz)/(Beam_Mass*Beam_gamma+Target_Mass);
  Gamma_CM = Sqrt(1/(1-Beta_CM*Beta_CM));
  Beam_Pz_CM = Gamma_CM*(Beam_Pz-Beta_CM*Beam_E_Total);
  Target_Pz_CM = Gamma_CM*(0-Beta_CM*Target_E_Total);
  
  //calculate the rapidity of beam in the CM
  Beam_Momentum_CM[0] = 0; Beam_Momentum_CM[1] = 0; Beam_Momentum_CM[2] = Beam_Pz_CM; Beam_Momentum_CM[3] = Sqrt(Beam_Pz_CM*Beam_Pz_CM+Beam_Mass*Beam_Mass); 
  Rapidity_Beam_CM = Cal_Rapidity_CM(Beam_Momentum_CM);
}

void Reaction_CM_Lab::Lab_to_CM(double* P_Lab,double Mass,double* P_CM)
{
  double E_total_Lab = Sqrt(P_Lab[0]*P_Lab[0]+P_Lab[1]*P_Lab[1]+P_Lab[2]*P_Lab[2]+Mass*Mass);
  P_CM[2] = Gamma_CM*(P_Lab[2]-Beta_CM*E_total_Lab);
  P_CM[0] = P_Lab[0];
  P_CM[1] = P_Lab[1];
}

void Reaction_CM_Lab::Lab_to_CM(double* P_Lab,double* P_CM)
{
  P_CM[2] = Gamma_CM*(P_Lab[2]-Beta_CM*P_Lab[3]);
  P_CM[0] = P_Lab[0];
  P_CM[1] = P_Lab[1];
  P_CM[3] = Gamma_CM*(P_Lab[3]-Beta_CM*P_Lab[2]);
}

void Reaction_CM_Lab::CM_to_Lab(double* P_CM,double Mass,double* P_Lab)
{
  double E_total_CM = Sqrt(P_CM[0]*P_CM[0]+P_CM[1]*P_CM[1]+P_CM[2]*P_CM[2]+Mass*Mass);
  P_Lab[2] = Gamma_CM*(P_CM[2]+Beta_CM*E_total_CM);
  P_Lab[0] = P_CM[0];
  P_Lab[1] = P_CM[1];
}

void Reaction_CM_Lab::CM_to_Lab(double* P_CM,double* P_Lab)
{
  P_Lab[2] = Gamma_CM*(P_CM[2]+Beta_CM*P_CM[3]);
  P_Lab[0] = P_CM[0];
  P_Lab[1] = P_CM[1];
  P_Lab[3] = Gamma_CM*(P_CM[3]+Beta_CM*P_CM[2]);
}

double Reaction_CM_Lab::Cal_Rapidity_CM(double* P_CM)
{
  double Rapidity_tem = 0.5*Log((P_CM[3]+P_CM[2])/(P_CM[3]-P_CM[2]));
return Rapidity_tem;
}

void Reaction_CM_Lab::Print_Info()
{
  cout<<"Beam Info : "<<endl
      <<"        A : "<<Beam_A<<"  Z: "<<Beam_Z<<" Mass: "<<Beam_Mass<<" MeV/c2 "<<endl
      <<"    gamma : "<<Beam_gamma<<" Beta: "<<Beam_beta<<endl
      <<"       Pz : "<<Beam_Pz<<" MeV/c "<<endl
      <<"------------------------------------------------------------------------"<<endl;
  
  cout<<"Target Info : "<<endl
      <<"        A : "<<Target_A<<"  Z: "<<Target_Z<<" Mass: "<<Target_Mass<<" MeV/c2 "<<endl
      <<"------------------------------------------------------------------------"<<endl;
      
  cout<<"C.M.   Info : "<<endl
      <<"    Beta in Lab : "<<Beta_CM<<endl
      <<"    Gamma   Lab : "<<Gamma_CM<<endl
      <<"  Beam Pz in CM : "<<Beam_Pz_CM<<" MeV/c"<<endl
      <<"Target Pz in CM : "<<Target_Pz_CM<<" MeV/c"<<endl
      <<"------------------------------------------------------------------------"<<endl;
}
