Innleveringen er en videreutbyggning og forbedring av det som ble levert i mappe 1, 2 og 3.

I mappe 4 er de viktigste utbyggelsene p� spaceshooteren de f�lgende:
*Sound manager basert p� SDL_Mixed. St�tter enkelt lydavspilling, enten sang eller effekt, p� flere kanaler
*Meny system. Noe rotete, men f�r jobben gjort. 
*Kamera som har tatt over skyboxen. Kameraet har st�tte for full 3d movement
*Flere typer prosjektiler
*Et "GUI" system for skriving av informasjon til skjermen, som poeng og liv etc.
*Et TextFactory for opprettelse av geometri-basert text.
*Lagt til en stateManager som tar seg av � oppdatere og rendre riktig state, og � bytte mellom states n�r den f�r beskjed om det.
*Simpelt score system

Endringer gjort fra tidligere mapper:
*Gjort skybox del av den nye kamera klassen
*Byttet ut c++ sin math.h sqrt funksjon med en egen som ved testing har vist � v�re opptil 4 ganger raskere
*

Menysystemet er ikke det beste, og ble forsovidt laget rimelig raskt bare for � ha det med. Det best�r av en base-meny, hvorp� menyer som mainMenu og OptionsMenu
arver fra den. Menyer bygges opp av MenuEntries som inneholder geometri text bygget av TextFactory. 

GUI systemet ligner menysystemet i oppbygning ved at et GUI er bygget opp av GUIEntries som inneholder geometri tekst.
