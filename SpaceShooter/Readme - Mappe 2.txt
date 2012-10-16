Innleveringen er en videreutbyggning og forbedring av det som ble levert i mappe 1. 

I tillegg til det som ble levert i mappe 1, er det n� lagt til f�lgende:
*Collision (bounding sphere collision)
*Fiende skip som kan opprettes og "drepes" ved skudd fra player.
*Player kan d� av fiende skudd
*AI for enemy spaceships, implementert med en stateMachine for hver enemy og flere "interchangable" states
*Enkel st�tte for forskjellige typer enemies og skudd fra factories
*Rendering viav VBO istedenfor display list/vertex arrays (forel�pig er particles et unntak)
*Innlasting av mesh filer viav enten lib3ds (forel�pig kun vertices og normaler) eller XML

Jeg valgte � bruke boundingSphere collision da virket som om det p�virket performancen desidert minst. Jeg har ogs� fremdeles planer om � bruke en form for rotasjon i spillet, og da vil BoundingSphere collision v�re mye letter � bruke. For modellene som er avlange blir kollisjonsboxen un�yaktig, jeg planlegger � rette opp i dette ved � opp boundingSpheren i flere mindre spheres for de objekter som f�r un�yaktige kollisjonbokser ved en.

Enemies kan n� enkelt opprettes, og det er lett � legge til forskjellige typer enemies ved � arve fra BaseEnemy. Eneste man trenger � legge til er filepath til modellen man vil bruke, samt AI logikken. AI logikken er ogs� lett � endre p� ved � bruke de eksisterende AI statene viav AiStateMachinen, eller legge til nye states, noe som er lett ved � bruke AiState base klassen.

N�r et skudd treffer enten en enemy eller player, vil den som blir truffet miste like mye liv som prosjektilet det ble truffet av er definert til � skade. Om et spaceship n�r 0 liv vil det bli slettet.

Lib3ds implementasjonen er ikke 100% fullf�rt enda. Det blir n� kun extracted vertices og normaler fra 3ds filene. Forh�pentlig vis f�r jeg til � extracte textur koordinater og paths til tekstur bildene som skal brukes. Det er ogs� lagt til en mer forenklet mesh importerings mulighet viav XML. Her lastes f�rst og fremst Vertices og indices. Her kan man alts� bruke drawElements istedenfor drawArrays, siden vi bruker indices. Normalene blir kalkulert utifra verticene og indicene n�r man laster de inn.

Alle VBOs blir kun opprettet en gang n�r man laster inn filen. Deretter opereres det kun med MeshInfo struct objekter. Disse blir sendt rundt n�r en klasse vil ha tilgang til en modell � tegne. MeshInfo inneholder VBO IDene til ojektene, og blir opprettet under innlasting. Dette gj�r at vi ikke trenger � sende noe data til GPU annet enn ved oppstart/load.

Jeg har lagt til partikler som skal se ut som stjerner vi beveger oss fort forbi. Dette blir tegnet som teksturerte quads med immediate mode, da jeg ikke har f�tt tid til � prioritere � gj�re det til vbos enda. Dette er selv�lgelig ikke optimalt, men ville heller ha det med som immediate mode, enn ikke � ha det med.