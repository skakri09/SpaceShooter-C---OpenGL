Innleveringen er en videreutbyggning og forbedring av det som ble levert i mappe 1 og 2. 

I tillegg til det som ble levert i mappe 1, er det nå lagt til følgende:
*Nye AI states, samt overhaling av de gamle.
*Skybox
*Fiendeskip har blitt overhalt og optimalisert.
*Player har fått liv og "helse". Player kan treffes 5 ganger før han mister et liv, og har 3 liv før han dør helt. Da avsluttes foreløpig spillet.
*Partikkel manager som også tegner partikkler med VBO istedenfor immediate mode.
*Lagt til et enkelt class diagram for å gi en oversikt over hva som brukes hvor o.l. Klarte ikke finne de riktige toolsene for å lage piler osv, så
det ble mest comments for å forklare hva som er hva.
*Lagt til en "EnvironmentManager" som senere vil ta seg av alt som har med environment å gjøre. Foreløpig drawer den bare en enkel planet.
*Lagt til fog

Jeg har optimalisert og endret store deler av koden, blandt annet:
*Muligheten til å transformere, tegne med VBO, texturere(foreløpig ikke i bruk), bruke AI, skyte og kollidere er gjort om til komponenter som en klasse kan bruke til å få tilgang til de aktuelle funksjonalitetene. Dette virker mer dynamisk og ryddig, fremfor å prøve å designe et arv hierarki som er dømt til å ende opp med kaos.

*Prosjektiler eies ikke av et spaceship lengre. Det er en felles "ProjectileManager" som spaceships kan fortelle at man vil skyte et gitt prosjektil. Spaceship manageren tar seg fremdeles av å sjekke kollisjon mellom prosjektiler og spaceships ved å be ProjecileManageren om å få en peker til vectoren med prosjektiler.

*"Stjerne" partikklene er foreløpig fjernet. Den gamle partikkel manager klassen ligger fremdeles utkommentert i prosjektet som "particleManager2" da den inneholder en del kode jeg muligens vil bruke senere om jeg skal legge til stjernepartikler eller lignende senere.

*Hele gameobject hierarkiet er omskrevet og ser derfor ikke veldig likt ut som ved forrige innlevering. Dette har med omgjøringen til komponenter slik jeg nevnte, og det ser mye ryddigere ut i mine øyne. Selve gameobject hierarkiet inneholder mye mindre kode, funksjonalitet som å skyte, tegne, flytte, skalere, kollidere etc er i komponenter.

*Jeg har fikset alle compiler warnings, hvertfall har jeg ingen på hverken stasjonær eller laptop nå.

Skyboxen min tegnes foreløpig med immediate mode. Jeg fikk ikke tid til å prioritere å tegne den med VBO da det var plenty annet å gjøre :P Er mulig den blir gjort om til VBO før siste innlevering, men tenkte det var bedre den var med som immediate mode nå, enn ikke å være med.

Kollisjonsboksene mine er fremdeles ikke optimale. Det vil bli en prioritet å optimalisere dem før neste innlevering. 

Enemies tar ikke hensyn til hverandre sin posision. Det ser kanskje litt dumpt ut når 2 fiender står oppå hverandre, men har ikke kunnet prioritere å kollisjon og reposisjonering mellom enemies. Blir muligens gjort for neste innlevering

Jeg opplevde en ekstremt merkelig bugg 2 dager før leveringsfristen, som jeg enda ikke har skjønt hva forårsaker. Jeg spurte om det på it'slearning, men er ikke kommet noen tilbakemeldinger der heller. Da jeg på et tidspunkt flyttet projektet mitt fra laptop til stasjonær var det plutselig wireframes på alle objekter. Jeg har kommet frem til at det er glBlend, med glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) som gjør det, men det merkelige er at dette ikke er et problem på noen andre pCer jeg har testet. Med andre ord vises wireframes på alle modeller på stasjonære pcen min, men ikke på noen andre pcer, selv med et 100% identisk prosjekt som er kopiert over. Skulle du også se wireframes på prosjektet hadde det vært supert om du kunne se om du skjønte noe av grunnen til det. Jeg har brukt en del tid på å finne ut av det, men uten hell, og som sakt er det kun min stasjonære PC som har problemet, ingen andre jeg har testet så langt.