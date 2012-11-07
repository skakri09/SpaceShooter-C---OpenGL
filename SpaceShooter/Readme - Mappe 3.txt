Innleveringen er en videreutbyggning og forbedring av det som ble levert i mappe 1 og 2. 

I tillegg til det som ble levert i mappe 1, er det n� lagt til f�lgende:
*Nye AI states, samt overhaling av de gamle.
*Skybox
*Fiendeskip har blitt overhalt og optimalisert.
*Player har f�tt liv og "helse". Player kan treffes 5 ganger f�r han mister et liv, og har 3 liv f�r han d�r helt. Da avsluttes forel�pig spillet.
*Partikkel manager som ogs� tegner partikkler med VBO istedenfor immediate mode.
*Lagt til en enkel

Jeg har optimalisert og endret store deler av koden, blandt annet:
*Muligheten til � transformere, tegne med VBO, texturere(forel�pig ikke i bruk), bruke AI, skyte og kollidere er gjort om til komponenter som en klasse kan bruke til � f� tilgang til de aktuelle funksjonalitetene. Dette virker mer dynamisk og ryddig, fremfor � pr�ve � designe et arv hierarki som er d�mt til � ende opp med kaos.

*Prosjektiler eies ikke av et spaceship lengre. Det er en felles "ProjectileManager" som spaceships kan fortelle at man vil skyte et gitt prosjektil. Spaceship manageren tar seg fremdeles av � sjekke kollisjon mellom prosjektiler og spaceships ved � be ProjecileManageren om � f� en peker til vectoren med prosjektiler.

*"Stjerne" partikklene er forel�pig fjernet. Den gamle partikkel manager klassen ligger fremdeles utkommentert i prosjektet som "particleManager2" da den inneholder en del kode jeg muligens vil bruke senere om jeg skal legge til stjernepartikler eller lignende senere.

*Hele gameobject hierarkiet er omskrevet og ser derfor ikke veldig likt ut som ved forrige innlevering. Dette har med omgj�ringen til komponenter slik jeg nevnte, og det ser mye ryddigere ut i mine �yne. Selve gameobject hierarkiet inneholder mye mindre kode, funksjonalitet som � skyte, tegne, flytte, skalere, kollidere etc er i komponenter.

*Jeg har fikset alle compiler warnings, hvertfall har jeg ingen p� hverken stasjon�r eller laptop n�.

Skyboxen min tegnes forel�pig med immediate mode. Jeg fikk ikke tid til � prioritere � tegne den med VBO da det var plenty annet � gj�re :P Er mulig den blir gjort om til VBO f�r siste innlevering, men tenkte det var bedre den var med som immediate mode n�, enn ikke � v�re med.

Kollisjonsboksene mine er fremdeles ikke optimale. Det vil bli en prioritet � optimalisere dem f�r neste innlevering. 

Jeg opplevde en ekstremt merkelig bugg 2 dager f�r leveringsfristen, som jeg enda ikke har skj�nt hva for�rsaker. Jeg spurte om det p� it'slearning, men er ikke kommet noen tilbakemeldinger der heller. Da jeg p� et tidspunkt flyttet projektet mitt fra laptop til stasjon�r var det plutselig wireframes p� alle objekter. Jeg har kommet frem til at det er glBlend, med glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) som gj�r det, men det merkelige er at dette ikke er et problem p� noen andre pCer jeg har testet. Med andre ord vises wireframes p� alle modeller p� stasjon�re pcen min, men ikke p� noen andre pcer, selv med et 100% identisk prosjekt som er kopiert over. Skulle du ogs� se wireframes p� prosjektet hadde det v�rt supert om du kunne se om du skj�nte noe av grunnen til det. Jeg har brukt en del tid p� � finne ut av det, men uten hell, og som sakt er det kun min stasjon�re PC som har problemet, ingen andre jeg har testet s� langt.