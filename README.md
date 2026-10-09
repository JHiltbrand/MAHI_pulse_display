# MAHI_pulse_display
A standalone setup for running the MAHI debugger for pulse display plotting.

Checkout a CMSSW release (150X for Run3 2025) for running the below commands.

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

3. Use CMSSW and the provided python config (`raw2digi_and_reco.py`) to run on the `pickevents.root` in order to run the MAHI debugger and make a flat ntuple with useful output to plot. This will yield yet another ROOT file `mahidebugger.root`.

```
cmsRun raw2digi_and_reco.py
```

4. Assuming knowledge of the iphi and ieta of interest, edit `pulsedisplay.C` to print out specifically for that tower and run. PDFs will be placed in a `pulse_plots` directory.

```
root -b -l -q pulsedisplay.C+
```
