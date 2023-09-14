#include <iostream>
#include <vector>
#include "TSystem.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TFile.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TString.h"
#include "TPad.h"
#include "TLine.h"
#include "TLatex.h"
#include "TChain.h"
#include "TError.h"
#include "THStack.h"
#include "TAxis.h"

#include "utilities.hpp"

using namespace std;

bool printHit(int run, int ls, int evt, int ieta, int iphi, int depth, float mahiEnergy, float chiSq, bool isData=false)
{
  bool printPulses = false;
  // 
  // data
  // 
  if(isData)
  {
	  if ((ieta == -5) && iphi==42) printPulses=true;
  }
  //
  // MC
  //
  else 
  {
	  if (run==1 && ls==1 && evt==48 && ieta==28 && iphi==33 && depth==2) printPulses=true;
  }
  //return true;
  return printPulses;
}


TLegend* drawPulsePlot(TChain *ch, int printIndex, THStack* &st, TH1D* &h1_data, TString title, float &max) 
                  //int run, int ls, int evt, int ieta, int iphi, int depth, 
{ 
  float inputTS[10];
  float itPulse[10];
  float ootPulse[7][10];
  float ootEnergy[7]={0};
  float mahiEnergy=0;
  float pedEnergy=0;
  float inGain=0;
  float chiSq=0;

  ch->SetBranchAddress("inputTS",    &inputTS);
  ch->SetBranchAddress("itPulse",    &itPulse);
  ch->SetBranchAddress("ootPulse",    &ootPulse);
  ch->SetBranchAddress("ootEnergy",   &ootEnergy);
  ch->SetBranchAddress("mahiEnergy", &mahiEnergy);
  //ch->SetBranchAddress("pedEnergy",  &pedEnergy);
  ch->SetBranchAddress("inGain",     &inGain);
  ch->SetBranchAddress("chiSq",      &chiSq);
      
  TH1D *h1_it   = InitTH1D("h1_it",   "h1_it",   8, -0.5, 7.5); 
  TH1D *h1_p1   = InitTH1D("h1_p1",   "h1_p1",   8, -0.5, 7.5); 
  TH1D *h1_p2   = InitTH1D("h1_p2",   "h1_p2",   8, -0.5, 7.5); 
  TH1D *h1_p3   = InitTH1D("h1_p3",   "h1_p3",   8, -0.5, 7.5); 
  TH1D *h1_n1   = InitTH1D("h1_n1",   "h1_n1",   8, -0.5, 7.5); 
  TH1D *h1_n2   = InitTH1D("h1_n2",   "h1_n2",   8, -0.5, 7.5); 
  TH1D *h1_n3   = InitTH1D("h1_n3",   "h1_n3",   8, -0.5, 7.5); 
  TH1D *h1_n4   = InitTH1D("h1_n4",   "h1_n4",   8, -0.5, 7.5); 
  //TH1D *h1_ped  = InitTH1D("h1_ped",  "h1_ped",  8, -0.5, 7.5); 
  TH1D *h1_all  = InitTH1D("h1_all",  "h1_all",  8, -0.5, 7.5); 

  ch->GetEntry(printIndex);

  title.ReplaceAll("E= GeV", Form("E=%.1f GeV", mahiEnergy*inGain)); 
  title.ReplaceAll("chi2=", Form("#chi^{2}= %.1f", chiSq)); 

  if(1)
  {
    cout << title << endl;
    cout << inGain << endl; 
    cout << ootEnergy[0] << endl; 
    cout << ootEnergy[1] << endl; 
    cout << ootEnergy[2] << endl; 
    cout << mahiEnergy << endl; 
    cout << ootEnergy[3] << endl; 
    cout << ootEnergy[4] << endl; 
    cout << ootEnergy[5] << endl; 
    cout << ootEnergy[6] << endl; 
    //cout << pedEnergy << endl; 
  }
  

  for(int its=0; its<8; its++) 
  {
 /* if(ootEnergy[1]<0) ootEnergy[1]=0; 
    if(ootEnergy[0]<0) ootEnergy[0]=0; 
    if(ootEnergy[4]<0) ootEnergy[4]=0; 
    if(ootEnergy[5]<0) ootEnergy[5]=0; 
    if(ootEnergy[6]<0) ootEnergy[6]=0; 
*/
    h1_data->SetBinContent(its+1, inputTS[its]*inGain);
    h1_it->SetBinContent(its+1, itPulse[its]*mahiEnergy*inGain);
    h1_p1->SetBinContent(its+1, ootPulse[2][its]*ootEnergy[2]*inGain);
    h1_p2->SetBinContent(its+1, ootPulse[1][its]*ootEnergy[1]*inGain);
    h1_p3->SetBinContent(its+1, ootPulse[0][its]*ootEnergy[0]*inGain);
    h1_n1->SetBinContent(its+1, ootPulse[3][its]*ootEnergy[3]*inGain);
    h1_n2->SetBinContent(its+1, ootPulse[4][its]*ootEnergy[4]*inGain);
    h1_n3->SetBinContent(its+1, ootPulse[5][its]*ootEnergy[5]*inGain);
    h1_n4->SetBinContent(its+1, ootPulse[6][its]*ootEnergy[6]*inGain);
    //h1_ped->SetBinContent(its+1, pedEnergy*inGain);
  } 
  
  //  
  if(mahiEnergy>0) h1_it->Scale(mahiEnergy*inGain/h1_it->Integral(1,8));
  if(ootEnergy[2]>0) h1_p1->Scale(ootEnergy[2]*inGain/h1_p1->Integral(1,8));
  if(ootEnergy[1]>0) h1_p2->Scale(ootEnergy[1]*inGain/h1_p2->Integral(1,8));
  if(ootEnergy[0]>0) h1_p3->Scale(ootEnergy[0]*inGain/h1_p3->Integral(1,8));
  if(ootEnergy[3]>0) h1_n1->Scale(ootEnergy[3]*inGain/h1_n1->Integral(1,8));
  if(ootEnergy[4]>0) h1_n2->Scale(ootEnergy[4]*inGain/h1_n2->Integral(1,8));
  if(ootEnergy[5]>0) h1_n3->Scale(ootEnergy[5]*inGain/h1_n3->Integral(1,8));
  if(ootEnergy[6]>0) h1_n4->Scale(ootEnergy[6]*inGain/h1_n4->Integral(1,8));

  // all 
  for(int its=0; its<8; its++)
  {
    float all = 0;
    all = h1_it->GetBinContent(its+1);  
    all += h1_p1->GetBinContent(its+1);
    all += h1_p2->GetBinContent(its+1);
    all += h1_p3->GetBinContent(its+1);
    all += h1_n1->GetBinContent(its+1);
    all += h1_n2->GetBinContent(its+1);
    all += h1_n3->GetBinContent(its+1);
    all += h1_n4->GetBinContent(its+1);
    //all += h1_ped->GetBinContent(its+1);
    h1_all->SetBinContent(its+1, all); 
  }

  if(h1_all->GetMaximum()>max) max = h1_all->GetMaximum();

  h1_data->SetLineColor(kBlack); h1_data->SetMarkerColor(kBlack);
  h1_data->SetMarkerStyle(20);   h1_data->SetMarkerSize(1); 
  h1_it->SetLineColor(kBlack);   h1_it->SetFillColor(kYellow-10);
  h1_p1->SetLineColor(kBlack);   h1_p1->SetFillColor(kAzure+1);
  h1_p2->SetLineColor(kBlack);   h1_p2->SetFillColor(kAzure+6);
  h1_p3->SetLineColor(kBlack);   h1_p3->SetFillColor(kAzure);
  h1_n1->SetLineColor(kBlack);   h1_n1->SetFillColor(kPink+1);
  h1_n2->SetLineColor(kBlack);   h1_n2->SetFillColor(kPink+6);
  h1_n3->SetLineColor(kBlack);   h1_n3->SetFillColor(kPink);
  h1_n4->SetLineColor(kBlack);   h1_n4->SetFillColor(kPink-3);
  //h1_ped->SetLineColor(kBlack);  h1_ped->SetFillColor(kGreen-10);
  h1_all->SetLineColor(kBlack);  h1_all->SetLineWidth(2);

  // legend 
  TLegend *l1 = new TLegend(0.15, 0.3, 0.25, 0.85);
  l1->SetNColumns(1);
  l1->SetBorderSize(0);
  l1->SetFillColor(0);
  l1->SetFillStyle(0);
  l1->SetTextFont(42);
  l1->SetTextAlign(12);
  l1->SetTextSize(0.06);
  l1->SetFillColor(kWhite);
  l1->SetLineColor(kWhite);
  l1->SetShadowColor(kWhite);
  l1->AddEntry(h1_data, " digi", "p");
  //if(h1_ped->Integral(1,8)>0) l1->AddEntry(h1_ped, Form(" base (%.1f GeV)",h1_ped->Integral(1,8)), "f");
  if(h1_p3->Integral(1,8)>0) l1->AddEntry(h1_p3,   Form(" -3BX (%.1f GeV)",h1_p3->Integral(1,8)),  "f");
  if(h1_p2->Integral(1,8)>0) l1->AddEntry(h1_p2,   Form(" -2BX (%.1f GeV)",h1_p2->Integral(1,8)),  "f");
  if(h1_p1->Integral(1,8)>0) l1->AddEntry(h1_p1,   Form(" -1BX (%.1f GeV)",h1_p1->Integral(1,8)),  "f");
  if(h1_it->Integral(1,8)>0) l1->AddEntry(h1_it,   Form("  0BX (%.1f GeV)",h1_it->Integral(1,8)),  "f");
  if(h1_n1->Integral(1,8)>0) l1->AddEntry(h1_n1,   Form(" +1BX (%.1f GeV)",h1_n1->Integral(1,8)),  "f");
  if(h1_n2->Integral(1,8)>0) l1->AddEntry(h1_n2,   Form(" +2BX (%.1f GeV)",h1_n2->Integral(1,8)),  "f");
  if(h1_n3->Integral(1,8)>0) l1->AddEntry(h1_n3,   Form(" +3BX (%.1f GeV)",h1_n3->Integral(1,8)),  "f"); 
  if(h1_n4->Integral(1,8)>0) l1->AddEntry(h1_n4,   Form(" +4BX (%.1f GeV)",h1_n4->Integral(1,8)),  "f");

  //if(h1_ped->Integral(1,8)>0) st->Add(h1_ped);
  if(h1_p3->Integral(1,8)>0) st->Add(h1_p3);
  if(h1_p2->Integral(1,8)>0) st->Add(h1_p2);
  if(h1_p1->Integral(1,8)>0) st->Add(h1_p1);
  if(h1_n1->Integral(1,8)>0) st->Add(h1_n1);
  if(h1_n2->Integral(1,8)>0) st->Add(h1_n2);
  if(h1_n3->Integral(1,8)>0) st->Add(h1_n3); 
  if(h1_n4->Integral(1,8)>0) st->Add(h1_n4); 
  if(h1_it->Integral(1,8)>0) st->Add(h1_it);
  st->SetTitle(title); 
  st->SetMaximum(h1_data->GetMaximum()*1.2); 
  //st->SetMinimum(h1_ped->GetMaximum()*0.5); 
  //st->GetXaxis()->SetLabelSize(0.);
  //st->GetYaxis()->SetLabelSize(0.);
  return l1;
}

void pulsedisplay(bool delay=false)
{
    gErrorIgnoreLevel=kError+1;
    TChain* ch_8p       = new TChain("mahiDebugger/HcalTree"); 
    ch_8p->Add("mahidebugger.root"); 
    
    int run;
    int ls;
    int evt;
    int ieta;
    int iphi;
    int depth;
    float mahiEnergy=0;
    float inGain=0;
    float chiSq=0;
    //float ootEnergy[7]={0};
    float inputTS[10];

    ch_8p->SetBranchAddress("run",        &run);
    ch_8p->SetBranchAddress("ls",         &ls);
    ch_8p->SetBranchAddress("evt",        &evt);
    ch_8p->SetBranchAddress("ieta",       &ieta);
    ch_8p->SetBranchAddress("iphi",       &iphi);
    ch_8p->SetBranchAddress("depth",      &depth);
    ch_8p->SetBranchAddress("mahiEnergy", &mahiEnergy);
    ch_8p->SetBranchAddress("inGain",     &inGain);
    ch_8p->SetBranchAddress("chiSq",      &chiSq);
    //ch_8p->SetBranchAddress("ootEnergy",   &ootEnergy);
    ch_8p->SetBranchAddress("inputTS",    &inputTS);

    vector<int> vec_printIndex;
    vector<TString> vec_title;

    int nentries = ch_8p->GetEntries();
    for(int i=0; i<nentries; i++)
    {
      ch_8p->GetEntry(i);  
      if(printHit(run,ls,evt,ieta,iphi,depth,mahiEnergy*inGain,chiSq,true))
      {
        vec_printIndex.push_back(i);
        vec_title.push_back(Form("run=%i ls=%i evt=%i (%i, %i, %i)",run, ls, evt, ieta, iphi, depth));
        //cout << vec_title.back().Data() << ", " << mahiEnergy*inGain << ", " << chiSq << endl;
      }
    }

    for(unsigned int i=0; i<vec_printIndex.size(); i++) 
    {
      //cout << vec_title.at(i).Data() << endl;
  
      THStack *st_8p    = new THStack("st_8p",        Form("8p   %s", vec_title.at(i).Data()));
      TH1D *h1_8p_data  = InitTH1D("h1_8p_data",      "h1_8p_data",       8, -0.5, 7.5); 

      float max=-1;
      TLegend *leg_8p   = drawPulsePlot(ch_8p,   vec_printIndex.at(i), st_8p,   h1_8p_data,   
                          Form("8 pulses + no baseline:     %s, E= GeV, chi2=; TS; E [GeV]", vec_title.at(i).Data()), max);
   
      if(h1_8p_data->GetMaximum()>max) max=h1_8p_data->GetMaximum();
 
      //
      TCanvas *c = new TCanvas("c","c",800,300); 
      st_8p->Draw(); 
      st_8p->SetMaximum(max*1.2);
      h1_8p_data->Draw("p same");
      leg_8p->Draw();
      if(delay) c->Print(Form("plots_temp/pulse_run%i_ls%i_evt%i_ieta%i_iphi%i_depth%i_10ns.pdf", run, ls, evt, ieta, iphi, depth));
      else c->Print(Form("plots_temp/pulse_run%i_ls%i_evt%i_ieta%i_iphi%i_depth%i.pdf", run, ls, evt, ieta, iphi, depth));
    }

}
