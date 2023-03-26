# TCPProxy
Proxy Tcp che fa da intermedio tra un client e un server remoto.\
Per l'utilizzo modificare i parametri contenuti in config.ini.

                                                  [PROXY]
                                                   IP=
                                                   PORT=
                                                   ..
                                                   [SERVER]
                                                   REMOTE_HOST=
                                                   REMOTE_PORT=
                                                   ..

## firewall
Nella stessa cartella dell'eseguibile è necessario, se non presente, creare un file chiamato ***firewall.rules*** dove inserire le regole del firewall. 
E' possibile bannare uno o più ip inserendoli nel file come in esempio:

                   
                                                  79.110.84.175
                                                  120.40.180.32
                                                          ecc..
       

## log
Quando il proxy viene eseguito, si genera automaticamente un file .log avente per nome la data e l'ora corrente, qui dentro verranno salvati gli interventi del firewall e le comunicazioni avvenute durante il periodo di attività del proxy.
## note
Il source di questo file sorgente può essere compilato soltanto su ambiente Windows, in quanto viene utilizzata la libreria winsock, che su Linux viene sostituita da un'altra E' possibile compilare sia un versione x32 che x64.
