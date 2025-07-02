# MAHI_pulse_display
Standalone setup for running MAHI debugger for pulse display
Checkout a CMSSW release (150X for Run3 2025) and use the env to run the below commands.

## How to Run

1. First, find where an event of interest is using `edmPickEvents.py`.

```
edmPickEvents.py "/JetMET0/Run2024B-v1/RAW" 379058:426:82018200
```

2. Second, run the command output to the terminal from the first command:

```
edmCopyPickMerge outputFile=pickevents.root \
  eventsToProcess=379058:82018200 \
  inputFiles=/store/data/Run2024B/JetMET0/RAW/v1/000/379/058/00000/974bdcae-ff6c-458d-b199-64441159c8e1.root
```

3. Use CMSSW and the provided python config to run on the `pickevents.root` in order to run the MAHI debugger and make flat ntuple with useful output to plot. This will yield yet another ROOT file `mahidebugger.root`. N.B. There is a bug in the MahiDebugger that needs to be resolved locally. The description at https://cmssdt.cern.ch/lxr/source/RecoLocalCalo/HcalRecAlgos/test/MahiDebugger.cc#L368 needs to read `thEnergeticPulses` (plural). So check out this package locally and build.

```
cmsRun raw2digi_and_reco.py
```

4. Assuming knowledge of the iphi and ieta of interest, edit `pulsedisplay.C` to print out specifically for that tower and run. PDFs will be placed in a `pulse_plots` directory.

```
root -b -l -q pulsedisplay.C+
```
