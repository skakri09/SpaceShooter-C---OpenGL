Innleveringen er en videreutbyggning og forbedring av det som ble levert i mappe 1. 

I tillegg til det som ble levert i mappe 1, er det nå lagt til følgende:
*Collision (bounding sphere collision)
*Fiende skip som kan opprettes og "drepes" ved skudd fra player.
*Player kan dø av fiende skudd
*AI for enemy spaceships, implementert med en stateMachine for hver enemy og flere "interchangable" states
*Enkel støtte for forskjellige typer enemies og skudd fra factories
*Rendering viav VBO istedenfor display list/vertex arrays (foreløpig er particles et unntak)
*Innlasting av mesh filer viav enten lib3ds (foreløpig kun vertices og normaler) eller XML

Jeg valgte å bruke boundingSphere collision da virket som om det påvirket performancen desidert minst. Jeg har også fremdeles planer om å bruke en form for rotasjon i spillet, og da vil BoundingSphere collision være mye letter å bruke. For modellene som er avlange blir kollisjonsboxen unøyaktig, jeg planlegger å rette opp i dette ved å opp boundingSpheren i flere mindre spheres for de objekter som får unøyaktige kollisjonbokser ved en.

Enemies kan nå enkelt opprettes, og det er lett å legge til forskjellige typer enemies ved å arve fra BaseEnemy. Eneste man trenger å legge til er filepath til modellen man vil bruke, samt AI logikken. AI logikken er også lett å endre på ved å bruke de eksisterende AI statene viav AiStateMachinen, eller legge til nye states, noe som er lett ved å bruke AiState base klassen.

Når et skudd treffer enten en enemy eller player, vil den som blir truffet miste like mye liv som prosjektilet det ble truffet av er definert til å skade. Om et spaceship når 0 liv vil det bli slettet.

Lib3ds implementasjonen er ikke 100% fullført enda. Det blir nå kun extracted vertices og normaler fra 3ds filene. Forhåpentlig vis får jeg til å extracte textur koordinater og paths til tekstur bildene som skal brukes. Det er også lagt til en mer forenklet mesh importerings mulighet viav XML. Her lastes først og fremst Vertices og indices. Her kan man altså bruke drawElements istedenfor drawArrays, siden vi bruker indices. Normalene blir kalkulert utifra verticene og indicene når man laster de inn.

Alle VBOs blir kun opprettet en gang når man laster inn filen. Deretter opereres det kun med MeshInfo struct objekter. Disse blir sendt rundt når en klasse vil ha tilgang til en modell å tegne. MeshInfo inneholder VBO IDene til ojektene, og blir opprettet under innlasting. Dette gjør at vi ikke trenger å sende noe data til GPU annet enn ved oppstart/load.

Jeg har lagt til partikler som skal se ut som stjerner vi beveger oss fort forbi. Dette blir tegnet som teksturerte quads med immediate mode, da jeg ikke har fått tid til å prioritere å gjøre det til vbos enda. Dette er selvølgelig ikke optimalt, men ville heller ha det med som immediate mode, enn ikke å ha det med.