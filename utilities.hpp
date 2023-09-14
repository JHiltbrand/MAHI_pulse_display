#include <iostream>
#include "TH1D.h" 
#include "TH2D.h" 
#include "TString.h" 
#include "TMath.h" 
#include "TLegend.h" 
#include "TColor.h"

//
//
//
bool passHBHELoose(int HPDHits, int HPDNoOtherHits, 
                   int MaxZeros, int HasBadRBXRechitR45Loose)
{
    bool pass = true;
    
    // Loose selection
    int minHPDHits_         =   17;
    int minHPDNoOtherHits_  =   10;
    int minZeros_           =   9999; 

    if(0)  // debugging 
    { 
       std::cout << "[Debug] maxHPDHits = " << HPDHits << ", " 
                 << "maxHPDNoOtherHits = " << HPDNoOtherHits << ", " 
                 << "maxZeros = " << MaxZeros << ", " 
                 << "HasBadRBXRechitR45Loose = " <<HasBadRBXRechitR45Loose << " " 
                 << std::endl;
    }

    //
    // Apply cuts
    //
    if( HPDHits>=minHPDHits_ ) pass = false;
    if( HPDNoOtherHits >= minHPDNoOtherHits_ ) pass=false;
    if( MaxZeros >= minZeros_ ) pass = false;
    if( HasBadRBXRechitR45Loose ) pass = false;

    return pass;
}

//
//
//
bool passHBHEIso(int NumIsolatedNoiseChannels, 
                 float IsolatedNoiseSumE, 
                 float IsolatedNoiseSumEt)
{
    bool pass = true;
    
    // Loose selection
    int     minNumIsolatedNoiseChannels_    =   10;
    float   minIsolatedNoiseSumE_           =   50.0;
    float   minIsolatedNoiseSumEt_          =   25.0;

    if(0)  // debugging 
    { 
       std::cout << "[Debug] NumIsolatedNoiseChannels = " << NumIsolatedNoiseChannels << ", " 
                 << "IsolatedNoiseSumE = " << IsolatedNoiseSumE << ", " 
                 << "IsolatedNoiseSumEt = " << IsolatedNoiseSumEt << " " 
                 << std::endl;
    }

    //
    // Apply cuts
    //
    if( NumIsolatedNoiseChannels>=minNumIsolatedNoiseChannels_ ) pass = false;
    if( IsolatedNoiseSumE>=minIsolatedNoiseSumE_ ) pass = false;
    if( IsolatedNoiseSumEt>=minIsolatedNoiseSumEt_ ) pass = false;

    return pass;
}

bool passTDCcut(int ieta, /*int iphi, int depth,*/ float charge, float time) 
{ 
    if(ieta==29 || ieta==-29) return true;
    else if(charge>200 && time>0 && time<4) return false; 
    else if(time>25) return false; 
    else return true;
}

bool passAsymcut(int ieta, int depth, float q1, float q2) 
{
    float R = (q1-q2)/(q1+q2); 

    //if((q1>400 || q2>400) && (R>0.6 || R<-0.6)) return false; 
    // else return false; 
    if (ieta>32 && depth==1) return true;
    else if (ieta>38 && depth==2) return true;
    else if (ieta<-32 && depth==1) return true;
    else if (ieta<-38 && depth==2) return true;
    else if ((q1+q2)>400 && (R>0.6 || R<-0.6)) return false;
    else return true;
}

float getMETx(float eta, float phi, float energy)
{  
    if(0) 
    {
        std::cout << energy << ", " << eta << ", " << phi << std::endl;
        std::cout << energy << " / " << TMath::CosH(eta) << " x " <<TMath::Cos(phi) << std::endl;
    }
    return energy/TMath::CosH(eta)*TMath::Cos(phi);
}

float getMETy(float eta, float phi, float energy)
{ 
    return energy/TMath::CosH(eta)*TMath::Sin(phi);
}

float getMET(float METx, float METy)
{ 
    return TMath::Sqrt(METx*METx+METy*METy);
}

bool flagWordDecoder( int word, unsigned int bitNo )
{
    if( ((word >> bitNo ) & 1) > 0 ) return true;
    else return false;
}

//
// h1 cosmetics
//
void h1cosmetic(TH1D* &h1, const char* title, int linecolor=kBlack, int linewidth=1, int fillcolor=0, TString var="")
{
    h1->SetLineColor(linecolor);
    h1->SetLineWidth(linewidth);
    h1->SetMarkerColor(linecolor);
    //h1->SetMarkerStyle(20);
    //h1->SetMarkerSize(1);
    h1->SetFillColor(fillcolor);
    h1->SetTitle(title);
    h1->SetXTitle(var);
    h1->SetStats(0);
}

//
// h2 cosmetics
//
void h2cosmetic(TH2D* &h2, const char* title, TString Xvar="", TString Yvar="", TString Zvar="Events/bin")
{
    h2->SetTitle(title);
    h2->SetXTitle(Xvar);
    h2->SetYTitle(Yvar);
    h2->SetZTitle(Zvar);
    h2->SetStats(0);
}

//
//TH1D initialization
//
//TH1D* InitTH1D(char* Name, char* Title, int Nbins, double XMin, double XMax)
//{
//    TH1D *h1 = new TH1D(Name, Title, Nbins, XMin, XMax);
//    h1->Sumw2();
//    return h1;
//}
TH1D* InitTH1D(TString Name, TString Title, int Nbins, double XMin, double XMax)
{
  TH1D *h1 = new TH1D(Name, Title, Nbins, XMin, XMax);
  h1->Sumw2();
  return h1;
}
//
//TH2D initialization
//
//TH2D* InitTH2D(char* Name, char* Title, int NXbins, double XMin, double XMax, int NYbins, double YMin, double YMax)
//{
//    TH2D *h2 = new TH2D(Name, Title, NXbins, XMin, XMax, NYbins, YMin, YMax);
//    h2->Sumw2();
//    return h2;
//}
TH2D* InitTH2D(TString Name, TString Title, int NXbins, double XMin, double XMax, int NYbins, double YMin, double YMax)
{
  TH2D *h2 = new TH2D(Name, Title, NXbins, XMin, XMax, NYbins, YMin, YMax);
  h2->Sumw2();
  return h2;
}
//
// Fill TH1D
//
void FillTH1D(TH1D* &h1, double var, double weight)
{
    if(var >= h1->GetXaxis()->GetBinUpEdge(h1->GetXaxis()->GetNbins()))
        var=h1->GetXaxis()->GetBinUpEdge(h1->GetXaxis()->GetNbins())-0.00001;
    if(var < h1->GetXaxis()->GetBinLowEdge(1))
        var=h1->GetXaxis()->GetBinLowEdge(1)+0.00001;
    h1->Fill(var, weight);
}

//
// Fill TH2D
//
void FillTH2D(TH2D* &h2, double varX, double varY, double weight)
{
    if(varX >= h2->GetXaxis()->GetBinUpEdge(h2->GetXaxis()->GetNbins()))
        varX=h2->GetXaxis()->GetBinUpEdge(h2->GetXaxis()->GetNbins())-0.00001;
    if(varY >= h2->GetYaxis()->GetBinUpEdge(h2->GetYaxis()->GetNbins()))
        varY=h2->GetYaxis()->GetBinUpEdge(h2->GetYaxis()->GetNbins())-0.00001;
    if(varX < h2->GetXaxis()->GetBinLowEdge(1))
        varX=h2->GetXaxis()->GetBinLowEdge(1)+0.00001;
    if(varY < h2->GetYaxis()->GetBinLowEdge(1))
        varY=h2->GetYaxis()->GetBinLowEdge(1)+0.00001;
    h2->Fill(varX, varY, weight);
}

bool isCollidingBX(int run, int bx)
{ 
//       Fill 5722: 295436 - 295463 
//       [32, 79, 126, 173, 220, 267, 314, 914, 961, 1008, 1055, 1102, 1149, 1196, 1808, 1855, 1902, 1949, 1996, 2043, 2090, 2702, 2749, 2796, 2843, 2890, 2937, 2984]
//       [43, 90, 137, 184, 231, 278, 325, 925, 972, 1019, 1066, 1113, 1160, 1207, 1819, 1866, 1913, 1960, 2007, 2054, 2101, 2713, 2760, 2807, 2854, 2901, 2948, 2995]
      if (run>=295436 && run<=295463) 
      {
        if( (bx>=32   && bx<=43)   || 
            (bx>=79   && bx<=90)   || 
            (bx>=126  && bx<=137)  || 
            (bx>=173  && bx<=184)  || 
            (bx>=220  && bx<=231)  || 
            (bx>=267  && bx<=278)  || 
            (bx>=314  && bx<=325)  || 
            (bx>=914  && bx<=925)  || 
            (bx>=961  && bx<=972)  || 
            (bx>=1008 && bx<=1019) || 
            (bx>=1055 && bx<=1066) || 
            (bx>=1102 && bx<=1113) || 
            (bx>=1149 && bx<=1160) || 
            (bx>=1196 && bx<=1207) || 
            (bx>=1808 && bx<=1819) || 
            (bx>=1855 && bx<=1866) || 
            (bx>=1902 && bx<=1913) || 
            (bx>=1949 && bx<=1960) || 
            (bx>=1996 && bx<=2007) || 
            (bx>=2043 && bx<=2054) || 
            (bx>=2090 && bx<=2101) || 
            (bx>=2702 && bx<=2713) || 
            (bx>=2749 && bx<=2760) || 
            (bx>=2796 && bx<=2807) || 
            (bx>=2843 && bx<=2854) || 
            (bx>=2890 && bx<=2901) || 
            (bx>=2937 && bx<=2948) || 
            (bx>=2984 && bx<=2995) 
        ) return true;
        else return false;
      }
//       Fill 5730: 295600 - 295655
//       [146, 1004, 1231, 1898, 2125, 2792, 3019]
//       [157, 1051, 1278, 1945, 2172, 2839, 3066]
//       Fill 5737: 295953 - 295979
//       [146, 1004, 1231, 1898, 2125, 2792, 3019]
//       [157, 1051, 1278, 1945, 2172, 2839, 3066]
      else if (run>=295600 && run<=295979) 
      {
        if( (bx>=146  && bx<=157)  || 
            (bx>=1004 && bx<=1051) || 
            (bx>=1231 && bx<=1278) || 
            (bx>=1898 && bx<=1945) || 
            (bx>=2125 && bx<=2172) || 
            (bx>=2792 && bx<=2839) || 
            (bx>=3019 && bx<=3066)  
        ) return true;
        else return false;
      }
//       Fill 5746: 296070 - 296116
//       [41, 183, 266, 349, 1077, 1160, 1243, 1971, 2054, 2137, 2865, 2948, 3031]
//       [52, 230, 313, 396, 1124, 1207, 1290, 2018, 2101, 2184, 2912, 2995, 3078]
//       Fill 5749: 296168
//       [41, 183, 266, 349, 1077, 1160, 1243, 1971, 2054, 2137, 2865, 2948, 3031]
//       [52, 230, 313, 396, 1124, 1207, 1290, 2018, 2101, 2184, 2912, 2995, 3078]
//       Fill 5750: 296172 - 296174   
//       [41, 183, 266, 349, 1077, 1160, 1243, 1971, 2054, 2137, 2865, 2948, 3031]
//       [52, 230, 313, 396, 1124, 1207, 1290, 2018, 2101, 2184, 2912, 2995, 3078]
      else if (run>=296070 && run<=296174) 
      {
        if( (bx>=41   && bx<=52)   || 
            (bx>=183  && bx<=230)  || 
            (bx>=266  && bx<=313)  || 
            (bx>=349  && bx<=396)  || 
            (bx>=1077 && bx<=1124) || 
            (bx>=1160 && bx<=1207) || 
            (bx>=1243 && bx<=1290) || 
            (bx>=1971 && bx<=2018) || 
            (bx>=2054 && bx<=2101) || 
            (bx>=2137 && bx<=2184) || 
            (bx>=2865 && bx<=2912) || 
            (bx>=2948 && bx<=2995) || 
            (bx>=3031 && bx<=3078)  
        ) return true;
        else return false;
      }
     else 
     { 
       return false;
     }
}


TCanvas* ratioPlot(TH1D *h1_num, TH1D *h1_deno, TString legend1, TString legend2)
{
  TLegend *leg = new TLegend(0.45, 0.7, 0.85, 0.87);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h1_num,  legend1,     "l");
  leg->AddEntry(h1_deno,  legend2,     "l");

  TCanvas *c = new TCanvas("c","c",600,600);
  TPad *pad_top;
  TPad *pad_bottom;

  pad_top = new TPad("p_main", "p_main", 0.0, 0.28, 1.0, 1.0);
  pad_top->SetTopMargin(0.1);
  pad_top->SetBottomMargin(0.04);
  pad_top->SetRightMargin(0.1);
  pad_top->SetLeftMargin(0.2);
  pad_top->Draw();
  pad_top->cd();
  pad_top->cd()->SetLogy(1);

  h1_num->SetLabelSize(0.15*0.28/0.7,"XY");
  h1_num->SetLineColor(kRed); 
  h1_num->SetLineWidth(2); 
  h1_deno->SetLineColor(kBlue); 
  h1_deno->SetLineWidth(2); 
  h1_num->Draw("hist");
  h1_deno->Draw("hist same");
  leg->Draw();

  c->cd();
  pad_bottom = new TPad("p_ratio", "p_pull", 0.0, 0.0, 1.0, 0.3);
  pad_bottom->SetLeftMargin(0.2);
  pad_bottom->Draw();
  pad_bottom->cd();
  pad_bottom->SetTopMargin(0.04);
  pad_bottom->SetRightMargin(0.1);
  pad_bottom->SetBottomMargin(0.4);

  TH1D *h1_ratio = static_cast<TH1D*>(h1_num->Clone("h1_ratio"));
  h1_ratio->Divide(h1_deno);
  h1_ratio->SetLineColor(kBlack); 
  h1_ratio->SetLineWidth(2); 
  h1_ratio->SetTitleSize(0.15); 
  h1_ratio->SetTitle("");
  h1_ratio->SetLabelSize(0.15,"XY");
  h1_ratio->GetYaxis()->SetNdivisions(/*3,false*/706);
  h1_ratio->GetXaxis()->SetNdivisions(/*3,false*/706);
  h1_ratio->SetMinimum(0.01);
  h1_ratio->SetMaximum(1.99);

  h1_ratio->Draw("e");

  return c;
}

void Set2DColor()
{ 
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
}
