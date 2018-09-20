* **************************************************************************** *
*                                                                              *
*               README_OR_DIE.fr.txt for 42Born2peer                           *
*               Created on : Mon Oct  5 18:13:59 2015                          *
*               Made by : David "Thor" GIRON <thor@staff.42.fr>                *
*               Updated by : Catherine "Cat" MADINIER <cat@42.fr>              *
*                                                                              *
* **************************************************************************** *

I - Démarrage rapide
--------------------

  Si vous êtes préssé ou déjà familier avec 42Born2Peer :

    1) Installez LaTeX sur votre système. Vérifiez que votre $PATH contient
    /usr/local/texlive/{{ANNEE}}/bin/x86_64-darwin/
    où {{ANNEE}} est la dernière version en date.

    2) Clonez votre dépôt 42Born2Peer

    3) A la racine de votre dépôt 42Born2Peer :
       $>git submodule init
       $>git submodule update
       $>git submodule foreach git pull origin master

    4) $>sudo pip install pygments (droits administrateur requis)
    OU $>pip install --user pygments (pas de droits administrateur requis)
    (Ajoutez $HOME/Library/Python/2.7/bin/ à votre $PATH)

    5) cd subject && make re

    6) Profitez
    OU Ragez, lisez ce qui suit



II - Vue d'ensemble de votre dépôt
----------------------------------

  Un dépôt 42Born2Peer avec ses paramètres par défaut est composé de
  4 dossiers :

  - correction/
    Les sources de votre implémentation fonctionnelle des exercices.

  - resources/
    Le submodule git@born2peer.42.fr:42born2peer/resources.git. Ce submodule
    fournit les ressources et classes de style pour LaTeX. Tout cela sera
    détaillé plus tard.

  - scale/
    C'est là que vous rédigerez votre barème de notation sous la forme d'une
    description YAML. Les fichiers YOUR_PROJECT_NAME.*.yml sont des templates
    auto-documentés pour votre barème de notation, disponibles dans plusieurs
    langues. Prenez soin de git delete les fichiers template dont vous
    n'avez pas besoin et de renommer ceux que vous gardez de façon adaptée,
    afin de garder ce dossier propre et ordonné. Par exemple : soit un dossier
    "lube" rédigé en anglais, vous pouvez supprimer YOUR_PROJECT_NAME.fr.yml,
    et ensuite renommer le fichier YOUR_PROJECT_NAME.en.yml en lube.en.yml.

  - subject/
    Sans surprise, c'est là que vous rédigerez votre sujet. De la même
    façon, vous trouverez des templates auto-documentés pour votre
    sujet. Effacez les templates dans les langues dont vous n'aurez
    pas besoin, et renommer les autres de façon adaptée. Pour le projet "lube"
    en anglais, renommez YOUR_PROJECT_NAME.en.tex en lube.en.tex. Pensez
    aussi à supprimer les fichiers inutiles dans le Makefile, et renommez les
    comme bon vous semble. Pour information, le fichier 42.png n'est utilisé
    que dans ces templates pour illustrer comment inclure des images dans
    votre PDF. N'hésitez pas à l'effacer.



III - Installation
------------------

  Afin de pouvoir rédiger votre sujet, vous devez avoir une
  installation LaTeX fonctionnelle sur votre système. Nous
  recommandons les distributions suivantes :

  - Linux: Texlive (via votre manager de paquets)
  - OSX: MacTex (http://tug.org/cgi-bin/mactex-download/MacTeX.pkg)

  Il devrait être possible de travailler sous Windows avec MiKTeX,
  mais je ne l'ai jamais essayé moi-même et je ne connais personne qui
  l'ait fait. Donc si vous choisissez de travailler sous Windows, je
  ne peux rien garantir et je ne pourrai pas vous apporter
  d'aide. Veuillez s'il vous plait envisager de passer sous Linux ou
  sous OSX si vous rencontrez des problèmes.

  Pour les étudiants de 42, MacTex peut être installé via le MSC
  de votre session. Tout est téléchargé et pré-installé pour vous,
  rapidement et sans douleur.

  IMPORTANT : Après l'installation, vous pourriez avoir besoin de
  configurer votre variable $PATH afin de permettre à votre système de
  trouver les binaires LaTeX. Par exemple, le paquet MacTex pour OSX
  installe généralement votre distribution LaTeX dans /usr/texbin
  (ceci peut varier légèrement d'une version à l'autre). Ce dossier ne
  fait pas parti du PATH usuel, vous devez donc l'ajouter à votre
  variable d'environnement $PATH vous-même. Ce comportement a
  également été observé pour certaines distributions Linux et est
  résolu de la même façon. Un symptôme fiable de ce problème est un
  'command not found' pour "pdflatex" quand vous tentez de contruire un
  PDF avec une installation de LaTeX pourtant correcte.

  Comme présenté dans la section précédente, le dossier resources/ est
  un submodule fourni par l'équipe Pédago. Son contenu vous permet de
  créer des PDF qui ont l'aspect visuel officiel des sujets de
  42. Vous n'aurez JAMAIS besoin de changer quoi que ce soit dans ces
  fichiers. Jamais. Ne vous embêtez même pas à les lire si cela ne
  vous intéresse pas. Les templates auto-documentés pour votre sujet
  sont déjà configurés pour utiliser nos ressources LaTeX et nos
  classes de style. Aucune configuration supplémentaire de LaTeX ni aucun
  code additionnel ne sont nécéssaires de votre part si vous avez
  bien une installation propre et fonctionnelle de LaTeX sur votre
  système.

  Toutefois, avant toute utilisation, le submodule GiT resources/ doit
  être initialisé. Si vous n'avez jamais utilisé de submodules GiT,
  prenez le temps de parcourir cette documentation pour découvrir le
  sujet : https://git-scm.com/book/en/v2/Git-Tools-Submodules. Après
  votre lecture, vous devriez probablement avoir compris que vous
  devez taper ces deux commandes à la racine de votre dépôt :

    $>git submodule init
    $>git submodule update

  Votre submodule resources/ n'est peut-être pas à jour :

  $>git submodule foreach git pull origin master

  Etape suivante, vous devez installer le paquet Python "pygments"
  utilisé par nos classes de style LaTeX qui en dépendent pour vous
  fournir de la coloration syntaxique dans les PDFs générés.
  Choisissez votre gestionnaire de paquet Python préféré, comme
  "easy_install" ou "pip". Par exemple en utilisant "pip" :

    $>sudo pip install pygments

  Si vous travaillez en tant qu'utilisateur sans droits admin
  sur votre session, utilisez plutôt la commande :

    $>pip install --user pygments

  Vous aurez peut-être besoin d'ajouter $HOME/Library/Python/2.7/bin/ à
  votre PATH pour que tout fonctionne.

  Bien entendu, il n'est nécessaire d'installer Pygments qu'une seule
  fois. Si vous créez plusieurs projets 42Born2Peer, vous pouvez
  sauter cette étape à partir de la seconde fois.

  Dernière étape, vous devez installer le paquet Ruby Kwalify pour
  utiliser le script de validation de barèmes.

    $>gem install kwalify

  Si vous travaillez en tant qu'utilisateur sans droits admin
  sur votre session, utilisez plutôt la commande :

    $>gem install --user kwalify

  Comme pour Pygments, vous n'avez à installer ce paquet qu'une seule
  fois.

* **************************************************************************** *
