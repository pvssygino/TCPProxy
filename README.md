# TCPProxy
Proxy Tcp che fa da intermediario tra un client e un server remoto.

Per l'utilizzo recarsi tramite CMD nella cartella dove il file .exe è presente ed avviarlo cosi:

<sub>tcpproxy.exe local_port remote_host remote_port</sub>

#firewall
Nella stessa cartella dell'eseguibile è necessario, se non presente, creare un file chiamato firewall.rules dove inserire le regole del firewall. 
E' possibile inserirei le regole seguendo questo esempio:

0.0.0.0/0,0.0.0.0/0,0 #Consente tutte le connessioni\
192.168.1.100,*,* #Blocca la connessione in entrata dell'indirizzo 192.168.1.100\
192.168.1.100-200,*,* #Blocca un range di indirizzi ip 192.168.1.100-200\
192.168.1.0/24,10.0.0.0/8,80 #Le connessioni in uscita dalla sottorete locale 192.168.1.0/24 alla sottorete remota 10.0.0.0/8 sulla porta 80 sono consentite.\
10.0.0.0/8,192.168.1.0/24,22 #Le connessioni in ingresso alla sottorete locale 192.168.1.0/24 dalla sottorete remota 10.0.0.0/8 sulla porta 22 sono consentite.


