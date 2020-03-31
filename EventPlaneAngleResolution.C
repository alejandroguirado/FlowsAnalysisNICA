/*
This macro calculate the event plane angle resolution using the standard event plane angle method
with differents weights(transverse momentum of particles, detector multuplicity and energy loss per cell).

Author: Alejandro Guirado Garcia.
Date: 25/07/19.
*/

#include <TChain.h>
#include <TString.h>
#include <TClonesArray.h>
#include <fstream>
#include <TVector3.h>
#include <TVector2.h>

#include <iostream>
#include <fstream>
#include <TStyle.h>
#include <TCanvas.h>



void StylePlots(){
  gStyle->SetOptFit(11111);
  //  cout << "Setting style!" << endl;
    gStyle->Reset("Plain");
  //  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  //  if(graypalette) gStyle->SetPalette(8,0);
  //  else gStyle->SetPalette(1);

  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPadColor(10); //
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.18); //0.12
  gStyle->SetPadLeftMargin(0.18); // 0.12
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(2);
  gStyle->SetFuncColor(kGreen);
  gStyle->SetLineWidth(2);

  gStyle->SetLabelSize(0.045,"xyz");
  gStyle->SetLabelOffset(0.01,"y");
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetLabelColor(kBlack,"xyz");
  gStyle->SetTitleSize(0.06,"xyz"); //0.5
  //  gStyle->SetTitleOffset(1.5,"y");  //0.95
  //  gStyle->SetTitleOffset(1.3,"x"); //0-95

 gStyle->SetTitleFillColor(kWhite);
  gStyle->SetTextSizePixels(26);
  gStyle->SetTextFont(42);

  gStyle->SetLegendBorderSize(0); //1
  gStyle->SetLegendFillColor(0);
    gStyle->SetFillColor(kWhite);
  gStyle->SetLegendFont(42);
  }

void EventPlaneAngleResolution(TString fileName = "/home/zarina/Alex/Event_Plane_Resolution/MOMENTUM/RESOLUTION/FINAL/11GeV_AuAu_MinBias_1500eve/100Time/5000Ev_11GeV_evetest.root")
//void ComparacionRESOLUCION(TString fileName = "/home/zarina/Alex/Event_Plane_Resolution/FINAL_ALV/evetest.root")
{

    StylePlots();

  //-----------------------------------
  const int Num_Harm = 1; //HARMONIC NUMBER OF FOURIER COEFFICIENTS
  const TString n_harm = "Primer"; //

	if (fileName == "")
	{
		cout << "File not specified!" << endl;
		return;
	}
//  TCanvas* cResolucion = new TCanvas("cResolucion","Resolucion", 1500, 1200);

  //------------------------HISTOGRAMS 1D----------------------
    TH2D* hResolucionPT = new TH2D("ResolucionPT","", 100,0,100 , 100, 0,1  );
    TH2D* hResolucionELOSS = new TH2D("ResolucionELOSS","", 100,0,100 , 100, 0,1);
    TH2D* hResolucionMULTI = new TH2D("ResolucionMULTI","", 100,0,100 , 100, 0,1);
    TH2D* hResolucionPRIMARY = new TH2D("ResolucionPRIMARY","", 100,0,100 , 100, 0,1);
    TH2D* hResolucionTRUE = new TH2D("ResolucionTRUE","", 100,0,100 , 100, 0,1 );


    //----------------------------Definition of centroid angle of every cell-----------------------
  		    Float_t phiXY[162] = {1.5708	,2.0944	,2.61799	,3.14159	,-2.61799	,-2.0944	,-1.5708	,-1.0472	,-0.523599	,0	,0.523599	,1.0472	,1.5708	,1.90427	,2.28452	,2.61799	,2.95147	,-2.95147	,-2.61799	,-2.28452	,-1.90427	,-1.5708	,-1.23732	,-0.857072	,-0.523599	,-0.190126	,0.190126	,0.523599	,0.857072	,1.23732	,1.5708	,1.81336	,2.0944	,2.37543	,2.61799	,2.86056	,3.14159	,-2.86056	,-2.61799	,-2.37543	,-2.0944	,-1.81336	,-1.5708	,-1.32823	,-1.0472	,-0.766163	,-0.523599	,-0.281035	,0	,0.281035	,0.523599	,0.766163	,1.0472	,1.32823	,1.5708	,1.76092	,1.97943	,2.20936	,2.42787	,2.61799	,2.80812	,3.02663	,-3.02663	,-2.80812	,-2.61799	,-2.42787	,-2.20936	,-1.97943	,-1.76092	,-1.5708	,-1.38067	,-1.16216	,-0.932237	,-0.713724	,-0.523599	,-0.333473	,-0.114961	,0.114961	,0.333473	,0.523599	,0.713724	,0.932237	,1.16216	,1.38067	,1.5708	,1.72697	,1.90427	,2.0944	,2.28452	,2.46182	,2.61799	,2.77417	,2.95147	,3.14159	,-2.95147	,-2.77417	,-2.61799	,-2.46182	,-2.28452	,-2.0944	,-1.90427	,-1.72697	,-1.5708	,-1.41462	,-1.23732	,-1.0472	,-0.857072	,-0.679776	,-0.523599	,-0.367422	,-0.190126	,0	,0.190126	,0.367422	,0.523599	,0.679776	,0.857072	,1.0472	,1.23732	,1.41462	,1.5708	,1.70325	,1.85183	,2.0121	,2.17669	,2.33696	,2.48554	,2.61799	,2.75045	,2.89903	,3.0593	,-3.0593	,-2.89903	,-2.75045	,-2.61799	,-2.48554	,-2.33696	,-2.17669	,-2.0121	,-1.85183	,-1.70325	,-1.5708	,-1.43834	,-1.28976	,-1.12949	,-0.964905	,-0.804634	,-0.656053	,-0.523599	,-0.391144	,-0.242564	,-0.0822923	,0.0822923	,0.242564	,0.391144	,0.523599	,0.656053	,0.804634	,0.964905	,1.12949	,1.28976	,1.43834
          };



//-------------------------------READ OUTPUT OF runMC.C---------------------------------------------
	TChain* out = new TChain("cbmsim");
	out->Add(fileName.Data());
	cout << "#recorded entries = " << out->GetEntries() << endl;
	TClonesArray* bmdPoints = NULL;
	TClonesArray* bmdTracks = NULL;
	TClonesArray* mcTracks = NULL;
	FairMCEventHeader* mcEventHeader = NULL;
	out->SetBranchAddress("BmdPoint", &bmdPoints);
	out->SetBranchAddress("MCTrack", &mcTracks);
	out->SetBranchAddress("MCEventHeader.", &mcEventHeader);

          double ResPT[9] = {0};
          double CountResPT[9] = {0};
          double ResELOSS[9] = {0};
          double CountResELOSS[9] = {0};
          double ResMULTI[9] = {0};
          double CountResMULTI[9] = {0};
          double b[10] = {0,3.349,6.699,8.205,9.474,10.592,11.603,12.533,13.398,14.211};

	for (Int_t iEv = 0; iEv < out->GetEntries(); iEv++)
	{
		Int_t n = bmdPoints->GetEntriesFast();
		n=n+1;
		out->GetEntry(iEv);
		Double_t impactParameter = mcEventHeader -> GetB();
    Double_t True_EPA = mcEventHeader -> GetRotZ();


     //---------------------------------Obtain BMD  Points-----------------------------------------
//----------------------STANDARD ANGLE METHOD-------------------------
     Double_t Qcos=0., Qsin=0.;
     Double_t AELoss[162] = {0};
     Double_t QcosELOSS=0., QsinELOSS=0.;
     Double_t AEMulti[162] = {0};
     Double_t QcosMULTI=0., QsinMULTI=0.;
     Double_t Qcos_Tracks=0., Qsin_Tracks=0.;

		for (Int_t iPoint = 0; iPoint < bmdPoints->GetEntriesFast(); iPoint++)
		{
			BmdPoint* bmdPoint = (BmdPoint*) bmdPoints->UncheckedAt(iPoint);

               //EXTRACT INFORMATION OF BRANCH
              Double_t z = bmdPoint->GetZ();
      				Double_t px = bmdPoint->GetPx();
      				Double_t py = bmdPoint->GetPy();
      				Double_t pz = bmdPoint->GetPz();
              Double_t pt = TMath::Sqrt(px*px + py*py);
              Double_t phi = TMath::ATan2(py,px);
              Int_t NumberRing = bmdPoint -> GetDetectorID();
  			      Int_t  NumberCell = bmdPoint->GetCellID();
              Double_t Eloss = bmdPoint -> GeteLoss();

                Double_t eta = 0;
                Double_t P = TMath::Sqrt( px*px + py*py + pz*pz);
                if(TMath::Abs(P- pz)>0.0000000001)
  	            {
  	             eta = 0.5*TMath::Log((P+pz)/(P-pz));
                  }

                  if (TMath::Abs(eta) <3.97 && TMath::Abs(eta)>1.9  ){
		//---------------------------Event Plane Angle Method----------------------
    //----------------------pT--------------------------------------
                    Qcos += pt*TMath::Cos(phi);
                    Qsin += pt*TMath::Sin(phi);
    //----------------------------------------------------------------
    //-----------------------EneryLoss--------------------------------
    if( NumberRing ==1 ){
      for (int i = 0; i<12;i++ ){
        if ( NumberCell == i ){
          AELoss[i] += Eloss;
          AEMulti[i] ++;
        }
      }
    }
      if( NumberRing ==2 ){
        for (int i = 0; i<18;i++ ){
          if ( NumberCell == i ){
            AELoss[i+12] += Eloss;
            AEMulti[i+12] ++;
          }
        }
      }
        if( NumberRing ==3 ){
          for (int i = 0; i<24;i++ ){
            if ( NumberCell == i ){
              AELoss[i+30] += Eloss;
              AEMulti[i+30] ++;
            }
          }
        }
          if( NumberRing ==4 ){
            for (int i = 0; i<30;i++ ){
              if ( NumberCell == i ){
                AELoss[i+54] += Eloss;
                AEMulti[i+54] ++;
              }
            }
          }
          if( NumberRing ==5 ){
            for (int i = 0; i<36;i++ ){
              if ( NumberCell == i ){
                AELoss[i+84] += Eloss;
                AEMulti[i+84] ++;
              }
            }
          }
          if( NumberRing ==6 ){
            for (int i = 0; i<42;i++ ){
              if ( NumberCell == i ){
                AELoss[i+120] += Eloss;
                AEMulti[i+120] ++;
              }
            }
          }
        }
    //----------------------------------------------------------------
      }//FINAL DE LOOP BMDPOINTS
      for (int i = 0; i<162; i++ ){
        QcosELOSS += AELoss[i]*TMath::Cos(phiXY[i]);
        QsinELOSS += AELoss[i]*TMath::Sin(phiXY[i]);
        QcosMULTI += AEMulti[i]*TMath::Cos(phiXY[i]);
        QsinMULTI += AEMulti[i]*TMath::Sin(phiXY[i]);
      }
		//----------------Event Plane Angle Filling Histograms-------------------
    Double_t PhiEP_PT = (1/Num_Harm)*TMath::ATan2(Qsin,Qcos);
    Double_t PhiEP_ELOSS = (1/Num_Harm)*TMath::ATan2(QsinELOSS,QcosELOSS);
    Double_t PhiEP_MULTI = (1/Num_Harm)*TMath::ATan2(QsinMULTI,QcosMULTI);

    for (int i = 0; i<9; i++){
      if ( b[i] <=impactParameter && impactParameter <b[i+1]){
        ResPT[i] += TMath::Cos(  Num_Harm*( TMath::Abs( PhiEP_PT-True_EPA)));
        CountResPT[i]++;
        ResELOSS[i] += TMath::Cos(  Num_Harm*( TMath::Abs(PhiEP_ELOSS-True_EPA)));
        CountResELOSS[i]++;
        ResMULTI[i] += TMath::Cos(  Num_Harm*( TMath::Abs(PhiEP_MULTI-True_EPA)));
        CountResMULTI[i]++;
      }
    }
  }//FINAL LOOP EVENTS
    double ACentrality[9] = {5,20,30,40,50,60,70,80,90};
    //FIlling histograms
    for (int i = 0; i<9; i++){
      if ( CountResELOSS[i] !=0 &&CountResELOSS[i] !=0 ) {
        hResolucionPT->Fill( ACentrality[i] , ResPT[i]/CountResPT[i] );
        hResolucionELOSS->Fill( ACentrality[i] , ResELOSS[i]/CountResELOSS[i] );
        hResolucionMULTI->Fill( ACentrality[i] , ResMULTI[i]/CountResMULTI[i] );
        }
    }

/*
        cResolucion ->cd();
        gStyle->SetOptStat(false);
        //hResolucionELOSS->GetYaxis()->SetRange(0,1);
        hResolucionELOSS->GetYaxis()->SetTitle("Event Plane Resolution(%)");
        hResolucionELOSS->GetXaxis()->SetTitle("Centrality(%)");
        hResolucionELOSS->SetMarkerStyle(20);
        hResolucionELOSS->SetMarkerSize(2);
        hResolucionELOSS->Draw();
        hResolucionPT->SetMarkerSize(2);
        hResolucionPT->SetMarkerStyle(21);
        hResolucionPT->Draw("SAMES");
        hResolucionMULTI->SetMarkerSize(2);
        hResolucionMULTI->SetMarkerStyle(22);
        hResolucionMULTI->Draw("SAMES");
        TLegend *leg = new TLegend(0.60,0.6,0.75,0.75);
        leg->SetTextFont(62);
        //leg2->SetTextSize(0.04);
        leg->SetLineColor(0);
        leg->SetLineStyle(0);
        leg->SetLineWidth(1);
        leg->SetFillColor(0);
        leg->SetFillStyle(1001);
        leg->AddEntry(hResolucionPT,"w = p_{T}","p");
        leg->AddEntry(hResolucionELOSS,"w = E_{Loss}"  ,"p");
        leg->AddEntry(hResolucionMULTI,"w = Multi","p");
        leg->Draw();

        TLegend *leg1 = new TLegend(0.25,0.25,0.55,0.55);
        leg1->SetLineColor(0);
        leg1->SetLineStyle(0);
        leg1->SetLineWidth(1);
        leg1->SetFillColor(0);
        leg1->SetFillStyle(1001);
        leg1-> AddEntry("", "R = #LT cos(#Psi_{EP} - #Psi_{MC} ) #GT, #Psi_{MC} = 0 ","");
        leg1->Draw();
        cResolucion->SaveAs("Resolucion.pdf");
*/
}
