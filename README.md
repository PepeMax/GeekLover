# :heart_on_fire: GeekLover :heart_on_fire:

GeekLover est un petit projet pour votre belle bien aimée. C'est tout simplement un compteur à 8 chiffres ([afficheur 7 segments](https://www.amazon.fr/gp/product/B0797NRMQH/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1)) qui s'incrémente depuis la date de votre rencontre. La durée peut s'afficher en **secondes, minutes, heures, jours ou semaines**.
Il est disponible en deux versions :

- **Application** : On change le type d'unité de temps grâce à une application mobile hybride (Ionic)
- **Bouton** : On change le type d'unité de temps grâce à un bouton

# Installation :

Pour installer GeekLover il suffit de télécharger la version en question. Si vous utilisez Arduino IDE il faudra installer les différentes librairies.

Si vous utilisez PlatFormIO, rajouter ce bloc dans le fichier platformio.ini

```ini
lib_deps = 
	https://github.com/arduino-libraries/NTPClient.git
	https://github.com/me-no-dev/ESPAsyncWebServer.git
	https://github.com/tzapu/WiFiManager.git
	https://github.com/ozhantr/DigitLedDisplay.git
```

## Version avec l'application mobile

Pour pouvoir utiliser l'application il vous faut un environement [Ionic](https://ionicframework.com) sur votre PC.

Dès que cela est fait, avec un terminal rendez-vous dans le dossier App est tapé la commande suivantes : 

```console
npm install
```

Cette commande permet d'installer toutes les plugins nécessaires au bbon fonctionnement de l'application.

Ensuite pour compiler votre application vous disposez de deux commandes : 

```console
ionic cordova build android
```
OU

```console
ionic cordova build ios
```

Si vous avez des conaissances en développement mobile vous pouvez brancher votre device et le mettre en debug puis éxécuter une des commandes : 

```console
ionic cordova run android
```
OU

```console
ionic cordova run ios
```

Faites les branchements éléctronqiues et si besoin, changez les `#define`

**IMPORTANT !** Il faut changer la valeur de la variable
```c++
the_day_all_men_must_remember = votre_valeur;
```

Pour trouver cette valeur il vous suffit d'aller [ici](http://www.timestamp.fr) et d'y renseigner la date et l'heure que vous voulez.


# Comment ça fonctionne ?

L'ESP démarre en mode Point d'Accès s'il ne connait pas ou n'arrive pas à se connecter à un réseau Wifi déjà enregistré. Dès que la configuration WiFi est prête il redémarre, se connecte au réseau WiFi et récupère le "temps" grâce au NTP.

L'ESP incrémente une nouvelle variable avec le calcul suivant :

```c++
loveDuration = nowInSecond - the_day_all_men_must_remember;
```

Avec cette valeur on obtient le nombre de secondes qui s'écoule depuis la date de votre rencontre.

A l'aide de calcul tout simple l'ESP convertit le nombre de secondes en minutes, heures, etc

Et avec soit le bouton ou l'application vous choisissez le format à afficher.

_A savoir : l'ESP met à jour le timestamp à chaque tour de boucle_ 
