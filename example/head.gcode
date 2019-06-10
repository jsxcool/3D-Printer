; Generated with MatterSlice 1.0
; filamentDiameter = 1.75
; extrusionWidth = 0.4
; firstLayerExtrusionWidth = 0.4
; layerThickness = 0.2
; firstLayerThickness = 0.3
; automatic settings before start_gcode
G21 ; set units to millimeters
M107 ; fan off
M190 S70 ; wait for bed temperature to be reached
M104 T0 S210 ; start heating extruder 1
T0 ; set the active extruder to 0
; settings from start_gcode
G28 ; home all axes
G1 Z5 F5000 ; lift nozzle
; automatic settings after start_gcode
M109 T0 S210 ; wait for extruder 1 to reach temperature
T0 ; set the active extruder to 0
G90 ; use absolute coordinates
G92 E0 ; reset the expected extruder position
M82 ; use absolute distance for extrusion
; Layer count: 50
; Layer Change GCode
; LAYER:0
M400
M107



; Layer Change GCode
; LAYER:1
M400
M106 S89



M400
M107
M104 S0 ; turn off temperature
G28 X0  ; home X axis
M84     ; disable motors
; filament used = 257.6
; filament used extruder 1 (mm) = 257.6
; filament used extruder 2 (mm) = 0.0
; total print time (s) = 567
; MatterControl Version 1.7.5 Build 1.7.5.9383 : GCode settings used
; Date 05/31/2018 00:00:00 Time 15:10
; numberOfBottomLayers = 5
; numberOfPerimeters = 3
; raftExtraDistanceAroundPart = 5
; numberOfSkirtLoops = 3
; supportInterfaceLayers = 3
; numberOfTopLayers = 3
; numberOfBrimLoops = 0
; outsidePerimeterExtrusionWidth = 0.4
; outsidePerimeterSpeed = 21
; firstLayerSpeed = 15
; raftPrintSpeed = 50
; topInfillSpeed = 50
; firstLayerExtrusionWidth = 0.4
; firstLayerThickness = 0.3
; extruderOffsets = [[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0],[0,0]]
; beforeToolchangeCode =
; endCode = M104 S0 ; turn off temperature\nG28 X0  ; home X axis\nM84     ; disable motors
; toolChangeCode =
; minimumTravelToCauseRetraction = 20
; retractionOnTravel = 1
; retractionZHop = 0
; unretractExtraExtrusion = 0
; retractRestartExtraTimeToApply = 0
; retractionSpeed = 30
; bridgeFanSpeedPercent = 100
; bridgeSpeed = 20
; firstLayerToAllowFan = 1
; extrusionMultiplier = 1
; infillStartingAngle = 45
; infillExtendIntoPerimeter = .06
; infillSpeed = 50
; infillType = TRIANGLES
; layerChangeCode = ; LAYER:[layer_num]
; fanSpeedMaxPercent = 100
; minimumExtrusionBeforeRetraction = .1
; fanSpeedMinPercent = 35
; minimumPrintingSpeed = 10
; insidePerimetersSpeed = 30
; raftAirGap = .2
; raftFanSpeedPercent = 100
; retractionOnExtruderSwitch = 10
; unretractExtraOnExtruderSwitch = 0
; skirtDistanceFromObject = 0
; minimumLayerTimeSeconds = 30
; supportAirGap = .3
; supportInfillStartingAngle = 45
; supportPercent = 50
; supportLineSpacing = 2.5
; supportMaterialSpeed = 50
; supportXYDistanceFromObject = 0.7
; supportType = LINES
; travelSpeed = 110
; wipeShieldDistanceFromObject = 0
; wipeTowerSize = 0
; zOffset = 0
; bottomClipAmount = 0
; filamentDiameter = 1.75
; layerThickness = 0.2
; extrusionWidth = 0.4
; avoidCrossingPerimeters = True
; enableRaft = False
; outsidePerimetersFirst = False
; outputOnlyFirstLayer = False
; retractWhenChangingIslands = True
; generateSupport = False
; generateInternalSupport = True
; generateSupportPerimeter = True
; wipeAfterRetraction = False
; centerObjectInXy = True
; expandThinWalls = True
; MergeOverlappingLines = True
; fillThinGaps = True
; continuousSpiralOuterPerimeter = False
; positionToPlaceObjectCenter = [100,100]
; startCode = ; automatic settings before start_gcode\nG21 ; set units to millimeters\nM107 ; fan off\nM190 S70 ; wait for bed temperature to be reached\nM104 T0 S210 ; start heating extruder 1\nT0 ; set the active extruder to 0\n; settings from start_gcode\nG28 ; home all axes\nG1 Z5 F5000 ; lift nozzle\n; automatic settings after start_gcode\nM109 T0 S210 ; wait for extruder 1 to reach temperature\nT0 ; set the active extruder to 0\nG90 ; use absolute coordinates\nG92 E0 ; reset the expected extruder position\nM82 ; use absolute distance for extrusion
; infillPercent = 10
; perimeterStartEndOverlapRatio = 1
; skirtMinLength = 0
; supportExtrusionPercent = 100
; raftExtruder = -1
; supportExtruder = 0
; supportInterfaceExtruder = 0