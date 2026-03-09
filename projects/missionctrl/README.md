# missionctrl

[generation] -> [telemetry:1337] [label="statsd"]
[telemetry:1337] -> [arduino] [label="USB"] 


arduino 
[router]
[FastLED]
[Multi7Seg] - time
[LCD Module] - log incoming


+ burndown
++ multi7seg clock
++ router
++_ manual coding
++_ random
++_ 
+++ multi7seg metrics
- LCD Module logging of received
- FastLED
