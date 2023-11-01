# MAHI_pulse_display
Standalone setup for running MAHI debugger for pulse display

## How to Run

1. First, find where an event of interest is using `edmPickEvents.py`.

```
edmPickEvents.py "/ZeroBias/Run2022G-v1/RAW" 362760:124:261054694
```

2. Second, run the command output to the terminal from the first command:

```
edmCopyPickMerge outputFile=pickevents.root \
  eventsToProcess=362760:261054694 \
  inputFiles=/store/data/Run2022G/ZeroBias/RAW/v1/000/362/760/00000/a06ea8cf-7810-4d25-bd02-1ddbed6352c4.root
```

3. The previous command extracts the event into a local ROOT file `pickevents.root`. Assuming knowledge of the iphi and ieta of interest. Edit `pulsedisplay.C` to print out specifically for that tower and run.

```
root pulsedisplay.C
```
