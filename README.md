# TCPProxy
Proxy Tcp che fa da intermediario tra un client e un server remoto.\
Per l'utilizzo recarsi tramite CMD nella cartella dove il file .exe è presente ed avviarlo cosi:

<sub>tcpproxy.exe local_port remote_host remote_port</sub>
## firewall
Nella stessa cartella dell'eseguibile è necessario, se non presente, creare un file chiamato ***firewall.rules*** dove inserire le regole del firewall. 
E' possibile inserire le regole seguendo questo esempio:

                   
        80.110.43.20,79.130.80.76,80      # 80.110.43.20 rappresenta l'indirizzo da bloccare, mentre 79.130.80.76:80 rappresentano l'indirizzo ip e la porta del server remoto                                           # E' possibile aggiungere più regole al firewall specificandole una per linea
       

## log
Quando il proxy viene eseguito, si generato automaticamente un file .log avente per nome la data e l'ora corrente, qui dentro verranno salvati gli interventi del firewall e le comunicazioni avvenute durante il periodo di attività del proxy.
## note
Il source di questo file sorgente può essere compilato soltanto su ambiente Windows, in quanto viene utilizzata la libreria winsock, che su Linux viene sostituita da un'altra E' possibile compilare sia un versione x32 che x64.
