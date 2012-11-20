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
*Teksturer p� de fleste modeller.
*"Powerups" i form av v�penoppgraderinger. 
*Boss fight
*Intro cinematic
*Keybinds overview


Endringer gjort fra tidligere mapper:
*Gjort skybox del av den nye kamera klassen
*Binder n� VBO kun en gang for partikkler og bruker deretter den sammme med egen translasjon for hver partikkel.
*Binder ogs� VBO kun en gang for alle prosjektiler n�, da de alle bruker samme model, kun forskjellig cooldown og translasjon/scale/rotation
*Skybox og loading screen tegnes n� med VBO. Dermed skal absolutt alt i spillet n� v�re drawet med VBO.
*AABB kollisjon

Kollisjons sjekking er n� byttet ut med AABB. Det gir mer presis kollisjonssjekk p� alle modellene mine, og implementasjonen min er mye mer effektiv en den gamle sphere sjekkingen var (de fleste sjekker returnerer false etter en if-sjekk, da z posisjonen sammenlignes f�rst). Jeg har ogs� st�tte for sub-AABB bokser inni en AABB boks. Er det sub-bokser i en AABB, vil de sjekkes rekursivt, og return valuen blir det sub-boksene returnerer. Bossen min tar i bruk dette, da det er en veldig stor modell som fikk ekstremt upresis kollisjon uten sub-bokser. N� er kollisjonsboksen meget presis. Boksen kan inspiseres i debug mode (les keybinds readme). Jeg har ikke fj�rnet den gamle sphere kollisjons koden, i tilfelle jeg senere vil ta i bruk den. 


Menysystemet er ikke det beste, og ble forsovidt laget rimelig raskt bare for � ha det med. Det best�r av en base-meny, hvorp� menyer som mainMenu og OptionsMenu arver fra den. Menyer bygges opp av MenuEntries som inneholder geometri text bygget av TextFactory.

GUI systemet ligner menysystemet i oppbygning ved at et GUI er bygget opp av GUIEntries som inneholder geometri tekst, men det kan ogs� inneholde bilder i form av teksturer limt p� VBOer.


Jeg fikk etter mye om og men til teksturering av VBO objekter, og har dermed n� teksturer p� det meste som tegnes. Teksturering av 3ds modeller ser ikke helt riktig ut, da de er laget for multiteksturering, og jeg ikke har skrevet shader for det. Det ser likevel bedre ut n� enn f�r.

Man kan n� oppgradere v�penen sine underveis i spillet ved � drepe spesielle type romskip som kommer ved gitte mellomrom. Man kan bytte mellom de forskjellige v�pentypene man har tilgang til.

Jeg har laget en enkel bossfight. Bossen kommer n�r det er spawnet 100 vanlige fiender. Man har HP bar for bossen oppe i venstre hj�rne p� skjermen. N�r bossen taes man tilbake til main-menu. Det er et score system i spillet, men scoren lagres ikke. I bossfighten kan man oppleve litt lagg p� trege maskiner n�r bossen gj�r sitt spesialagrep, da det best�r av veldig mange prosjektiler. Dette skyldes at prosjektil-poolingen min ikke er helt optimal for spawning av s� mange prosjektiler om gangen. 

Intro cinematicen blir spilt av i vanlig SDL 2d kontext. Dette er en liten "hack" fra min side, da det funker d�rlig � spille video med SMPEG i opengl kontext. Jeg gj�r dette ved � f�rst initialisere SDL kontext, spille filmen, og n�r filmen er ferdig eller blir avsluttet, opprettes opengl kontexten. Det g�r ikke � opprette sdl 2d kontext etter � ha laget opengl kontext, s� filmen kan kun spilles p� startup av spillet. 


Jeg har lagt til et dokument med alle keybinds. Anbefaler � se raskt over de for � vite hvordan man bruker "debug mode". Synes det ser fancy ut n�r man pauser spillet og beveger seg fritt i 3d space ;)


OBS: Ang�ende SMPEG lib. Jeg har lagt til smpeg libet i en egen mappe. SMPEG pathen i prosjektet skal v�re satt til den sammme mappen som alle andre libs.