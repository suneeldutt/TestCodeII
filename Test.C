#define Test_cxx
#include "Test.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <iostream>
#include <TFile.h>
#include <TH1.h>
//using namespace std;
using std::cout;
using std::endl;
void Test::Loop()
{
   if (fChain == 0) return;
TFile *f = new TFile("test.root","RECREATE");
   Long64_t nentries = fChain->GetEntries();
TH1F *HitEnergy  = new TH1F("HitEnergy","Energy of Reconstructed Hit", 200, 0, 10);
TH1F *HitTime  = new TH1F("HitTime","Timing", 300, -60, 60);
TH1F *HitEt = new TH1F("HitEt","Et of Reconstructed Hit", 200, 0, 10);
TH1F *HitIfkWeird = new TH1F("HitIfkWeird","kWeird of Reconstructed Hit", 200, -10, 10);
TH1F *HitSwissCross = new TH1F("HitSwissCross","swissCross of Reconstructed Hit", 200, 0, 10);
TH2F *HitSwissCross_HitTime = new TH2F("HitSwissCross_HitTime","Swiss-cross vs. time of MultiFit", 200, 0.2, 2, 100, -60, 60);
TH1F *HitIfkOOT = new TH1F("HitIfkOOT","kOOT  of Reconstructed Hit", 200, -10, 10);
TH1F *HitIfkDiWeird = new TH1F("HitIfkDiWeird","kDiWeird of Reconstructed Hit", 200, -10, 10);
TH2F *HitIfkDiWeird_HitIfkWeird = new TH2F("HitIfkDiWeird_HitIfkWeird","kDiWeird+KWeird",200, 0.2, 1.2, 200, -60, 60);
//TH2F *HitIfkDiWeird_HitIfkWeird_HitIfkOOT = new TH2F("HitIfkDiWeird_HitIfkWeird_HitIfkOOT","kDiWeird+KWeird+ifkOOT",200, 0.2, 1.2, 200, -60, 60);
//TH1F *HitIfkDiWeird_HitIfkWeird_HitIfkOOT = new TH1F("HitIfkDiWeird_HitIfkWeird_HitIfkOOT","kDiWeird+KWeird+kOutOfTime",200, 0.2, 2);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
unsigned int temp;
temp = Rechit_energy->size();
printf("Total number of rec hits in this event %d\n", temp);
for(unsigned int ihit=0; ihit !=Rechit_energy->size(); ++ihit){
if( Rechit_energy->at(ihit) > 4){
printf("energy & time of rec hit number %d\t is %f\t%f\n", ihit, Rechit_energy->at(ihit), Rechit_time->at(ihit));
HitEnergy->Fill(Rechit_energy->at(ihit));
HitTime->Fill(Rechit_time->at(ihit));
HitEt->Fill(Rechit_et->at(ihit));
HitSwissCross->Fill(Rechit_swissCross->at(ihit));
HitIfkWeird->Fill(Rechit_ifkWeird->at(ihit));
HitSwissCross_HitTime->Fill(Rechit_swissCross->at(ihit), Rechit_time->at(ihit));
HitSwissCross_HitTime->GetXaxis()->SetTitle("Swiss-Cross");
HitSwissCross_HitTime->GetXaxis()->CenterTitle(1);
HitSwissCross_HitTime->GetYaxis()->SetTitle("RecHit Timing[ns]");
HitSwissCross_HitTime->GetYaxis()->CenterTitle(1);
HitIfkOOT->Fill(Rechit_ifkOOT->at(ihit));
HitIfkDiWeird->Fill(Rechit_ifkDiWeird->at(ihit));
if(Rechit_swissCross->at(ihit) > 0.95) {
HitIfkDiWeird_HitIfkWeird->Fill(Rechit_swissCross->at(ihit), Rechit_time->at(ihit));
HitIfkDiWeird_HitIfkWeird->GetXaxis()->SetTitle("Swiss-Cross");
HitIfkDiWeird_HitIfkWeird->GetXaxis()->CenterTitle(1);
HitIfkDiWeird_HitIfkWeird->GetYaxis()->SetTitle("RecHit Timing[ns]");
HitIfkDiWeird_HitIfkWeird->GetYaxis()->CenterTitle(1);


/*HitIfkDiWeird_HitIfkWeird_HitIfkOOT->Fill(Rechit_swissCross->at(ihit), Rechit_time->at(ihit));
HitIfkDiWeird_HitIfkWeird_HitIfkOOT->GetXaxis()->SetTitle("Swiss-Cross");
HitIfkDiWeird_HitIfkWeird_HitIfkOOT->GetXaxis()->CenterTitle(1);
HitIfkDiWeird_HitIfkWeird_HitIfkOOT->GetYaxis()->SetTitle("RecHit Timing[ns]");
HitIfkDiWeird_HitIfkWeird_HitIfkOOT->GetYaxis()->CenterTitle(1);*/

//HitIfkDiWeird_HitIfkWeird_HitIfkOOT->Fill(Rechit_ifkDiWeird->at(ihit))+(Rechit_ifkWeird->at(ihit))+(Rechit_ifkOOT->at(ihit));

//cout << "hit " << ihit << "\tEnergy " << Rechit_energy->at(ihit) << endl;
}
}
}
cout << "****************************" << endl;

   }
f->Write();
f->Close();
}

