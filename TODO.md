Haut d'écran :
- Changer position pochette [Screens/MusicSelect/SongInfo.cpp]
- Changer position Titre et artiste [Screens/MusicSelect/SongInfo.cpp]
- Changer position level [Screens/MusicSelect/SongInfo.cpp]

Panel :
- Changer taille et position des titres des songs sur les vignettes
- Changer couleur fond d'écran ingame [Screens/Gameplay/Gameplay.cpp]
- Changer la police des combos [Screens/Gameplay/Gameplay.cpp]
- Changer la couleur des combos [Screens/Gameplay/Gameplay.cpp]
- Changer le compteur de départ des combos [Screens/Gameplay/Gameplay.cpp]
- Changer la position des combos [Screens/Gameplay/Gameplay.cpp]
- Changer l'écartement des caratères des combos [Screens/Gameplay/Gameplay.cpp]
- Changer la couleur du score ingame [Screens/Gameplay/Gameplay.cpp]
- Changer la couleur du score résultat [Screens/Results/Results.cpp]
- Changer le sens des fléches pour faire défiler les songs [Screens/MusicSelect/Ribbon.cpp]
- Fond animé qui suit les BPM
- Combo qui bumpe à chaque note touchée, avec ombre portée
- Preview des premières notes avec délais de 6 secondes avant départ de la song
- Full Combo !


Marker :
- Changer la résolution des vignettes des markers (plus grande comme jubeat)
- Vérifier/Changer le nombre de phases d'animations des marker MISS et POOR (pour avoir 16 comme sur jubeat)
- Song de test pour faire réglages avec clap


# v0.2.0
## Misc
- THE THEME SYSTEM HOLY SHIT
- Refactor Panels to use a command pattern
- Refactor most things into drawables
- Input Lag Setting
- Revamp Markers to speed loading on launch
- Logging system
- Generic Error-reporting / Crash handling
- Correct all preferences being overridden when one value is not found
- "Value" class with delayed update for *n i c e* score display
- LN Marker
    - Selection screen in Options
- Customizable button highlight
    - Format
    - selection screen in Options
- Global Offset
- Fix the crash occuring sometimes when you select a song

## Music Select Screen
- Add Touch support

# v1.0.0
## Music Select Screen
- bound memory usage of Toolkit::Cache
- Chart Panel
- Sort menu
    - Differenciate Sort / Selection
- Song Panel click
    - animation
    - cd
- Sound
    - Sound Effects

### Options menu
- Volume Settings
- Give marker selection the timing check feature when your re-click on the same panel
    
## memo Compatibility

## Themeing support
- Python bindings ?

## Misc
- Make Drawables lazily react to resolution changes
- update .memon spec and memoncpp to support BPM Changes
- Optimize input thread in gameplay

## FB9 Support

# v1.1.0
## P4IO Support
- Buy a P4IO