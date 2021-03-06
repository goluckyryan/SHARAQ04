{
   {
      TString path = gSystem->GetDynamicPath();
      path.Append(":./share/src:.");
      gSystem->SetDynamicPath(path);
      gSystem->Load("libuser.so");
//      gSystem->Load("libMinuit");
   }

   TCatCmdFactory *cf = TCatCmdFactory::Instance();
   cf->SetOptExactName(kFALSE);
   cf->Register(TCatCmdHelp::Instance());
   cf->Register(TCatCmdHt::Instance());
   cf->Register(TCatCmdHtp::Instance());
   cf->Register(TCatCmdHb::Instance());
   cf->Register(TCatCmdHn::Instance());
   cf->Register(TCatCmdZone::Instance());
   cf->Register(TCatCmdLs::Instance());
   cf->Register(TCatCmdCd::Instance());
   cf->Register(TCatCmdPrx::Instance());
   cf->Register(TCatCmdPry::Instance());
//   cf->Register(TCatCmdMnx::Instance());
//   cf->Register(TCatCmdMny::Instance());
//   cf->Register(TCatCmdAvx::Instance());
//   cf->Register(TCatCmdAvy::Instance());
//   cf->Register(TCatCmdBnx::Instance());
//   cf->Register(TCatCmdBny::Instance());
   cf->Register(TCatCmdSly::Instance());
   cf->Register(TCatCmdLoopAdd::Instance());
   cf->Register(TCatCmdLoopResume::Instance());
   cf->Register(TCatCmdLoopSuspend::Instance());
   cf->Register(TCatCmdLoopTerminate::Instance());
   cf->Register(new TCatCmdHstore);
   cf->Register(new art::TCmdFiga);
   cf->Register(TCatCmdSave::Instance());
   cf->Register(TCatCmdXval::Instance());
   cf->Register(art::TCatCmdListg::Instance());
   cf->Register(art::TCmdMWDCCalib::Instance());
   cf->Register(art::TCmdMWDCConfig::Instance());
   cf->Register(new art::TCmdUpdateCanvas);
   cf->Register(new TCatCmdLg(TCatCmdLg::kX,0)); // log x
   cf->Register(new TCatCmdLg(TCatCmdLg::kY,0)); // log y
   cf->Register(new TCatCmdLg(TCatCmdLg::kZ,0)); // log z
   cf->Register(new TCatCmdLg(TCatCmdLg::kX,1)); // unset log x
   cf->Register(new TCatCmdLg(TCatCmdLg::kY,1)); // unset log x
   cf->Register(new TCatCmdLg(TCatCmdLg::kZ,1)); // unset log x

   {
      TString path = gSystem->GetIncludePath();
      TString artemis_inc = gSystem->Getenv("ARTEMIS_HOME");
      path.Append(TString::Format("-I%s/include",artemis_inc.Data()));
      gSystem->SetIncludePath(path);
   }
   {
      art::TModuleDecoderFactory *df = art::TModuleDecoderFactory::Instance();
// mod ID 0: Fixed16
      const Int_t digits0 = 16;
      df->Register(new art::TModuleDecoderFixed<unsigned short>(0,digits0) );
// mod ID 1: Fixed16
      const Int_t digits1 = 24;
      df->Register(new art::TModuleDecoderFixed<unsigned int>(1,digits1) );
// mod ID 21 : V7XX
      df->Register(new art::TModuleDecoderV7XX);
// mod ID 23 : V767
      df->Register(new art::TModuleDecoderV767);
// mod ID 24 : V1190
      df->Register(new art::TModuleDecoderV1190);
// mod ID 25 : ???
      df->Register(new art::TModuleDecoderSkip(25));
// mod ID 26 : V1190C == V1190 (reference ch. modified)
      df->Register(new art::TModuleDecoderV1190(26));
// mod ID 63 : V1740
      df->Register(new art::TModuleDecoderV1740);

      
//      TArtDecoderFactory *df = TArtDecoderFactory::Instance();
//      df->Register(TArtDecoderSIS3610::Instance());
//      df->Register(TArtDecoderSIS3820::Instance());
////      TArtDecoderV1190 *dc = (TArtDecoderV1190*)TArtDecoderV1190::Instance();
////      dc->SetTrailingChOffset(128);
////      df->Register(TArtDecoderV1190::Instance());
//      df->Register(new TCatDecoderV1190);
//      df->Register(TArtDecoderFixed16::Instance());
//      df->Register(TArtDecoderV7XX::Instance());
////      df->Register(TCatDecoderV1740::Instance());
   }
}
