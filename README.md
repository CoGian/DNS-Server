dai17153, GIANTSIOS KONSTANTINOS

This is a project for the course of  Computer Netwroks. 

GR:
Χρησιμοποίησα την βιβλιοθήκη  cnaiapi.h του Comer για να
κατασκευάσω αυτόν τον απλοϊκό DNS server(servDNS.c) και 
το πρόγραμμα πελάτη του (clDNS.c) .Για την αποθήκευση των 
domain name  και των IP τους έφτιαξα μια νέα struct ονόματι
storage  και έναν πινακα  store αυτού του τύπου . 

Η μορφη με την οποία  πρέπει να καλούνται ο  servDNS και ο  clDNS
είναι  servDNS  και  clDNS  <compname> δεν χρειάζεται ο αριθμός 
της θύρα γιατί ειναι πάντα η 20000.

Για το πρόγραμμα πελάτη δεν εχω να πω πολλά γιατι μοιάζει με 
τον  chatclient  λαμβάνει και στέλνει μυνήματα .

Για το πρόγραμμα σερβερ  αφου κανει τον έλεγχο για το αν υπάρχει 
το  domain name  στο store  ή οχι (και βρει την IP )  μορφοποιώ την διεύθυνση που βρήσκεται 
σε μια μεταβλητή τυπου  computer  ώστε να παρει την μορφη IPV4 και την κάνω αλαφαριθμιτικό.
Η συνάρτηση add  είναι μια απλή συνάρτηση για να προσθέτω στοιχεία στον  store . 

EN:
I used Comer's cnaiapi.h library to
make this simplistic DNS server (servDNS.c) and
the client's program (clDNS.c). To store them
domain name and IPs I have created a new struct name
storage and a storage table of this type.

The form that should be called servDNS and clDNS
is servDNS and clDNS <compname> does not need the number
of the port because it is always the 20000.

For the client program I do not have much to say because it looks like
chatclient receives and sends messages.

For the server program after checking whether it exists
the domain name in the store or not (and find the IP) format the address it finds
in a computer variable to take the form of IPV4 and make it alphanumeric.
The add function is a simple function to add items to the store.

