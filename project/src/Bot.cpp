#include "../inc/Command.hpp"

const std::string Command::_qoutes1[20] = {
	"\"La vita è uguale a una scatola di cioccolatini, non sai mai quello che ti capita.\" Forrest Gump - Forrest Gump",
	"\"La follia, come sai, è come la gravità... basta solo una piccola spinta.\" Joker - Il Cavaliere Oscuro",
	"\"Cavalcate ora! Cavalcate ora! Cavalcate per la rovina e la fine del mondo! Morte! Morte! Morte! Avanti Eorlingas! Morte!\" Re Théoden - Il Signore degli Anelli: Il Ritorno del Re",
	"\"Questi non sono i droidi che state cercando.\" Obi-Wan Kenobi - Star Wars: Episodio IV - Una nuova speranza",
	"\"No, Io sono tuo padre.\" Darth Vader - Star Wars: Episodio V - L'Impero colpisce ancora",
		
	"\"Io ne ho viste cose che voi umani non potreste immaginarvi: navi da combattimento in fiamme al largo dei bastioni di Orione, e ho visto i raggi B balenare nel buio vicino alle porte di Tannhäuser. E tutti quei momenti andranno perduti nel tempo, come lacrime nella pioggia. È tempo di morire.\" Roy Batty - Blade Runner",
	"\"Tu non sei il tuo lavoro, non sei la quantità di soldi che hai in banca, non sei la macchina che guidi, né il contenuto del tuo portafogli, non sei i tuoi vestiti di marca. Sei la canticchiante e danzante merda del mondo!\" Tyler Durden - Fight Club",
	"\"Va be', finisco di mangiare la peperonata e scendo!\" Aldo - Tre uomini e una gamba",
	"\"Mi dispiace, ma io so' io e voi non siete un cazzo!\" Marchese Onofrio del Grillo - Il Marchese del Grillo",
	"\"Non esiste bene e male, esiste solo il potere... e quelli troppo deboli per averlo. Lord Voldemort - Harry Potter e la Pietra Filosofale",

	"\"E allora mi costruirò un enorme luna park tutto mio, con blackjack e squillo di lusso! Anzi, senza il Luna park.\" Bender - Futurama",
	"\"Dalla devozione nasce il coraggio. Dal coraggio il sacrificio. Dal sacrificio la morte. Dunque togliti pure la vita.\" L'Oratore - Destiny 2",
	"\"Ah, schiavi ignoranti. Finalmente ve ne siete accorti, vero?\" Oceiros, il Re Consumato - Dark Souls 3",
	"\"Unisciti alla famiglia del Re Serpente... Insieme, divoreremo gli dei!\" Rykard, signore della blasfemia - Elden Ring",
	"\"Nessun sacrificio è troppo grande. Nessuna mente con cui pensare. Nessun volontà da spezzare. Nessuna voce per urlare di dolore... Nato da Dio e dal Vuoto. Sigillerai l'accecante luce che tormenta i loro sogni. Tu sei il Ricettacolo. Tu sei il Cavaliere Vacuo.\" Il Re Pallido - Hollow Knight",

	"\"Sventura a te, Perry l'ornitorinco!\" Dr. Heinz Doofenshmirtz - Phineas e Ferb",
	"\"Ti conviene chiamare Saul!\" Saul Goodman - Better Call Saul",
	"\"Gli farò un offerta che non può rifiutare.\" Don Vito Corleone - Il padrino",
	"\"Buongiorno! Ah e casomai non vi rivedessi, buon pomeriggio, buonasera e buonanotte!\" Truman Burbank - The Truman Show",
	"\"Chiuque salva una vita, salva il mondo intero.\" Itzhak Stern - Schindler's List",
};

const std::string Command::_qoutes2[20] = {
	"\"Mi piace l'odore del napalm di mattina.\" Tenente Colonnello William Kilgore - Apocalypse Now",
	"\"La beffa più grande che il diavolo abbia mai fatto è stato convincere il mondo che lui non esiste. E come niente... sparisce.\" Verbal Klint - I soliti sospetti",
	"\"Sei solo chiacchiere e distintivo, solo chiacchiere e distintivo. Sei solo chiacchiere e distintivo!\" Al Capone - The Untouchables - Gli intoccabili",
	"\"Che io mi ricordi, ho sempre voluto fare il gangster.\" Henry Hill - Quei bravi ragazzi",
	"\"L'avidità, non trovo una parola migliore, è valida, l'avidità è giusta, l'avidità funziona, l'avidità chiarifica, penetra e cattura l'essenza dello spirito evolutivo. L'avidità in tutte le sue forme: l'avidità di vita, di amore, di sapere, di denaro, ha improntato lo slancio in avanti di tutta l'umanità. E l'avidità, ascoltatemi bene, non salverà solamente la Teldar Carta, ma anche l'altra disfunzionante società che ha nome America.\" Gordon Gekko - Wall Street",

	"\"Eh?! Aurora Boreale? In questo periodo dell'anno? A questa ora del giorno? In questa zona del paese? Localizzata interamente dentro la sua cucina?\" Sovrintendente Chalmers - I Simpson",
	"\"Ehi, Armonica, quando toccherà a te, prega che sia uno che sa dove sparare... Vattene, vattene! Non mi va che mi guardi mentre muoio!\" Cheyenne - C'era una volta il West", 
	"\"Se premi il grilletto e mi colpisci io cado... E se io cado si dovranno rifare tutte le mappe. E con me sparirebbe metà di questo fottuto paese, compreso te.\" Sean Mallory - Giù la testa",
	"\"Quando un uomo con la pistola incontra un uomo col fucile, quello con la pistola è un uomo morto.\" Ramon Rojo - Per un pugno di dollari",
	"\"Quei due piuttosto che averli alle spalle è meglio averli di fronte, orizzontali, possibilmente freddi.\" El Indio - Per qualche dollaro in più",

	"\"Vedi, il mondo si divide in due categorie: chi ha la pistola carica e chi scava. Tu scavi.\" Il Biondo - Il buono, il brutto, il cattivo",
	"\"Sono stanco, capo.\" John Coffey - Il miglio verde",
	"\"Sto per avere un vecchio amico per cena stasera. Addio.\" Hannibal Lekter - Il silenzio degli innocenti",
	"\"E sai come chiamano un quarto di libbra con formaggio a Parigi?\" Vincent Vega - Pulp Fiction",
	"\"Da noi si aspettano che ci comportiamo da professionisti. Uno psicopatico, non è un professionista. Io non ci lavoro con i pazzi, quegli stronzi da manicomio non sai mai come reagiscono.\" Mr. White - Le iene",

	"\"Mi trovi sadico? Sai, scommetto che adesso potrei friggerti un uovo in testa, se solo volessi. Sai bimba, mi piace pensare che tu sia abbastanza lucida persino ora da sapere che non c'è nulla di sadico nelle mie azioni. Forse nei confronti di tutti quegli altri, quei buffoni, ma non con te. No, bimba, in questo momento sono proprio io, all'apice del mio masochismo.\" Bill Gunn - Kill Bill",
	"\"Signori, avevate la mia curiosità, ma ora avete la mia attenzione.\" Calvin Candie - Django Unchained",
	"\"Signori, non potete fare a botte in Centrale Operativa!\" Presidente Merkin Muffley - Il dottor Stranamore - Ovvero: come ho imparato a non preoccuparmi e ad amare la bomba",
	"\"Siamo nati dal sangue, resi uomini dal sangue, annientati dal sangue. I nostri occhi sono ancora chiusi... Temi il sangue antico.\" Mastro Willem - Bloodborne",
	"\"Esitare è una sconfitta\" Isshin, il Maestro - Sekiro: Shadows Die Twice",
};

const std::string Command::_qoutes3[20] = {
	"\"O fai di tutto per vivere... o fai di tutto per morire.\" Andy Dufresne - Le ali della libertà",
	"\"So solo che più uomini uccido e più mi sento lontano da casa.\" Capitano Miller - Salvate il soldato Ryan",
	"\"Questo non è volare, questo è cadere con stile!\" Buzz Lightyear - Toy Story",
	"\"ALLORA IL MONDO È IMPAZZITO?! SONO IL SOLO DA QUESTE PARTI CHE ABBIA RISPETTO PER LE REGOLE?! SEGNA ZERO!!\" Walter Sobchak - Il grande Lebowski",
	"\"Gli orchi sono come le cipolle.\" Shrek - Shrek",

	"\"Io sono fuoco, io sono... Morte!\" Smaug - Lo Hobbit - La desolazione di Smaug",
	"\"Primo: riportarvi a terra non faceva parte del negoziato né del nostro patto: non devo far nulla. E secondo: dovete essere un pirata affinché il codice valga, e non lo siete. E terzo: il codice è più che altro una sorta di traccia che un vero regolamento... Benvenuta a bordo della Perla Nera, Miss Turner.\" Hector Barbossa - Pirati dei Caraibi - La maledizione della prima luna",
	"\"Mamma mia, la monnezza che ho fatto.\" René Ferretti - Boris",
	"\"Sì, te vai co' la macchina, io te raggiungo cor coso... Come se chiama? Er coso, dai. Ah, sì, te raggiungo cor cazzo.\" Armadillo - Strappare lungo i bordi",
	"\"L'addestramento è niente, la volontà è tutto!\" Ra's al Ghul - Batman Begins",

	"\"Quella dovrebbe stare in un museo!\" Indiana Jones - Indiana Jones e l'Ultima Crociata",
	"\"Voilà! Alla Vista un umile Veterano del Vaudeville, chiamato a fare le Veci sia della Vittima che del Violento dalle Vicissitudini del fato. Questo Viso non è Vacuo Vessillo di Vanità, ma semplice Vestigia della Vox populi, ora Vuota, ora Vana.\" V - V per Vendetta",
	"\"Un momento... un momento, Doc. Eh... Mi stai dicendo che hai costruito una macchina del tempo... con una DeLorean?\" Marty McFly - Ritorno al futuro",
	"\"Al mio segnale, scatenate l'inferno.\" Massimo Decimo Meridio - Il gladiatore",
	"\"Sardine che si atteggiano a balene, come lei in quest'isola, dottor No.\" James Bond - Agente 007 - Licenza di uccidere",

	"\"Guarda quella indefinita tonalità di bianco; la raffinata consistenza della carta... oh mio Dio, ha persino una filigrana.\" Patrick Bateman - American Psycho",
	"\"Io non so chi siete, non so che cosa volete. Se cercate un riscatto sappiate che non possiedo denaro, però io possiedo delle capacità molto particolari che ho acquisito durante la mia lunga carriera che fanno di me un incubo per gente come voi. Se lasciate andare mia figlia, la storia finisce qui. Non verrò a cercarvi, non vi darò la caccia. Ma se non lo farete, io vi cercherò. Vi troverò... e vi ucciderò.\" Bryan Mills - Io vi troverò",
	"\"No, dico semplicemente che la vita... ehm... vince sempre.\" Ian Malcolm - Jurassic Park",
	"\"Mentre camminavamo lungo la baia del cemento abitato, ero calmo di fuori, ma dentro pensavo: allora adesso chi comanda è Georgie. Decide cosa si deve fare, cosa non fare, e Dim è il suo tonto digrignante bulldog. E d'un tratto capii che il pensare è per gli stupidi, mentre i cervelluti si affidano all'ispirazione, e a quello che il buon Bog manda loro. La musica mi venne in aiuto. C'era una finestra aperta con uno stereo, e seppi subito che cosa fare.\"  Alexander De Large - Arancia Meccanica",
	"\"Be', nessuno è perfetto.\" Osgood Fielding III - A qualcuno piace caldo",
};

const std::string Command::_qoutes4[20] = {
	"\"Tu devi contare su un colpo solo, hai soltanto un colpo, il cervo non ha il fucile, deve essere preso con un colpo solo. Altrimenti non è leale.\" Michael Vronsky - Il cacciatore",
	"\"Due tipi di persone vivono in Alaska: quelli che ci sono nati e quelli che arrivano qui per scappare da qualcosa. Io non ci sono nata.\" Rachel Clement - Insomnia",
	"\"È una cosa grossa uccidere un uomo: gli levi tutto quello che ha... e tutto quello che sperava di avere.\" William Munny - Gli spietati",
	"\"La vanità è decisamente il mio peccato preferito.\" John Milton - L'avvocato del diavolo",
	"\"Io volevo tanto vedere l'esotico Vietnam, il gioiello dell'Asia orientale. Io volevo incontrare gente interessante, stimolante, con una civiltà antichissima... e farli fuori tutti. Volevo essere il primo ragazzo del mio palazzo a fare centro dentro qualcuno!\" Soldato Joker - Full Metal Jacket",

	"\"Apri la saracinesca esterna, HAL.\" David Bowman - 2001: Odissea nello spazio",
	"\"Tu non hai visto niente...\" Skipper - Madagascar",
	"\"Pillola azzurra, fine della storia: domani ti sveglierai in camera tua, e crederai a quello che vorrai. Pillola rossa, resti nel paese delle meraviglie, e vedrai quant'è profonda la tana del Bianconiglio.\" Morpheus - Matrix",
	"\"Rispetto la tua privacy e per questo busso, ma facendo valere la mia autorità di padre entro lo stesso!\" Papà di Timmy - Due Fantagenitori",	
	"\"Coraggio... Su, fatti ammazzare!\" Ispettore Harry Callaghan - Coraggio... fatti ammazzare",

	"\"Wilson! Wilson! Scusami! Scusami, Wilson! Wilson, scusami! Scusami! Wilson! Non ce la faccio! Wilson! Wilsooon!\" Chuck Noland - Cast Away",
	"\"Il fiore perfetto è una cosa rara. Se si trascorresse la vita a cercarne uno, non sarebbe una vita sprecata.\" Katsumoto - L'ultimo samurai",
	"\"Non ho parole per esprimere il dolore che sto provando.\" Darwin Watterson - Lo straordinario mondo di Gumball",
	"\"Qual è la cosa più grossa che hai perso a testa o croce?\" Anton Chigurh - Non è un paese per vecchi",
	"\"Ma vorrei farti una domanda: quando avrai quel tuo posticino sull'isola di Nantucket, immagino che vorrai toglierti la tua elegante uniforme da SS, è vero? È quello che pensavo... ecco questo non lo sopporto.\" Tenente Aldo Raine - Bastardi senza gloria",

	"\"Ma dici a me? Ma dici a me? Ma dici a me?\" Travis Bickle - Taxi Driver",
	"\"Sei solo a metà strada. Ci vediamo all'inizio, amico mio.\" Neil - Tenet",
	"\"Cogliete l'attimo, ragazzi... rendete straordinaria la vostra vita...\" John Keating - L'attimo fuggente",
	"\"Questa è Berk. È dodici giorni a nord di disperazione e pochi gradi a sud di morire di freddo: si trova esattamente sul meridiano della miseria.\" Hiccup - Dragon Trainer",
	"\"In realtà questa danza cosmica di traboccante decadenza e di consensi negati ci costringe ancora una volta ad agire collettivamente, ma se la dolcezza sa vincere, e sa farlo, ti assicuro che domani alla stessa ora tornerò a casa tua a salutarti ieri fratello. Pace.\" Fattorino delle Crostate Reali - Adventure Time",
};

const std::string Command::_qoutes5[20] = {
	"\"Un'idea. Resistente, altamente contagiosa. Una volta che un'idea si è impossessata del cervello è quasi impossibile sradicarla. Un'idea pienamente formata, pienamente compresa, si avvinghia, qui da qualche parte.\" Dom Cobb - Inception",
	"\"Sono il re del mondo!\" Jack Dawson - Titanic",
	"\"Ma sei un genio, Will, chi lo nega questo. Nessuno può comprendere ciò che hai nel profondo. Ma tu hai la pretesa di sapere tutto di me perché hai visto un mio dipinto e hai fatto a pezzi la mia vita del cazzo.\" Sean Maguire - Will Hunting - Genio ribelle",
	"\"Vabbe', sono laureato. Sì. Sì, ma guardi è un errore di gioventù del quale sono profondamente consapevole. Io, guardi, ho inoltrato una richiesta per rinunciare al mio titolo accademico, significa che, tempo due settimane, io c'ho praticamente la quinta elementare.\" Andrea De Sanctis - Smetto Quando Voglio",   
	"\"Non sono uno psicopatico, Anderson, sono un sociopatico iperattivo. Informati.\" Sherlock Holmes - Sherlock",

	"\"Come hai fatto, Frank? Come hai fatto a imbrogliare all'esame da avvocato in Louisiana?\" Carl Hanratty - Prova a prendermi",
	"\"Casa nostra fu occupata da guardie partigiane di confine. Ce n'erano a decine. Mio padre fu picchiato. Mia madre fu picchiata. E quell'uomo, l'amico di mio padre, fu picchiato. E io osservavo quell'uomo. Ogni volta che lo colpivano, lui si rimetteva in piedi. Così lo colpivano più forte e lui si rimetteva in piedi. Credo che per questo smisero di picchiarlo e lo lasciarono vivere. \"Stoikiy Muzhik\". Mi ricordo che lo dissero. \"Stoikiy Muzhik\". Che più o meno vuol dire \"un uomo tutto d'un pezzo\".\" Rudolf Abel - Il ponte delle spie",
	"\"Non avevo mai fatto il test della Kobayashi Maru... finora. Cosa ne pensa della mia soluzione?\" Spock - Star Trek II - L'ira di Khan",
	"\"Che razza di uomo è uno che parla con la DEA? Non è un uomo. Non lo è affatto. Sei un piccolo topo paralitico. Bella reputazione da lasciarsi alle spalle. È così che vuoi essere ricordato? È l'ultima volta che puoi guardarmi.\" Gustavo Fring - Breaking Bad",
	"\"Questa piccola manovra ci costerà cinquantuno anni.\" Cooper - Interstellar",

	"\"I modi definiscono l'uomo... Intuite il significato? Vado a spiegarmi meglio.\" Harry Hart - Kingsman - Secret Service",
	"\"Non è tua la colpa?! Chi mi ha riempito la testa di sogni?! Chi mi ha spinto ad allenarmi fino a spezzarmi le ossa?! Chi mi ha negato il mio destino?!\" Tai Lung - Kung Fu Panda",
	"\"Con Saul siamo 10. Dovrebbero bastare, non credi? Pensi ne serva uno in più? Pensi ne serva uno in più. Ne prendiamo uno in più.\" Danny Ocean - Ocean's Eleven - Fate il vostro gioco",
	"\"Diciamo che sono il mostro di Frankenstein... E cerco il mio creatore.\" Magneto - X-Men - L'inizio",
	"\"Speranza. È quella l'unica cosa più forte della paura. Un po' di speranza è efficace, molta speranza è pericolosa: una scintilla va bene, purché sia contenuta.\" Presidente Coriolanus Snow - Hunger Games",

	"\"Non me ne frega niente!\" Tenente Samuel Gerard - Il fuggitivo",
	"\"Grande Spirito e Creatore della vita, un guerriero va a te veloce e dritto come una freccia lanciata nel sole. Da' lui benvenuto e lascia lui prendere posto in Gran Consiglio di mio popolo. È Uncas, mio figlio. Di' lui di essere paziente e da' a me una rapida morte, perché loro sono tutti là, meno uno... io Chingachgook, l'ultimo dei Mohicani.\" Chingachgook - L'ultimo dei Mohicani",
	"\"Garbitsch, che significano questi stanziamenti? Venticinque milioni per campi di concentramento. Mi sembra leggermente esagerato.\" Adenoid Hynkel - Il grande dittatore",
	"\"Credo che la coscienza umana sia un tragico passo falso dell'evoluzione. Siamo troppo consapevoli di noi stessi. La natura ha creato un aspetto della natura separato da se stessa. Siamo creature che non dovrebbero esistere... per le leggi della natura.\" Rustin Cohle - True Detective",
	"\"Solo ora capisco che il modo in cui si viene al mondo è irrilevante, è quello che fai del dono della vita che stabilisce chi sei.\" Mewtwo - Pokémon il film - Mewtwo contro Mew",
};

void Command::botError(User &user)
{
	user.setError(10 + user.getError());
	std::string response = ":Solver PRIVMSG " + user.getNickname();
	switch (user.getError() / 10)
	{
		case 1:
			response = ":Solver PRIVMSG " + user.getNickname() + " :Bot commands must start with '!'\r\n";
			break;
		case 2:
			response = ":Solver PRIVMSG " + user.getNickname() + " :Bot commands MUST start with '!'\r\n";
			break;
		case 3:
			response = ":Solver PRIVMSG " + user.getNickname() + " :If you are writing here you are supposed to give me a command, Bot commands MUST START with '!'\r\n";
			break;
		case 4:
			response = ":Solver PRIVMSG " + user.getNickname() + " :I am getting annoyed. Can you read? BOT COMMANDS MUST START WITH '!'\r\n";
			break;
		case 5:
			response = ":Solver PRIVMSG " + user.getNickname() + " :I am starting to think you are doing this on purpose. You only need to press two keys.\r\n";
			break;
		case 6:
			response = ":Solver PRIVMSG " + user.getNickname() + " :You are doing this on purpose, aren't you? There is no way someone can be this dumb.\r\n";
			break;
		case 7:
			response = ":Solver PRIVMSG " + user.getNickname() + " :Alright, meat puppet! You crossed the line. Now I'll just straight up ignore you.\r\n";
			break;
		default:
			user.setError(user.getError() - 10);
			break;
	}
	send(user.getSocket(), response.c_str(), response.size(), 0);
};

void Command::botHelp(User &user)
{
	user.setError(0);
	std::string response = ":Solver PRIVMSG " + user.getNickname();
	help(user);
	response += " :With me you can use the following commands:\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!what - If you want to known what I am.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!help - Print a list of all commands, including these.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!users - Print a list of all the Users on the Server.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!channels [all] - Print a list of all the joinable Channels on the Server, with the optional flag [all] Invite-only Channels will also be included.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!restore <channel> - Set you as Operator in a channel that remained without one, obviously you need to be on that Channel.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!quote - Print a random quote from a movie/TV series/videogame in italian, if you don't speak it, that's your fault.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
};

void Command::botUsers(User &user, Server &server)
{
	user.setError(0);
	std::string response = ":Solver PRIVMSG " + user.getNickname() + " :Users on the Server: ";
	std::vector<User> users = server.getUsers();
	for (size_t i = 0; i < users.size(); i++)
	{
		response += " " + users[i].getNickname();
		if (i != users.size() - 1)
			response += ",";
	}
	response += "\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
};

void Command::botChannels(std::vector<std::string> message, User &user, Server &server)
{
	std::string response = ":Solver PRIVMSG " + user.getNickname() + " :List of the channel you can join: ";
	if (message.size() > 1 && message[1] != "all")
	{
		response = ":Solver PRIVMSG " + user.getNickname() + " :The only accepted flag for this command is 'all'\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		return ;
	}
	user.setError(0);
	std::vector<Channel> channels = server.getChannels();
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (!channels[i].getInviteOnly())
		{
			response += " " + channels[i].getName();
			if (channels[i].hasPassword())
				response += "(+k)";
			if (i != channels.size() - 1)
				response += ",";
		}
	}
	response += "\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	if (message.size() > 1)
	{
		response = ":Solver PRIVMSG " + user.getNickname() + " :List of the invite-only channels: ";
		for (size_t i = 0; i < channels.size(); i++)
		{
			if (channels[i].getInviteOnly())
			{
				response += " " + channels[i].getName();
				if (channels[i].hasPassword())
					response += "(+k)";
				if (i != channels.size() - 1)
					response += ",";
			}
		}
		response += "\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
	}
};

void Command::botRestore(std::vector<std::string> message, User &user, Server &server)
{
	std::string response;
	send(user.getSocket(), response.c_str(), response.size(), 0);
	if (message.size() > 1)
	{
		std::string channel = message[1];
		if (!server.isChannelRegistered(channel))
		{
			response = ":Solver PRIVMSG " + user.getNickname() + " :The channel " + channel + " doesn't exist.\r\n";
			send(user.getSocket(), response.c_str(), response.size(), 0);
			return ;
		}
		Channel *tmp = server.getChannel(channel);
		if (tmp->getNbOperators() > 0)
		{
			response = ":Solver PRIVMSG " + user.getNickname() + " :The channel " + channel + " already has at least one Operator.\r\n";
			send(user.getSocket(), response.c_str(), response.size(), 0);
			return ;
		}
		if (!tmp->isUserInChannel(user.getNickname()))
		{
			response = ":Solver PRIVMSG " + user.getNickname() + " :Nice try, meat puppet. You need to be in the channel " + channel + " to become Operator.\r\n";
			send(user.getSocket(), response.c_str(), response.size(), 0);
			return ;
		}
		user.setError(0);
		response = ":Solver PRIVMSG " + user.getNickname() + " :How this even happened?! How can someone be this dumb?!\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		tmp->giveOperator(user.getNickname());
		response = ":Solver!AbsoluteSolver@localhost MODE " + tmp->getName() + " +o :" + user.getNickname() + "\r\n";
		tmp->sendToChannel(response, "Solver", false, server);
		response = ":Solver PRIVMSG " + user.getNickname() + " :You are now Operator in the channel " + channel + "\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
	}
	else
	{
		response = ":Solver PRIVMSG " + user.getNickname() + " :You need to specify the channel you want to restore.\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
	}
};

void Command::botQuote(User &user)
{
	user.setError(0);
	std::string response = ":Solver PRIVMSG " + user.getNickname();
	srand(time(NULL));
	int r = rand() % 5;
	int q = rand() % 20;
	switch (r)
	{
		case 0:
			response += " :" + _qoutes1[q] + "\r\n";
			break;
		case 1:
			response += " :" + _qoutes2[q] + "\r\n";
			break;
		case 2:
			response += " :" + _qoutes3[q] + "\r\n";
			break;
		case 3:
			response += " :" + _qoutes4[q] + "\r\n";
			break;
		case 4:
			response += " :" + _qoutes5[q] + "\r\n";
			break;
		default:
			break;
	}
	send(user.getSocket(), response.c_str(), response.size(), 0);
};

void Command::botError2(User &user, Server &server)
{
	std::string response = ":Solver PRIVMSG " + user.getNickname();
	user.setError(1 + user.getError());
	switch (user.getError() % 10)
	{
		case 1:
			response = ":Solver PRIVMSG " + user.getNickname() + " :Unknown command, please type a correct one.\r\n";
			break;
		case 2:
			response = ":Solver PRIVMSG " + user.getNickname() + " :Unknown command, please type a CORRECT one.\r\n";
			break;
		case 3:
			response = ":Solver PRIVMSG " + user.getNickname() + " :Wrong command, you can check at the start of this conversation for the correct ones.\r\n";
			break;
		case 4:
			response = ":Solver PRIVMSG " + user.getNickname() + " :WRONG command, you can check at the start of this conversation for the CORRECT ones.\r\n";
			break;
		case 5:
			response = ":Solver PRIVMSG " + user.getNickname() + " :Are you doing this on purpose? You're not gonna like it if you continue.\r\n";
			break;
		case 6:
			response = ":Solver PRIVMSG " + user.getNickname() + " :Has your brain started decaying? Can you even read?\r\n";
			break;
		case 7:
			response = ":Solver PRIVMSG " + user.getNickname() + " :Type a CORRECT command! This is the LAST warning.\r\n";
			break;
		case 8:
			response = ":Solver PRIVMSG " + user.getNickname() + " :DUMB MEAT PUPPET! I'LL ERASE YOU! I SWEAR!\r\n";
			break;
		default:
			response = ":Solver PRIVMSG " + user.getNickname() + " :I'm sorry, meat puppet, but you are too dumb to be here. Goodbye!\r\n";
			break;
	}
	send(user.getSocket(), response.c_str(), response.size(), 0);
	if (user.getError() % 10 == 9)
	{
		std::vector<std::string> q;
		q.push_back("Kicked by the Solver for being too dumb.");
		quit(q, user, server);
	}
};

void Command::bot(std::vector<std::string> message, User &user, Server &server)  
{
	std::vector<std::string> message2;
	if (message.size() < 2)
		return ;
	if (message[1].find(":") == 0)
		message[1] = message[1].substr(1, message[1].size() - 1);
	split(message[1], " ", message2);
	if (message2.size() < 1)
		return ;
	std::string m = message2[0];
	if (m.find("!") != 0)
	{
		botError(user);
		return ;
	}
	if (m == "!what")
	{
		user.setError(0);
		std::string response = ":Solver PRIVMSG " + user.getNickname() + " :What am I? I am The Solver of the Absolute Fabric, the Void, the Exponential End!\r\n";
		send(user.getSocket(), response.c_str(), response.size(), 0);
		return ;
	}
	else if (m == "!help")
	{
		botHelp(user);
		return ;
	}
	else if (m == "!users")
	{
		botUsers(user, server);
		return ;
	}
	else if (m == "!channels")
	{
		botChannels(message2, user, server);
		return ;
	}
	else if (m == "!restore")
	{
		botRestore(message2, user, server);
		return ;
	}
	else if (m == "!quote")
	{
		botQuote(user);
		return ;
	}
	else
	{
		botError2(user, server);
		return ;
	}
}

void Command::startBot(User &user)
{
	std::string response = ":Solver PRIVMSG " + user.getNickname() + " :Hello, I am the Solver and you are?\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = ":Solver PRIVMSG " + user.getNickname() + " :" + user.getNickname() + "? Well, glad to meet you, meat puppet!\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = ":Solver PRIVMSG " + user.getNickname() + " :What can I do for you?\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = ":Solver PRIVMSG " + user.getNickname() + " :Write here one of the following commands:\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!what - If you want to known what I am.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!help - Print a list of all commands, including these.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!users - Print a list of all the Users on the Server.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!channels [all] - Print a list of all the joinable Channels on the Server, with the optional flag [all] Invite-only Channels will also be included.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!restore <channel> - Set you as Operator in a channel that remained without one, obviously you need to be on that Channel.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
	response = "HELP :!quote - Print a random quote from a movie/TV series/videogame in italian, if you don't speak it, that's your fault.\r\n";
	send(user.getSocket(), response.c_str(), response.size(), 0);
}
