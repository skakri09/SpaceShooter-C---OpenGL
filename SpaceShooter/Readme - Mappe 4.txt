Innleveringen er en videreutbyggning og forbedring av det som ble levert i mappe 1, 2 og 3.

I mappe 4 er de viktigste utbyggelsene på spaceshooteren de følgende:
*Sound manager basert på SDL_Mixed. Støtter enkelt lydavspilling, enten sang eller effekt, på flere kanaler
*Meny system. Noe rotete, men får jobben gjort. 
*Kamera som har tatt over skyboxen. Kameraet har støtte for full 3d movement
*Flere typer prosjektiler
*Et "GUI" system for skriving av informasjon til skjermen, som poeng og liv etc.
*Et TextFactory for opprettelse av geometri-basert text.
*Lagt til en stateManager som tar seg av å oppdatere og rendre riktig state, og å bytte mellom states når den får beskjed om det.
*Simpelt score system
*Teksturer på de fleste modeller.
*"Powerups" i form av våpenoppgraderinger. 
*Boss fight
*Intro cinematic
*Keybinds overview


Endringer gjort fra tidligere mapper:
*Gjort skybox del av den nye kamera klassen
*Binder nå VBO kun en gang for partikkler og bruker deretter den sammme med egen translasjon for hver partikkel.
*Binder også VBO kun en gang for alle prosjektiler nå, da de alle bruker samme model, kun forskjellig cooldown og translasjon/scale/rotation
*Skybox og loading screen tegnes nå med VBO. Dermed skal absolutt alt i spillet nå være drawet med VBO.
*AABB kollisjon

Kollisjons sjekking er nå byttet ut med AABB. Det gir mer presis kollisjonssjekk på alle modellene mine, og implementasjonen min er mye mer effektiv en den gamle sphere sjekkingen var (de fleste sjekker returnerer false etter en if-sjekk, da z posisjonen sammenlignes først). Jeg har også støtte for sub-AABB bokser inni en AABB boks. Er det sub-bokser i en AABB, vil de sjekkes rekursivt, og return valuen blir det sub-boksene returnerer. Bossen min tar i bruk dette, da det er en veldig stor modell som fikk ekstremt upresis kollisjon uten sub-bokser. Nå er kollisjonsboksen meget presis. Boksen kan inspiseres i debug mode (les keybinds readme). Jeg har ikke fjærnet den gamle sphere kollisjons koden, i tilfelle jeg senere vil ta i bruk den. 


Menysystemet er ikke det beste, og ble forsovidt laget rimelig raskt bare for å ha det med. Det består av en base-meny, hvorpå menyer som mainMenu og OptionsMenu arver fra den. Menyer bygges opp av MenuEntries som inneholder geometri text bygget av TextFactory.

GUI systemet ligner menysystemet i oppbygning ved at et GUI er bygget opp av GUIEntries som inneholder geometri tekst, men det kan også inneholde bilder i form av teksturer limt på VBOer.


Jeg fikk etter mye om og men til teksturering av VBO objekter, og har dermed nå teksturer på det meste som tegnes. Teksturering av 3ds modeller ser ikke helt riktig ut, da de er laget for multiteksturering, og jeg ikke har skrevet shader for det. Det ser likevel bedre ut nå enn før.

Man kan nå oppgradere våpenen sine underveis i spillet ved å drepe spesielle type romskip som kommer ved gitte mellomrom. Man kan bytte mellom de forskjellige våpentypene man har tilgang til.

Jeg har laget en enkel bossfight. Bossen kommer når det er spawnet 100 vanlige fiender. Man har HP bar for bossen oppe i venstre hjørne på skjermen. Når bossen taes man tilbake til main-menu. Det er et score system i spillet, men scoren lagres ikke. I bossfighten kan man oppleve litt lagg på trege maskiner når bossen gjør sitt spesialagrep, da det består av veldig mange prosjektiler. Dette skyldes at prosjektil-poolingen min ikke er helt optimal for spawning av så mange prosjektiler om gangen. 

Intro cinematicen blir spilt av i vanlig SDL 2d kontext. Dette er en liten "hack" fra min side, da det funker dårlig å spille video med SMPEG i opengl kontext. Jeg gjør dette ved å først initialisere SDL kontext, spille filmen, og når filmen er ferdig eller blir avsluttet, opprettes opengl kontexten. Det går ikke å opprette sdl 2d kontext etter å ha laget opengl kontext, så filmen kan kun spilles på startup av spillet. 


Jeg har lagt til et dokument med alle keybinds. Anbefaler å se raskt over de for å vite hvordan man bruker "debug mode". Synes det ser fancy ut når man pauser spillet og beveger seg fritt i 3d space ;)


OBS: Angående SMPEG lib. Jeg har lagt til smpeg libet i en egen mappe. SMPEG pathen i prosjektet skal være satt til den sammme mappen som alle andre libs.