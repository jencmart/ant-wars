HOW TO PLAY:
   YOUR antHills are GREEN ones. 
   Select one of them by LMB(Left mouse button)
   Then select other anthill ( your || enemy || neutral )


ANT HILL TYPES:
   GREEN ANTHILL            - yours
   WHITE ANTHILL            - neutral, must be conquered
   RED   ANTHHILL           - ultraBogo AI enemy ants
   BLUE  && PURPLE ANTHILL  - bogo AI


OTHER INFO:
   Game is paused by 'p'
   In menu you can usually go back by 'q'

   
WARING:
   Editing save game files leads to unpredictable behavior !!!
   But you can try >>ANYTHING<< else an you realize, that program is absolutley bulletproof! :-)

# ANT WARS

```
      _    _ _                                     _____  _____ 
     | |  (_|_)               /\                  |_   _|/ ____|
  ___| | ___ _ _ __   __ _   /  \   _ __ ___  __ _  | | | (___  
 / __| |/ / | | '_ \ / _` | / /\ \ | '__/ _ \/ _` | | |  \___ \ 
 \__ \   <| | | | | | (_| |/ ____ \| | |  __/ (_| |_| |_ ____) |
 |___/_|\_\_|_|_| |_|\__, /_/    \_\_|  \___|\__,_|_____|_____/ 
                      __/ |                                     
    by Martin Jenc   |___/                                     
```
Software engineering class team project.

Modeling and documentation were team work.

Implementation was done by myself.
 
## Getting Started
The project has been written in Spring and Hibernate frameworks with MySQL database. 

With Maven Jetty plugin it can be easily deployed.

### Prerequisites
*   MySQL
*   Maven


### Installing

1. Clone git repo

```
git clone https://github.com/MartanJe/skiingAreaIS.git
```

2. Create database using **skiingAreaIS_db_dump.sql**

3. Edit DB connection properties accordingly

```
vim ./skiingAreaIS/main/java/resources/application.properties
```

4. Go to project root folder 
```
cd ./skiingAreaIS
```
```
mvn clean install
```
```
mvn jetty:run-war
```
Done! project is deployed to localhost:8080

## Usage
    * Sample Customer account - username: user passwd: user
    * Sample Employee account - username: admin passwd: admin


Project is far from complete. Only these Use Cases were implemented:  

* As customer you can
    *   UC1 - register and log in.
    *   UC2 - anonymously (or logged in) order skipass from e-shop. Basic shopping cart is implemented. No payment or delivery options. (You will get order number with which you'll pay and pick up your order at box office.)

* As employee you can
    *   UC3 - add/remove/edit skipass to e-shop.
    *   UC4 - add/remove/edit RFID cards.
    *   UC5 - mark orders as payed.
    *   UC6 - assign RFID cards to the e-shop orders and lend them to the customers.
    *   UC7 - receive returned RFID cards.
    *   UC8 - create new order.
    *   UC9 - add new employees.
    *   UC10 - watch some basic statistics...

## Built With

* [Spring](https://spring.io/) - The web framework used
* [Hibernate](https://hibernate.org/) - ORM
* [JSP](http://www.oracle.com/technetwork/java/index-jsp-138231.html) - view Technology
* [Maven](https://maven.apache.org/) - Dependency Management


## Authors

* **Ema Holinska**      - *Modelling*
* **Martin Jenc**       - *Modelling*, *Coding*
* **Martin Kupka**      - *Modelling*
* **Irina Sushkova**    - *Modelling*
* **Marek Moucek**      - *Modelling*, *Documentation*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
